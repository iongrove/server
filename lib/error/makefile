NAME = error
VERSION = 0.4

AR = ar rcs
CC = cc -std=c89
CFLAGS = -O2 -static
WARNINGS = -pedantic -Werror -Wall -Wextra

LIB_NAME = lib$(NAME).a
ZIP_NAME = $(NAME)-$(VERSION)

INCLUDES = -Isrc
BASE_CFLAGS = $(EXTRA_CFLAGS) $(WARNINGS) $(INCLUDES)
ALL_CFLAGS = $(CFLAGS) $(BASE_CFLAGS)


all: lib

zip: all doc
	$(MAKE) clean
	mkdir $(ZIP_NAME)
	cp -RL doc src licence makefile readme.md readme.html $(ZIP_NAME)
	zip -rq9 $(ZIP_NAME).zip $(ZIP_NAME)
	rm -rf $(ZIP_NAME)

doc: readme.html
doc: doc/introduction.html

readme.md: doc/introduction.md
	cp doc/introduction.md readme.md
	sed -i -e 's/.h`](/.h`](doc\//g' readme.md

lib: src/error.o
	$(AR) $(LIB_NAME) $?

.SUFFIXES: .c .o .md .html

.c.o:
	$(CC) $(ALL_CFLAGS) -o $*.o -c $<

.md.html:
	pandoc -s -c main.css -c doc/main.css -T "$(NAME)" --quiet -o $*.html $<
	sed -i -e 's/.md/.html/g' $*.html

mostlyclean:
	rm -f src/*.o

clean: mostlyclean
	rm -f $(ZIP_NAME).zip
	rm -f $(LIB_NAME)

options:
	echo 'AR="$(AR)"'
	echo 'CC="$(CC)"'
	echo 'CFLAGS="$(CFLAGS)"'
	echo 'EXTRA_CFLAGS="$(EXTRA_CFLAGS)"'

help:
	echo "make           builds the library"
	echo "make doc       builds the documentation"
	echo "make zip       builds an archive of the project"
	echo "make clean     removes previously generated files"
	echo "make options   shows options that can be passed to $(MAKE)"

.SILENT:
