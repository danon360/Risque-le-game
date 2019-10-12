
#include <iostream>
#include "Cards.h"

using namespace std;


int main()
{

	Deck* deck = new Deck();
	deck->loadDeck(42);

	cout << endl << "Cards in hands test" << endl << endl;

	Hand* hand = new Hand();


	hand->add(Card(INFANTRY));
	hand->add(Card(ARTILLERY));
	hand->add(Card(INFANTRY));
	hand->add(Card(INFANTRY));
	hand->add(Card(CAVALRY));


	hand->Display();
	cout << endl;

	hand->exchange();

	 
	cout << "Cards Driver" << endl;
	return 0;


}
