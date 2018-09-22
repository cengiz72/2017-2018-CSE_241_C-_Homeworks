/*
    author: Cengiz Toprak
    ID    : 161044087
*/

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
#include "Cell.h"
#include <string>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;
class ConnectFourAbstract {
    public:
        ConnectFourAbstract();
        ~ConnectFourAbstract();
        //allocate space with respect to given number of row and column.
        void createNewBoard();
        //deallocate dynamic array.
        void destroyBoard();
        //print letters above board with rescpect to size of column.
        void printTheLabelBoard() const;
        void playGame();
        //assign dot to all cells.
        void initializeBoard();
        virtual void readFile(string &filename,int &ppORpc,char &playerType);
        virtual void writeFile(string &filename,int &ppORpc,char &playerType);
        bool takesTheSizeAndChooise(int &sizeW,int &sizeL,char &selection);
        void userToUser(char orderOfPcOrPlayer='N');
        void userToComputer(char orderOfPcOrPlayer='N');
        //it converts to all Uppercase found four matching cells into lowercase.
        void tolowerFourLettersMatching(int row,int &column,int down,int left,int right,
                                    int left_up,int right_down,int right_up,int left_down,char symbol);//
        void allConvertsToLower(string &array);
        void showTheBoard() const;
        int get_Row() const;
        int get_Column() const;
        char get_ppORpc() const;
        void set_Row(int witdh);
        void set_Column(int length);
        void set_ppORpc(char typeOfGame);
        int play();
        int play(char position,char user1ORUser2);
        bool isCellLegal(int xCoordinate,int yCoordinate) const;
        virtual bool move(string str,char &symbol,int &ppORpc);
        virtual bool moveOfComputer(string str,char symbol);
        bool isCellAvaiable(int row) const;
        bool getRowOfAvaiable(int &row,char playerType)  const;
        bool checkEmptyIsStillExisting() const;
        virtual bool determineTheWinWho(char type,int position,int currentRow,int valuE) = 0;
        bool findTheConnectFour(int column,char symbol,int value,int currentRow);
        bool findTheConnectFour(char symbol,int column,int value,int currentRow);
        bool findTheConnectFour(int value,int currentRow,char symbol,int column);
        bool findTheConnectFour(int column,int value,int currentRow,char symbol);
    protected:
      Cell **gameCells;
    private:
        int row;
        char ppORpc;
        int column;
};


#endif /* CONNECTFOURABSTRACT_H */