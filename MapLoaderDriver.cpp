#include "MapLoader.h"

int main() {
	vector<string> locations = vector<string>();
	
	locations.push_back("C:\\Users\\Dan\\Dropbox\\Concordia\\7 - Fall 2019\\COMP 345 - Advance program design with C++\\RiskLocal\\Maps\\solar.map");
	int display= 0;
	int index =0;
	int country = 0;
	vector<Map*> maps = vector<Map*>(locations.size());
	
	for (int i = 0; i < locations.size();i++) {
		maps.at(i) = MapLoader(locations.at(i)).init();
		
	}
	while(index != -1){
		cout << "please specify which map do you want to see 0 - " << locations.size()-1 << "\n type -1 to exit"<< endl;
		std::cin >> index;
		if (index < 0) { // exit loop and terminate
			std::cout << "Thank you for using the maploader! Have a lovely day :)" << std::endl;
			break;
		}
				for (int i = 0; i < maps.at(index)->continents->size(); i++) {
					for (int j = 0; j < maps.at(index)->continents->at(i)->countries->size(); j++) {
						cout << " ID: "<<maps.at(index)->continents->at(i)->countries->at(j)->getID() << " Name: " << maps.at(index)->continents->at(i)->countries->at(j)->getName() << " Belongs to continent " << maps.at(index)->continents->at(i)->getName() << endl;
					}
				}	
		
	}
	return 0;
}

