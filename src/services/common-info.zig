const std = @import("std");

const mem = std.mem;
const io = std.io;
const fs = std.fs;
const os = std.os;
const ChildProcess = std.ChildProcess;

pub fn readWhoami(allocator: mem.Allocator) ![]u8 {
    const result = try ChildProcess.exec(.{
        .allocator = allocator,
        .argv = &[_][]const u8 {"whoami"},
    });

    defer {
        allocator.free(result.stdout);
        allocator.free(result.stderr);
    }

    var stripped_stdout = mem.trimRight(u8, result.stdout, "\n");

    return allocator.dupe(u8, stripped_stdout) catch
        std.debug.panic("Cannot allocate memory??\n", .{});
}

pub fn readHostname(allocator: mem.Allocator) ![]u8 {
    var buf: [os.HOST_NAME_MAX]u8 = undefined;
    var hostname = try os.gethostname(buf[0..]);
    return try allocator.dupe(u8, hostname);
}