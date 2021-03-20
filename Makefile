ROOT=.

CFLAGS?= -O2 -Wall -W

LDFLAGS= -ldouble-conversion

DOUBLE_CONVERSION_LIBDIR=$(ROOT)/deps/double-conversion
LIBDOUBLE_CONVERSION=$(DOUBLE_CONVERSION_LIBDIR)/libdouble-conversion.a


all: double-conversion-c

$(LIBDOUBLE_CONVERSION):
	@echo Building $@...
	cd $(DOUBLE_CONVERSION_LIBDIR); cmake .; make -j; 

double-conversion-c: $(LIBDOUBLE_CONVERSION)
	@echo Building $@...
	$(SHOW)$(CC) -c $(CFLAGS) double-conversion-c.cpp -I$(DOUBLE_CONVERSION_LIBDIR)
	@echo Creating static library $@...
	ar rcs libdouble-conversion-c.a double-conversion-c.o

clean:
	rm -f libdouble-conversion-c.a *.gcov *.o