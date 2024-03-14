const std = @import("std");
const Banner = @import("./banner.zig");
const Bunny = @import("../static.zig").Bunny;

const io = std.io;
const mem = std.mem;

const Self = @This();

const stdout = io.getStdOut().writer();
const stderr = io.getStdErr().writer();

offset_width: usize,
current_banner_part: usize,
allocator: mem.Allocator,

pub fn new(allocator: mem.Allocator) !*Self {
    var instance = try allocator.create(Self);
    instance.offset_width = Banner.maxSize() + 1;
    instance.current_banner_part = 0;
    instance.allocator = allocator;
    return instance;
}

fn printOffset(self: *Self) !void {
    for (0..self.offset_width) |_| {
        try stdout.print(" ", .{});
    }
}

pub fn renderEmpty(self: *Self, component_renderer: *const fn (mem.Allocator) void) !void {
    try self.printOffset();
    component_renderer(self.allocator);
}

pub fn render(self: *Self, component_renderer: *const fn (mem.Allocator) void) !void {
    Banner.printPart(self.current_banner_part) catch |err| {
        switch (err) {
            Banner.BunnyPrintError.InvalidPartId => {
                // render without banner when there's no more rows available
                try self.renderEmpty(component_renderer);
                return;
            },
            Banner.BunnyPrintError.WriteError => {
                try stderr.print("Failed to write to stdout! {s}\n", .{@errorName(err)});
                std.process.exit(1);
                return err;
            },
        }
    };

    // aligning content to the right by using `self.offset_width`
    // as a padding-reference value.
    var left_spaces = self.offset_width - Bunny[self.current_banner_part].len;

    for (0..left_spaces) |_| {
        try stdout.print(" ", .{});
    }

    component_renderer(self.allocator);
    self.current_banner_part += 1;
}

pub fn deinit(self: *Self) void {
    self.allocator.destroy(self);
}
