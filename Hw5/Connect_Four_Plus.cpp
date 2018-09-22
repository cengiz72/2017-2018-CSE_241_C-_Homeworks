/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#include "ConnectFourPlus.h"

bool ConnectFourPlus::determineTheWinWho(char type,int current,int position,int valuE){
    return   findTheConnectFour(type,current,valuE,position) ||
             findTheConnectFour(current,valuE,position,type);
}

ConnectFourPlus::ConnectFourPlus() : ConnectFourAbstract() 
{}
ConnectFourPlus::~ConnectFourPlus() {
  destroyBoard();
}