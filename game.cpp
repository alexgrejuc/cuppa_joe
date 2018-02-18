#include "game.hpp"

#include <iostream>
using std::endl;
using std::cin;
using std::cout;

/******************************************************************************
 * abstraction: a game interface
 * purpose: to setup and run the game
 * how-to: call Game.play()
 * functionality: sets game up and plays it
 * ***************************************************************************/

/******************************************************************************
 * description: default constructor
 * args: steps, the number of steps that the game runs for
 * restrictions: none
 * returns: none
 * ***************************************************************************/
Game::Game(int steps){
	this->steps = steps;
}

/******************************************************************************
 * description: sets the links for each room so that doors will allow player
 * 				to traverse from room to room.
 * args: none
 * restrictions: none
 * returns: none
 * ***************************************************************************/
void Game::set_links(){
	//arguments: top, right, bottom, left
	b_room.set_links(nullptr, &hallway, nullptr, nullptr);
	hallway.set_links(nullptr, &store_room, nullptr, &b_room);
	store_room.set_links(nullptr, &kitchen, nullptr, &hallway);	
	kitchen.set_links(nullptr, nullptr, &living_room, &store_room);
	living_room.set_links(&kitchen, nullptr, &outdoors, nullptr);
	outdoors.set_links(&living_room, nullptr, nullptr, nullptr);
}

/******************************************************************************
 * description: starts the game by setting up the links and printing the
 * 				welcome message
 * args: none
 * restrictions: none
 * returns: none
 * ***************************************************************************/

void Game::start(){
	string action; //used to wait until user presses enter
	set_links();	
	room = prev_room = &b_room;

	//print wlecome message
	cout << string(50, '\n');	
	cout << WELCOME << HELP << KEY << NEXT;
	getline(cin, action);
	cout << string(50, '\n');
}

/******************************************************************************
 * description: plays the game by getting user input, updating, and displaying
 * 				each room
 * args: none
 * restrictions: none 
 * returns: none
 * ***************************************************************************/
void Game::play(){
	char c = 'e'; //determines action, updated by menu function

	do {
		cout << string(60, '\n'); 

		if(steps > 0){ 
			if(c != 'q'){
				room->set_action(c);
				if( room->update() ){ //room does not update if player leave is
					room->display();
				}
				else{
					//move to next room 
					room->traverse_room();
					room = room->get_next_room();

					//final room points to nullptr to signify end of game
					if(room!= nullptr){ 
						room->enter_room(prev_room);
						prev_room = room;
						room->display();
					}
					else{
						break; //break if the game is over
					}
				}
				cout << "Number of steps before Joe falls asleep: " << steps << endl;
				c = game_menu("Enter w, a, s, d, e, v, or q: ", "wasdeqv");
				steps--;
			}
		}
		else{ //if joe is out of steps
			cout << "Oh no! Joe ran out of energy and fell asleep. Game over." << endl;
			break; //end game
		}
	
	} while(c != 'q'); //while user does not wish to quit

	if(room == nullptr) cout << "Congratulations! Joe safely got to work" << endl;
	else cout << "Sorry, better luck next time" << endl;
}

/******************************************************************************
 * description:
 * args: 
 *		
 * restrictions: 
 * returns:
 * ***************************************************************************/

