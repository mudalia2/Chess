/*
  Pawn.cpp
  Chess

  Created by Vikram Mudaliar on 9/13/17.
  Copyright © 2017 VR. All rights reserved.
*/

#include "Pawn.hpp"
#include <iostream>
using namespace std;

Pawn::Pawn(char color, char type, int x, int y):Piece(color,type,x,y)
{
    change_move_list();
}

Pawn::~Pawn()
{
    
}

Pawn::Pawn(Pawn const & rhs):Piece(rhs)
{
    
}

void Pawn::change_move_list()
{
    possible_moves.clear();
    int dir[]={-1,0,1};
    
    if(color == 'W')
    {
        for(int k =0;k<3;k++)
        {
            int new_x = pos_x+1;
            int new_y = pos_y+dir[k];
            if(new_y>0 && new_y<=8 && new_x<=8)
            {
                pair<int,int> pos(new_x,new_y);
                possible_moves.push_back(pos);
            }
        }
    }
    else
    {
        for(int k =0;k<3;k++)
        {
            int new_x = pos_x-1;
            int new_y = pos_y+dir[k];
            if(new_y>0 && new_y<=8 && new_x>-1)
            {
                pair<int,int> pos(new_x,new_y);
                possible_moves.push_back(pos);
            }
        }
    }
}
