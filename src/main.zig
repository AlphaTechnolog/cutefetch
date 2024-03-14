const std = @import("std");
const ComponentFormatter = @import("./components/components-formatter.zig");

const ArrayList = std.ArrayList;
const heap = std.heap;
const mem = std.mem;
const debug = std.debug;
const process = std.process;

const Header = @import("./components/header.zig");
const OS = @import("./components/os.zig");
const Kernel = @import("./components/ker.zig");
const Hostname = @import("./components/hostname.zig");
const Ram = @import("./components/ram.zig");
const Colors = @import("./components/colors.zig");
const Disk = @import("./components/disk.zig");

pub fn main() !void {
    var gpa = heap.GeneralPurposeAllocator(.{}){};

    defer if (gpa.deinit() == .leak) {
        std.debug.print("Memory leak detected!\n", .{});
    };

    const allocator = gpa.allocator();

    var fmt = try ComponentFormatter.new(allocator);
    defer fmt.deinit();

    // rendering the components, header should
    // be printed without the bunny part.
    try fmt.renderEmpty(Header.renderHeader);

    const common_renderers = [_]*const fn(mem.Allocator) void {
        OS.renderOs,
        Kernel.renderKerVer,
        Hostname.renderHostname,
        Ram.renderRam,
        Disk.renderDisk,
        Colors.renderColors,
    };

    for (common_renderers) |renderer| {
        fmt.render(renderer) catch |err| {
            debug.panic("Cannot render a component: {s}\n", .{@errorName(err)});
            process.exit(1);
            return err;
        };
    }
}
