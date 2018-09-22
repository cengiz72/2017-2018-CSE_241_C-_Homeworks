#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int MAXSIZE=20;
bool takesTheSizeAndChooise(int &size,char &selection);
void allConvertsToLower(string &array);
void showTheBoard(const int size ,char board[][MAXSIZE]);
//print the full board.
void showTheBoard(char board[][MAXSIZE], const int size);
//initialize the board to empty cells.
void tolowerFourLettersMatching(char board[][MAXSIZE],int row,int &column,int down,int left,
                                int right,int left_up,int right_down,int right_up,int left_down,char symbol);
//Convert uppercase to lower case four matching cells.
void printTheLabelBoard(int size);
//print letters above board.
bool findTheConnectFour(int indexOfFull[],int column,char board[][MAXSIZE],char symbol,int size,int value);
bool findTheConnectFour(int indexOfFull[],int column,char board[][MAXSIZE],int size,char symbol,int value);
bool findTheConnectFour(char symbol,int size,int indexOfFull[],int column,char board[][MAXSIZE],int value);
bool findTheConnectFour(int indexOfFull[],char board[][MAXSIZE],int column,char symbol,int size,int value);
//above four functions finds the four matching cells
const bool isCellLegal(int xCoordinate,int yCoordinate,int size);
//it checks wheather cells is legal.
bool checkTheTotalEmpty(char board[][MAXSIZE],int size);
void gameUserViaUser(char board[][MAXSIZE],int &size,char orderOfPcOrPlayer ='N');
void gameUserViaComputer(char board[][MAXSIZE],int &size,char orderOfPcOrPlayer ='N');
bool move(string str,int index[],int &size,char board[][MAXSIZE],char &symbol,int &ppORpc);
//takes move from users.
bool moveOfComputer(string str,int index[],int size,char board[][MAXSIZE],char symbol);
int main(){
    char array[MAXSIZE][MAXSIZE];
    int userSize; //take input from user.
    char chooise;
    bool flag;

    do
    {
        flag=takesTheSizeAndChooise(userSize,chooise);
        if (flag==false) 
            cerr<<"Wrong entry!!!\n"
                <<"Please enter the integer number."<<endl;
        else {
            showTheBoard(array,userSize); //initialization of game board.
            if (tolower(chooise)=='p') gameUserViaUser(array,userSize);
            if (tolower(chooise)=='c') gameUserViaComputer(array,userSize);
        } 
    } while (!flag);
       
    return 0;
}

//check the from left-up to right -down diagonal for finding four mathcing cells.
bool findTheConnectFour(int indexOfFull[],int column, char board[][MAXSIZE],int size,char symbol,int value){
    bool result=false;
    bool flag=true;
    int countOfLeftToUpMathcingCells=0;
    int countOfRihgtToDownMatchingCells=0;
    //first,it is scaned left-up board from current cell.
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(indexOfFull[column]+1-i,column-j,size)) {
            
            if (board[indexOfFull[column]+1-i][column-j]==symbol) ++countOfLeftToUpMathcingCells;
            else flag=false;
        }
        else break;
    }
    flag=true;
    //then,it is scanned right-down from current cell.
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(indexOfFull[column]+1+i,column+j,size)) {
            
            if (board[indexOfFull[column]+1+i][column+j]==symbol) ++countOfRihgtToDownMatchingCells;
            else flag=false;
        }
        else break;
    
    }
    if (countOfRihgtToDownMatchingCells+countOfLeftToUpMathcingCells>=3) {
        if (value==1)
        //Finding four matching cells converts to lowercase.
        tolowerFourLettersMatching(board,indexOfFull[column]+1,column,0,0,0,countOfLeftToUpMathcingCells,
                                                              countOfRihgtToDownMatchingCells,0,0,symbol);
        result=true;
    }
    return result;
}
//check the down vertical in order to find four mathcing cells
bool findTheConnectFour(int indexOfFull[],char board[][MAXSIZE],int column,char symbol,int size,int value) {
    bool result=false;
    bool flag=true;
    int counterMatchingCells=0;

    for (int i = indexOfFull[column]+2; i<= indexOfFull[column]+4 && flag; ++i){
        
        if(isCellLegal(i,column,size)) {
            if (board[i][column]==symbol) counterMatchingCells=counterMatchingCells+1;
            else flag=false;

        }
        else break;

    }
    if (counterMatchingCells>=3) {
        if (value==1)
        tolowerFourLettersMatching(board,indexOfFull[column]+1,column,counterMatchingCells,0,0,0,0,0,0,symbol);
        result=true;
    }

    return result;
}
//check the from left-down to right-up diagonal in order to find four mathcing cells
bool findTheConnectFour(int indexOfFull[],int column,char board[][MAXSIZE],char symbol,int size,int value){
    bool result=false;
    bool flag=true;
    int countOfLeftToDownMatchingCells=0;
    int countOfRightToUpMatchingCells=0;
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(indexOfFull[column]+1+i,column-j,size)) {
            
            if (board[indexOfFull[column]+1+i][column-j]==symbol) ++countOfLeftToDownMatchingCells;
            else flag=false;
        }
        else break;
    }
     flag=true;
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(indexOfFull[column]+1-i,column+j,size)) {
            
            if (board[indexOfFull[column]+1-i][column+j]==symbol) ++countOfRightToUpMatchingCells;
            else flag=false;
        }
        else break;
    }
    if (countOfRightToUpMatchingCells+countOfLeftToDownMatchingCells>=3) {
        if (value==1)
        tolowerFourLettersMatching(board,indexOfFull[column]+1,column,0,0,0,0,0,
                                countOfRightToUpMatchingCells,countOfLeftToDownMatchingCells,symbol);

        result=true;
    }

    return result;
}    
//check the lefthand-righthand horizontal in order to find matching cells.
bool findTheConnectFour(char symbol,int size,int indexOfFull[],int column,char board[][MAXSIZE],int value){
    bool result=false;
    bool flag=true;
    auto countOfLeftSideMatchingCells=0;
    auto countOfRightSideMatchingCells=0;
    for (int i = column-1; i >= column-3 && flag; --i) {
        if (isCellLegal(indexOfFull[column]+1,i,size)) {
            if (board[indexOfFull[column]+1][i]==symbol) ++countOfLeftSideMatchingCells;
            else flag=false;
        }
        else break;
    }
    flag=true;
    for (int i = column+1; i <= column+3 && flag; ++i) {
        if (isCellLegal(indexOfFull[column]+1,i,size)) {
            if (board[indexOfFull[column]+1][i]==symbol) ++countOfRightSideMatchingCells;
            else flag=false;
        }
        else break;
    }   
    countOfLeftSideMatchingCells+countOfRightSideMatchingCells;
    if (countOfLeftSideMatchingCells+countOfRightSideMatchingCells>=3) {
        if(value==1)
        tolowerFourLettersMatching(board,indexOfFull[column]+1,column,0,countOfLeftSideMatchingCells,
                                  countOfRightSideMatchingCells,0,0,0,0,symbol);
        result=true;
    }

    return result;
}
void gameUserViaUser(char board[][MAXSIZE],int &size,char orderOfPcOrPlayer){

    int indexOfEmptyCell[MAXSIZE]; //This array keep the indexes of empty cells of each column. 
    int counter=0;
    char symbol; // determine order of pc or user.
    int ppORpc; // game belongs to user-user or user-pc.
    bool flag=true;
    bool user1=false,user2=false,equality=false;
    decltype (size-1) y;
    y=size;
    for (int i=0; i<size; ++i)
         indexOfEmptyCell[i]=y-1; // it is provided first move go latest cell of each column.
    if (orderOfPcOrPlayer=='X' || orderOfPcOrPlayer=='N') {

        while(flag){
            if (size*size-3 > counter){
                symbol='X';
                ppORpc=3;
               user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
               // if ppORpc is 1 and symbol is X order belong to user1 and game is user-user.
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user1==true) flag=false;
               }
               // if ppORpc is 1 and symbol is O order belong to user2 and game is user-user.
               if (ppORpc==1 && symbol=='O') {
                   ppORpc=3;
                   counter=0;
                   user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user2==true) flag=false;
               }
               //// if ppORpc is 2 User-Computer function is called.
               if (ppORpc==2) {
                   gameUserViaComputer(board,size,symbol);
                   return;
               }
               ++counter;
               if (user1==true) flag=false;

               else {
                symbol='O';
                ppORpc=3;
                user2=move("User2 move:",indexOfEmptyCell,size,board,symbol, ppORpc);
                if (ppORpc==1 && symbol=='O') {
                    ppORpc=3;
                    counter=0;
                    user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                    if (user2==true) flag=false;
                }
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user1==true) flag=false;
               }            
                if (ppORpc==2) {
                    gameUserViaComputer(board,size,symbol);
                    return;
                }
                ++counter;
                if (user2==true) flag=false;            
               }
            }
             //it is checked wheather empty cells exist in case of equality.
            else {
                if (checkTheTotalEmpty(board,size)==false) flag=false, equality=true;

                else {
                symbol='X';
                ppORpc=3;
               user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user1==true) flag=false;
               }
               if (ppORpc==1 && symbol=='O') {
                   ppORpc=3;
                   counter=0;
                   user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user2==true) flag=false;
               }
               if (ppORpc==2) {
                   gameUserViaComputer(board,size,symbol);
                   return;
               }
               ++counter;
               if (user1==true) flag=false;

               else {
                symbol='O';
                ppORpc=3;
                user2=move("User2 move:",indexOfEmptyCell,size,board,symbol, ppORpc);
                if (ppORpc==1 && symbol=='O') {
                    ppORpc=3;
                    counter=0;
                    user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                    if (user2==true) flag=false;
                }
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user1==true) flag=false;
               }            
                if (ppORpc==2) {
                    gameUserViaComputer(board,size,symbol);
                    return;
                }
                ++counter;
                if (user2==true) flag=false;            
               }               
               }  
            }
        }
    }

    else if(orderOfPcOrPlayer=='O') {

        while(flag){
            if (size*size-3 > counter){
                symbol='O';
                ppORpc=0;
                user2=move("User2 move:",indexOfEmptyCell,size,board,symbol, ppORpc);
                if (ppORpc==1 && symbol=='O') {
                    ppORpc=0;
                    counter=0;
                    user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                    if (user2==true) flag=false;
                }
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=0;
                   counter=0;
                   user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (user1==true) flag=false;
               }            
                if (ppORpc==2) {
                    gameUserViaComputer(board,size,symbol);
                    return;
                }
                ++counter;
                if (user2==true) flag=false; 
               else {
                    symbol='X';
                    ppORpc=0;
                   user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                   if (ppORpc==1 && symbol=='X') {
                       ppORpc=0;
                       counter=0;
                       user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                       if (user1==true) flag=false;
                   }
                   if (ppORpc==1 && symbol=='O') {
                       ppORpc=0;
                       counter=0;
                       user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                       if (user2==true) flag=false;
                   }
                   if (ppORpc==2) {
                       gameUserViaComputer(board,size,symbol);
                       return;
                   }
                   ++counter;
                   if (user1==true) flag=false;
               }
            }
             //it is checked wheather empty cells exist in case of equality.
            else {
                if (checkTheTotalEmpty(board,size)==false) flag=false, equality=true;

                else {

                    symbol='O';
                    ppORpc=3;
                    user2=move("User2 move:",indexOfEmptyCell,size,board,symbol, ppORpc);
                    if (ppORpc==1 && symbol=='O') {
                        ppORpc=3;
                        counter=0;
                        user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                        if (user2==true) flag=false;
                    }
                   if (ppORpc==1 && symbol=='X') {
                       ppORpc=3;
                       counter=0;
                       user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                       if (user1==true) flag=false;
                   }            
                    if (ppORpc==2) {
                        gameUserViaComputer(board,size,symbol);
                        return;
                    }
                    ++counter;
                    if (user2==true) flag=false; 
                   else {

                        symbol='X';
                        ppORpc=3;
                       user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                       if (ppORpc==1 && symbol=='X') {
                           ppORpc=3;
                           counter=0;
                           user1=move("User1 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                           if (user1==true) flag=false;
                       }
                       if (ppORpc==1 && symbol=='O') {
                           ppORpc=3;
                           counter=0;
                           user2=move("User2 move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                           if (user2==true) flag=false;
                       }
                       if (ppORpc==2) {
                           gameUserViaComputer(board,size,symbol);
                           return;
                       }
                       ++counter;
                       if (user1==true) flag=false;
                   }               
               }  
            }
        }
    }
     showTheBoard(size,board);
     if (user1)          cout<<"User1 win the game."<<endl;
     else if (user2)     cout<<"User2 win the game."<<endl;
     else if(equality)   cout<<"Nobody win the game."<<endl;
}

void showTheBoard(const int size ,char board[][MAXSIZE]){

    printTheLabelBoard(size);
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j)
            cout <<board[i][j]<<" ";
        cout <<endl;
    }
        cout<<endl;
}
void printTheLabelBoard(int size){
    
    char letter='a';

    for (int i=0; i<size; ++i)
        cout << letter++<<" ";
    cout << endl;
    
}

const bool isCellLegal(int xCoordinate,int yCoordinate,int size){

    if (xCoordinate >= 0 && xCoordinate < size && yCoordinate >=0 && yCoordinate < size) return true;
    else return false;
        
}

void showTheBoard(char board[][MAXSIZE], const int size){
    
    printTheLabelBoard(size);

    for (int i=0; i<size; ++i){
        for (int j=0; j<size; ++j){
             
             board[i][j]='.';
             cout << board[i][j]<<" ";
        }
        cout << endl;
    }
    cout <<endl;
}

bool checkTheTotalEmpty(char board[][MAXSIZE],int size){
    
    bool flag=false;
    for (int i=0; i<size && !flag; ++i)
        for (int j=0; j<size && !flag; ++j)
            if (board[i][j]=='.') flag=true;
    return flag;
}

bool move(string str,int index[],int &size,char board[][MAXSIZE],char &symbol,int &ppORpc){
    
    bool flagForCorrect=false;
    char ch;
    string move;
    string file;
    int order;
    char player;
        do
        {
            cout << endl;
            cout <<str;
            cin >>move;
            allConvertsToLower(move);
            if (move=="save") {
                cin>>file;
                ofstream saving;
                saving.open(file);
                if (!saving) {
                   cerr<<"file is not  open."<<endl;
                   exit(1); 
                }
                saving<<size<<endl;
                if (ppORpc==3) {
                    saving<<1<<endl; //player to player.
                    ppORpc=1;
                } 
                if (ppORpc==4) {
                    saving<<2<<endl; //player to computer.
                    ppORpc=2;
                } 
                saving<<symbol<<endl;
                for (int i = 0; i < size; ++i){
                    for (int j = 0; j < size; ++j){
                         saving<<board[i][j];
                         }
                    saving << endl;
                }
             saving.close();
             return false; 
            }
            if (move=="load") {
                cin>>file;
                fstream load;
                load.open(file);
                if (!load)
                {
                   cerr<<"file is not  open."<<endl;
                   exit(1); 
                }
                load>>size;
                load<<endl;
                load>>order;
                load<<endl;
                load>>player;
                load<<endl;
                for (int i = 0; i < size; ++i){
                    for (int j = 0; j < size; ++j){
                         load>>board[i][j];
                    }
                    load<<endl;  
                }  
                load.close();
                ppORpc=order;
                symbol=player;
                showTheBoard(size,board);
                return false;
            }           
            cin.clear();
            cin.ignore(999,'\n'); 
            if (tolower(move[0]) >'a'+size-1){
                cerr<<"Wrong move!!"
                    <<"Please hit move again."<<endl;
            }
            else if (index[tolower(move[0])-'a']<0)
                cerr<<"This cells of column are all full."
                    <<"Please hit move again."<<endl;
            else 
                {
                    board[index[tolower(move[0])-'a']][tolower(move[0])-'a']=symbol;
                    --index[tolower(move[0])-'a'];
                    flagForCorrect=true;
                }
            showTheBoard(size,board);                                       
        } while (!flagForCorrect);

        return  findTheConnectFour(index,tolower(move[0])-'a',board,symbol,size,1) ||
                findTheConnectFour(index,tolower(move[0])-'a',board,size,symbol,1) ||
                findTheConnectFour(symbol,size,index,tolower(move[0])-'a',board,1) ||
                findTheConnectFour(index,board,tolower(move[0])-'a',symbol,size,1);
}

bool moveOfComputer(string str,int index[],int size,char board[][MAXSIZE],char symbol){

    bool flag=true;
    int move=0;
    
    //find four matching.
    for (int i = 0; i < size && flag; ++i) {
        if (index[i]>=0) {
            board[index[i]][i]=symbol;
            --index[i];
            if (findTheConnectFour(index,i,board,symbol,size,1) ||
                findTheConnectFour(index,i,board,size,symbol,1) ||
                findTheConnectFour(symbol,size,index,i,board,1) ||
                findTheConnectFour(index,board,i,symbol,size,1))  {
                flag=false;
                move=i;
            }
            else {
            ++index[i];
            board[index[i]][i]='.';
            }
        }

    }
    
    if (flag==false) {
        showTheBoard(size,board);
        cout<<"Move of Computer :"<< static_cast<char>(move+'a')<<endl;
        return true;
    }
    move=0;
    //prevent the four matching.
    for (int i = 0; i < size && flag; ++i) {
        if (index[i]>=0) {
            board[index[i]][i]='X';
            --index[i];
            if (findTheConnectFour(index,i,board,'X',size,0) ||
                findTheConnectFour(index,i,board,size,'X',0) ||
                findTheConnectFour('X',size,index,i,board,0) ||
                findTheConnectFour(index,board,i,'X',size,0)) {

                flag=false;
                board[index[i]+1][i]=symbol;
                move=i;
            }
            else {
                ++index[i];
                board[index[i]][i]='.';
            }
        }

    }    
    
    if (flag==false) {
        showTheBoard(size,board);
        cout<<"Move of Computer :"<< static_cast<char>(move+'a')<<endl;
        return false;
    }

    move=0;
    for (int i = 0; i < size && flag; ++i) {
        
        if (board[index[i]+1][i]==symbol) {
            board[index[i]][i]=symbol;
            move=i;
            flag=false;
            --index[i];
        }
        
        else if (isCellLegal(index[i],i-1,size) && isCellLegal(index[i]+1,i-1,size) && 
                 board[index[i]+1][i-1]!='.' && board[index[i]][i-1]=='.') {
           
            board[index[i-1]][i-1]=symbol;
            move=i-1;
            flag=false;  
            --index[i-1];      

        }
        
        else if (isCellLegal(index[i],i+1,size) && isCellLegal(index[i]+1,i+1,size) && 
                 board[index[i]+1][i+1]!='.' && board[index[i+1]][i+1]=='.') {
           
            board[index[i+1]][i+1]=symbol;
            move=i+1;
            flag=false;
            --index[i+1];        
        }        
       

    }

    if (flag==false) {
        showTheBoard(size,board); 
        cout<<"Move of Computer :"<<static_cast<char>(move+'a')<<endl;
        return false;
    }    
    move=0;
    // move random.
    for (int i = 0; i< size && flag; ++i) {

        if (index[i]>0) {
            if (index[size-1-i]==size-1) {
                board[index[size-1-i]][size-1-i]=symbol;
                --index[size-1-i];
                flag=false;
                move=size-1-i;
            }
            else {
                board[index[size-1-i]][size-1-i]=symbol;
                flag=false;
                move=size-1-i;
                --index[size-1-i];
            }
        }
    }
    showTheBoard(size,board);
    cout<<"Move of Computer:"<<static_cast<char>(move+'a')<<endl;
    return false;
}

void gameUserViaComputer(char board[][MAXSIZE],int &size,char orderOfPcOrPlayer){

    int indexOfEmptyCell[MAXSIZE];
    int counter=0;
    int ppORpc;
    char symbol;
    bool flag=true;
    bool user=false,computer=false,equality=false;
    for (int i=0; i<size; ++i)
        indexOfEmptyCell[i]=size-1;

    if (orderOfPcOrPlayer=='X' || orderOfPcOrPlayer=='N') {

            while(flag){
                if (size*size-3 > counter){
                    symbol='X';
                    ppORpc=4;
                    user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                    if (ppORpc==2 && symbol=='X') {
                        ppORpc=4;
                        counter=0;
                        user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                        if (user==true) flag=false; 
                    }
                    if (ppORpc==2 && symbol=='O') {
                         ppORpc=4;
                        counter=0;
                       computer=moveOfComputer("Computer move:",indexOfEmptyCell,size,board,'O');
                       ++counter;
                       if (computer==true) flag=false;
                    }
                    if (ppORpc==1) {
                        gameUserViaUser(board,size,symbol);
                        return;
                    }
                    ++counter;
                    if (user==true) flag=false; 

                   else {
                       computer=moveOfComputer("Computer move:",indexOfEmptyCell,size,board,'O');
                       ++counter;
                       if (computer==true) flag=false;
                   }
                }

                else {
                    if (checkTheTotalEmpty(board,size)==false) flag=false, equality=true;

                    else {
                        symbol='X';
                         ppORpc=4;
                        user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                        if (ppORpc==2 && symbol=='X') {
                            ppORpc=0;
                            counter=0;
                            user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                            if (user==true) flag=false; 
                        }
                        if (ppORpc==2 && symbol=='O') {
                            ppORpc=4;
                            user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                            if (user==true) flag=false;  
                        }
                        if (ppORpc==1) {
                            gameUserViaUser(board,size,symbol);
                            return;
                        }
                        ++counter;
                        if (user==true) flag=false;   
                        else {
                            computer=moveOfComputer("Computer move:",indexOfEmptyCell,size,board,'O');
                            ++counter;
                            if (computer==true) flag=false;
                        }               
                   }  
                }
            }
    }
    
    else if (orderOfPcOrPlayer=='O') {
            
            while(flag){
                if (size*size-3 > counter){
                    computer=moveOfComputer("Computer move:",indexOfEmptyCell,size,board,'O');
                    ++counter;
                    if (computer==true) flag=false;

                   else {
                        symbol='X';
                        ppORpc=4;
                        user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                        if (ppORpc==2 && symbol=='X') {
                            ppORpc=4;
                            counter=0;
                            user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                            if (user==true) flag=false; 
                        }
                        if (ppORpc==2 && symbol=='O') {
                            ppORpc=4;
                            counter=0;
                            user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                            if (user==true) flag=false;  
                        }
                        if (ppORpc==1) {
                            gameUserViaUser(board,size,symbol);
                            return;
                        }
                        ++counter;
                        if (user==true) flag=false;                       
                   }
                }

                else {
                    if (checkTheTotalEmpty(board,size)==false) flag=false, equality=true;

                    else {
                        
                        computer=moveOfComputer("Computer move:",indexOfEmptyCell,size,board,'O');
                        ++counter;
                        if (computer==true) flag=false;
                        else {
                            symbol='X';
                            ppORpc=4;
                            user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                            if (ppORpc==2 && symbol=='X') {
                                ppORpc=0;
                                counter=0;
                                user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                                if (user==true) flag=false; 
                            }
                            if (ppORpc==2 && symbol=='O') {
                                 ppORpc=4;
                                counter=0;
                                user=move("User move:",indexOfEmptyCell,size,board,symbol,ppORpc);
                                if (user==true) flag=false;  
                            }
                            if (ppORpc==1) {
                                gameUserViaUser(board,size,symbol);
                                return;
                            }
                            ++counter;
                            if (user==true) flag=false;                            
                        }               
                   }  
                }
            }
    }
     showTheBoard(size,board);
     if (computer)          cout<<"Computer win the game."<<endl;
     else if (user)     cout<<"User win the game."<<endl;
     else if(equality)   cout<<"Nobody win the game."<<endl;
}

void tolowerFourLettersMatching(char board[][MAXSIZE],int row,int &column,int down,int left,
                                int right,int left_up,int right_down,int right_up,int left_down,char symbol)
{


    if (left+right>=3) {
        for (int i = 0; i <= right; ++i)
             board[row][column+i]=tolower(symbol);

        for (int i = 0; i <= left; ++i)
            board[row][column-i]=tolower(symbol);
    }

    else if(down>=3) {
        for (int i = 0; i <= down; ++i)
            board[row+i][column]=tolower(symbol);
    }

    else if (left_up+right_down>=3) {
        for (int i = 0; i <= left_up; ++i)
             board[row-i][column-i]=tolower(symbol);
        for (int i = 0; i <= right_down; ++i)
            board[row+i][column+i]=tolower(symbol);
    }

    else if (left_down+right_up>=3) {
 
        for (int i = 0; i <= left_down; ++i)
            board[row+i][column-i]=tolower(symbol);
        for (int i = 0; i <= right_up; ++i)
            board[row-i][column+i]=tolower(symbol);
    }
}                                
bool takesTheSizeAndChooise(int &size,char &selection) {
    
    bool flag=true;
    bool flag1=true;
    do
    {
        cout << "Please enter the game board size"
             << "a range of 4 and 20 as even number:";
        cin >> size; 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999,'\n');
            return false;
        }

        else {
            if (size%2==0 && size>=4 && size<=20) {

                flag1=false;
                cout <<"To play player to player,press the   P type."<<endl
                     <<"To play player to computer,press the C type."<<endl;
               
                while(flag){
                    cout <<"Please enter your chooise:";
                    cin>>selection;

                    if (tolower(selection)=='c' || tolower(selection)=='p') {
                        
                        flag=false;

                    }
                    else cerr<<"Wrong chooise!!!"<<endl;
                }
            } 
        }      
    } while (flag1);
    
    return true;
}

void allConvertsToLower(string &array) {
    for (int i=0; i<array.length(); ++i)
        array[i]=tolower(array[i]);
}