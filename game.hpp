#ifndef GAME_HPP
#define GAME_HPP

#include "item.hpp"
#include "player.hpp"
#include "space.hpp"
#include "bedroom.hpp"
#include "hall.hpp"
#include "storage.hpp"
#include "kitchen.hpp"
#include "liv_room.hpp"
#include "outside.hpp"
#include "utilities.hpp" 

//messages shown in beginning of game
const string WELCOME =	"Welcome to Joe's life! Joe is a sleepy individual and\n"
						"he really needs your help getting his morning coffee.\n"
						"Guide him along from room to room so he can drink some\n" 
						"coffee and go to work. Be careful, however! If you don't\n"
						"get him his coffee quickly enough he will fall back" 
						" asleep\nGood luck!\n\n";

const string HELP = 	"\nUse w, a, s, d (up, left, down, right, respectively)\n"
						"to move around, v to view the objects that Joe has in his\n"
						"hands, and e to interact (must be around a special item).\n"
						"Interact with a door (}) to go to the next room\n";

const string KEY = 		"\nKey: [.] floor [#] wall [}] door [@] Joe\n";

const string NEXT = "\nPress enter to continue ";
						
class Game{
	private:
		//the six rooms of the game
		Bedroom b_room;
		Hall hallway;
		Storage store_room;
		Kitchen kitchen;
		Liv_room living_room;
		Outside outdoors;

		//track where the player is and was
		Space* room, *prev_room;
		void set_links();
		int steps;	
	public:
		Game(int = 100);
		void start();
		void play();
};

#endif
