#ifndef PIECE
#define PIECE

#include <list>
#include <vector>
#include "Tuple.h"

#define VIDE 0
#define KING 1
#define QUEEN 2
#define TOWER 3
#define KNIGHT 4
#define BISHOP 5
#define PAWN 6

#ifndef WHITE
#define WHITE true
#endif

#ifndef BLACK
#define BLACK false
#endif

class Piece {
    private:
        // STATIC VALUES
        static int tab120[];
        static int tab64[];
        static int move_tower[];
        static int move_bishop[];
        static int move_knight[];
        static int valPiece[];
        static int namePiece[];

        //ATTRIBUTES
        int name;
        bool color;
        int value;
    public:
        Piece();
        Piece(int i_name, bool i_color);
        int getVal();
        bool isEmpty();
        int getName();
        bool getColor();

        //MOVE FUNCTION
        static void pos2_knight(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board);
        static void pos2_tower(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board);
        static void pos2_bishop(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board);
        static void pos2_king(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board);
        static void pos2_pawn(std::vector<struct Tuple*>& liste, int pos1, bool color, Piece** chess_board);

};
#endif