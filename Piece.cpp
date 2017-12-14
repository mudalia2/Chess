/*
  Piece.cpp
  Chess

  Created by Vikram Mudaliar on 9/13/17.
  Copyright © 2017 VR. All rights reserved.
*/

#include "Piece.hpp"
#include <iostream>
using namespace std;


Piece::Piece(char color, char type, int x, int y)
{
    this->type = type;
	this->color = color;
	pos_x = x;
	pos_y = y;
}

Piece::~Piece()
{
    
}

Piece::Piece(Piece const & rhs)
{
    color=rhs.color;
    type=rhs.type;
    pos_x=rhs.pos_x;
    pos_y=rhs.pos_y;
    possible_moves=rhs.possible_moves;
}

vector<pair<int,int> > Piece::get_possible_moves()const
{
    return this->possible_moves;
}

void Piece::change_position(int new_x, int new_y)
{
	pos_x = new_x;
	pos_y = new_y;
}


pair<int,int> Piece::get_position()const
{
	pair<int,int> ret = make_pair(pos_x, pos_y);
	return ret;
}

char Piece::get_color()const
{
	return this->color;
}

char Piece::get_type()const
{
    return this->type;
}

void Piece::change_move_list()
{
    possible_moves.clear();
}
