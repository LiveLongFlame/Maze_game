/* 
	reinterpret_cast
	Purpose: Player method file 
 */

#include "player.h"
#include <iostream>
#include <string>
using namespace std;
Player::Player(const string name){
	this-> name = name;
}


void Player::setName(const string name){
	this->name = name;
}

string Player::getName(){
	return name;
}

void Player::move_set(){
	//todo: visulaise and print out the player move and add it to the score board
}


