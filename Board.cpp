/*
 Board.cpp
 Chess
 
 Created by Vikram Mudaliar on 9/16/17.
 Copyright © 2017 VR. All rights reserved.
 */

#include "Board.hpp"
#include <iostream>
#include <vector>

using namespace std;

const int COL = 8;
const int ROW = 8;


Board::Board()
{
    //initilize board size
    board.assign(ROW,vector<Piece*>(COL,NULL));
    
    //initialize positions of the rooks
    board[7][0] = new Rook('B', 'R', 8, 1);
    black_pieces.push_back(board[7][0]);
    board[7][7] = new Rook('B', 'R', 8, 8);
    black_pieces.push_back(board[7][7]);
    board[0][0] = new Rook('W', 'R', 1, 1);
    white_pieces.push_back(board[0][0]);
    board[0][7] = new Rook('W', 'R', 1, 8);
    white_pieces.push_back(board[0][7]);
    
    //initialize positions of the bishops
    board[7][2] = new Bishop('B', 'B', 8, 3);
    black_pieces.push_back(board[7][2]);
    board[7][5] = new Bishop('B', 'B', 8, 6);
    black_pieces.push_back(board[7][5]);
    board[0][2] = new Bishop('W', 'B', 1, 3);
    white_pieces.push_back(board[0][2]);
    board[0][5] = new Bishop('W', 'B', 1, 6);
    white_pieces.push_back(board[0][5]);

    
    //initialize positions of the kings
    board[7][4] = new King('B', 'K', 8, 5);
    black_pieces.push_back(board[7][4]);
    board[0][4] = new King('W', 'K', 1, 5);
    white_pieces.push_back(board[0][4]);

    
    //initialize positions of the pawns
    int j = 0;
    char row = 1;
    while(j<8)
    {
        board[6][j]=new Pawn('B', 'P', 7, row);
        black_pieces.push_back(board[6][j]);
        board[1][j]=new Pawn('W', 'P', 2, row);
        white_pieces.push_back(board[1][j]);
        row++;
        j++;
    }
}

bool Board::check_obstruction(int start_x, int start_y, int end_x, int end_y, Piece * curr_piece)const
{
    char piece_type = curr_piece->get_type();
    Piece * dest_piece = get_piece(end_x, end_y);
    //Rook checking
    if(piece_type == 'R')
    {
        if(start_x==end_x)
        {
            int start_cord= min(end_y,start_y)+1;
            int end_cord= max(end_y,start_y);
            while(start_cord<end_cord)
            {
                if(get_piece(start_x, start_cord)!=NULL)
                {
                    return false;
                }
                start_cord++;
            }
        }
        else
        {
            int start_cord= min(start_x, end_x)+1;
            int end_cord= max(start_x, end_x);
            while(start_cord<end_cord)
            {
                if(get_piece(start_cord, start_y)!=NULL)
                    return false;
                start_cord++;
            }
        }
    }
    //Bishop Condition
    else if (piece_type == 'B')
    {
        if(start_x < end_x && start_y > end_y) //right down
        {
            for(int i = start_x+1, j = start_y - 1; i<end_x && j>end_y; i++, j--)
            {
                if(get_piece(i, j) != NULL)
                {
                    return false;
                }
            }
            
        }
        else if(start_x > end_x && start_y > end_y) //left down
        {
            for(int i = start_x-1, j = start_y - 1; i>end_x && j>end_y; i--, j--)
            {
                if(get_piece(i, j) != NULL)
                {
                    return false;
                }
            }
        }
        else if(start_x > end_x && start_y < end_y) //left up
        {
            for(int i = start_x-1, j = start_y + 1; i>end_x && j<end_y; i--, j++)
            {
                if(get_piece(i, j) != NULL)
                {
                    return false;
                }
            }
        }
        else if(start_x < end_x && start_y < end_y) //right up
        {
            for(int i = start_x + 1, j = start_y + 1; i < end_x && j < end_y; i++, j++)
            {
                if(get_piece(i, j) != NULL)
                {
                    return false;
                }
            }
        }
        
    }
    
    //King Condition
    else if (piece_type == 'K')
    {
        //invalid if occupied by friendly color piece
        if(dest_piece != NULL && dest_piece->get_color() == curr_piece->get_color())
        {
            return false;
        }
    }
    
    //Pawn Condition
    else
    {
        char color = curr_piece->get_color();
        
        //COMMON COND: if  position in front is not free then invalid move irrespective of color
        if(start_y == end_y && dest_piece != NULL)
        {
            return false;
        }
        
        //if positions to the top left or top right are not occupied by enemy piece then invalid
        if(color == 'W' && start_y != end_y && (dest_piece == NULL || dest_piece->get_color()=='W'))
        {
            return false;
        }
        
        else if(color == 'B' && start_y != end_y && (dest_piece == NULL || dest_piece->get_color()=='B'))
        {
            return false;
        }
    }
    
    return true;
}

bool Board::check_end_dest(int end_x, int end_y, char color)const
{
    Piece * dest = get_piece(end_x, end_y);
    //check if friendly piece is present at dest
    if(dest!=NULL)
    {
        if(dest->get_color()==color)
        {
            return false;
        }
    }
    return true;
}


bool Board::check_valid_move(int start_x, int start_y, int end_x, int end_y)const
{
    //get pointer to the piece by finding it in the board
    Piece * curr_piece = get_piece(start_x, start_y);
    pair<int,int> dest(end_x,end_y);
    //all possible peice of the current piece
    vector<pair<int,int> > poss_moves = curr_piece->get_possible_moves();
    
    //check if end_dest is in list of possible moves
    if (find(poss_moves.begin(), poss_moves.end(), dest) == poss_moves.end())
    {
        return false;
    }
    
    //check if there is no obstruction between start and end
    else if(!(check_obstruction(start_x, start_y, end_x, end_y, curr_piece)))
    {
        return false;
    }
    //check if the end position does not contain a piece of the same color
    else if(!(check_end_dest(end_x, end_y, curr_piece->get_color())))
    {
        return false;
    }
    
    return true;
}

void Board::print_board()const
{
    cout<<"  -----------------------"<<endl;
    for(int i=7;i>-1;i--)
    {
        cout<<i+1<<'|';
        for(int j=0;j<8;j++)
        {
            if(board[i][j]!=NULL)
            {
                cout<<board[i][j]->get_color()<<board[i][j]->get_type()<<" ";
            }
            else
                cout<<".. ";
        }
        cout<<'|'<<endl;
    }
    cout<<"  -----------------------"<<endl;
    cout<<"  A  B  C  D  E  F  G  H "<<endl;

}

void Board::set_piece(Piece * new_piece, int end_x, int end_y)
{
    if(new_piece!=NULL)
    {
        new_piece->change_position(end_x, end_y);
    }
    
    board[end_x - 1][end_y - 1] = new_piece;
}

bool Board::move_piece(int start_x, int start_y, int end_x, int end_y)
{
    if(check_valid_move(start_x,start_y,end_x,end_y))
       {
           Piece * p = get_piece(start_x, start_y);
           p->change_position(end_x,end_y);
           board[end_x-1][end_y-1] = p;
           board[start_x-1][start_y-1] = NULL;
           p->change_move_list();
           return true;
       }
       return false;
}

Piece* Board::get_piece(int x, int y)const
{
    return board[x-1][y-1];
}

void Board::delete_from_piece_list(Piece * del_piece)
{
    char color = del_piece->get_color();
    vector<Piece*>::iterator it;
    if(color == 'W')
    {
        for(it=white_pieces.begin();it!=white_pieces.end(); it++)
        {
            if(*it == del_piece)
            {
                white_pieces.erase(it);
                return;
            }
        }
    }
    else
    {
        for(it=black_pieces.begin();it!=black_pieces.end(); it++)
        {
            if(*it == del_piece)
            {
                black_pieces.erase(it);
                return;
            }
        }
    }
}

void Board::delete_piece(int pos_x, int pos_y)
{
    Piece * del_piece = get_piece(pos_x, pos_y);
    if(del_piece != NULL)
    {
        delete_from_piece_list(del_piece);
        delete del_piece;
        del_piece = NULL;
    }
}


pair<int,int> Board::get_king_location(char color)const
{
    pair<int,int> ret;
    if(color == 'W')
    {
        for(int i=0;i<white_pieces.size();i++)
        {
            Piece * val = white_pieces[i];
            if(val->get_type()=='K')
            {
                ret = val->get_position();
                break;
            }
        }
    }
    else
    {
        for(int i=0;i<black_pieces.size();i++)
        {
            Piece * val = black_pieces[i];
            if(val->get_type()=='K')
            {
                ret = val->get_position();
                break;
            }
        }
    }
    return ret;
}


vector<Piece *> Board::get_all_pieces(char color)const
{
    if(color == 'W')
    {
        return white_pieces;
    }
    else
    {
        return black_pieces;
    }

}

char Board::get_enemy_color(char color)const
{
    if(color == 'W')
    {
        return 'B';
    }
    else
    {
        return 'W';
    }
}

bool Board::correct_piece_color(char color, int pos_x, int pos_y)const
{
    return (get_piece(pos_x, pos_y)->get_color() == color);
}

bool Board::only_kings_left()
{
    if(black_pieces.size()==1 && white_pieces.size()==1)
    {
        if(black_pieces[0]->get_type()=='K' && white_pieces[0]->get_type()=='K')
        {
            return true;
        }
    }
    return false;
}
