#include "Piece.h"
#include<stdlib.h>
#include<iostream>

using namespace std;

int Piece::tab120[] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
            -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
            -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
            -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
            -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
            -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
            -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
            -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
        };

int Piece::tab64[] = {
            21, 22, 23, 24, 25, 26, 27, 28,
            31, 32, 33, 34, 35, 36, 37, 38,
            41, 42, 43, 44, 45, 46, 47, 48,
            51, 52, 53, 54, 55, 56, 57, 58,
            61, 62, 63, 64, 65, 66, 67, 68,
            71, 72, 73, 74, 75, 76, 77, 78,
            81, 82, 83, 84, 85, 86, 87, 88,
            91, 92, 93, 94, 95, 96, 97, 98
};

int Piece::move_tower[] = {-10, 10, -1, 1};
int Piece::move_bishop[] = {-11, -9, 11, 9};
int Piece::move_knight[] = {-12, -21, -19, -8, 12, 21, 19, 8};

int Piece::namePiece[] = {VIDE, KING, QUEEN, TOWER, KNIGHT, BISHOP, PAWN};
int Piece::valPiece[] = {0, 99999, 200, 5, 3, 3, 1};

Piece::Piece() {
    name = VIDE;
    color = true;
    value = valPiece[VIDE];
}
Piece::Piece(int i_name, bool i_color) {
    name = i_name;
    color = i_color;
    value = valPiece[name];
}

int Piece::getVal() {
    return value;
}

int Piece::getName() {return name;}

bool Piece::getColor() {return color;}

bool Piece::isEmpty() { return name==VIDE;}

void Piece::pos2_knight(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board) {
    int position = 0;
    int i;
    for(i=0; i<sizeof(Piece::move_knight)/sizeof(int);i++) {
        position = tab120[tab64[pos1]+Piece::move_knight[i]];
        if(position != -1) {
            if(chess_board[position]->getName() == VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            } 
        }
    }
}

void Piece::pos2_tower(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board) {
    int position = 0;
    int i;
    for(i=0; i<sizeof(Piece::move_tower)/sizeof(int);i++) {
        int j = 1;
        do {
            position = tab120[tab64[pos1]+Piece::move_tower[i]*j];
            if(position != -1) {
                if(chess_board[position]->getName() == VIDE || chess_board[position]->getColor() == !color) {
                    struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                    retour->firstPos = pos1;
                    retour->lastPos = position;
                    retour->color = color;
                    liste.push_back(retour);
                }   
            }
            j = j +1;
        }while(position != -1 && (chess_board[position]->getName() == VIDE ));
        
    }
}

void Piece::pos2_bishop(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board) {
    int position = 0;
    int i;
    for(i=0; i<sizeof(Piece::move_bishop)/sizeof(int);i++) {
        int j = 1;
        do {
            position = tab120[tab64[pos1]+Piece::move_bishop[i]*j];
            if(position != -1) {
                if(chess_board[position]->getName() == VIDE || chess_board[position]->getColor() == !color) {
                    struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                    retour->firstPos = pos1;
                    retour->lastPos = position;
                    retour->color = color;
                    liste.push_back(retour);
                }   
            }
            j = j + 1;
        }while(position != -1 && (chess_board[position]->getName() == VIDE ));
        
    }
}

//Color is the color of our king
void Piece::pos2_king(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board) {
    int position = 0;
    int i;
    for(i=0; i<sizeof(Piece::move_bishop)/sizeof(int);i++) {
        position = tab120[tab64[pos1]+Piece::move_bishop[i]];
        if(position != -1) {
            if(chess_board[position]->getName() == VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            } 
        }
        
    }

    for(i=0; i<sizeof(Piece::move_tower)/sizeof(int);i++) {
        position = tab120[tab64[pos1]+Piece::move_tower[i]];
        if(position != -1) {
            if(chess_board[position]->getName() == VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }
        
    }
}

void Piece::pos2_pawn(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board) {
    int position = 0;

    //True for WHITE, check Piece.h to see the Define value
    if(color) {
        position = tab120[tab64[pos1]-10];
        if(position != -1) {
            if(chess_board[position]->getName() == VIDE) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }

        //For the first move, the pawn can move of 2 squares
        //Checki if the pawn is on the init row (the pawn can't reverse so if the pawn is on this row, that's the first move of this pawn)
        position = tab120[tab64[pos1]-20];
        if(position != -1 && pos1/8 == 6) {
            int tmp_position1 = tab120[tab64[pos1]-10];
            if(chess_board[tmp_position1]->getName() == VIDE && chess_board[position]->getName() == VIDE) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }

        // Move attack
        position = tab120[tab64[pos1]-11];
        if(position != -1) {
            if(chess_board[position]->getName() != VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }
        

        position = tab120[tab64[pos1]-9];
        if (position != -1) {
            if(chess_board[position]->getName() != VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }

    } else {
        position = tab120[tab64[pos1]+10];
        if(position != -1) {
            if(chess_board[position]->getName() == VIDE) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }

        //For the first move, the pawn can move of 2 squares
        //Checki if the pawn is on the init row (the pawn can't reverse so if the pawn is on this row, that's the first move of this pawn)
        position = tab120[tab64[pos1]+20];
        if(position != -1 && pos1/8 == 1) {
            int tmp_position1 = tab120[tab64[pos1]+10];
            if(chess_board[tmp_position1]->getName() == VIDE && chess_board[position]->getName() == VIDE) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }

        // Move attack
        position = tab120[tab64[pos1]+11];
        if(position != -1) {
            if(chess_board[position]->getName() != VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }
        

        position = tab120[tab64[pos1]+9];
        if (position != -1) {
            if(chess_board[position]->getName() != VIDE || chess_board[position]->getColor() != color) {
                struct Tuple *retour = (struct Tuple *)malloc(sizeof(struct Tuple));
                retour->firstPos = pos1;
                retour->lastPos = position;
                retour->color = color;
                liste.push_back(retour);
            }
        }
    }
    
}
