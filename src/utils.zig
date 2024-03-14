const std = @import("std");

const mem = std.mem;
const fmt = std.fmt;

pub fn formatBytes(allocator: mem.Allocator, bytes: u64) ![]u8 {
    const units = [_][]const u8 {
        "B", "KB", "MB",
        "GB", "TB", "PB",
        "EB", "ZB", "YB"
    };

    var i: usize = 0;
    var val = @as(f64, @floatFromInt(bytes));

    while (val >= 1024.0 and i < units.len - 1) {
        val /= 1024.0;
        i += 1;
    }

    return try fmt.allocPrint(allocator, "{d:.2} {s}", .{
        val, units[i]
    });
}