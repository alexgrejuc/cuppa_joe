#include "player.hpp"
#include "utilities.hpp" 
#include <iostream>

using std::cout;
using std::endl;
/******************************************************************************
 * abstraction: a player controlled by a user in a game
 * purpose: model and store data for a player 
 * how-to: set info then place in a space 
 * functionality: get and set data, manage inventory
 * ***************************************************************************/

//constructors
Player::Player(){
	set_yx(-1, -1);
	icon = '@'; 
	special = false; //change to true if interaction is desired
	capacity = 2; //size of joe's inventory (small because his hands are his inventory) 
}

//allows coordinates to be start when object created
Player::Player(int y, int x){
	this->y = y;
	this->x = x;
	special = false;
	icon = '@';
	capacity = 3;
}


/******************************************************************************
 * description: getters and setters for player
 * args: self-explanatory 
 * restrictions: 
 * returns: self-explanatory
 * ***************************************************************************/
void Player::set_next(int y, int x){
	this->next_y = y;
	this->next_x = x;	
}

void Player::next_to_current(){
	next_y = y;
	next_x = x;
}
int Player::get_next_y(){
	return next_y;
}

int Player::get_next_x(){
	return next_x;
}

/******************************************************************************
 * description: allows x or y to be incremented/decremented (used to move Joe around)
 * args:
 * 		type: either + or -, to increment or decrement
 *		xy: either x or y, the coordinate to be changed
 * restrictions: type must be +/-, xy must be x/y
 * returns: none
 * ***************************************************************************/
void Player::inc_dec_next(char type, char xy){
	//increment or decrement y
	if(xy == 'y'){
		switch (type){
			case '+': next_y++; break;
			case '-': next_y--; break;
		}
	}
	//increment or decrement x
	else if(xy == 'x'){
		switch (type){
			case '+': next_x++; break;
			case '-': next_x--; break;
		}
	}
}

//interaction not used, here in case it is added 
int Player::interact(){
	cout << "nothing" << endl;
	return 0;
}

/******************************************************************************
 * description: displays the contents of Joe's hands or prints message if he
 * 				is holding nothing
 * args: none
 * restrictions: none
 * returns: none
 ****************************************************************************/
void Player::display(){
	//if joe is holding something
	if(hands.size() > 0){
		cout << "\nJoe is holding: " << endl;
		for(int i = 0; i < hands.size(); i++){
			cout << i << ")" << hands[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "Joe is not holding anything\n" << endl;
	}
	cout << endl;
}

/******************************************************************************
 * description: adds an object to joe's hands if they are not full
 * args: object, the object to be added
 * restrictions: none
 * returns: none
 ****************************************************************************/
void Player::add(string object){
	if(hands.size() < capacity && object != "nothing"){
		hands.push_back(object);
	}
	display(); //show what he is holding after it's added
}

/******************************************************************************
 * description: removes an item from joe's hands if he is holding something
 * args: none
 * restrictions: none
 * returns: the item that was removed (so it can be transferred to another)
 ****************************************************************************/
string Player::remove(){
	//if joe has something to remove 
	if(hands.size() > 0){
		display();
		int choice = -1;

		//use menu to get the object
		choice = menu (0, hands.size(), "Enter an item number to remove from Joe's hands: ");
		string object = hands[choice];
		hands.erase(hands.begin() + choice);
		return object;
	}
	else {
		cout << "Joe has nothing in his hands" << endl;
		return "nothing"; 
	}
}

/******************************************************************************
 * description: linear search through joe's hands for specified object
 * args: object, the object that is desired
 * restrictions: none
 * returns: none
 ****************************************************************************/
bool Player::has(string object) const{
	//iterate through joe's hands until the object is found or end is reached
	//return true if found, false if not
	for(int i = 0; i < hands.size(); i++){
		if(hands.at(i) == object)
			return true;
	}	
	return false;
}

//gets rid of everything in Joe's inventory (used in kitchen to make coffee)
void Player::drop_objects(){
	hands.clear();
}

//checks if Joe's hands are full
bool Player::at_capacity(){
	return (hands.size() == capacity);
}

