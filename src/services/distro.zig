const std = @import("std");

const mem = std.mem;
const fs = std.fs;

pub fn readPrettyName(allocator: mem.Allocator) !?[]u8 {
    var os_release = try fs.openFileAbsolute("/etc/os-release", .{});
    defer os_release.close();

    const reader = os_release.reader();

    var buf: [1024]u8 = undefined;
    var pretty_name: ?[]u8 = null;

    comptime var prefix = "PRETTY_NAME=";

    while (try reader.readUntilDelimiterOrEof(buf[0..], '\n')) |line| {
        if (mem.startsWith(u8, line, prefix)) {
            var value = line[prefix.len..];

            // remove trailing " by using slices.
            pretty_name = allocator.dupe(u8, value[1..value.len - 1]) catch
                std.debug.panic("Cannot allocate memory??\n", .{});

            break;
        }
    }

    return pretty_name;
}

pub fn getKerVer(allocator: mem.Allocator) ![]u8 {
    var buf: [1024]u8 = undefined;

    const uts = std.os.uname();
    const release = mem.sliceTo(&uts.release, 0);
    const result = buf[0..release.len];
    @memcpy(result, release);

    return try allocator.dupe(u8, result);
}