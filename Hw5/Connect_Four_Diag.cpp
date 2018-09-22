/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#include "ConnectFourDiag.h"

bool ConnectFourDiag::determineTheWinWho(char type, int position, int currentRow, int valuE) {
    return  findTheConnectFour(currentRow,type,valuE,position) || 
            findTheConnectFour(valuE,position,type,currentRow);
}

ConnectFourDiag::ConnectFourDiag() : ConnectFourAbstract()
{}
ConnectFourDiag::~ConnectFourDiag() {
    destroyBoard();
}