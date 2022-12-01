#ifndef TREE
#define TREE

#include <stdlib.h>
#include <list>
#include "Board.h"
#include "Piece.h"
#include "Tuple.h"
#include <vector>

using namespace std;

class Tree {
    private:
        static struct Tuple* my_max(std::vector<struct Tuple*> &liste);
        static struct Tuple* my_min(std::vector<struct Tuple*> &liste);

        std::list<Tree*> children;
        Board* chess_node;
        struct Tuple* move;
        
    public:
        Tree(int profondeur, Board* chess_board, bool color, struct Tuple* move_old);
        struct Tuple* minimax(int profondeur, bool evalMax, int profondeur_debut);
};

#endif