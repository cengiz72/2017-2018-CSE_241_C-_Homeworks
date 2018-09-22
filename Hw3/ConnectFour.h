
#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
using namespace std;
class ConnectFour {
public:
    ConnectFour();
    ConnectFour(int witdh ,int length);
    ConnectFour(int witdh);
    //takes size of board and chooise of game from user.
    bool takesTheSizeAndChooise(int &sizeW,int &sizeL,char &selection);
    void readFile(string &filename,int &ppORpc,char &playerType);
    void writeFile(string &filename,int &ppORpc,char &playerType);
    void userToUser(char orderOfPcOrPlayer='N');
    void userToComputer(char orderOfPcOrPlayer='N');
    //it converts to all Uppercase found four matching cells into lowercase.
    void tolowerFourLettersMatching(int row,int &column,int down,int left,int right,
                                    int left_up,int right_down,int right_up,int left_down,char symbol);
    void allConvertsToLower(string &array);
    void showTheBoard() const;
    void initializeBoard();
    //update board size.
    void resizeTheVector();
    void printTheLabelBoard() const;
    int play();
    int play(char position,char user1ORUser2);
    bool move(string str,char &symbol,int &ppORpc);
    bool moveOfComputer(string str,char symbol);
    bool isCellAvaiable(int row) const;
    bool getRowOfAvaiable(int &row,char playerType)  const;
    bool checkEmptyIsStillExisting() const;
    bool moveMultiMode(char &player,int &ppORpc);
    void playGame();
    bool determineTheWinWho(char type,int position,int currentRow,int valuE);
    bool isCellLegal(int xCoordinate,int yCoordinate) const;
    bool findTheBetter(const ConnectFour &other) const;
    bool findTheConnectFour(int column,char symbol,int value,int currentRow);
    bool findTheConnectFour(char symbol,int column,int value,int currentRow);
    bool findTheConnectFour(int value,int currentRow,char symbol,int column);
    bool findTheConnectFour(int column,int value,int currentRow,char symbol);
    int get_width() const;
    int get_length() const;
    char get_ppORpc() const;
    void set_width(int witdh);
    void set_length(int length);
    void set_ppORpc(char typeOfGame);
private:
    class Cell{
        public:
            Cell();
            char get_column() const;
            int get_row() const;
            char get_PlayerType() const;
            void set_column(char yCoordinate);
            void set_row(int xCoordinate);
            void set_PlayerType(char player);
            static int get_livingCells();
            static void set_livingCells(int count);
        private:
            char typeOfPlayer;
            int row;
            char column;
            static int livingCells;
    };
    int width;
    int length;
    char ppORpc;
    vector< vector<Cell> > gameCells;
};



#endif /* CONNECTFOUR_H */
