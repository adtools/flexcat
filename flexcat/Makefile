CC=gcc

# Specify path to gd library for include files
INCLUDES=

#specify paths for support libraries
LIBDIRS=
LIBS=
CFLAGS=-g
OBJS= createcat.o createcatsrc.o createct.o globals.o main.o readprefs.o \
      scancd.o scanct.o showfuncs.o swapfuncs.o utils.o locale_other.o 

flexcat: $(OBJS)
	$(CC) $(LDFLAGS) -o flexcat $(OBJS)

#test: test.class txt2fax
#	-rm -f output.png*
#	java test
#
#test.class: test.java
#	javac -encoding iso8859-2 test.java
#
#dist:
#	$(CC) -O2 $(INCLUDES) $(LIBDIRS) -o txt2fax txt2fax.c $(LIBS)
#
clean:
	rm -f *.o
	rm -f flexcat
