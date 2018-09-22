/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H
#include "ConnectFourAbstract.h"
class ConnectFourDiag : public ConnectFourAbstract{
    public:
         ConnectFourDiag();
        ~ConnectFourDiag();
        bool determineTheWinWho(char type, int position, int currentRow, int valuE) override;
    private:
};
#endif /* CONNECTFOURDIAG_H */

