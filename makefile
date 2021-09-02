null :=
SPACE := $(null) $(null)
exec = $(notdir $(subst $(SPACE),_,$(PWD)))
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g
libs = -lSDL2 -lm
includes = -I./src

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec) $(libs)
	chmod +x $(exec)

%.o: %.c $(wildcard src/include/*.h)
	gcc -c $(flags) $(includes) $< -o $@

install:
	make
	cp ./$(exec) /usr/local/bin/$(exec)
	make clean

clean:
	rm $(exec)
	rm src/*.o
