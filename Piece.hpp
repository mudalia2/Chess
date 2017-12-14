/*
    Piece.hpp

    Class that defines properties of all pieces. This abstract class is used as a base class by all types of pieces.

    Chess
    Created by Vikram Mudaliar on 9/13/17.
    Copyright © 2017 VR. All rights reserved.
*/

#ifndef PIECE_H
#define PIECE_H

#include <ostream>
#include <vector>
#include <utility>

using namespace std;

class Piece
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
    Piece(char color, char type, int x, int y);
    
    /*
     Virtual Destructor.
     
     @param NONE.
     @return NONE.
     */
    virtual ~Piece();
    
    /*
     Copy Constructor.
     
     @param rhs Piec object that needs to be deep copied.
     @return NONE.
     */
    Piece(Piece const & rhs);
    
    /*
     Getter function for possible moves.
     
     @param NONE.
     @return a vector containing all the possible moves the piece can take.
     */
    vector<pair<int,int> > get_possible_moves()const;

    /*
     Setter function to change the position of a piece.
     
     @param new_x the new x position of the piece.
     @param new_y the new y position of the piece.
     @return NONE.
     */
	void change_position(int new_x, int new_y);

    /*
     getter function to obtain the current position of a piece.
     
     @param NONE.
     @return a pair containing the (pos_x,pos_y) of the piece.
     
     */
	pair<int,int> get_position()const;

    /*
     getter function to obtain the color of a piece.
     
     @param NONE.
     @return the color of the piece.
     
     */
	char get_color()const;
    
    /*
     getter function to obtain the type of piece.
     
     @param NONE.
     @return the type of the piece.
     
     */
    char get_type()const;

    /*
     virtual function to update the possible moves list for a piece.
     
     @param NONE.
     @return NONE.
     */
	virtual void change_move_list()=0;

protected:
    //Defines whether color of piece is Black or White
	char color;
    //Defines the type of piece
    char type;
    //Defines the x position of the piece on the board
	int pos_x;
    //Defines the y position of the piece on the board
	int pos_y;
    //Contains a list of all possible moves the piece can make given its currrent position
	vector<pair<int, int> > possible_moves;
};

#endif //PIECE_H
