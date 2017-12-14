/*
  Rook.cpp
  Chess

  Created by Vikram Mudaliar on 9/13/17.
  Copyright © 2017 VR. All rights reserved.
*/

#include "Rook.hpp"
#include <iostream>
using namespace std;

Rook::Rook(char color, char type, int x, int y):Piece(color,type,x,y)
{
    change_move_list();
}

Rook::~Rook()
{
    
}

Rook::Rook(Rook const & rhs):Piece(rhs)
{
    
}

void Rook::change_move_list()
{
    possible_moves.clear();    
    //offset vector to get all the valid points
    int dir_pos[]={1,2,3,4,5,6,7};
    
    for(int k =0;k<7;k++)
    {
        int new_x = pos_x+dir_pos[k];
        int new_y = pos_y;
        if(new_x>0 && new_x<=8)
        {
            pair<int,int> pos(new_x,new_y);
            possible_moves.push_back(pos);
        }
        new_x = pos_x-dir_pos[k];
        if(new_x>0 && new_x<=8)
        {
            pair<int,int> pos(new_x,new_y);
            possible_moves.push_back(pos);
        }
        new_x = pos_x;
        new_y = pos_y+dir_pos[k];
        if(new_y>0 && new_y<=8)
        {
            pair<int,int> pos(new_x,new_y);
            possible_moves.push_back(pos);
        }
        new_y = pos_y-dir_pos[k];
        if(new_y>0 && new_y<=8)
        {
            pair<int,int> pos(new_x,new_y);
            possible_moves.push_back(pos);
        }
    }
}
