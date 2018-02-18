/******************************************************************************
 * program: cuppa_joe 
 * author: Alex Grejuc
 * date: 8/10/17
 * description: cuppa_joe, an ascii-based game in which the user tries to help
 * 				joe make and drink his morning cup of coffee so that he can
 * 				get to work before falling asleep. 
 * ***************************************************************************/

//#include "utilities.hpp"
//#include "iostream"
//#include "item.hpp"
#include "player.hpp"
#include "game.hpp"

/*
using std::string;
using std::cout;
using std::cin;
using std::endl;
*/

Player* Space::joe = new Player;

const int NUM_STEPS = 300; //number of steps before Joe falls asleep

int main(){

	Game g(NUM_STEPS);
	g.start();
	g.play();

	return 0;
}
