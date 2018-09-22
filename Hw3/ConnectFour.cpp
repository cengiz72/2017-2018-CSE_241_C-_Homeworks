#include "ConnectFour.h"

int ConnectFour::Cell::livingCells = 0;

ConnectFour::ConnectFour() : length(4) , width(4),ppORpc('N')
{/*Body intentionally empty*/}

ConnectFour::ConnectFour(int width) : width(width),length(4),ppORpc('N') 
{/*Body intentionally empty*/}

ConnectFour::ConnectFour(int width, int length): length(length) , width(width),ppORpc('N')
{/*Body intentionally empty*/}

ConnectFour::Cell::Cell() : typeOfPlayer('.') 
{/*Body intentionally empty*/}
inline char ConnectFour::Cell::get_column() const{
    return column;
}
inline int ConnectFour::Cell:: get_row() const {
    return row;
}
inline char ConnectFour::Cell::get_PlayerType() const {
    return typeOfPlayer;
}
inline void ConnectFour::Cell:: set_column(char yCoordinate) {

    column=yCoordinate;
}
inline void ConnectFour::Cell::set_row(int xCoordinate) {
    row=xCoordinate;
}
inline void ConnectFour::Cell::set_PlayerType(char player) {
    typeOfPlayer=player;
}
inline  void ConnectFour::Cell::set_livingCells(int count){
    livingCells += count;
}
inline int ConnectFour::get_width() const {
    return width;
}
inline int ConnectFour::get_length() const {
    return length;
}

inline  int ConnectFour::Cell::get_livingCells() {
    return livingCells;
}
char ConnectFour::get_ppORpc() const {
    return ppORpc; 
}
inline void ConnectFour::set_width(int a) {
    width=a;
}
inline void ConnectFour::set_length(int b) {
    length=b;
}
void ConnectFour::set_ppORpc(char typeOfGame) {
    ppORpc=typeOfGame;
}
void ConnectFour::readFile(string &filename,int &ppORpc,char &playerType) {
    fstream load;
    int lengtH;
    int widtH;
    int order;
    int countOfLivingcellsOfCurrentObject=0;
    int countOfLivingcellsOfNewObject=0;
    char typeOfPlayer;
    char symbol;
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
    for (int i = 0; i < get_width(); ++i)
 		for (int j = 0; j < get_length(); ++j)
 			if (gameCells[i][j].get_PlayerType()!='.') ++countOfLivingcellsOfCurrentObject;

    set_width(widtH);
    set_length(lengtH);
    resizeTheVector(); //yeni vektor create edildi.
    for (int i = 0; i < get_width(); ++i){
        for (int j = 0; j < get_length(); ++j){
             load>>symbol;
             if (symbol!='.') ++countOfLivingcellsOfNewObject;
             gameCells[i][j].set_PlayerType(symbol);
             gameCells[i][j].set_row(i);
             gameCells[i][j].set_column(static_cast<char>('a'+j));
        }
        load<<endl;  
    }
    ConnectFour::Cell::set_livingCells(countOfLivingcellsOfNewObject-countOfLivingcellsOfCurrentObject);
    load.close();
    ppORpc=order;
    playerType=typeOfPlayer;
    showTheBoard();
}
void ConnectFour::writeFile(string &filename,int &ppORpc,char &playerType) {
    ofstream saving;
    saving.open(filename);
    if (!saving) {
       cerr<<"file is not  open."<<endl;
       return;
    }
    saving<<get_length()<<endl;//length of board
    saving<<get_width()<<endl;//width of board
    if (ppORpc==3) {
        saving<<1<<endl; //player to player.
        ppORpc=1;
    } 
    if (ppORpc==4) {
        saving<<2<<endl; //player to computer.
        ppORpc=2;
    } 
    saving<<playerType<<endl;
    for (int i = 0; i < get_width(); ++i){
        for (int j = 0; j < get_length(); ++j){
             saving<<gameCells[i][j].get_PlayerType();
             }
        saving << endl;
    }
 saving.close();
}
void ConnectFour::initializeBoard() {
    resizeTheVector();
    for (int i=0; i< get_width(); ++i)
        for (int j=0; j<get_length(); ++j) {
            gameCells[i][j].set_row(i);
            gameCells[i][j].set_column(static_cast<char>('a'+i));
        }
}
void ConnectFour::showTheBoard() const {
    printTheLabelBoard();
    for (int i=0; i<get_width(); ++i){
        for (int j=0; j<get_length(); ++j)
           cout<<gameCells[i][j].get_PlayerType()<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void ConnectFour::resizeTheVector() {
    gameCells.resize(get_width());
    for (int i=0; i<get_width(); ++i)
        gameCells[i].resize(get_length());
}
int  ConnectFour::play() {
    int result;
    if (moveOfComputer("Computer move:",'O')) result=1;
    else result=0;
    
    return result;
}
int  ConnectFour::play(char position,char user1ORUser2) {
    int currentYcoordinate=0;
    bool flag=true;
    for (int i=get_width()-1; i>=0 && flag; --i) {
        if (gameCells[i][static_cast<int>(position-'a')].get_PlayerType()=='.') {
            gameCells[i][static_cast<int>(position-'a')].set_PlayerType(user1ORUser2);
            currentYcoordinate=gameCells[i][static_cast<int>(position-'a')].get_row();
            flag=false;
            ConnectFour::Cell::set_livingCells(1);
        }
    }
    return currentYcoordinate;
}
void ConnectFour::playGame() {
    int witdH;
    int lengtH;
    char chooise;
    bool flag=true;
    while(flag) {
        if(takesTheSizeAndChooise(witdH,lengtH,chooise)) flag=false;
    }
    set_length(lengtH);
    set_width(witdH);
    set_ppORpc(tolower(chooise));
    initializeBoard();
    showTheBoard();
    if (tolower(chooise)=='p') userToUser();
    else userToComputer();

    
}
void ConnectFour::printTheLabelBoard() const{
    
    char letter='a';
    for (int i=0; i<get_length(); ++i)
        cout << letter++<<" ";
    cout << endl;
}
void ConnectFour::userToUser(char orderOfPcOrPlayer ) {
    
    int counter=0;
    char symbol; // determine order of pc or user.
    int ppORpc; // game belongs to user-user or user-pc.
    bool flag=true;
    bool user1=false,user2=false,equality=false;
    if (orderOfPcOrPlayer=='X' || orderOfPcOrPlayer=='N') {

        while(flag){
            if (get_length()*get_width()-3 > counter){
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
            if (get_length()*get_width()-3 > counter){
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
void ConnectFour::userToComputer(char orderOfPcOrPlayer) {
    int counter=0;
    int ppORpc;
    int computer;
    char symbol;
    bool flag=true;
    bool user=false,equality=false;
    
    if (orderOfPcOrPlayer=='X' || orderOfPcOrPlayer=='N') {

            while(flag){
                if (get_length()*get_width()-3> counter){
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
                if (get_length()*get_width()-3> counter){
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
bool ConnectFour::takesTheSizeAndChooise(int &sizeW,int &sizeL,char &selection){
    
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
bool ConnectFour::determineTheWinWho(char type,int current,int position,int valuE){
    
   return  findTheConnectFour(current,type,valuE,position) ||
           findTheConnectFour(type,current,valuE,position) ||
           findTheConnectFour(valuE,position,type,current) ||
           findTheConnectFour(current,valuE,position,type);
}
bool ConnectFour::findTheBetter(const ConnectFour &other) const {

}
bool ConnectFour::isCellLegal(int xCoordinate,int yCoordinate) const {
    if (xCoordinate >= 0 && xCoordinate < get_width() && yCoordinate >=0 && yCoordinate < get_length() )
        return true;
    else 
        return false;
}
//check the from left-up to right -down diagonal for finding four mathcing cells.
bool ConnectFour::findTheConnectFour(int currentRow,char symbol,int value,int column) {
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
bool ConnectFour::findTheConnectFour(char symbol,int currentRow,int value,int column) {
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
bool ConnectFour::findTheConnectFour(int value,int column,char symbol,int currentRow) {
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
bool ConnectFour::findTheConnectFour(int currentRow,int value,int column,char symbol) {
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
bool ConnectFour::isCellAvaiable(int row) const {
    bool flag=false;
    for (int i=get_width()-1; i>=0 && !flag; --i)
        if (gameCells[i][row].get_PlayerType()=='.') flag=true;
    return flag;
}
bool ConnectFour::getRowOfAvaiable(int &row,char playerType) const {
    bool flag=false;
    for (int i=get_width()-1; i>=0 && !flag; --i)
        if (gameCells[i][row].get_PlayerType()==playerType) {
            row=i;
            flag=true;
        }
    return flag;
}
bool ConnectFour::checkEmptyIsStillExisting() const {
    for (int i=0; i<get_width(); ++i)
        for (int j=0; j<get_length(); ++j)
            if (gameCells[i][j].get_PlayerType()=='.') return true;
    return false;    
}

void ConnectFour::tolowerFourLettersMatching(int row,int &column,int down,int left,int right,
                                    int left_up,int right_down,int right_up,int left_down,char symbol) {
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

void ConnectFour::allConvertsToLower(string &array) {
    for (int i=0; i<array.length(); ++i)
        array[i]=tolower(array[i]);
}
bool ConnectFour::move(string str,char &symbol,int &ppORpc){
    
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
            allConvertsToLower(move);
            if (move=="save") {
                cin>>file;
                writeFile(file,ppORpc,symbol);
                cin.clear();
                cin.ignore(999,'\n'); 
                return false; 
            }
            if (move=="load") {
                cin>>file;                
                readFile(file,ppORpc,symbol);
                cin.clear();
                cin.ignore(999,'\n'); 
                return false;
            }           
            if (static_cast<int>(move[0]) > static_cast<int>('a'+get_length()-1)){
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
         cout<<" Total living cells :"<<ConnectFour::Cell::get_livingCells()<<"\n\n";
        if (determineTheWinWho(symbol,rowOfCell,static_cast<int>(move[0]-'a'),1)){
            showTheBoard();
            return true;
        }
        else return false; 
}
bool ConnectFour::moveOfComputer(string str,char symbol){
    
    bool flag=true;
    int move=0;
    int row;
    int otherRow;
    int randomNumber;
    //find four matching.
    for (int i = 0; i < get_length() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.')) {
            gameCells[row][i].set_PlayerType(symbol);
            if (determineTheWinWho(symbol,row,i,1))  {
                flag=false;
                move=i;
                ConnectFour::Cell::set_livingCells(1);
            }
            else {
                gameCells[row][i].set_PlayerType('.');
            }
        }

    }
    
    if (flag==false) {
        showTheBoard();
        cout<<"Move of Computer :"<< static_cast<char>(move+'a')<<endl;
        cout<<" Total living cells :"<<ConnectFour::Cell::get_livingCells()<<"\n\n";
        return true;
    }
    move=0;
    //prevent the four matching.
    for (int i = 0; i < get_length() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.')) {
            gameCells[row][i].set_PlayerType('X');
            if (determineTheWinWho('X',row,i,0))  {
                flag=false;
                gameCells[row][i].set_PlayerType(symbol);
                move=i;
                ConnectFour::Cell::set_livingCells(1);
            }
            else {
                gameCells[row][i].set_PlayerType('.');
            }
        }

    }
    if (flag==false) {
        showTheBoard();
        cout<<"Move of Computer :"<< static_cast<char>(move+'a')<<endl;
        cout<<" Total living cells :"<<ConnectFour::Cell::get_livingCells()<<"\n\n";
        return false;
    }

    move=0;
    for (int i = 0; i < get_length() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.') && isCellLegal(row+1,i) && isCellLegal(row+2,i) &&
		gameCells[row+1][i].get_PlayerType()==symbol && gameCells[row+2][i].get_PlayerType()==symbol) {
		    gameCells[row][i].set_PlayerType(symbol);
		    move=i;
		    flag=false;
		    row=i;
		    ConnectFour::Cell::set_livingCells(1);
	    }

        else if (getRowOfAvaiable(row,'.') && isCellLegal(row+1,i)
                  && gameCells[row+1][i].get_PlayerType()==symbol){
            gameCells[row][i].set_PlayerType(symbol);
            move=i;
            flag=false;
            row=i;
            ConnectFour::Cell::set_livingCells(1);
        }

    }

    
    if (flag==false) {
        showTheBoard(); 
        cout<<"Move of Computer :"<<static_cast<char>(move+'a')<<endl;
        cout<<" Total living cells :"<<ConnectFour::Cell::get_livingCells()<<"\n\n";
        return false;
    }    
    move=0;
    // move random.
    do
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(0,get_length()-1);
        randomNumber=dist(mt);
        row=randomNumber;
        if (isCellAvaiable(randomNumber)) {
            getRowOfAvaiable(row,'.');
            gameCells[row][randomNumber].set_PlayerType(symbol);
            flag=false;
            move=randomNumber;
            ConnectFour::Cell::set_livingCells(1);
        }
    }while(flag);

    showTheBoard();
    cout<<"Move of Computer:"<<static_cast<char>(move+'a')<<endl;
    cout<<" Total living cells :"<<ConnectFour::Cell::get_livingCells();
    return false;
}

bool ConnectFour::moveMultiMode(char &player,int &ppORpc) {
    bool user1;
    bool user2;
    bool user;
    bool computer;
    // player-player.
    if (ppORpc==3) {
        
        if (player=='X') {
            user1=move("User1 move:",player, ppORpc);
            if (user1==true) return true; 
            else if(ppORpc==1 && player=='X') {
                user1=move("User1 move:",player, ppORpc);
                if (user1==true) return true;
            }
            else if (ppORpc==1 && player=='O') {
                ppORpc=3;
                user2=move("User2 move:",player,ppORpc);
                if (user2==true) return true;
            }

            else if(ppORpc==2 && player=='X') {
                 user=move("User move:",player,ppORpc);
                 if (user==true) return true;
            }
            else if(ppORpc==2 && player=='O') {
                 computer=moveOfComputer("Computer Move:",player);
                 if (computer==true) return true;
            }
        }
        else {
            user2=move("User2 move:",player, ppORpc);
            if (user2==true) return true; 
            else if(ppORpc==1 && player=='X') {
                user1=move("User1 move:",player, ppORpc);
                if (user1==true) return true;
            }
            else if (ppORpc==1 && player=='O') {
                ppORpc=3;
                user2=move("User2 move:",player,ppORpc);
                if (user2==true) return true;
            }

            else if(ppORpc==2 && player=='X') {
                 user=move("User move:",player,ppORpc);
                 if (user==true) return true;
            }
            else if(ppORpc==2 && player=='O') {
                 computer=moveOfComputer("Computer move:",player);
                 if (computer==true) return true;
            }
        }
    }
    //player-computer
    if (ppORpc==4) {
        
        if (player=='X') {
            user=move("User move:",player, ppORpc);
            if (user==true) return true; 
            else if(ppORpc==2 && player=='X') {
                ppORpc=4;
                user=move("User move:",player, ppORpc);
                if (user==true) return true;
            }
            else if (ppORpc==2 && player=='O') {
                
                computer=moveOfComputer("Computer move:",player);
                if (computer==true) return true;
            }

            else if(ppORpc==1 && player=='X') {
                ppORpc=3;
                user1=move("User1 move:",player,ppORpc);
                 if (user==true) return true;
            }
            else if(ppORpc==1 && player=='O') {
                ppORpc=3;
                user2=move("User2 move:",player,ppORpc);
                 if (user2==true) return true;
            }       
        }
        else {
            computer=moveOfComputer("Computer move:",player);
            if (computer==true) return true;
        }
    }   
    return false;
}
