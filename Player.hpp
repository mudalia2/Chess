#ifndef PLAYER_H
#define PLAYER_H

/*
 Player.hpp
 
 Class that defines all the characteristics of a player including his score, color and name.
 
 Chess
 Created by Vikram Mudaliar on 9/16/17.
 Copyright © 2017 VR. All rights reserved.
 */

#include <ostream>
#include <vector>
#include <utility>
using namespace std;

class Player
{
public:
    /*
     Constructor.
     
     @param color sets the players color.
     @param name sets the players name.
     @return NONE.
     */
    Player(char color, string name);
    
    /*
     Destructor.
     
     @param NONE.
     @return NONE.
     */
    ~Player();
    
    /*
     Getter function to obtain the players color.
     
     @param NONE.
     @return Return the color which can be W or B.
     */
    char get_color()const;
    
    /*
    Getter function to obtain the players name.
    
    @param NONE.
    @return Return the name of the player.
    */
    string get_name()const;
    /*
    Update the players score when he captures an opponents piece
    
    @param NONE.
    @return NONE.
    */
    void increment_score();
    
    /*
     Getter function to obtain the players score.
     
     @param NONE.
     @return Return the score of the player.
     */
    int get_score()const;
    
private:
    //score for the player
    int score;
    //color of the player
    char color;
    //name of the player
    string name;
};


#endif //Player_H
