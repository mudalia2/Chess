/*
 Player.cpp
 Chess
 
 Created by Vikram Mudaliar on 9/16/17.
 Copyright © 2017 VR. All rights reserved.
 */

#include "Player.hpp"
#include <iostream>
using namespace std;

Player::Player(char color, string name)
{
    this->color = color;
    this->name = name;
    this->score = 0;
}

Player::~Player()
{
    
}

char Player::get_color()const
{
    return color;
}

string Player::get_name()const
{
    return name;
}

void Player::increment_score()
{
    score++;
}

int Player::get_score()const
{
    return score;
}
