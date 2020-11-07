BINDIR := bin
OBJDIR := obj
INCDIR := inc
SRCDIR := src

OBJ := object.o coop_string.o
OBJS := $(patsubst %, $(OBJDIR)/%, $(OBJ))

all: main
.PHONY: all

main: $(OBJS)
	$(CC) $(SRCDIR)/main.c $(OBJS) -O3 -o $(BINDIR)/coop -I$(INCDIR)

debug: $(OBJS)
	$(CC) $(SRCDIR)/main.c $(OBJS) -g -o $(BINDIR)/coop -I$(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $< -c -o $@ -I$(INCDIR)
