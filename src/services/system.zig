const std = @import("std");
const utils = @import("../utils.zig");

const c = @cImport({
    @cDefine("_LARGEFILE64_SOURCE", "");
    @cInclude("stdlib.h");
    @cInclude("mntent.h");
    @cInclude("sys/statvfs.h");
    @cInclude("errno.h");
    @cInclude("string.h");
});

const io = std.io;
const mem = std.mem;
const debug = std.debug;
const fmt = std.fmt;
const ArrayList = std.ArrayList;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

pub const Disk = struct {
    allocator: mem.Allocator,
    mountpoint: []const u8,
    used_size: []u8,
    total_size: []u8,
    used_bytes: u64,
    total_bytes: u64,

    const Self = @This();

    pub fn fromMountpoint(allocator: mem.Allocator, mountpoint: []const u8) !*Self {
        var instance = try allocator.create(Self);
        instance.allocator = allocator;
        // instance.mountpoint = mountpoint;
        try instance.fetchUsage(mountpoint);
        return instance;
    }

    pub fn fetchUsage(self: *Self, mnt: []const u8) !void {
        var fs_info: c.struct_statvfs64 = undefined;

        if (c.statvfs64(mnt.ptr, &fs_info) != 0) {
            const errno = std.c.getErrno(-1);
            debug.panic("Failed to call `statvfs()` on `{s}`: {d}\n", .{ mnt, errno });
        }

        self.used_bytes = (fs_info.f_blocks - fs_info.f_bfree) * fs_info.f_frsize;
        self.total_bytes = fs_info.f_blocks * fs_info.f_frsize;

        self.used_size = try utils.formatBytes(self.allocator, self.used_bytes);
        self.total_size = try utils.formatBytes(self.allocator, self.total_bytes);
    }

    pub fn deinit(self: *Self) void {
        self.allocator.free(self.used_size);
        self.allocator.free(self.total_size);
        self.allocator.destroy(self);
    }
};

pub const Disks = struct {
    allocator: mem.Allocator,
    mountpoints: ArrayList([]u8),

    const Self = @This();

    pub fn init(allocator: mem.Allocator) !*Self {
        var instance = try allocator.create(Self);
        instance.allocator = allocator;
        try instance.fetchMounts();
        return instance;
    }

    pub const MountsFetchingErrors = fmt.AllocPrintError || error{
        FailedMtabOpening,
    };

    fn fetchMounts(self: *Self) MountsFetchingErrors!void {
        const mounts_file: ?*c.FILE = c.setmntent("/etc/mtab", "r");
        defer _ = c.endmntent(mounts_file);

        if (mounts_file == null) {
            return error.FailedMtabOpening;
        }

        self.mountpoints = ArrayList([]u8).init(self.allocator);

        while (true) {
            const mnt = c.getmntent(mounts_file);

            if (mnt == null) {
                break;
            }

            const mnt_type: []u8 = try fmt.allocPrint(self.allocator, "{s}", .{mnt.*.mnt_type});
            const mnt_dir: []u8 = try fmt.allocPrint(self.allocator, "{s}", .{mnt.*.mnt_dir});

            defer self.allocator.free(mnt_type);

            const valid_fs_types = [_][]const u8{ "ext2", "ext3", "ext4", "xfs", "btrfs", "zfs", "vfat", "ntfs" };

            var is_valid_fs: bool = false;

            for (valid_fs_types) |fs| {
                if (mem.eql(u8, fs, mnt_type)) {
                    is_valid_fs = true;
                    break;
                }
            }

            if (!is_valid_fs) {
                self.allocator.free(mnt_dir);
                continue;
            }

            try self.mountpoints.append(mnt_dir);
        }
    }

    pub fn deinit(self: *Self) void {
        for (self.mountpoints.items) |mnt| self.allocator.free(mnt);
        self.mountpoints.deinit();
        self.allocator.destroy(self);
    }
};
