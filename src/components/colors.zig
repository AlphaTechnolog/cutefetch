const std = @import("std");
const static = @import("../static.zig");

const mem = std.mem;
const io = std.io;
const debug = std.debug;

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

const Character = "";

pub fn renderColors(_: mem.Allocator) void {
    comptime var colors = [_]*const [5:0]u8 {
        static.Red, static.Green, static.Yellow, static.Blue, static.Magenta,
        static.Cyan, static.White
    };

    for (colors) |color| {
        stdout.print("{s}{s}{s} ", .{color, Character, static.Reset}) catch
            debug.panic("Failed to write to stdout!\n", .{});
    }

    stdout.print("\n", .{}) catch unreachable;
}