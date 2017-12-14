/*
 Board.hpp
 
 Class that defines all the logic and functionality of the chessboard. It moves, deletes and makes pieces. Finally it also makes sure all moves attempted by the various piece are valid.
 
 Chess
 Created by Vikram Mudaliar on 9/16/17.
 Copyright © 2017 VR. All rights reserved.
 */

#ifndef BOARD_H
#define BOARD_H

#include <ostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include "Piece.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Rook.hpp"
#include "Pawn.hpp"

class Board
{
public:
    /*
     Constructor that sets the board with all ppieces in their correct starting positions.
     
     @param NONE.
     @return NONE.
     */
    Board();
    
    /*
     Checks if the move from the starting position to the ending position is not obstructed by any other piece. We take in the current piece pointer as well to obtain all the possible moves it can make and check if whether any of the moves it can make between start and dest has another piece.
     
     @param start_x starting x cordinate of the piece.
     @param start_y starting y cordinate of the piece.
     @param end_x ending x cordinate of the piece.
     @param end_y ending y cordinate of the piece.
     @param curr_piece pointer to the current piece being moved.
     @return True if there are no obstructions between the start and end positions.
     */
    bool check_obstruction(int start_x, int start_y, int end_x, int end_y, Piece * curr_piece)const;
    
    /*
     Checks if the ending position has a piece of the same color being moved. It deems a move invalid if a piece is trying to occupy a position already occupied by another peice of the same color
     
     @param end_x ending x cordinate of the piece.
     @param end_y ending y cordinate of the piece.
     @param color color of the piece being moved
     @return True if the end destination does not contain a piece of the same color
     */
    bool check_end_dest(int end_x, int end_y, char color)const;
    
    /*
     Checks if the move from the starting position to the ending position is valid. It first checks if the move is in the valid list of possible mves for that piece. It then invokes check_obstruction and check_end_dest.
     
     @param start_x starting x cordinate of the piece.
     @param start_y starting y cordinate of the piece.
     @param end_x ending x cordinate of the piece.
     @param end_y ending y cordinate of the piece.
     @return True if the move is valid, False if one of the three conditions fails.
     */
    bool check_valid_move(int start_x, int start_y, int end_x, int end_y)const;
    
    /*
     Prints the board to STDOUT with current peice positions

     @param NONE.
     @return NONE.
     */
    void print_board()const;
    
    /*
        Similar to move_piece but is used to move pieces temporarily to a new location
     
     @param end_x ending x cordinate of the piece.
     @param end_y ending y cordinate of the piece.
     @param Piece pointer to piece being moved
     @return NONE.
     */
    void set_piece(Piece * new_piece, int end_x, int end_y);
    
    /*
     Function to actually move one piece from start to end location, changes the board values at the start and end to reflect the change in location and finally updates the piece's move list
     
     @param start_x starting x cordinate of the piece.
     @param start_y starting y cordinate of the piece.
     @param end_x ending x cordinate of the piece.
     @param end_y ending y cordinate of the piece.
     @return True if the is move is valid and completed
     */
    bool move_piece(int start_x, int start_y, int end_x, int end_y);
    
    /*
     Return pointer to the piece present at pos_x and pos_y on the board
     
     @param x x position of the piece you want.
     @param y y position of the piece you want.
     @return Piece pointer to the piece at pos x&y.
     */
    Piece * get_piece(int x, int y)const;
    
    /*
     Delete a piece from the piece list. It will search the corresponding piece list of the same list, find the piece and remove it.
     
     @param Piece pointer to the piece that needs to be removed from the list.
     @return NONE
     */
    void delete_from_piece_list(Piece * del_piece);
    
    /*
     Delete a piece from the board. Given the x and y position of the piece from the board, the function will call the destrcutor for the particular piece and delete it. Used when piece is captured by enemy.
     
     @param x x position of the piece you want to delete.
     @param y y position of the piece you want to delete.
     @return NONE
     */
    void delete_piece(int pos_x, int pos_y);
    
    /*
     Obtain the location of the king given the color of the piece.
        
    @param color color of the king piece whose location you want.
    @return pair containing the x and y location of the specified color king
    */
    pair<int,int> get_king_location(char color)const;
    
    
    /*
     Getter function to obtain the piece list of the particular color
     
     @param color color of the piece list you want.
     @return list containing all the availble pieces of the specified color
     */
    vector<Piece *> get_all_pieces(char color)const;
    
    /*
     Getter function to obtain the color of the enemy given the players color
     
     @param color color of the current player.
     @return color of the enemy player.
     */
    char get_enemy_color(char color)const;
    
    /*
     Checks whether the color of the piece of pos x and y is the same as the color of the player being passed in
     
     @param color color of the player.
     @param x x position of the piece whose color you want to check.
     @param y y position of the piece whose color you want to check.
     @return True is the color of the piece and player passed in match
     */
    bool correct_piece_color(char color, int pos_x, int pos_y)const;
    
    /*
     Checks whether only the King piece is present in both the black and white piece list which results in a draw
     
     @return True if only Kings present in either list
     */
    bool only_kings_left();

    
private:
    //list containing a list of Piece pointers that represent the board in its entirety
    vector<vector<Piece *> > board;
    //list of all the white pieces
    vector<Piece *> white_pieces;
    //list of all the black pieces
    vector<Piece *> black_pieces;

};


#endif
