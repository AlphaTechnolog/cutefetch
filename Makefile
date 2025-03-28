CC=gcc

CFLAGS=-Wall -std=c89 -O3
LDFLAGS=

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
	cp $^ $@
	chmod +x $^

install: $(DESTDIR)/$(PREFIX)/bin/$(OUTPUT)

uninstall: $(DESTDIR)/$(PREFIX)/bin/$(OUTPUT)
	rm $^
