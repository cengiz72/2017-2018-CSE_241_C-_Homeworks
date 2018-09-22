
#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <iostream>
#include <string>
#include <fstream>
#include <random>
using namespace std;
class ConnectFour {
public:
    ConnectFour();
    ConnectFour(int witdh ,int length);
    ConnectFour(string &boardname);
    ~ConnectFour();
    bool moveMultiMode(char &player,int &ppORpc);
    //takes size of board and chooise of game from user.
    bool takesBoardNameAndChooise(string &filename,char &selection);
    void playGame();
    int get_Row() const;
    int get_Column() const;
    char get_ppORpc() const;
    void set_Row(int witdh);
    void set_Column(int length);
    void set_ppORpc(char typeOfGame);
private:
    class Cell{
        public:
            Cell();
            Cell(char type);
            friend ostream & operator <<(ostream &out,const Cell & cell);
            friend istream & operator >>(istream &input,Cell & cell);
            bool operator ==(const Cell & cell1) const;
            ConnectFour::Cell operator ++();
            ConnectFour::Cell operator ++(int i);
            ConnectFour::Cell operator --();
            ConnectFour::Cell operator --(int i);
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
    friend ostream & operator <<(ostream &out,const ConnectFour::Cell & cell);
    friend istream & operator >>(istream &input,ConnectFour::Cell & cell);
    bool determineTheWinWho(char type,int position,int currentRow,int valuE);
    bool isCellLegal(int xCoordinate,int yCoordinate) const;
    bool findTheConnectFour(int column,char symbol,int value,int currentRow);
    bool findTheConnectFour(char symbol,int column,int value,int currentRow);
    bool findTheConnectFour(int value,int currentRow,char symbol,int column);
    bool findTheConnectFour(int column,int value,int currentRow,char symbol);
    bool operator ==(const ConnectFour & another) const;
    bool operator !=(const ConnectFour & another) const;
    void readboard(string &file);
    void readFile(string &filename,int &ppORpc,char &playerType);
    void writeFile(string &filename,int &ppORpc,char &playerType);
    void userToUser(char orderOfPcOrPlayer='N');
    void userToComputer(char orderOfPcOrPlayer='N');
    //it converts to all Uppercase found four matching cells into lowercase.
    void tolowerFourLettersMatching(int row,int &column,int down,int left,int right,
                                    int left_up,int right_down,int right_up,int left_down,char symbol);
    void allConvertsToLower(string &array);
    void createNewBoard();
    void destroyBoard();
    void showTheBoard() const;
    void printTheLabelBoard() const;
    int likeStrlen(char *str) const;
    int play();
    int play(char position,char user1ORUser2);
    bool move(string str,char &symbol,int &ppORpc);
    bool moveOfComputer(string str,char symbol);
    bool isCellAvaiable(int row) const;
    bool getRowOfAvaiable(int &row,char playerType)  const;
    bool checkEmptyIsStillExisting() const;
    int row_;
    int column_;
    char ppORpc;
    Cell **board;
};



#endif /* CONNECTFOUR_H */
