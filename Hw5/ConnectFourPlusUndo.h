/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"


class ConnectFourPlusUndo : public ConnectFourPlus
{
    public:
        ConnectFourPlusUndo();
        ~ConnectFourPlusUndo();
        void undo();
        void allocateForStruct();
        void freeForStruct();
        int get_used() const;
        void set_used(char incOrdec); 
        bool move(string str,char &symbol,int &ppORpc);
        virtual void playGame();
        void readFile(string &filename,int &ppORpc,char &playerType);
        void writeFile(string &filename,int &ppORpc,char &playerType);
        bool moveOfComputer(string str,char symbol);
    private:
        typedef struct undo{
            int row;
            int column;
        }Undo; 
        Undo * array;
    int used;
};

#endif /* CONNECTFOURPLUSUNDO_H */

