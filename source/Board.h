#ifndef BOARD
#define BOARD

#include "Piece.h"
#include "Tuple.h"
#include <list>
#include <vector>

#define DEFAULT_VALUE 10

#ifndef WHITE
#define WHITE true
#endif

#ifndef BLACK
#define BLACK false
#endif

class Board {
    private:
        //ATTRIBUTE
        Piece* chess_board[64];
        bool color;
    public:
        Board(bool color_king);
        Piece** getChessBoard();
        bool getColor();
        void getAllMoves(std::vector<struct Tuple*>& liste);
        void movePiece(int position1, int position2);
        int heuristic();
};
#endif