const std = @import("std");
const Bunny = @import("../static.zig").Bunny;
const static = @import("../static.zig");

const mem = std.mem;
const io = std.io;

pub fn maxSize() usize {
    var max_width: usize = 0;
    for (Bunny) |part| {
        const width = @as(usize, @intCast(part.len));
        if (width > max_width) {
            max_width = width;
        }
    }

    return max_width;
}

pub const BunnyPrintError = error{ InvalidPartId, WriteError };

pub fn printPart(part_id: usize) BunnyPrintError!void {
    if (part_id < 0 or part_id >= Bunny.len) {
        return error.InvalidPartId;
    }

    const part = Bunny[part_id];
    const stdout = io.getStdOut().writer();

    // NOTE: The characters `=` will be printed in yellow
    // and the characters `"` in red, this will make the bunny
    // look pretty and stylished. :)
    for (part) |c| {
        const color = switch (c) {
            '=' => static.Yellow,
            '"' => static.Red,
            else => "",
        };

        stdout.print("{s}{c}{s}", .{
            color, c,
            if (mem.eql(u8, color, "")) "" else static.Reset
        }) catch {
            return error.WriteError;
        };
    }
}
