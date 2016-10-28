CPP=g++
FLAGS= -std=c++11

main: coloreo.o greedy.o local.o
	$(CPP) $(FLAGS) main.cpp -o $@ coloreo.o greedy.o local.o

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm main
