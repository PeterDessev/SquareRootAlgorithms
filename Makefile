CC = clang

CFLAGS = -Iinclude/ -Wno-unknown-pragmas -lm -O3
SOURCE = src/IteratingAnEstimate/goldschmidt.c\
		 src/IteratingAnEstimate/halley.c\
		 src/IteratingAnEstimate/newton.c\
		 src/IteratingAnEstimate/babylonian.c\
\
	     src/ProducingAnEstimate/floatingpoint.c\
	     src/ProducingAnEstimate/inputOver.c\
		 src/ProducingAnEstimate/inverseSquare.c\
		 src/ProducingAnEstimate/oneAsAnEstimate.c\
\
		 src/output.c\
		 src/parameters.c\
		 main.c

OBJECTS = $(SOURCE:.c=.o)

COMPILE = $(CC) -Wall $(CFLAGS)
OUTPUT = squareRoots

all: $(OBJECTS)
	$(COMPILE) $(OBJECTS) -o $(OUTPUT)

clean:
	rm -f $(OBJECTS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@