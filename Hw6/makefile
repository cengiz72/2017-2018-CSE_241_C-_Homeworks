all: compile  exe 

compile:
	 g++ -c  Gtuiterator.cpp GtuMap.cpp Gtuset.cpp GtuSetBase.cpp main.cpp -std=c++11
  
exe:
	 g++ -o exe Gtuiterator.o GtuMap.o Gtuset.o GtuSetBase.o main.o 
		
clean:
		rm *.o exe					   
