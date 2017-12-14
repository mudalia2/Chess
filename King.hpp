/*
 King.hpp
 
 Derived Class that defines additonal properties of the King piece. This class is derived from the Piece base class.
 
 Chess
 Created by Vikram Mudaliar on 9/13/17.
 Copyright © 2017 VR. All rights reserved.
 */

#ifndef KING_H
#define KING_H

#include <ostream>
#include <vector>
#include <utility>
#include "Piece.hpp"

class King : public Piece
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
    King(char color, char type, int x, int y);
    
    /*
     Destructor.
     
     @param NONE.
     @return NONE.
     */
    ~King();
    
    /*
     Copy Constructor.
     
     @param rhs Piec object that needs to be deep copied.
     @return NONE.
     */
    King(King const & rhs);
    
    /*
     Update move list based on the current pos_x and pos_y and the movement rules for the Rook Piece.
     
     @param NONE.
     @return NONE.
     */
    void change_move_list();    
    
};


#endif //KING_H
