/*
    author: Cengiz Toprak
    ID    : 161044087
*/
#ifndef CELL_H
#define CELL_H
    class Cell{
        public:
            Cell();
            char get_column() const;
            int get_row() const;
            char get_PlayerType() const;
            void set_column(char yCoordinate);
            void set_row(int xCoordinate);
            void set_PlayerType(char player);
        private:
            char typeOfPlayer;
            int row;
            char column;
    };
#endif /* CELL_H */

