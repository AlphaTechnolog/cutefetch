const std = @import("std");
const static = @import("../static.zig");

const Distro = @import("../services/distro.zig");

const mem = std.mem;
const io = std.io;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

pub fn renderOs(allocator: mem.Allocator) void {
    stdout.print("{s}os  {s}", .{static.Green, static.Reset}) catch
        unreachable;

    var pretty_name = Distro.readPrettyName(allocator) catch |x| {
        stderr.print("Cannot read pretty name from /etc/os-release! {s}\n", .{@errorName(x)}) catch
            unreachable;
        std.process.exit(1);
        return;
    };

    defer {
        if (pretty_name) |name| {
            allocator.free(name);
        }
    }

    if (pretty_name) |name| {
        std.debug.print("{s}\n", .{name});
    }
}