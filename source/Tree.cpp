#include "Tree.h"
#include "Board.h"
#include "Tuple.h"
#include <iostream>
#include <vector>

#include <omp.h>



Tree::Tree(int profondeur, Board* chess_board, bool color, struct Tuple* move_old) {
    chess_node = chess_board;
    move = move_old;

    if(profondeur != 0) {
        std::vector<struct Tuple*> liste_all_moves;
        chess_node->getAllMoves(liste_all_moves);
        
        // std::list<struct Tuple*>::iterator it;

        #pragma omp parallel for default(none) shared(color, profondeur, liste_all_moves) num_threads(16) 
        for(int i =0; i< liste_all_moves.size(); i++) {
        // for(it= liste_all_moves.begin(); it!= liste_all_moves.end(); it++) {
        //     struct Tuple* tuple_val = *it;
            struct Tuple* tuple_val = liste_all_moves[i];
            //cout << "Thread: " << omp_get_thread_num() << "\n";

            Board* chess_child = new Board(!color);
            chess_child->movePiece(tuple_val->firstPos, tuple_val->lastPos);
            tuple_val->heuristic = chess_child->heuristic();

            Tree* node_child;
            
            //#pragma omp task
            node_child = new Tree(profondeur-1, chess_child, !color, tuple_val);
            
            //#pragma omp taskwait
            children.push_back(node_child);
        }
    }
}

struct Tuple* Tree::my_max(std::vector<struct Tuple*> &liste){
    int i;
    
    Tuple* result = liste.front();
    int max = result->firstPos;

    for(int i =0; i < liste.size(); i++) {
        struct Tuple* tmp_tuple = liste[i];
        if(max < tmp_tuple->heuristic) {
            max = tmp_tuple->heuristic;
            result = tmp_tuple;
        }

    }

    return result;
}

struct Tuple* Tree::my_min(std::vector<struct Tuple*> &liste){
    int i;
    int min = liste.front()->heuristic;
    Tuple* result = liste.front();

    
    for(int i =0; i < liste.size(); i++) {
        struct Tuple* tmp_tuple = liste[i];
        if(min > tmp_tuple->heuristic) {
            min = tmp_tuple->heuristic;
            result = tmp_tuple;
        }

    }

    return result;
}


struct Tuple* Tree::minimax(int profondeur, bool evalMax, int profondeur_debut) {

    if(profondeur == 0) {
        // cout << "Move minimax: " << move->firstPos << ":" << move->lastPos << "\n";
        return move; 
    } else {
        std::vector<struct Tuple*> liste_tuple;

        std::list<Tree*>::iterator it;
        for(it= children.begin(); it!= children.end(); it++) {
            Tree* tree_child = *it;

            struct Tuple* movement = tree_child->minimax(profondeur-1, !evalMax, profondeur_debut);

            liste_tuple.push_back(movement);
        }

        if(evalMax) {
            Tuple* max = Tree::my_max(liste_tuple);
            if(profondeur == profondeur_debut) {max->movement_register = move;}
            return max;
        }
        else {
            Tuple* min = Tree::my_min(liste_tuple);
            if(profondeur == profondeur_debut) {min->movement_register = move;}
            return min;
        }
    }

}

int Tree::getNumberNodes()