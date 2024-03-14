const std = @import("std");
const static = @import("../static.zig");
const CommonInfo = @import("../services/common-info.zig");

const mem = std.mem;
const io = std.io;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

pub fn renderHostname(allocator: mem.Allocator) void {
    var hostname = CommonInfo.readHostname(allocator) catch |err| {
        stderr.print("Failed to read hostname! {s}\n", .{@errorName(err)}) catch unreachable;
        std.process.exit(1);
        return;
    };

    defer allocator.free(hostname);

    stdout.print("{s}hs  {s}{s}\n", .{
        static.Cyan,
        static.Reset,
        hostname
    }) catch unreachable;
}