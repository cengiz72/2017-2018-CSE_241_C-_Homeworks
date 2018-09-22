#include "ConnectFour.h"

int ConnectFour::Cell::livingCells = 0;

ConnectFour::ConnectFour() : row_(5) , column_(5),ppORpc('N') {
    createNewBoard();
}
ConnectFour::ConnectFour(string & boardname) {
    fstream file;
    file.open(boardname);
    if (!file)
    {
       cerr<<"file is not found!!!"<<endl;
       return;
    }
    file.close();
    readboard(boardname);
}
ConnectFour::~ConnectFour() {

  destroyBoard();
}

ConnectFour::ConnectFour(int row, int column): column_(column) , row_(row),ppORpc('N')
{/*Body intentionally empty*/}

ConnectFour::Cell::Cell() : typeOfPlayer('*') 
{/*Body intentionally empty*/}
ConnectFour::Cell::Cell(char type) : typeOfPlayer(type)
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
inline int ConnectFour::get_Row() const {
    return row_;
}
inline int ConnectFour::get_Column() const {
    return column_;
}

inline  int ConnectFour::Cell::get_livingCells() {
    return livingCells;
}
char ConnectFour::get_ppORpc() const {
    return ppORpc; 
}
inline void ConnectFour::set_Row(int a) {
   row_=a;
}
inline void ConnectFour::set_Column(int b) {
    column_=b;
}

void ConnectFour::createNewBoard() {
    board=new Cell*[get_Row()];
    for (int i = 0; i < get_Row(); ++i)
        board[i]=new Cell[get_Column()];
}
void ConnectFour::destroyBoard() {
    for (int i = 0; i < get_Row(); ++i)
        delete [] board[i];
    delete [] board;
    board=NULL;
}
// compare rows and columns of two of ConnectFour objects.
// if row1==row2 and column1==column2 return true,else return false 
bool ConnectFour::operator ==(const ConnectFour & another) const {
    return (another.get_Row()==get_Row() && get_Column()==another.get_Column());  
}
// compare rows and columns of two of ConnectFour objects.
// if row1!=row2 and column1!=column2 return true,else return false 
bool ConnectFour::operator !=(const ConnectFour & another) const {
    return (another.get_Row()!=get_Row() || get_Column()!=another.get_Column());
}
ostream & operator <<(ostream &out,const ConnectFour::Cell & cell) {
    out << cell.get_PlayerType();
    out << cell.get_row();
    out << cell.get_column();
    return out;
}
istream & operator >>(istream &input, ConnectFour::Cell & cell) {
    
    input >>cell.typeOfPlayer;

    input >>cell.row;

    input >>cell.column;

    return input;
}
//from empty to user1 
ConnectFour::Cell ConnectFour::Cell::operator ++() {
    return Cell('X');
}
// from user1 to user2.
ConnectFour::Cell ConnectFour::Cell::operator ++(int ignore) {
    return Cell('O');
}
// from user to computer.
ConnectFour::Cell ConnectFour::Cell::operator--() {
    return Cell('O');
}
//from computer to empty.
ConnectFour::Cell ConnectFour::Cell::operator--(int ignore) {
    return Cell('*');
}
bool ConnectFour::Cell::operator == (const Cell & cell1) const {
    return(cell1.get_PlayerType()==get_PlayerType());
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
    for (int i = 0; i < get_Row(); ++i)
 		for (int j = 0; j < get_Column(); ++j)
 			if (board[i][j].get_PlayerType()!='*') ++countOfLivingcellsOfCurrentObject;
    destroyBoard();
    set_Row(widtH);
    set_Column(lengtH);
    createNewBoard();
    for (int i = 0; i < get_Row(); ++i){
        load.getline(arr,99,'\n');
        for (int j = 0; j < get_Column(); ++j){
             if (arr[j]!='*' && arr[j]!=' ') ++countOfLivingcellsOfNewObject;
             board[i][j].set_PlayerType(arr[j]);
             board[i][j].set_row(i);
             board[i][j].set_column(static_cast<char>('a'+j));
        }

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
             saving<<board[i][j].get_PlayerType();
             }
        saving<<endl;     
    }
 saving.close();
}

void ConnectFour::showTheBoard() const {
    cout<<endl;
    printTheLabelBoard();
    for (int i=0; i<get_Row(); ++i){
        for (int j=0; j<get_Column(); ++j)
           cout<<board[i][j].get_PlayerType()<<" ";
        cout<<endl;
    }
    cout<<endl;
}
//read file and create a game board.
void ConnectFour::readboard(string &filename) {
    fstream file;
    int row=0;
    int column=0;
    char arr[200];
    char ch;
    file.open(filename);
    //find row and column of board by reading file up to eof.
    while(!file.eof()) {
        
        if ((file.getline(arr,199,'\n'))) {
            if (likeStrlen(arr)>column)  column=likeStrlen(arr);
          ++row;
        }
    }
    file.close();
    set_Row(row);
    set_Column(column);
    createNewBoard();
    file.open(filename);

    for (int i=0; i<get_Row(); ++i) {
        file.getline(arr,199,'\n');
        for (int j=0; j<get_Column(); ++j) {
            board[i][j].set_PlayerType(arr[j]);
            board[i][j].set_row(i);
            board[i][j].set_column(static_cast<char>(j+'a'));
        }
    }
    file.close();
}
//find length of a given string.
int  ConnectFour::likeStrlen(char *str) const{

  int count=0;

  while(*str!='\0') {

    ++count;
    ++str;
  }
  return count;
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
    for (int i=get_Row()-1; i>=0 && flag; --i) {
        if (board[i][static_cast<int>(position-'a')].get_PlayerType()=='*') {
            board[i][static_cast<int>(position-'a')].set_PlayerType(user1ORUser2);
            currentYcoordinate=board[i][static_cast<int>(position-'a')].get_row();
            flag=false;
            ConnectFour::Cell::set_livingCells(1);
        }
    }
    return currentYcoordinate;
}
void ConnectFour::playGame() {
    char chooise;
    string filename;
    bool flag=true;
    while(flag) {
        cout<<endl;
        cout<<"please enter board name:";
        cin >> filename;
        if(takesBoardNameAndChooise(filename,chooise)) flag=false;
    }

    set_ppORpc(tolower(chooise));
    showTheBoard();
    if (tolower(chooise)=='p') userToUser();
    else userToComputer();
}
void ConnectFour::printTheLabelBoard() const{
    
    char letter='a';
    for (int i=0; i<get_Column(); ++i)
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
void ConnectFour::userToComputer(char orderOfPcOrPlayer) {
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
bool ConnectFour::takesBoardNameAndChooise(string &filename,char &selection){
    
    bool flag=true;
    fstream file;
    file.open(filename);
    if (!file)
    {
       cerr<<"file is not found!!!"<<endl;
       return false;
    }
    file.close();
    do 
    {
        cout<<endl;
        cout <<"To play player to player,press the   P type."<<endl
             <<"To play player to computer,press the C type."<<endl;

        
            cout <<"Please enter your chooise:";
            cin>>selection;
            if (cin.eof())
            {
                cout<<"EOF is handled!!!"<<endl;
                cout<<"Program is over."<<endl;
                exit(1);
            }
        if (tolower(selection)=='c' || tolower(selection)=='p') flag=false;
        else cerr<<"Wrong chooise!!!"<<endl;
    }while(flag);
    readboard(filename);
    return true;
}
bool ConnectFour::determineTheWinWho(char type,int current,int position,int valuE){
    
   return  findTheConnectFour(current,type,valuE,position) ||
           findTheConnectFour(type,current,valuE,position) ||
           findTheConnectFour(valuE,position,type,current) ||
           findTheConnectFour(current,valuE,position,type);
}

bool ConnectFour::isCellLegal(int xCoordinate,int yCoordinate) const {
    if (xCoordinate >= 0 && xCoordinate < get_Row() && yCoordinate >=0 &&
       board[xCoordinate][yCoordinate].get_PlayerType()!=' ' && yCoordinate < get_Column())
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
            
            if (board[currentRow-i][column-j].get_PlayerType()==symbol) ++countOfLeftToUpMathcingCells;
            else flag=false;
        }
        else break;
    }
    flag=true;
    //then,it is scanned right-down from current cell.
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(currentRow+i,column+j)) {
            
            if (board[currentRow+i][column+j].get_PlayerType()==symbol) ++countOfRihgtToDownMatchingCells;
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
            if (board[i][column].get_PlayerType()==symbol) counterMatchingCells=counterMatchingCells+1;
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
            
            if (board[currentRow+i][column-j].get_PlayerType()==symbol) ++countOfLeftToDownMatchingCells;
            else flag=false;
        }
        else break;
    }
     flag=true;
    for (int i = 1,j=1; i < 4 && j<=3 && flag; ++i,++j) {
        if (isCellLegal(currentRow-i,column+j)) {
            
            if (board[currentRow-i][column+j].get_PlayerType()==symbol) ++countOfRightToUpMatchingCells;
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
            if (board[currentRow][i].get_PlayerType()==symbol) ++countOfLeftSideMatchingCells;
            else flag=false;
        }
        else break;
    }
    flag=true;
    for (int i = column+1; i <= column+3 && flag; ++i) {
        if (isCellLegal(currentRow,i)) {
            if (board[currentRow][i].get_PlayerType()==symbol) ++countOfRightSideMatchingCells;
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
    for (int i=get_Row()-1; i>=0 && !flag; --i)
        if (board[i][row].get_PlayerType()=='*') flag=true;
    return flag;
}
bool ConnectFour::getRowOfAvaiable(int &row,char playerType) const {
    bool flag=false;
    for (int i=get_Row()-1; i>=0 && !flag; --i)
        if (board[i][row].get_PlayerType()==playerType) {
            row=i;
            flag=true;
        }
    return flag;
}
bool ConnectFour::checkEmptyIsStillExisting() const {
    for (int i=0; i<get_Row(); ++i)
        for (int j=0; j<get_Column(); ++j)
            if (board[i][j].get_PlayerType()=='*') return true;
    return false;    
}

void ConnectFour::tolowerFourLettersMatching(int row,int &column,int down,int left,int right,
                                    int left_up,int right_down,int right_up,int left_down,char symbol) 
{
    if (left+right>=3) {
        for (int i = 0; i <= right; ++i)
             board[row][column+i].set_PlayerType(tolower(symbol));

        for (int i = 0; i <= left; ++i)
            board[row][column-i].set_PlayerType(tolower(symbol));
    }

    else if(down>=3) {
        for (int i = 0; i <= down; ++i)
            board[row+i][column].set_PlayerType(tolower(symbol));
    }

    else if (left_up+right_down>=3) {
        for (int i = 0; i <= left_up; ++i)
            board[row-i][column-i].set_PlayerType(tolower(symbol));
        for (int i = 0; i <= right_down; ++i)
            board[row+i][column+i].set_PlayerType(tolower(symbol));
    }

    else if (left_down+right_up>=3) {
 
        for (int i = 0; i <= left_down; ++i)
            board[row+i][column-i].set_PlayerType(tolower(symbol));
        for (int i = 0; i <= right_up; ++i)
            board[row-i][column+i].set_PlayerType(tolower(symbol));
    }

}

void ConnectFour::allConvertsToLower(string &array) {
    for (int i=0; i<array.length(); ++i)
        array[i]=tolower(array[i]);
}
//move for players.
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
         cout<<" Total living cells :"<<ConnectFour::Cell::get_livingCells()<<"\n\n";
        if (determineTheWinWho(symbol,rowOfCell,static_cast<int>(move[0]-'a'),1)){
            showTheBoard();
            return true;
        }
        else return false; 
}
//move for computer.
bool ConnectFour::moveOfComputer(string str,char symbol){
    
    bool flag=true;
    int move=0;
    int row;
    int otherRow;
    int randomNumber;
    //find four matching.
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'*')) {
            board[row][i].set_PlayerType(symbol);
            if (determineTheWinWho(symbol,row,i,1))  {
                flag=false;
                move=i;
                ConnectFour::Cell::set_livingCells(1);
            }
            else {
                board[row][i].set_PlayerType('*');
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
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'*')) {
            board[row][i].set_PlayerType('X');
            if (determineTheWinWho('X',row,i,0))  {
                flag=false;
                board[row][i].set_PlayerType(symbol);
                move=i;
                ConnectFour::Cell::set_livingCells(1);
            }
            else {
                board[row][i].set_PlayerType('*');
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
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'*') && isCellLegal(row+1,i) && isCellLegal(row+2,i) &&
		board[row+1][i].get_PlayerType()==symbol && board[row+2][i].get_PlayerType()==symbol) {
		    board[row][i].set_PlayerType(symbol);
		    move=i;
		    flag=false;
		    row=i;
		    ConnectFour::Cell::set_livingCells(1);
	    }

        else if (getRowOfAvaiable(row,'*') && isCellLegal(row+1,i)
                  && board[row+1][i].get_PlayerType()==symbol){
            board[row][i].set_PlayerType(symbol);
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
        std::uniform_int_distribution<int> dist(0,get_Column()-1);
        randomNumber=dist(mt);
        row=randomNumber;
        if (isCellAvaiable(randomNumber)) {
            getRowOfAvaiable(row,'*');
            board[row][randomNumber].set_PlayerType(symbol);
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