SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
CC_x64 := x86_64-w64-mingw32-gcc
STRIP_x64 := x86_64-w64-mingw32-strip

all: $(OBJS)

%.o: %.c
	$(CC_x64) $(CFLAGS) -o ../$@ -c $<
	$(STRIP_x64) --strip-unneeded ../$@

clean:
	rm ../*.o