#ifndef GAME_H
#define GAME_H

#include <ostream>
/*
 Game.hpp
 
 Class that defines all the logic for the actuall Chess game itself. It decides which and when players take turns. It handles the input and output for the game
 
 Chess
 Created by Vikram Mudaliar on 9/16/17.
 Copyright © 2017 VR. All rights reserved.
 */

#include <vector>
#include <utility>
#include "Board.hpp"
#include "Player.hpp"


class Game
{
public:
    /*
     Constructor that creates a new board and two players. It also initializes the unordered_map that is used to translate Letter moves to Board indices
     
     @param NONE.
     @return NONE.
     */
    Game();
    
    /*
     Handles the functionality of the Check condition. Takes in the color of the player and returns a bool accordingly
     
     @param color color of the player who you want to check for the condition
     @return True if the player of color being input is in Check.
     */
    bool check_condition(char color);
    
    /*
     Handles the functionality of the Check Mate condition. Takes in the color of the player and returns a bool accordingly
     
     @param color color of the player who you want to check for the condition
     @return True if the player of color being input is in CheckMate.
     */
    bool check_mate_condition(char color);
    
    /*
     Main Game loop, handles all the input and output. Uses other functions to decide each move's validity, piece movement and check/checkmate conditons. This funcion is called from the main.cpp file.
     
     @param NONE.
     @return NONE.
     */
    void game_loop();
    
    /*
     Setter function to initialize the list of players with their respective colors and names
     
     @param p1 name of player 1.
     @param p2 name of player 2.
     @return NONE.
     */
    void set_players(string p1, string p2);
    
    /*
    Parses the input from STDIN and checks if the input is valid
    
    @param input STDIN from the user that needs to parsed.
    @return vector containing 4 integers(start_x,start_y,end_x,end_y). Vector is empty if invalid, Vector is of size 4 if valid
    */
    vector<int> parse_input(string input);
    
    /*
    Checks whether a move being implemented by the player results in them coming into the Check condition. Making a move that results in you being check is invalid
    
     @param color color of the current player.
     @param start_x starting x cordinate of the piece.
     @param start_y starting y cordinate of the piece.
     @param end_x ending x cordinate of the piece.
     @param end_y ending y cordinate of the piece.
     @return True if move results in self-check.
     */
    bool move_results_in_selfcheck(char color, int start_x,int start_y,int end_x,int end_y);
    
    /*
     Checks whether there is adifference between the number of opponent pieces and total pieces to update the players score
     
     @param NONE
     @return NONE
     */
    void update_score();

private:
    //Pointer to a Board object
    Board * chessboard;
    //Array containing two player pointers
    Player * players [2];
    //Index to the players array indicating which player's turn it currently is
    int active_player;
    //hashmap to help map the letter moves to board indices
    unordered_map<char, int> letter_to_idx;
};


#endif //GAME_H
