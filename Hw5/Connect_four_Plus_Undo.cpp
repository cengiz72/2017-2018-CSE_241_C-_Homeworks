/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#include "ConnectFourPlusUndo.h"

ConnectFourPlusUndo::ConnectFourPlusUndo() : ConnectFourPlus(),used(0)
{}

ConnectFourPlusUndo::~ConnectFourPlusUndo() {
    destroyBoard();
    freeForStruct();
}

bool ConnectFourPlusUndo::move(string str,char &symbol,int &ppORpc) {

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
            if (move=="undo") {
                
                if (ppORpc==4 && get_used() > 1) {
                        gameCells[array[get_used()-1].row][array[get_used()-1].column].set_PlayerType('.');
                        set_used('d');//decrease used by 1.
                        gameCells[array[get_used()-1].row][array[get_used()-1].column].set_PlayerType('.');
                        set_used('d');//decrease used by 1.
                        showTheBoard();
                        return false;
                }
                else {
                    if (get_used() > 0) {
                        gameCells[array[get_used()-1].row][array[get_used()-1].column].set_PlayerType('.');
                        set_used('d');//decrease used by 1.
                        showTheBoard();
                        return false;
                    } 
                }
            }
            
            if (move=="undo" && get_used() < 1) cerr<<"can not be undo"<<endl;
               
            
            else {
                
                if (static_cast<int>(move[0]) > static_cast<int>('a'+get_Column()-1)){
                    cerr<<"Wrong move!!"
                        <<"Please hit move again."<<endl;
                }
                else if (!isCellAvaiable(static_cast<int>(move[0]-'a')))
                    cerr<<"This cells of column are all full."
                        <<"Please hit move again."<<endl;
                else {
                   rowOfCell=play(move[0],symbol);
                   set_used('i');
                   array[get_used()-1].row=rowOfCell;
                   array[get_used()-1].column=static_cast<int>(move[0]-'a');
                   flagForCorrect=true;
                }
            
            }

        } while (!flagForCorrect);
         showTheBoard();
        if (determineTheWinWho(symbol,rowOfCell,static_cast<int>(move[0]-'a'),1)){
            showTheBoard();
            return true;
        }
        else return false; 
}

void ConnectFourPlusUndo::allocateForStruct() {
    
    array=new Undo[get_Row()*get_Column()];
}
void ConnectFourPlusUndo::freeForStruct() {
   
    delete [] array;
    array=nullptr;
}
int ConnectFourPlusUndo::get_used() const {
    return used;
}
void ConnectFourPlusUndo::set_used(char incOrdec) {
    
    if (incOrdec=='i') ++used;
    else --used;
}

void ConnectFourPlusUndo::playGame() {
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
    allocateForStruct();
    if (tolower(chooise)=='p') userToUser();
    else userToComputer();
}

void ConnectFourPlusUndo::readFile(string &filename,int &ppORpc,char &playerType) {
    
    fstream load;
    int lengtH;
    int widtH;
    int order;
    char typeOfPlayer;
    char arr[100];
    load.open(filename);
    if (!load)
    {
       cerr<<"file is not  open."<<endl;
       exit(1);
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
    freeForStruct();
    allocateForStruct();
    for (int i = 0; i < get_Row(); ++i){
        load.getline(arr,99,'\n');
        for (int j = 0; j < get_Column(); ++j){
             gameCells[i][j].set_PlayerType(arr[j]);
             gameCells[i][j].set_row(i);
             gameCells[i][j].set_column(static_cast<char>('a'+j));
        }

    }
    load>>used;
    for (int i=0; i<get_used(); i++) {
        load>>array[i].row;
        load>>array[i].column;
    }
    load.close();
    ppORpc=order;
    playerType=typeOfPlayer;
    showTheBoard();
}
void ConnectFourPlusUndo::writeFile(string &filename,int &ppORpc,char &playerType) {
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
    saving<<get_used()<<endl;
    for (int i=0; i<get_used(); i++) {
        saving<<array[i].row<<" ";
        saving<<array[i].column<<" ";
    }
 saving.close();
 showTheBoard();
}

bool ConnectFourPlusUndo::moveOfComputer(string str,char symbol){
    
    bool flag=true;
    int move=0;
    int row;
    int randomNumber;
    //find four matching.
    for (int i = 0; i < get_Column() && flag; ++i) {
        row=i;
        if (getRowOfAvaiable(row,'.')) {
            gameCells[row][i].set_PlayerType(symbol);
            if (determineTheWinWho(symbol,row,i,1))  {
                flag=false;
                move=i;
                set_used('i');// used increment by 1.
                array[get_used()-1].row=row;
                array[get_used()-1].column=move;
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
                set_used('i');
                array[get_used()-1].row=row;
                array[get_used()-1].column=move;
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
            set_used('i');
            array[get_used()-1].row=row;
            array[get_used()-1].column=move;
        }

        else if (getRowOfAvaiable(row,'.') && isCellLegal(row+1,i)
                  && gameCells[row+1][i].get_PlayerType()==symbol){
            gameCells[row][i].set_PlayerType(symbol);
            move=i;
            flag=false;
            row=i;
            set_used('i');
            array[get_used()-1].row=row;
            array[get_used()-1].column=move;
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
            set_used('i');
            array[get_used()-1].row=row;
            array[get_used()-1].column=move;
        }
    }while(flag);

    showTheBoard();
    cout<<"Move of Computer:"<<static_cast<char>(move+'a')<<endl;
    return false;
}