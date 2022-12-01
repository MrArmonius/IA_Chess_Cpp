#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Board.h"
#include "Piece.h"
#include "Tree.h"
#include "Tuple.h"
#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

#define LENGTH 150
#define NUMTHREADS 16


int string_to_int(char first, char last) {
    int colonne = first - 'a';
    int ligne = last - '1';
    int result = colonne + (7-ligne)*8;
    return result;
}

void move_string_to_int(string move, Tuple &tuple_int) {
    tuple_int.firstPos = string_to_int(move[0], move[1]);
    tuple_int.lastPos = string_to_int(move[2], move[3]);
}

string move_int_to_string(Tuple &tuple_int) {
    char retour[4];
    retour[0] = 'a' + tuple_int.firstPos%8; //Colonne
    retour[1] = '1' + (7-(tuple_int.firstPos/8)); // Ligne

    retour[2] = 'a' + tuple_int.lastPos%8; //Colonne
    retour[3] = '1' + (7-(tuple_int.lastPos/8)); // Ligne

    string strResult(retour);

    return strResult;

}

int main()
{
    omp_set_dynamic(0);              /** Explicitly disable dynamic teams **/
    omp_set_num_threads(NUMTHREADS); /** Use N threads for all parallel regions **/  
    Board chess(WHITE);

    string S, T;
  
    getline(cin, S);
  
    stringstream X(S);
  
    std::vector<struct Tuple*> liste;
    while (getline(X, T, ' ')) {
        cout << T << endl;
        Tuple* ptr_tuple = new Tuple();
        move_string_to_int(T, *ptr_tuple);
        liste.push_back(ptr_tuple);
    }

    // std::list<struct Tuple*>::iterator it;
    for(int i =0; i < liste.size(); i++) {
    // for(it= liste.begin(); it!= liste.end(); it++) {
        // struct Tuple* tuple_val = *it;
        struct Tuple* tuple_val = liste[i];
        int firstPos = tuple_val->firstPos;
        int SecondPos = tuple_val->lastPos;

        cout << "FirstPos: " << firstPos << " SecondPos: " << SecondPos << "\n";
        chess.movePiece(firstPos, SecondPos);
        delete(liste[i]);
    }

    Tree* arbre;

    #pragma omp parallel
    {
        #pragma omp single
        arbre = new Tree(5, &chess, WHITE, new Tuple());
    }

    Tuple* move = arbre->minimax(5,false, 4);

    cout << "Move found: " <<  move->movement_register->firstPos<<":"<< move->movement_register->lastPos << "\n";
    cout << move_int_to_string(*move->movement_register) << "\n";

    delete(arbre);

    // chess.movePiece(0,56);
    // cout << "heuristic board init: " << chess.heuristic() << "\n";

    // Piece* test = chess.getChessBoard()[38];
    // cout << "True:False -> " << true << ":" << false << "\n";
    // cout << "Piece pos 0: " << test->getName() <<" color: " << test->getColor() << "\n";

    // //chess.movePiece(0,16);

    // Piece* test2 = chess.getChessBoard()[39];
    // cout << "True:False -> " << true << ":" << false << "\n";
    // cout << "Piece pos 0 after move it: " << test2->getName() <<" color: " << test2->getColor() << "\n";

    // std::list<struct Tuple*> liste;
    // Piece::pos2_knight(liste, 20, WHITE, chess.getChessBoard());
    // Piece::pos2_bishop(liste, 25, WHITE, chess.getChessBoard());
    // Piece::pos2_tower(liste, 56, BLACK, chess.getChessBoard());
    // Piece::pos2_king(liste, 16, WHITE, chess.getChessBoard());
    // Piece::pos2_pawn(liste, 16, WHITE, chess.getChessBoard());

    // chess.getAllMoves(liste);


    // cout << "Moves that we have: \n";
    // std::list<struct Tuple*>::iterator it;
    // for(it= liste.begin(); it!= liste.end(); it++) {
    //     struct Tuple* tuple_val = *it;
    //     int firstPos = tuple_val->firstPos;
    //     int SecondPos = tuple_val->lastPos;

    //     cout << "FirstPos: " << firstPos << " SecondPos: " << SecondPos << "\n";
    //     delete(*it);
    // }

    

    
    

    
  
    return 0;
}