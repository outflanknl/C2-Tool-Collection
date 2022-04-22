BOF := Askcreds
CC_x64 := x86_64-w64-mingw32-gcc
STRIP_x64 := x86_64-w64-mingw32-strip

all:
	$(CC_x64) -o ../$(BOF).o -c $(BOF).c
	$(STRIP_x64) --strip-unneeded ../$(BOF).o

clean:
	rm ../$(BOF).o
