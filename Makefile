MINGW := $(shell expr "$(UNAME_S)" : 'MINGW')

CFLAGS := -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-unused-parameter -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments

LDFLAGS := -lc -lm
DESTDIR := /usr/bin

SRC := $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ := $(SRC:.c=.o)
BIN := bin

APPNAME := cutefetch

.PHONY: all clean

all: dirs app

dirs:
	mkdir -p $(BIN)

run: all
	$(BIN)/$(APPNAME)

app: $(OBJ)
	$(CC) -o $(BIN)/$(APPNAME) $^ $(LDFLAGS)
	strip $(BIN)/$(APPNAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

install: $(BIN)/$(APPNAME)
	mkdir -pv $(DESTDIR)
	install -Dm755 $< $(DESTDIR)/$(APPNAME)

uninstall:
	rm -fv $(DESTDIR)/$(APPNAME)
