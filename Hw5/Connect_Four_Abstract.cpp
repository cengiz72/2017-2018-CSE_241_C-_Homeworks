/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#include "ConnectFourAbstract.h"
ConnectFourAbstract::ConnectFourAbstract() : row(4),column(4){
    createNewBoard();
}
ConnectFourAbstract::~ConnectFourAbstract() {
    destroyBoard();
}

void ConnectFourAbstract::createNewBoard() {
    gameCells=new Cell *[get_Row()];
    for (int i = 0; i < get_Row(); i++) {
        gameCells[i] = new Cell[get_Column()];
    }
}
void ConnectFourAbstract::destroyBoard() {

    if (gameCells!=nullptr){
	    for (int i = 0; i < get_Row(); ++i)
	        delete [] gameCells[i];
	    delete [] gameCells;
    	gameCells=nullptr;
    }
}
int ConnectFourAbstract::get_Row() const {
    return row;
}
int ConnectFourAbstract::get_Column() const {
    return column;
}
char ConnectFourAbstract::get_ppORpc() const {
    return ppORpc;
}
void ConnectFourAbstract::set_Row(int witdh) {
    row=witdh;
}
void ConnectFourAbstract::set_Column(int length) {
    column=length;
}
void ConnectFourAbstract::set_ppORpc(char typeOfGame) {
    ppORpc=typeOfGame;
}
void ConnectFourAbstract::readFile(string &filename,int &ppORpc,char &playerType) {
    
    fstream load;
    int lengtH;
    int widtH;
    int order;
    int countOfLivingcellsOfCurrentObject=0;
    int countOfLivingcellsOfNewObject=0;
    char typeOfPlayer;
    char arr[100];
    load.open(filename);
    if (!load)
    {
       cerr<<"file is not  open."<<endl;
       return;
    }
    load>>lengtH;
    load<<endl;
    load>>widtH;
    load<<endl;
    load>>order;
    load<<endl;
    load>>typeOfPlayer;
    load<<endl;
    destroyBoard();
    set_Row(widtH);
    set_Column(lengtH);
    createNewBoard();
    for (int i = 0; i < get_Row(); ++i){
        load.getline(arr,99,'\n');
        for (int j = 0; j < get_Column(); ++j){
             gameCells[i][j].set_PlayerType(arr[j]);
             gameCells[i][j].set_row(i);
             gameCells[i][j].set_column(static_cast<char>('a'+j));
        }

    }
    load.close();
    ppORpc=order;
    playerType=typeOfPlayer;
    showTheBoard();
}
void ConnectFourAbstract::writeFile(string &filename,int &ppORpc,char &playerType) {
    ofstream saving;
    saving.open(filename);
    if (!saving) {
       cerr<<"file is not  open."<<endl;
       return;
    }
    saving<<get_Column()<<endl;//length of board
    saving<<get_Row()<<endl;//width of board
    if (ppORpc==3) {
        saving<<1<<endl; //player to player.
        ppORpc=1;
    } 
    if (ppORpc==4) {
        saving<<2<<endl; //player to computer.
        ppORpc=2;
    } 
    saving<<playerType<<endl;
    for (int i = 0; i < get_Row(); ++i){
        for (int j = 0; j < get_Column(); ++j){
             saving<<gameCells[i][j].get_PlayerType();
             }
        saving<<endl;     
    }
 saving.close();
 showTheBoard();
}
void ConnectFourAbstract::showTheBoard() const {
    cout<<endl;
    printTheLabelBoard();
    for (int i=0; i<get_Row(); ++i){
        for (int j=0; j<get_Column(); ++j)
           cout<<gameCells[i][j].get_PlayerType()<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void ConnectFourAbstract::printTheLabelBoard() const{
    
    char letter='a';
    for (int i=0; i<get_Column(); ++i)
        cout << letter++<<" ";
    cout << endl;
}

bool ConnectFourAbstract::takesTheSizeAndChooise(int &sizeW,int &sizeL,char &selection){
    
    bool flag1=true;
    bool flag2=true;
    bool flag3=true;
    
    do 
    {
        cout << "Please enter the weight size"
             << "a range of 4 and 26:";
        cin >> sizeW; 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999,'\n');
            return false;
        }
        else if(sizeW>=4) flag1=false;
    }while(flag1);
    
    do 
    {
        cout << "Please enter the length size"
             << "a range of 4 and 26:";
        cin >> sizeL; 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999,'\n');
            return false;
        }
        else if(sizeL>=4 && sizeL<=26) flag2=false;
    }while(flag2);

    do 
    {
        cout <<"To play player to player,press the   P type."<<endl
             <<"To play player to computer,press the C type."<<endl;

        
            cout <<"Please enter your chooise:";
            cin>>selection;
        if (tolower(selection)=='c' || tolower(selection)=='p') flag3=false;
        else cerr<<"Wrong chooise!!!"<<endl;
    }while(flag3);
    
    return true;
}

bool ConnectFourAbstract::determineTheWinWho(char type,int current,int position,int valuE){
    
   return  findTheConnectFour(current,type,valuE,position) ||
           findTheConnectFour(type,current,valuE,position) ||
           findTheConnectFour(valuE,position,type,current) ||
           findTheConnectFour(current,valuE,position,type);
}

bool ConnectFourAbstract::isCellLegal(int xCoordinate,int yCoordinate) const {
    if (xCoordinate >= 0 && xCoordinate < get_Row() && yCoordinate >=0 
                                                    && yCoordinate < get_Column())
        return true;
    else 
        return false;
}
//check the from left-up to right -down diagonal for finding four mathcing cells.
bool ConnectFourAbstract::findTheConnectFour(int currentRow,char symbol,int value,int column) {
    bool result=false;
    bool flag=true;
    int countOfLeftToUpMathcingCells=0;
    int countOfRihgtToDownMatchingCells=0;
    //first,it is scaned left-up board from current cell.
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(currentRow-i,column-j)) {
            
            if (gameCells[currentRow-i][column-j].get_PlayerType()==symbol) ++countOfLeftToUpMathcingCells;
            else flag=false;
        }
        else break;
    }
    flag=true;
    //then,it is scanned right-down from current cell.
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(currentRow+i,column+j)) {
            
            if (gameCells[currentRow+i][column+j].get_PlayerType()==symbol) ++countOfRihgtToDownMatchingCells;
            else flag=false;
        }
        else break;
    
    }
    if (countOfRihgtToDownMatchingCells+countOfLeftToUpMathcingCells>=3) {
        if (value==1)
        //Finding four matching cells converts to lowercase.
        tolowerFourLettersMatching(currentRow,column,0,0,0,countOfLeftToUpMathcingCells,
                                                              countOfRihgtToDownMatchingCells,0,0,symbol);
        result=true;
    }
    return result;
}
//check the down vertical in order to find four mathcing cells
bool ConnectFourAbstract::findTheConnectFour(char symbol,int currentRow,int value,int column) {
    bool result=false;
    bool flag=true;
    int counterMatchingCells=0;

    for (int i = currentRow+1; i<= currentRow+3 && flag; ++i){
        
        if(isCellLegal(i,column)) {
            if (gameCells[i][column].get_PlayerType()==symbol) counterMatchingCells=counterMatchingCells+1;
            else flag=false;

        }
        else break;

    }
    if (counterMatchingCells>=3) {
        if (value==1)
        tolowerFourLettersMatching(currentRow,column,counterMatchingCells,0,0,0,0,0,0,symbol);
        result=true;
    }

    return result;
}
//check the from left-down to right-up diagonal in order to find four mathcing cells
bool ConnectFourAbstract::findTheConnectFour(int value,int column,char symbol,int currentRow) {
    bool result=false;
    bool flag=true;
    int countOfLeftToDownMatchingCells=0;
    int countOfRightToUpMatchingCells=0;
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(currentRow+i,column-j)) {
            
            if (gameCells[currentRow+i][column-j].get_PlayerType()==symbol) ++countOfLeftToDownMatchingCells;
            else flag=false;
        }
        else break;
    }
     flag=true;
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(currentRow-i,column+j)) {
            
            if (gameCells[currentRow-i][column+j].get_PlayerType()==symbol) ++countOfRightToUpMatchingCells;
            else flag=false;
        }
        else break;
    }
    if (countOfRightToUpMatchingCells+countOfLeftToDownMatchingCells>=3) {
        if (value==1)
        tolowerFourLettersMatching(currentRow,column,0,0,0,0,0,
                                countOfRightToUpMatchingCells,countOfLeftToDownMatchingCells,symbol);

        result=true;
    }

    return result;
}
//check the lefthand-righthand horizontal in order to find matching cells.
bool ConnectFourAbstract::findTheConnectFour(int currentRow,int value,int column,char symbol) {
    bool result=false;
    bool flag=true;
    auto countOfLeftSideMatchingCells=0;
    auto countOfRightSideMatchingCells=0;
    for (int i = column-1; i >= column-3 && flag; --i) {
        if (isCellLegal(currentRow,i)) {
            if (gameCells[currentRow][i].get_PlayerType()==symbol) ++countOfLeftSideMatchingCells;
            else flag=false;
        }
        else break;
    }
    flag=true;
    for (int i = column+1; i <= column+3 && flag; ++i) {
        if (isCellLegal(currentRow,i)) {
            if (gameCells[currentRow][i].get_PlayerType()==symbol) ++countOfRightSideMatchingCells;
            else flag=false;
        }
        else break;
    }   
    if (countOfLeftSideMatchingCells+countOfRightSideMatchingCells>=3) {
        if(value==1)
        tolowerFourLettersMatching(currentRow,column,0,countOfLeftSideMatchingCells,
                                  countOfRightSideMatchingCells,0,0,0,0,symbol);
        result=true;
    }

    return result;
}
bool ConnectFourAbstract::isCellAvaiable(int row) const {
    bool flag=false;
    for (int i=get_Row()-1; i>=0 && !flag; --i)
        if (gameCells[i][row].get_PlayerType()=='.') flag=true;
    return flag;
}
bool ConnectFourAbstract::getRowOfAvaiable(int &row,char playerType) const {
    bool flag=false;
    for (int i=get_Row()-1; i>=0 && !flag; --i)
        if (gameCells[i][row].get_PlayerType()==playerType) {
            row=i;
            flag=true;
        }
    return flag;
}
bool ConnectFourAbstract::checkEmptyIsStillExisting() const {
    for (int i=0; i<get_Row(); ++i)
        for (int j=0; j<get_Column(); ++j)
            if (gameCells[i][j].get_PlayerType()=='.') return true;
    return false;    
}

void ConnectFourAbstract::tolowerFourLettersMatching(int row,int &column,int down,int left,int right,
                                    int left_up,int right_down,int right_up,int left_down,char symbol) 
{
    if (left+right>=3) {
        for (int i = 0; i <= right; ++i)
             gameCells[row][column+i].set_PlayerType(tolower(symbol));

        for (int i = 0; i <= left; ++i)
            gameCells[row][column-i].set_PlayerType(tolower(symbol));
    }

    else if(down>=3) {
        for (int i = 0; i <= down; ++i)
            gameCells[row+i][column].set_PlayerType(tolower(symbol));
    }

    else if (left_up+right_down>=3) {
        for (int i = 0; i <= left_up; ++i)
            gameCells[row-i][column-i].set_PlayerType(tolower(symbol));
        for (int i = 0; i <= right_down; ++i)
            gameCells[row+i][column+i].set_PlayerType(tolower(symbol));
    }

    else if (left_down+right_up>=3) {
 
        for (int i = 0; i <= left_down; ++i)
            gameCells[row+i][column-i].set_PlayerType(tolower(symbol));
        for (int i = 0; i <= right_up; ++i)
            gameCells[row-i][column+i].set_PlayerType(tolower(symbol));
    }

}

void ConnectFourAbstract::allConvertsToLower(string &array) {
    for (int i=0; i<array.length(); ++i)
        array[i]=tolower(array[i]);
}
//move for players.
bool ConnectFourAbstract::move(string str,char &symbol,int &ppORpc){
    
    bool flagForCorrect=false;
    string move;
    string file;
    int rowOfCell;
        do
        {   cout << endl;
            showTheBoard();
            cout << endl;
            cout <<str;
            cin >>move;
            if (cin.eof())
            {
                cout<<"EOF is handled!!!"<<endl;
                cout<<"Program is over."<<endl;
                exit(1);
            }
            allConvertsToLower(move);
            if (move=="save") {
                cin>>file;
                if (cin.eof())
                {
                    cout<<"EOF is handled!!!"<<endl;
                    cout<<"Program is over."<<endl;
                    exit(1);
                }
                writeFile(file,ppORpc,symbol);
                cin.clear();
                cin.ignore(999,'\n');
                return false; 
            }
            if (move=="load") {
                cin>>file;  
                if (cin.eof())
                {
                    cout<<"EOF is handled!!!"<<endl;
                    cout<<"Program is over."<<endl;
                    exit(1);
                }              
                readFile(file,ppORpc,symbol);
                cin.clear();
                cin.ignore(999,'\n');
                return false;
            }           
            if (static_cast<int>(move[0]) > static_cast<int>('a'+get_Column()-1)){
                cerr<<"Wrong move!!"
                    <<"Please hit move again."<<endl;
            }
            else if (!isCellAvaiable(static_cast<int>(move[0]-'a')))
                cerr<<"This cells of column are all full."
                    <<"Please hit move again."<<endl;
            else {
               rowOfCell=play(move[0],symbol);
               flagForCorrect=true;
            }
        } while (!flagForCorrect);
         showTheBoard();
        if (determineTheWinWho(symbol,rowOfCell,static_cast<int>(move[0]-'a'),1)){
            showTheBoard();
            return true;
        }
        else return false; 
}
//move for computer.
bool ConnectFourAbstract::moveOfComputer(string str,char symbol){
    
    bool flag=true;
    int move=0;
    int row;
    int otherRow;
    int randomNumber;
    //find four matching.
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.')) {
            gameCells[row][i].set_PlayerType(symbol);
            if (determineTheWinWho(symbol,row,i,1))  {
                flag=false;
                move=i;
            }
            else {
                gameCells[row][i].set_PlayerType('.');
            }
        }

    }
    
    if (flag==false) {
        showTheBoard();
        cout<<"Move of Computer :"<< static_cast<char>(move+'a')<<endl;
        return true;
    }
    move=0;
    //prevent the four matching.
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.')) {
            gameCells[row][i].set_PlayerType('X');
            if (determineTheWinWho('X',row,i,0))  {
                flag=false;
                gameCells[row][i].set_PlayerType(symbol);
                move=i;
            }
            else {
                gameCells[row][i].set_PlayerType('.');
            }
        }

    }
    if (flag==false) {
        showTheBoard();
        cout<<"Move of Computer :"<< static_cast<char>(move+'a')<<endl;
        return false;
    }

    move=0;
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.') && isCellLegal(row+1,i) && isCellLegal(row+2,i) &&
		gameCells[row+1][i].get_PlayerType()==symbol && gameCells[row+2][i].get_PlayerType()==symbol) {
		    gameCells[row][i].set_PlayerType(symbol);
		    move=i;
		    flag=false;
		    row=i;
	    }

        else if (getRowOfAvaiable(row,'.') && isCellLegal(row+1,i)
                  && gameCells[row+1][i].get_PlayerType()==symbol){
            gameCells[row][i].set_PlayerType(symbol);
            move=i;
            flag=false;
            row=i;
        }

    }

    
    if (flag==false) {
        showTheBoard(); 
        cout<<"Move of Computer :"<<static_cast<char>(move+'a')<<endl;
        return false;
    }    
    move=0;
    // move random.
    do
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0,get_Column()-1);
        randomNumber=dist(mt);
        row=randomNumber;
        if (isCellAvaiable(randomNumber)) {
            getRowOfAvaiable(row,'.');
            gameCells[row][randomNumber].set_PlayerType(symbol);
            flag=false;
            move=randomNumber;
        }
    }while(flag);

    showTheBoard();
    cout<<"Move of Computer:"<<static_cast<char>(move+'a')<<endl;
    return false;
}

void ConnectFourAbstract::userToUser(char orderOfPcOrPlayer ) {
    
    int counter=0;
    char symbol; // determine order of pc or user.
    int ppORpc; // game belongs to user-user or user-pc.
    bool flag=true;
    bool user1=false,user2=false,equality=false;
    if (orderOfPcOrPlayer=='X' || orderOfPcOrPlayer=='N') {

        while(flag){
            if (get_Column()*get_Row()-3 > counter){
                symbol='X';
                ppORpc=3;
               user1=move("User1 move:",symbol,ppORpc);
               // if ppORpc is 1 and symbol is X order belong to user1 and game is user-user.
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",symbol,ppORpc);
                   if (user1==true) flag=false;
               }
               // if ppORpc is 1 and symbol is O order belong to user2 and game is user-user.
               if (ppORpc==1 && symbol=='O') {
                   ppORpc=3;
                   counter=0;
                   user2=move("User2 move:",symbol,ppORpc);
                   if (user2==true) flag=false;
               }
               //// if ppORpc is 2 User-Computer function is called.
               if (ppORpc==2) {
                   userToComputer(symbol);
                   return;
               }
               ++counter;
               if (user1==true) flag=false;

               else {
                symbol='O';
                ppORpc=3;
                user2=move("User2 move:",symbol, ppORpc);
                if (ppORpc==1 && symbol=='O') {
                    ppORpc=3;
                    counter=0;
                    user2=move("User2 move:",symbol,ppORpc);
                    if (user2==true) flag=false;
                }
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",symbol,ppORpc);
                   if (user1==true) flag=false;
               }            
                if (ppORpc==2) {
                    userToComputer(symbol);
                    return;
                }
                ++counter;
                if (user2==true) flag=false;            
               }
            }
             //it is checked wheather empty cells exist in case of equality.
            else {
                if (checkEmptyIsStillExisting()==false) flag=false, equality=true;

                else {
                symbol='X';
                ppORpc=3;
               user1=move("User1 move:",symbol,ppORpc);
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",symbol,ppORpc);
                   if (user1==true) flag=false;
               }
               if (ppORpc==1 && symbol=='O') {
                   ppORpc=3;
                   counter=0;
                   user2=move("User2 move:",symbol,ppORpc);
                   if (user2==true) flag=false;
               }
               if (ppORpc==2) {
                   userToComputer(symbol);
                   return;
               }
               ++counter;
               if (user1==true) flag=false;

               else {
                symbol='O';
                ppORpc=3;
                user2=move("User2 move:",symbol, ppORpc);
                if (ppORpc==1 && symbol=='O') {
                    ppORpc=3;
                    counter=0;
                    user2=move("User2 move:",symbol,ppORpc);
                    if (user2==true) flag=false;
                }
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=3;
                   counter=0;
                   user1=move("User1 move:",symbol,ppORpc);
                   if (user1==true) flag=false;
               }            
                if (ppORpc==2) {
                    userToComputer(symbol);
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
            if (get_Column()*get_Row()-3 > counter){
                symbol='O';
                ppORpc=0;
                user2=move("User2 move:",symbol, ppORpc);
                if (ppORpc==1 && symbol=='O') {
                    ppORpc=0;
                    counter=0;
                    user2=move("User2 move:",symbol,ppORpc);
                    if (user2==true) flag=false;
                }
               if (ppORpc==1 && symbol=='X') {
                   ppORpc=0;
                   counter=0;
                   user1=move("User1 move:",symbol,ppORpc);
                   if (user1==true) flag=false;
               }            
                if (ppORpc==2) {
                    userToComputer(symbol);
                    return;
                }
                ++counter;
                if (user2==true) flag=false; 
               else {
                    symbol='X';
                    ppORpc=0;
                   user1=move("User1 move:",symbol,ppORpc);
                   if (ppORpc==1 && symbol=='X') {
                       ppORpc=0;
                       counter=0;
                       user1=move("User1 move:",symbol,ppORpc);
                       if (user1==true) flag=false;
                   }
                   if (ppORpc==1 && symbol=='O') {
                       ppORpc=0;
                       counter=0;
                       user2=move("User2 move:",symbol,ppORpc);
                       if (user2==true) flag=false;
                   }
                   if (ppORpc==2) {
                       userToComputer(symbol);
                       return;
                   }
                   ++counter;
                   if (user1==true) flag=false;
               }
            }
             //it is checked wheather empty cells exist in case of equality.
            else {
                if (checkEmptyIsStillExisting()==false) flag=false, equality=true;

                else {

                    symbol='O';
                    ppORpc=3;
                    user2=move("User2 move:",symbol, ppORpc);
                    if (ppORpc==1 && symbol=='O') {
                        ppORpc=3;
                        counter=0;
                        user2=move("User2 move:",symbol,ppORpc);
                        if (user2==true) flag=false;
                    }
                   if (ppORpc==1 && symbol=='X') {
                       ppORpc=3;
                       counter=0;
                       user1=move("User1 move:",symbol,ppORpc);
                       if (user1==true) flag=false;
                   }            
                    if (ppORpc==2) {
                        userToComputer(symbol);
                        return;
                    }
                    ++counter;
                    if (user2==true) flag=false; 
                   else {

                        symbol='X';
                        ppORpc=3;
                       user1=move("User1 move:",symbol,ppORpc);
                       if (ppORpc==1 && symbol=='X') {
                           ppORpc=3;
                           counter=0;
                           user1=move("User1 move:",symbol,ppORpc);
                           if (user1==true) flag=false;
                       }
                       if (ppORpc==1 && symbol=='O') {
                           ppORpc=3;
                           counter=0;
                           user2=move("User2 move:",symbol,ppORpc);
                           if (user2==true) flag=false;
                       }
                       if (ppORpc==2) {
                           userToComputer(symbol);
                           return;
                       }
                       ++counter;
                       if (user1==true) flag=false;
                   }               
               }  
            }
        }
    }
    showTheBoard();
     if (user1)          cout<<"User1 win the game."<<endl;
     else if (user2)     cout<<"User2 win the game."<<endl;
     else if(equality)   cout<<"Nobody win the game."<<endl;    
}
void ConnectFourAbstract::userToComputer(char orderOfPcOrPlayer) {
    int counter=0;
    int ppORpc;
    int computer;
    char symbol;
    bool flag=true;
    bool user=false,equality=false;
    
    if (orderOfPcOrPlayer=='X' || orderOfPcOrPlayer=='N') {

            while(flag){
                if (get_Column()*get_Row()-3> counter){
                    symbol='X';
                    ppORpc=4;
                    user=move("User move:",symbol,ppORpc);
                    if (ppORpc==2 && symbol=='X') {
                        ppORpc=4;
                        counter=0;
                        user=move("User move:",symbol,ppORpc);
                        if (user==true) flag=false; 
                    }
                    if (ppORpc==2 && symbol=='O') {
                         ppORpc=4;
                        counter=0;
                       computer=play();
                       ++counter;
                       if (computer==1) flag=false;
                    }
                    if (ppORpc==1) {
                        userToUser(symbol);
                        return;
                    }
                    ++counter;
                    if (user==true) flag=false; 

                   else {
                       computer=play();
                       ++counter;
                       if (computer==1) flag=false;
                   }
                }

                else {
                    if (checkEmptyIsStillExisting()==false) flag=false, equality=true;

                    else {
                        symbol='X';
                         ppORpc=4;
                        user=move("User move:",symbol,ppORpc);
                        if (ppORpc==2 && symbol=='X') {
                            ppORpc=0;
                            counter=0;
                            user=move("User move:",symbol,ppORpc);
                            if (user==true) flag=false; 
                        }
                        if (ppORpc==2 && symbol=='O') {
                            ppORpc=4;
                            user=move("User move:",symbol,ppORpc);
                            if (user==true) flag=false;  
                        }
                        if (ppORpc==1) {
                           userToUser(symbol);
                            return;
                        }
                        ++counter;
                        if (user==true) flag=false;   
                        else {
                            computer=play();
                            ++counter;
                            if (computer==1) flag=false;
                        }               
                   }  
                }
            }
    }
    
    else if (orderOfPcOrPlayer=='O') {
            
            while(flag){
                if (get_Column()*get_Row()-3> counter){
                    computer=play();
                    ++counter;
                    if (computer==1) flag=false;

                   else {
                        symbol='X';
                        ppORpc=4;
                        user=move("User move:",symbol,ppORpc);
                        if (ppORpc==2 && symbol=='X') {
                            ppORpc=4;
                            counter=0;
                            user=move("User move:",symbol,ppORpc);
                            if (user==true) flag=false; 
                        }
                        if (ppORpc==2 && symbol=='O') {
                            ppORpc=4;
                            counter=0;
                            user=move("User move:",symbol,ppORpc);
                            if (user==true) flag=false;  
                        }
                        if (ppORpc==1) {
                            userToUser(symbol);
                            return;
                        }
                        ++counter;
                        if (user==true) flag=false;                       
                   }
                }

                else {
                    if (checkEmptyIsStillExisting()==false) flag=false, equality=true;

                    else {
                        
                        computer=play();
                        ++counter;
                        if (computer==1) flag=false;
                        else {
                            symbol='X';
                            ppORpc=4;
                            user=move("User move:",symbol,ppORpc);
                            if (ppORpc==2 && symbol=='X') {
                                ppORpc=0;
                                counter=0;
                                user=move("User move:",symbol,ppORpc);
                                if (user==true) flag=false; 
                            }
                            if (ppORpc==2 && symbol=='O') {
                                 ppORpc=4;
                                counter=0;
                                user=move("User move:",symbol,ppORpc);
                                if (user==true) flag=false;  
                            }
                            if (ppORpc==1) {
                                userToUser(symbol);
                                return;
                            }
                            ++counter;
                            if (user==true) flag=false;                            
                        }               
                   }  
                }
            }
    }
     showTheBoard();
     if (computer==1)   cout<<"Computer win the game."<<endl;
     else if (user)     cout<<"User win the game."<<endl;
     else if(equality)  cout<<"Nobody win the game."<<endl; 
}
int  ConnectFourAbstract::play() {
    int result;
    if (moveOfComputer("Computer move:",'O')) result=1;
    else result=0;
    
    return result;
}
int  ConnectFourAbstract::play(char position,char user1ORUser2) {
    int currentYcoordinate=0;
    bool flag=true;
    for (int i=get_Row()-1; i>=0 && flag; --i) {
        if (gameCells[i][static_cast<int>(position-'a')].get_PlayerType()=='.') {
            gameCells[i][static_cast<int>(position-'a')].set_PlayerType(user1ORUser2);
            currentYcoordinate=gameCells[i][static_cast<int>(position-'a')].get_row();
            flag=false;
        }
    }
    return currentYcoordinate;
}
void  ConnectFourAbstract::playGame() {
    int witdH;
    int lengtH;
    char chooise;
    bool flag=true;
    while(flag) {
        if(takesTheSizeAndChooise(witdH,lengtH,chooise)) flag=false;
    }
    set_Column(lengtH);
    set_Row(witdH);
    set_ppORpc(tolower(chooise));
    createNewBoard();
    initializeBoard();
    showTheBoard();
    if (tolower(chooise)=='p') userToUser();
    else userToComputer();
}

void ConnectFourAbstract::initializeBoard() {

    for (int i=0; i<get_Row(); i++) {
        for (int j=0; j<get_Column(); j++){
            gameCells[i][j].set_PlayerType('.');
            gameCells[i][j].set_row(i);
            gameCells[i][j].set_column(static_cast<char>(j+'a'));
        }
    }
}