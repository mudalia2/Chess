/*
 Game.cpp
 Chess
 
 Created by Vikram Mudaliar on 9/16/17.
 Copyright © 2017 VR. All rights reserved.
 */

#include "Game.hpp"
#include <iostream>
using namespace std;

const int TOTAL_PIECES = 13;

Game::Game()
{
    chessboard = new Board();
    active_player = 0; //White goes first
    letter_to_idx['A']=1;
    letter_to_idx['B']=2;
    letter_to_idx['C']=3;
    letter_to_idx['D']=4;
    letter_to_idx['E']=5;
    letter_to_idx['F']=6;
    letter_to_idx['G']=7;
    letter_to_idx['H']=8;
    
}

bool Game::check_condition(char player_color)
{
    char enemy_color = chessboard->get_enemy_color(player_color);
    pair<int,int> king_loc = chessboard->get_king_location(player_color);
    vector<Piece *> enemy_pieces = chessboard->get_all_pieces(enemy_color);
    int num_of_enemy_pieces = (int)enemy_pieces.size();
    
    for(int i=0;i<num_of_enemy_pieces;i++)
    {
        pair<int,int> piece_loc =enemy_pieces[i]->get_position();
        if(chessboard->check_valid_move(piece_loc.first, piece_loc.second, king_loc.first, king_loc.second))
        {
            return true;
        }
    }
    
    return false;
}

bool Game::check_mate_condition(char player_color)
{
    //condition where King can escape check by moving to one of its eight valid positions
    int dir[]={-1,0,1};
    
    
    for(int k =0;k<3;k++)
    {
        for(int l =0;l<3;l++)
        {
            pair<int,int> king_loc = chessboard->get_king_location(player_color);
            int new_x = king_loc.first+dir[k];
            int new_y = king_loc.second+dir[l];
            if((new_y>0 && new_y<=8) && (new_x>0 && new_x<=8) && !(dir[k]==0 && dir[l]==0))
            {
                chessboard->move_piece(king_loc.first, king_loc.second, new_x, new_y);
                
                //if moving the king to possible location results in breaking out of the check condition
                if(!check_condition(player_color))
                {
                    //move piece back
                    chessboard->move_piece(new_x, new_y, king_loc.first, king_loc.second);
                    return false;
                }
                
                chessboard->move_piece(new_x, new_y, king_loc.first, king_loc.second);
            }
        }
    }
    
    //condition where another friedly piece can intercept and help the king out
    
    //get all friednly pieces
    vector<Piece*> friendly_pieces = chessboard->get_all_pieces(player_color);
    for(int i =0;i<friendly_pieces.size();i++)
    {
        Piece * start_piece =friendly_pieces[i];
        //location of current piece
        pair<int,int> piece_pos = start_piece->get_position();
        vector<pair<int, int> > poss_moves = start_piece->get_possible_moves();
        //iterate through all possible moves for this current piece
        for(int j =0;j<poss_moves.size();j++)
        {
            Piece * end_piece = chessboard->get_piece(poss_moves[j].first, poss_moves[j].second);

            //check if a possible move is a valid move
            if(chessboard->check_valid_move(piece_pos.first, piece_pos.second, poss_moves[j].first, poss_moves[j].second))
            {
                
                
                chessboard->set_piece(start_piece, poss_moves[j].first, poss_moves[j].second);
                // Check if this current board config for color_player is in check.
                if(check_condition(player_color))
                {
                    //if yes, return false as it will be an invalid move
                    // set the piece back
                    chessboard->set_piece(start_piece, piece_pos.first , piece_pos.second);
                    chessboard->set_piece(end_piece, poss_moves[j].first, poss_moves[j].second);
                    continue;
                    //Return pieces to original location
                }
                else
                {
                    chessboard->set_piece(start_piece, piece_pos.first , piece_pos.second);
                    chessboard->set_piece(end_piece, poss_moves[j].first, poss_moves[j].second);
                    return false;
                }
            }
        }
    }
    return true; // Player in checkmate
}

void Game::game_loop()
{
    string p1,p2;
    bool valid_move_parse = 0, valid_move_board =0, check_mate_flag =0, draw_flag=0;
    
    vector<int> moves;
    cout<<"Enter Player 1's Name"<<endl;
    cin>>p1;
    cout<<"Enter Player 2's Name"<<endl;
    cin>>p2;
    
    //set player names
    set_players(p1, p2);
    
    //start game and print out the board
    cout<<"==== BEGIN GAME ===="<<endl;
    chessboard->print_board();
    
    //get valid input
    while(!check_mate_flag)
    {
        string move_input;
        cout<<players[active_player]->get_name()<< ": Enter Move"<<endl;
        cin>>move_input;

        moves = parse_input(move_input);
        if(moves.size()==0)
        {
            cout<<"Invalid Move!! Enter Again!! (EX:A1,A3)"<<endl;
        }
        else
            valid_move_parse = 1;
        
        //check if move input is valid
        if(valid_move_parse)
        {
            /* Conditions:
             1. Check if piece being moved belongs to the active player
             2. Check if move itself is valid
             3. Check if move results in self check.
            */
            if(chessboard->correct_piece_color(players[active_player]->get_color(), moves[0], moves[1]) && chessboard->check_valid_move(moves[0], moves[1], moves[2], moves[3]) && !move_results_in_selfcheck(players[active_player]->get_color(), moves[0], moves[1], moves[2], moves[3]))
            {
                
                chessboard->delete_piece(moves[2], moves[3]);
                chessboard->move_piece(moves[0], moves[1], moves[2], moves[3]);
                chessboard->print_board();
                valid_move_board =1;
            }
            else
            {
                cout<<"Invalid Move!!! Enter Valid Move!!!"<<endl;
                valid_move_parse =0;
            }
            
        }
        
        //check if opp is in check and checkmate
        if(valid_move_board)
        {
            //check enemy is in check
            if(check_condition(players[1-active_player]->get_color()))
            {
                cout<<players[1-active_player]->get_name()<< "  is in Check!!!!!!!!"<<endl;
                //then check if enemy is checkmate as well
                if(check_mate_condition(players[1-active_player]->get_color()))
                {
                    check_mate_flag =1;
                    break;
                }
            }
        
            update_score();
            
            //If both players have only kings left, then it is a DRAW
            if(chessboard->only_kings_left())
            {   draw_flag=1;
                break;
            }
            //enemy is not in check then switch players
            //reset flags & switch player
            valid_move_board=0;
            valid_move_parse=0;
            active_player = 1-active_player;
        }
    }
    //if draw
    if(draw_flag)
        cout<<"==== DRAW GAME ===="<<endl<<endl;
    
    //Game over print winner
    cout<<"==== GAME OVER ===="<<endl<<endl;
    cout<<players[active_player]->get_name()<<": WINS THE GAME!!"<<endl;
}

void Game::set_players(string p1, string p2)
{
    players[0] = new Player('W', p1);
    players[1] = new Player('B', p2);
    
}


vector<int> Game::parse_input(string input)
{
    vector<int> ret;
    int start_y, end_y, start_x, end_x;
    if((input[0]>='A' && input[0]<='H') && input[3]>='A' && input[3]<='H')
    {
        start_y = letter_to_idx[input[0]];
        end_y = letter_to_idx[input[3]];
    }
    else
        return ret;
    
    if((input[1]>='1' && input[1]<='8') && input[4]>='1' && input[4]<='8')
    {
        start_x = input[1]-'0';
        end_x = input[4]-'0';
    }
    else
        return ret;
    
    ret.push_back(start_x);
    ret.push_back(start_y);
    ret.push_back(end_x);
    ret.push_back(end_y);
    
    return ret;
    
}


bool Game::move_results_in_selfcheck(char color, int start_x, int start_y, int end_x, int end_y)
{
    //get piece at the end
    Piece * end_piece = chessboard->get_piece(end_x, end_y);
    Piece * start_piece = chessboard->get_piece(start_x, start_y);
    chessboard->set_piece(start_piece, end_x, end_y);
    // Check if this current board config for color_player is in check.
    if(check_condition(color))
    {
        //if yes, return true as it will be an invalid move
        
        //Return pieces to original location
        chessboard->set_piece(start_piece, start_x, start_y);
        chessboard->set_piece(end_piece,end_x, end_y);
        return true;
    }
    chessboard->set_piece(start_piece, start_x, start_y);
    chessboard->set_piece(end_piece,end_x, end_y);
    return false;
}

void Game::update_score()
{
    //update score of current TOTAL_PIECES - current player's score is less than number of opponent pieces left
    if((TOTAL_PIECES-players[active_player]->get_score()) > chessboard->get_all_pieces(players[1-active_player]->get_color()).size())
    {
        players[active_player]->increment_score();
    }
}







