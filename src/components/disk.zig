const std = @import("std");
const static = @import("../static.zig");
const System = @import("../services/system.zig");

const io = std.io;
const mem = std.mem;
const process = std.process;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

// fn printDiskInformation(allocator: mem.Allocator) !void {
//     var disk = try System.Disk.fromMountpoint(allocator, "/");
//     defer disk.deinit();
//     try stdout.print("{s} / {s}", .{disk.used_size, disk.total_size});
//     try stdout.print(" ({s}/{s})\n", .{static.Cyan, static.Reset});
// }

pub fn renderDisk(allocator: mem.Allocator) void {
    stdout.print("{s}dsk {s}", .{
        static.Red,
        static.Reset
    }) catch unreachable;

    var disks = System.Disks.init(allocator) catch unreachable;
    defer disks.deinit();

    for (disks.mountpoints.items) |mnt| {
        var disk = System.Disk.fromMountpoint(allocator, mnt) catch unreachable;
        defer disk.deinit();
    }

    // var disk = System.Disk.fromMountpoint(allocator, "/") catch unreachable;
    // defer disk.deinit();

    // printDiskInformation(allocator) catch |err| {
    //     stderr.print("Cannot obtain disk information from '/': {s}\n", .{@errorName(err)}) catch unreachable;
    //     process.exit(1);
    // };
}