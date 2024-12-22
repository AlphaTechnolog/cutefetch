CC=gcc

CFLAGS=-Wall -std=c89 -O3 $(shell pkg-config --cflags libbsd-overlay)
LDFLAGS=$(shell pkg-config --libs libbsd-overlay)

DESTDIR := /
PREFIX := /usr

SRCS=$(wildcard src/**/*.c src/*.c src/**/**/*.c)
OBJS=$(SRCS:.c=.o)

OUTPUT=cutefetch

$(OUTPUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean: $(OUTPUT) $(OBJS)
	rm $^

$(DESTDIR)/$(PREFIX)/bin/$(OUTPUT): $(OUTPUT)
	install -Dvm755 $^ $@

install: $(DESTDIR)/$(PREFIX)/bin/$(OUTPUT)

uninstall: $(DESTDIR)/$(PREFIX)/bin/$(OUTPUT)
	rm $^
