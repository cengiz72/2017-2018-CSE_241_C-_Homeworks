/* 
 * File:   main.cpp
 * Author: cengiz toprak
 * ID: 161044087
 *
 */
#include "ConnectFour.h"
using namespace std;
void gameOfAllObjects(ConnectFour *objects);


int main(int argc, char** argv) {
    
    bool flag=true;
    char mode; 
    ConnectFour objects[5];
    do
    {
        cout<<"Please chooise the game mode S for single and M for Multiple:";
        cin>>mode;
        if (cin.eof())
        {
            cout<<"EOF is handled!!!"<<endl;
            cout<<"Program is over."<<endl;
            exit(1);
        }
        if (mode=='S' || mode=='M') flag=false;
    }while(flag);

    if (mode=='M') {

        gameOfAllObjects(objects);
    }
    else {
        objects[0].playGame();
    }
    return 0;
}

void gameOfAllObjects(ConnectFour *objects) {
    bool gameOverInAllObjects=true;
    bool flag1=true;
    bool flag=true;
    char playerType[]={'X','O'};
    int ppOrpc;
    int chooise;
    char gameType;
    string filename;
    int holdGameOverOrNot[10];
    int counterOfOvergames=0;
    int witdH;
    int lengtH;
    for(int i=0; i<5; ++i) {
        flag1=true;
        cout<<"operation for "<<i+1<<". object."<<endl;        
        while(flag1) {
            cout<<"Enter board name:";
            cin >> filename;
            if( objects[i].takesBoardNameAndChooise(filename,gameType)) flag1=false;
        }
        objects[i].set_ppORpc(tolower(gameType));
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
            if (cin.eof())
            {
              cout<<"EOF is handled!!!"<<endl;
              cout<<"Program is over."<<endl;
              exit(1);
            }
            
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
        
        for (int j=0; j<5; ++j) 
            if (holdGameOverOrNot[j]==-1) ++counterOfOvergames;
        if (counterOfOvergames==5) gameOverInAllObjects=false;
        }
    
    cout<<"All games are over."<<endl;
    
}


