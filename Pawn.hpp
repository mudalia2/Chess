/*
 Pawn.hpp
 
 Derived Class that defines additonal properties of the Pawn piece. This class is derived from the Piece base class.
 
 Chess
 Created by Vikram Mudaliar on 9/13/17.
 Copyright © 2017 VR. All rights reserved.
 */
#ifndef PAWN_H
#define PAWN_H

#include <ostream>
#include <vector>
#include <utility>
#include "Piece.hpp"

class Pawn: public Piece
{
public:
    /*
     Constructor that sets the color, type, pos_x and pos_y.
     
     @param color the color of the piece.
     @param type the type of the piece.
     @param x the position x of the piece.
     @param y the position y of the piece.
     @return NONE.
     */
    Pawn(char color, char type, int x, int y);
    
    /*
     Destructor.
     
     @param NONE.
     @return NONE.
     */
    ~Pawn();
    
    /*
     Copy Constructor.
     
     @param rhs Piec object that needs to be deep copied.
     @return NONE.
     */
    Pawn(Pawn const & rhs);
    
    /*
     Update move list based on the current pos_x and pos_y and the movement rules for the Rook Piece.
     
     @param NONE.
     @return NONE.
     */
    void change_move_list();    
    
};


#endif //PAWN_H
