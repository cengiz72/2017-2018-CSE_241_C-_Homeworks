all: ConnectFour.o main.o  exe 

main.o:
	   g++ -std=c++11 -c main.cpp

ConnectFour.o:
		g++ -std=c++11 -c  ConnectFour.cpp     
exe:
	   g++ -o exe  ConnectFour.o main.o 
		
clean:
		rm *.o exe					   
