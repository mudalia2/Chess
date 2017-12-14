/*
  King.cpp
  Chess

  Created by Vikram Mudaliar on 9/13/17.
  Copyright © 2017 VR. All rights reserved.
*/

#include "King.hpp"
#include <iostream>
using namespace std;

King::King(char color, char type, int x, int y):Piece(color,type,x,y)
{
    change_move_list();
}

King::~King()
{
    
}

King::King(King const & rhs):Piece(rhs)
{
    
}

void King::change_move_list()
{
    possible_moves.clear();
    int dir[]={-1,0,1};
    
    
    for(int k =0;k<3;k++)
    {
        for(int l =0;l<3;l++)
        {
            int new_x = pos_x+dir[k];
            int new_y = pos_y+dir[l];
            if((new_y>0 && new_y<=8) && (new_x>0 && new_x<=8) && !(dir[k]==0 && dir[l]==0))
            {
                pair<int,int> pos(new_x,new_y);
                possible_moves.push_back(pos);
            }
        }
    }
    
}
