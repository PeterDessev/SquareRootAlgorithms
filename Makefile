COMPILER = clang

CFLAGS   = -Iinclude/IteratingAnEstimate -Iinclude/ProducingAnEstimate -DDEBUG_LEVEL=0
OBJECTS  = src/IteratingAnEstimate/goldschmidt.c\
		   src/IteratingAnEstimate/halley.c\
		   src/IteratingAnEstimate/lucas.c\
		   src/IteratingAnEstimate/newton.c\
\
		   src/ProducingAnEstimate/floatingpoint.c\
		   src/ProducingAnEstimate/inputOver.c\
		   src/ProducingAnEstimate/inverseSquare.c\
		   src/ProducingAnEstimate/oneAsAnEstimate.c\
		   main.o

COMPILE  = $(COMPILER) -Wall $(CFLAGS)

program: build 


build: 
	$(AVRDUDE) $(OBJECTS)

clean:
	rm -f src/IteratingAnEstimate/*.o src/ProducingAnEstimate/*.o

.c.o:
	$(COMPILE) -c $< -o $@ -Wno-unknown-pragmas