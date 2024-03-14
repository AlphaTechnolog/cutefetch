const std = @import("std");
const utils = @import("../utils.zig");

const fs = std.fs;
const mem = std.mem;
const debug = std.debug;
const fmt = std.fmt;
const process = std.process;
const ChildProcess = std.ChildProcess;

filesystem: []u8,
size: []u8,
used: []u8,
available: []u8,
use: []u8,
mountpoint: []u8,
allocator: mem.Allocator,

const Self = @This();

pub fn fromMountpoint(allocator: mem.Allocator, mountpoint: []const u8) !*Self {
    var instance = try allocator.create(Self);
    instance.allocator = allocator;
    instance.mountpoint = try allocator.dupe(u8, mountpoint);
    try instance.fetchData();
    return instance;
}

fn collectDFOutput(self: *Self) !?[]u8 {
    var result = try ChildProcess.exec(.{
        .allocator = self.allocator,
        .argv = &[_][]const u8 {
            "df",
            self.mountpoint
        },
    });

    defer {
        self.allocator.free(result.stdout);
        self.allocator.free(result.stderr);
    }

    var original_stdout = mem.trimRight(u8, result.stdout, "\n");
    var buf: [1024]u8 = undefined;
    var it = std.mem.tokenize(u8, original_stdout, "\n");
    var retval: ?[]u8 = null;

    // ignore df output header.
    _ = it.next();

    if (it.next()) |info| {
        const information = buf[0..info.len];
        @memcpy(information, info);
        retval = try self.allocator.dupe(u8, info);
    }

    return retval;
}

fn processQuantity(self: *Self, token: []const u8) ![]u8 {
    var onekblocks_value: u64 = fmt.parseInt(u64, token, 10) catch |err| {
        debug.panic("Attempt to parse non-numeric value as u64: {s}\n", .{token});
        process.exit(1);
        return err;
    };

    // 1k blocks to formatted bytes.
    return try utils.formatBytes(self.allocator, onekblocks_value * 1024);
}

fn fetchData(self: *Self) !void {
    var output = try self.collectDFOutput();

    if (output == null) {
        debug.panic("Failed to read `df` output!!\n", .{});
        return;
    }
    
    defer self.allocator.free(output.?);

    var i: usize = 0;
    var it = mem.tokenize(u8, output.?, " ");

    while (it.next()) |token| : (i += 1) {
        switch (i) {
            0 => self.filesystem = try self.allocator.dupe(u8, token),
            1 => self.size = try self.processQuantity(token),
            2 => self.used = try self.processQuantity(token),
            3 => self.available = try self.processQuantity(token),
            4 => self.use = try self.allocator.dupe(u8, token),
            else => continue,
        }
    }
}

pub fn deinit(self: *Self) void {
    const data = [_][]u8 {
        self.filesystem,
        self.size,
        self.used,
        self.available,
        self.use,
        self.mountpoint,
    };

    for (&data) |item| {
        self.allocator.free(item);
    }

    self.allocator.destroy(self);
}