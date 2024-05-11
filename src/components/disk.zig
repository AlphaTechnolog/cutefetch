const std = @import("std");
const static = @import("../static.zig");
const System = @import("../services/system.zig");

const io = std.io;
const mem = std.mem;
const process = std.process;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

fn printSystemInformation(allocator: mem.Allocator) !void {
    var disk = try System.Disk.fromMountpoint(allocator, "/");
    defer disk.deinit();
    try stdout.print("{s} / {s}", .{ disk.used_size, disk.total_size });
    try stdout.print(" ({s}/{s})\n", .{ static.Cyan, static.Reset });
}

pub fn renderDisk(allocator: mem.Allocator) void {
    stdout.print("{s}dsk {s}", .{ static.Red, static.Reset }) catch unreachable;

    printSystemInformation(allocator) catch |err| {
        stderr.print("Cannot obtain disk information from '/': {s}\n", .{@errorName(err)}) catch unreachable;
        process.exit(1);
    };

    // FIXME: For some reason, when we pass that `mnt` variable, statvfs64 fails with a weird error
    // of NAMETOOLONG in the errno buffer :skull: tbh, no idea here, because passing literal "/" works.
    // HINT: Prolly skill issue though.

    // var disks = System.Disks.init(allocator) catch unreachable;
    // defer disks.deinit();

    // for (disks.mountpoints.items) |raw_mnt| {
    //     const mnt = try allocator.dupe(u8, raw_mnt);
    //     defer allocator.free(mnt);

    //     const disk = System.Disk.fromMountpoint(allocator, mnt) catch |err| {
    //         try stderr.print("cannot fetch information for mountpoint {s} -> {s}\n", .{
    //             mnt, @errorName(err)
    //         });

    //         std.process.exit(1);
    //     };

    //     defer disk.deinit();
    // }
}
