const std = @import("std");
const static = @import("../static.zig");
const Df = @import("../services/df.zig");

const io = std.io;
const mem = std.mem;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

fn printDiskUsage(allocator: mem.Allocator, mountpoint: []const u8) !void {
    var df = try Df.fromMountpoint(allocator, mountpoint);
    defer df.deinit();
    try stdout.print("{s} / {s}", .{df.used, df.size});
    try stdout.print(" ({s}/{s})\n", .{static.Cyan, static.Reset});
}

pub fn renderDisk(allocator: mem.Allocator) void {
    stdout.print("{s}dsk {s}", .{
        static.Red,
        static.Reset
    }) catch unreachable;

    printDiskUsage(allocator, "/") catch |err| {
        stderr.print("Failed to read disk information for `/`: {s}\n", .{@errorName(err)}) catch
            unreachable;
        std.process.exit(1);
        return err;
    };
}