CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
APPNAME = cutefetch

SRCDIR = src
OBJDIR = obj
BINDIR = bin

PREFIX=/usr
INSTALLDIR = $(PREFIX)/bin

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(addprefix $(OBJDIR)/,$(notdir $(SRCFILES:.c=.o)))
TARGET = $(BINDIR)/${APPNAME}

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJFILES) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir $(BINDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

install: $(TARGET)
	mkdir -pv $(INSTALLDIR)
	install -Dm755 $< $(INSTALLDIR)/$(APPNAME)

uninstall:
	rm -fv $(INSTALLDIR)/$(APPNAME)
