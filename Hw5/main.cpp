/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"
#include "namespace.h"
using namespace ConnectFour;
int main(int argc, char** argv) {
    char temp;
    ConnectFourDiag object1;
    ConnectFourPlus object2;
    ConnectFourPlusUndo object3;
    cout<<" Enter the type:";
    cin >> temp;
    if (tolower(temp)=='u') {
        object3.playGame();
    }
    else if (tolower(temp)=='p') {
        object2.playGame();
    }
    else if (tolower(temp)=='d') {
        object1.playGame();
    }
    else cerr<<"wrong type"<<endl;
    return 0;
}
