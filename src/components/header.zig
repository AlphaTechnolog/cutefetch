const std = @import("std");
const static = @import("../static.zig");
const CommonInfo = @import("../services/common-info.zig");

const io = std.io;
const mem = std.mem;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

const readWhoami = CommonInfo.readWhoami;
const readHostname = CommonInfo.readHostname;

pub fn renderHeader(allocator: mem.Allocator) void {
    var username = readWhoami(allocator) catch |err| {
        stderr.print("Failed to read username! {s}\n", .{@errorName(err)}) catch unreachable;
        std.process.exit(1);
        return;
    };

    var hostname = readHostname(allocator) catch |err| {
        stderr.print("Failed to read hostname! {s}\n", .{@errorName(err)}) catch unreachable;
        std.process.exit(1);
        return;
    };

    defer {
        for (&[_][]u8{ username, hostname }) |name| {
            allocator.free(name);
        }
    }

    stdout.print("{s}{s}{s}@{s}{s}{s}\n", .{
        static.Cyan,
        username,
        static.Blue,
        static.Magenta,
        hostname,
        static.Reset
    }) catch unreachable;
}