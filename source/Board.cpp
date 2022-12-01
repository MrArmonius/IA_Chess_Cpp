#include "Board.h"
#include <stdlib.h>
Board::Board(bool color_king) {
    // chess_board{
    //     Piece(TOWER, BLACK), Piece(KNIGHT, BLACK), Piece(BISHOP, BLACK), Piece(QUEEN, BLACK), Piece(KING, BLACK), Piece(BISHOP, BLACK), Piece(KNIGHT, BLACK), Piece(TOWER, BLACK),
    //     Piece(PAWN, BLACK), Piece(PAWN, BLACK), Piece(PAWN, BLACK), Piece(PAWN, BLACK), Piece(PAWN, BLACK), Piece(PAWN, BLACK), Piece(PAWN, BLACK), Piece(PAWN, BLACK),
    //     Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    //     Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    //     Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    //     Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
    //     Piece(PAWN, WHITE), Piece(PAWN, WHITE), Piece(PAWN, WHITE), Piece(PAWN, WHITE), Piece(PAWN, WHITE), Piece(PAWN, WHITE), Piece(PAWN, WHITE), Piece(PAWN, WHITE),
    //     Piece(TOWER, WHITE), Piece(KNIGHT, WHITE), Piece(BISHOP, WHITE), Piece(QUEEN, WHITE), Piece(KING, WHITE), Piece(BISHOP, WHITE), Piece(KNIGHT, WHITE), Piece(TOWER, WHITE)
    // };
    int i;
    for(i=0; i < 64; i++) {
        Piece* piece_tmp;
        if(i/8 == 1) {
            piece_tmp = new Piece(PAWN, BLACK);
        } else if(i/8 == 6) {
            piece_tmp = new Piece(PAWN, WHITE);
        } else if(i/8 == 0 && (i%8==0 || i%8 == 7)) {
            piece_tmp = new Piece(TOWER, BLACK);
        } else if(i/8 == 7 && (i%8==0 || i%8 == 7)) {
            piece_tmp = new Piece(TOWER, WHITE);
        } else if(i/8 == 0 && (i%8==1 || i%8 == 6)) {
            piece_tmp = new Piece(KNIGHT, BLACK);
        } else if(i/8 == 7 && (i%8==1 || i%8 == 6)) {
            piece_tmp = new Piece(KNIGHT, WHITE);
        } else if(i/8 == 0 && (i%8==2 || i%8 == 5)) {
            piece_tmp = new Piece(BISHOP, BLACK);
        } else if(i/8 == 7 && (i%8==2 || i%8 == 5)) {
            piece_tmp = new Piece(BISHOP, WHITE);
        } else if(i/8 == 0 && (i%8==3)) {
            piece_tmp = new Piece(QUEEN, BLACK);
        } else if(i/8 == 7 && (i%8==3)) {
            piece_tmp = new Piece(QUEEN, WHITE);
        } else if(i/8 == 0 && (i%8==4)) {
            piece_tmp = new Piece(KING, BLACK);
        } else if(i/8 == 7 && (i%8==4)) {
            piece_tmp = new Piece(KING, WHITE);
        } else {
            piece_tmp = new Piece();
        }
        
        chess_board[i] = piece_tmp;
    }

    color = color_king;
    
}

Piece** Board::getChessBoard() { return chess_board;}
bool Board::getColor() {return color;}

void Board::getAllMoves(std::vector<struct Tuple*>& liste) {
    int i = 0;
    for(i = 0; i < 64; i++) {
        Piece* tmp_piece = chess_board[i];
        if(tmp_piece->getColor() == color) {
            if(tmp_piece->getName() == KING) {
                Piece::pos2_king(liste, i, tmp_piece->getColor(), chess_board);

            } else if(tmp_piece->getName() == QUEEN) {
                Piece::pos2_tower(liste, i, tmp_piece->getColor(), chess_board);
                Piece::pos2_bishop(liste, i, tmp_piece->getColor(), chess_board);

            } else if(tmp_piece->getName() == BISHOP) {
                Piece::pos2_bishop(liste, i, tmp_piece->getColor(), chess_board);

            } else if(tmp_piece->getName() == KNIGHT) {
                Piece::pos2_knight(liste, i, tmp_piece->getColor(), chess_board);

            } else if(tmp_piece->getName() == TOWER) {
                Piece::pos2_tower(liste, i, tmp_piece->getColor(), chess_board);

            } else if(tmp_piece->getName() == PAWN) {
                Piece::pos2_pawn(liste, i, tmp_piece->getColor(), chess_board);

            }
        }
        
    }
}

void Board::movePiece(int position1, int position2) {
    Piece* tmp = chess_board[position1];
    chess_board[position1] = new Piece();
    delete(chess_board[position2]);
    chess_board[position2] = tmp;
}

int Board::heuristic() {
    int i;
    int EnnemyScore =0;
    int OurScore = 0;
    for(i=0; i < 64; i++) {
        Piece* tmp_piece = chess_board[i];
        if(tmp_piece->getName() != VIDE && tmp_piece->getColor() == color) {
            OurScore += tmp_piece->getVal();
        } else if(tmp_piece->getName() != VIDE && tmp_piece->getColor() != color) {
            EnnemyScore += tmp_piece->getVal();
        }
    }
    return OurScore-EnnemyScore;
}
