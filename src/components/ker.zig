const std = @import("std");
const static = @import("../static.zig");

const Distro = @import("../services/distro.zig");

const mem = std.mem;
const io = std.io;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

pub fn renderKerVer(allocator: mem.Allocator) void {
    stdout.print("{s}ker {s}", .{static.Blue, static.Reset}) catch
        unreachable;

    var kerver = Distro.getKerVer(allocator) catch |err| {
        stderr.print("cannot fetch kernel version! ({s})\n", .{@errorName(err)}) catch
            unreachable;
        std.process.exit(1);
        return;
    };

    defer allocator.free(kerver);

    stdout.print("{s}\n", .{kerver}) catch
        unreachable;
}