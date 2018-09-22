/* 
 * File:   main.cpp
 * Author: cengiz toprak
 * ID: 161044087
 *
 */
#include "ConnectFour.h"
using namespace std;
void gameOfAllObjects(ConnectFour *objects,int &size);


int main(int argc, char** argv) {
    
    int numberOfObject;
    bool flag=true;
    char mode;  
    ConnectFour objects[10];
    do
    {
        cout<<"Please chooise the game mode S for single and M for Multiple:";
        cin>>mode;
        if (mode=='S' || mode=='M') flag=false;
    }while(flag);
    flag=true;
    if (mode=='M') {
        do
        {
            cout<<"Please enter the number of objects:";
            cin>>numberOfObject;
            if (numberOfObject>=2 && numberOfObject<=10) flag=false;
            else {
                cin.clear();
                cin.ignore(999,'\n'); 
            }
        }while(flag);
        gameOfAllObjects(objects,numberOfObject);
    }
    else {
        objects[0].playGame();
    }
    return 0;
}

void gameOfAllObjects(ConnectFour *objects,int &size) {
    bool gameOverInAllObjects=true;
    bool flag1=true;
    bool flag=true;
    char playerType[]={'X','O'};
    int ppOrpc;
    int chooise;
    char gameType;
    int holdGameOverOrNot[10];
    int counterOfOvergames=0;
    int witdH;
    int lengtH;
    for(int i=0; i<size; ++i) {
        flag1=true;
        cout<<"operation for "<<i+1<<". object."<<endl;        
        while(flag1) {
            if( objects[i].takesTheSizeAndChooise(witdH,lengtH,gameType)) flag1=false;
        }
        objects[i].set_length(lengtH);
        objects[i].set_width(witdH);
        objects[i].set_ppORpc(tolower(gameType));
        objects[i].initializeBoard();
        holdGameOverOrNot[i]=i;
    }
    while (gameOverInAllObjects) {
        counterOfOvergames=0;
        flag=true;
        do
        {
            cout<<endl;
	    cout<<"Enter the objects:";
            cin>>chooise;
            
            if (chooise>=1 && chooise<=5 && holdGameOverOrNot[chooise-1]>=0) flag=false;
            else {
                cin.clear();
                cin.ignore(999,'\n');
                if (holdGameOverOrNot[chooise-1]<0) 
                    cerr<<chooise<<". game is over."<<endl;
                else cerr<<"wrong chooise!!!"<<endl;
            }
        }while(flag);
       
           
        
        if (objects[chooise-1].get_ppORpc()=='p') {            
            ppOrpc=3;
               if (objects[chooise-1].moveMultiMode(playerType[0],ppOrpc)) {
                   cout<<"User1 win the game."<<endl;
                   holdGameOverOrNot[chooise-1]=-1;
               }
               else  if(objects[chooise-1].moveMultiMode(playerType[1],ppOrpc)) {
                    cout<<"User2 win the game."<<endl;
                    holdGameOverOrNot[chooise-1]=-1;
               }
        }
           
           else if (objects[chooise-1].get_ppORpc()=='c'){
               ppOrpc=4;
               if (objects[chooise-1].moveMultiMode(playerType[0],ppOrpc)) {
                   cout<<"User win the game."<<endl;
                   holdGameOverOrNot[chooise-1]=-1;
               }
               else if (objects[chooise-1].moveMultiMode(playerType[1],ppOrpc)) {
                   cout<<"Computer win the game."<<endl;
                   holdGameOverOrNot[chooise-1]=-1;              
               }
           }
        
        for (int j=0; j<size; ++j) 
            if (holdGameOverOrNot[j]==-1) ++counterOfOvergames;
        if (counterOfOvergames==5) gameOverInAllObjects=false;
        }
    
    cout<<"All games are over."<<endl;
    
}
