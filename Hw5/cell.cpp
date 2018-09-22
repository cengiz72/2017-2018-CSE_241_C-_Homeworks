/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#include "Cell.h"

Cell::Cell() : typeOfPlayer('*') 
{/*Body intentionally empty*/}
char Cell::get_column() const{
    return column;
}
int Cell:: get_row() const {
    return row;
}
char Cell::get_PlayerType() const {
    return typeOfPlayer;
}
void Cell:: set_column(char yCoordinate) {

    column=yCoordinate;
}
void Cell::set_row(int xCoordinate) {
    row=xCoordinate;
}
void Cell::set_PlayerType(char player) {
    typeOfPlayer=player;
}