const std = @import("std");
const static = @import("../static.zig");
const utils = @import("../utils.zig");

const io = std.io;
const mem = std.mem;
const fmt = std.fmt;
const fs = std.fs;

const stdout = std.io.getStdOut().writer();
const stderr = std.io.getStdErr().writer();

const RamReader = struct {
    // total of available memory in bytes
    total_mem: u64,

    // free memory in bytes
    free_mem: u64,

    // used memory in bytes. It's the difference
    // of `total_mem` and `free_mem`
    used_mem: u64,

    // The used allocator to allocate the struct
    // serves to destroy the struct later.
    allocator: mem.Allocator,

    const Self = @This();

    // A formatter util which returns the allocated
    // strings with the proper output
    const Formatter = struct {
        fmtted_used_mem: []u8,
        fmtted_total_mem: []u8,
        result: []u8,
        allocator: mem.Allocator,

        // applies the bytes formatting by using the ram reader instance
        // as the base parent implementation.
        pub fn fromRamReader(ram_reader: *RamReader) !Formatter {
            var ret = Formatter{
                .fmtted_used_mem = try utils.formatBytes(ram_reader.allocator, ram_reader.used_mem),
                .fmtted_total_mem = try utils.formatBytes(ram_reader.allocator, ram_reader.total_mem),
                .result = undefined,
                .allocator = ram_reader.allocator,
            };

            // performing the actual formatting
            ret.result = try fmt.allocPrint(ret.allocator, "{s} / {s}", .{
                ret.fmtted_used_mem,
                ret.fmtted_total_mem,
            });

            return ret;
        }

        // Deinitialises the Formatter instance and the sub-allocated strings.
        pub fn deinit(self: Formatter) void {
            self.allocator.free(self.fmtted_total_mem);
            self.allocator.free(self.fmtted_used_mem);
            self.allocator.free(self.result);
        }
    };

    // Create a new instance of RamReader
    pub fn new(allocator: mem.Allocator) !*Self {
        var instance = try allocator.create(Self);
        instance.allocator = allocator;
        instance.free_mem = 0;
        instance.used_mem = 0;
        instance.total_mem = 0;
        return instance;
    }

    // Parse the MemTotal line from /proc/meminfo
    fn parseMemTotal(self: *Self, line: []u8) !void {
        var it = std.mem.tokenize(u8, line, " ");

        // ignore the first value as it's the prefix
        _ = it.next();

        // second value separating by " " is the total memory
        // the * 1024 is to convert it from kB to bytes
        if (it.next()) |value| {
            self.total_mem = 1024 * (fmt.parseInt(u64, value, 10) catch |err| {
                try stderr.print("Attempt to parse non-numeric value {s} as total memory ({s})\n", .{
                    value,
                    @errorName(err)
                });

                std.process.exit(1);
                return err;
            });
        }
    }

    // Parse the MemAvailable line from /proc/meminfo
    fn parseMemAvailable(self: *Self, line: []u8) !void {
        var it = std.mem.tokenize(u8, line, " ");

        // ignore first value as it's the prefix
        _ = it.next();

        // second value separating by " " is the available memory
        // the * 1024 is to convert it from kB to bytes
        if (it.next()) |value| {
            self.free_mem = 1024 * (fmt.parseInt(u64, value, 10) catch |err| {
                try stderr.print("Attempt to parse non-numeric value {s} as available memory ({s})\n", .{
                    value,
                    @errorName(err)
                });

                std.process.exit(1);
                return err;
            });
        }
    }

    // Fetch the memory information from /proc/meminfo
    pub fn fetch(self: *Self) !void {
        var meminfo = try fs.openFileAbsolute("/proc/meminfo", .{});
        defer meminfo.close();

        const reader = meminfo.reader();

        var buf: [1024]u8 = undefined;

        while (try reader.readUntilDelimiterOrEof(buf[0..], '\n')) |line| {
            if (mem.startsWith(u8, line, "MemTotal:")) {
                try self.parseMemTotal(line);
            } else if (mem.startsWith(u8, line, "MemAvailable")) {
                try self.parseMemAvailable(line);
            }
        }

        self.used_mem = self.total_mem - self.free_mem;
    }

    // Deinitialises the instance of RamReader
    pub fn deinit(self: *Self) void {
        self.allocator.destroy(self);
    }
};

pub fn renderRam(allocator: mem.Allocator) void {
    stdout.print("{s}ram {s}", .{
        static.Magenta,
        static.Reset
    }) catch unreachable;

    var ramreader = RamReader.new(allocator) catch
        std.debug.panic("Cannot allocate a new ramreader object!\n", .{});

    defer ramreader.deinit();

    ramreader.fetch() catch |err| {
        stderr.print("Failed to parse `/proc/meminfo`! {s}\n", .{@errorName(err)}) catch
            unreachable;
        std.process.exit(1);
        return err;
    };

    var formatted_ramreader = RamReader.Formatter.fromRamReader(ramreader) catch
        std.debug.panic("Cannot format the ramreader object!\n", .{});

    defer formatted_ramreader.deinit();

    stdout.print("{s}\n", .{formatted_ramreader.result}) catch
        unreachable;
}