OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o calculadora_privats.o calculadora_publics.o Primitives.o defines.o
	g++ -o program.exe *.o
	rm *.o

calculadora_publics.o: calculadora_publics.cc calculadora.hh defines.hh Primitives.hh
	g++ -c calculadora_publics.cc $(OPCIONS)

calculadora_privats.o: calculadora_privats.cc calculadora.hh defines.hh Primitives.hh
	g++ -c calculadora_privats.cc $(OPCIONS)

Primitives.o: Primitives.cc Primitives.hh
	g++ -c Primitives.cc $(OPCIONS)

defines.o: defines.cc defines.hh
	g++ -c defines.cc $(OPCIONS)

program.o: program.cc calculadora.hh Primitives.hh
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.exe
	rm *.o