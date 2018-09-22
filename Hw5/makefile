all: compile  exe 

compile:
	 g++ -c Connect_Four_Abstract.cpp Connect_Four_Plus.cpp Connect_four_Plus_Undo.cpp Connect_Four_Diag.cpp cell.cpp main.cpp -std=c++11
  
exe:
	 g++ -o exe Connect_Four_Abstract.o Connect_Four_Plus.o cell.o main.o Connect_four_Plus_Undo.o Connect_Four_Diag.o  
		
clean:
		rm *.o exe					   
