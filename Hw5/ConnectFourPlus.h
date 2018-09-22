/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "ConnectFourAbstract.h"
class ConnectFourPlus : public ConnectFourAbstract{

public:
   ConnectFourPlus();
   ~ConnectFourPlus();
    bool determineTheWinWho(char type,int current,int position,int valuE) override;
private:
};

#endif /* CONNECTFOURPLUS_H */