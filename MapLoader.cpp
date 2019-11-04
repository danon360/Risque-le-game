#include "MapLoader.h";

	string* fileLocation;

	MapLoader::MapLoader() {
		fileLocation = new string();
	}
	MapLoader::MapLoader(string location) {
		fileLocation = new string(location);
	}
	 
	Map* MapLoader::init() {
		vector<Continent*>* contVec = new vector < Continent*>();
		map<int, Country*>* countryMap = new map<int, Country*>();
		string* strContinents = new string();
		string* strCountries = new string();
		string* strBorders = new string();

		string* fileLocation = this->fileLocation;
		bool* noError = new bool();
		Map* map;


		*noError = loadFileToStrings(fileLocation, strContinents, strCountries, strBorders);

		if (!*noError) {
			MapLoaderException ex;
			throw ex;
		}

		contVec = continentLoader(*strContinents);

		countryMap = countryLoader(*strCountries,contVec);

		addBorders(*strBorders, countryMap);

		 map = new Map(countryMap,contVec);
		

		 return map;
	}

	bool verifier(string input) {
		input = trim(input);
		if (input.find("[continents]") == std::string::npos) {
			std::cerr << "error, could not find continents list" << endl;
			MapLoaderException ex;
			throw ex;
			// exit(1);
		}
		if (input.find("[countries]") == std::string::npos) {
			std::cerr << "error, could not find countries list" << endl;
			MapLoaderException ex;
			throw ex;
			// exit(1);
		} 
		if (input.find("[borders]") == std::string::npos) {
			std::cerr << "error, could not find borders list" << endl;
			MapLoaderException ex;
			throw ex;
			//exit(1);
		}
		
	}
 
	

	bool MapLoader::loadFileToStrings(string* fileLocation, string* continent, string* country, string* borders) {
		ifstream* infile;
		string* indata;
		stringstream* stream1;
		int* indexCountries, * indexContinents, * indexBorders;

		//initialising the objects infile and stream1
		infile = new ifstream();
		stream1 = new stringstream();

		//openning the file MAKE SURE FILE LOCATION IS CORRECT
		(*infile).open(*fileLocation);

		//making sure that the file is actually open
		if (!(*infile).is_open()) {
			cout << "problem with openning the map file.\nThe program will now terminate.";
			MapLoaderException ex;
			throw ex;
			//exit(1);
		}



		//loading file contents into stream
		*stream1 << (*infile).rdbuf();

		//assigning indata pointer to the newly created string containing the data of the .map file
		indata = new string((*stream1).str());

		//verifying that continents, countries, and borders and tags exist
		if (indata->find("[continents]") == std::string::npos) {
			std::cerr << "error, could not find borders list" << endl;
			return false;
		}
		if (indata->find("[countries]") == std::string::npos) {
			std::cerr << "error, could not find borders list" << endl;
			return false;
		}
		if (indata->find("[borders]") == std::string::npos) {
			std::cerr << "error, could not find borders list" << endl;
			return false;
		}

		//findex the starting index of continents
		indexContinents = new int((*indata).find("[continents]", 0));	//13 is to skip over the "[continents]" and start at the first continent right away
		//finding the starting index of countries
		indexCountries = new int((*indata).find("[countries]", 0));
		//finding the starting index of borders
		indexBorders = new int((*indata).find("[borders]", 0));

		

		//making sure the index reflects the actual starting position of the continents rather than the keyword [continents]
		*indexContinents += 13;

		//making sure the continents are listed first
		if (*indexCountries <= *indexContinents || *indexBorders <= *indexContinents) {
			cout << "erro : continents has to be the first section in the file" << endl;
			return false;
		}

		//making sure the countries are listed before borders
		if (*indexBorders <= *indexCountries) {
			cout << "erro : countries have to be listed before the borders" << endl;
			return false;
		}

		//generating a substring that would contain the list of continents
		*continent = trim(string((*indata).substr(*indexContinents, *indexCountries - *indexContinents)));	//note that we're doin indexcountrie-indexcontinents because the 2nd parameter takes 

		//making sure the index reflects the actual starting position of the countries rather than the keyword [countries]
		*indexCountries += 11;																									//a character length (from the starting point) rather than an ending index

		//generating a substring that would contain the list of countries
		*country = trim(string((*indata).substr(*indexCountries, *indexBorders - *indexCountries)));

		//making sure the index reflects the actual starting position of the borders rather than the keyword [borders]
		*indexBorders += 9;

		//generating a substring that would contain the list of borders
		*borders = trim(string((*indata).substr(*indexBorders)));

		//closing the file stream
		(*infile).close();

		//deleting pointers
		delete(infile);
		delete(indata);
		delete(stream1);
		delete(indexCountries);
		delete(indexContinents);
		delete(indexBorders);
		return true;
	}
	

	vector<Continent*>* MapLoader::continentLoader(string input) {

		input = trim(input);
		// pointer to keep track of the start of the line
		int* startLine = new int(0);
		//pointer to keep track of the ending index of the 1st word in a line
		int* wordEnd = new int();
		//pointer to keep track of the ending index of the 2nd word in the line (which is the bonus)
		int* bonusEnd = new int();
		//string to hold the name of the continent
		string* contName = new string();
		//int to hold the bonus amount for each continent
		int* bonus = new int();
		//int to hold the total number of continents
		int* numOfContinents = new int(count(input.begin(), input.end(), '\n') + 1);
		//vector tostore the continent objects in
		vector<Continent*>* contVec = new vector<Continent*>();
		

		for (int i = 0; i < *numOfContinents - 1; i++) {		//-1 is importan. We want to deal with the last line seperately 

			//calculating indexes of wordEnd and bonusEnd
			*wordEnd = input.find(' ', *startLine);
			*bonusEnd = input.find(' ', *wordEnd + 1);

			//checking if the line is a comment
			if (input.substr(*startLine, 1).compare(";") == 0) {
				*startLine = input.find('\n', *startLine + 1);
				continue;
			}

			//converting bonus from string to int and saving it into the bonus pointer
			*bonus = stoi(trim(input.substr(*wordEnd, *bonusEnd - *wordEnd)));

			*contName = trim(input.substr(*startLine, *wordEnd - *startLine));

			Continent a = Continent(*bonus, i, *contName);

			(*contVec).push_back(new Continent(*bonus,i, *contName));

			//recalculating startline and endline
			*startLine = input.find('\n', *startLine + 1);

		}

		//Manualy recalculating indexes of the last line an adding the last object to the vectot
		*wordEnd = input.find(' ', *startLine);
		*bonusEnd = input.find(' ', *wordEnd + 1);
		//converting the bonus from string to int and saving it into the bonus pointer
		*bonus = stoi(trim(input.substr(*wordEnd, *bonusEnd - *wordEnd)));
		(*contVec).push_back(new Continent(*bonus ,*numOfContinents - 1, trim(input.substr(*startLine, *wordEnd - *startLine))));

		//removing any unused allocations
		(*contVec).shrink_to_fit();

		//TODO:delete pointers
		delete(startLine);
		delete(wordEnd);
		delete(bonusEnd);
		delete(contName);
		delete(bonus);
		delete(numOfContinents);

		return contVec;
	}


	map<int, Country*>* MapLoader::countryLoader(string input, vector<Continent*>* contVec) {

		input = trim(input);
		// pointer to keep track of the start of the line
		int* startLine = new int(0);
		//pointer to keep track of the ending index of the 1st word in a line (which is country ID number)
		int* idEnd = new int();
		//pointer to keep track of the 2nd word in the line (which is the name of the country)
		int* nameEnd = new int();
		//pointer to keep track of the ending index of the 3rd word in the line (which is the continent number)
		int* continentEnd = new int();
		//string to hold the name of the continent
		string* countryName = new string();
		//int to hold the bonus amount for each continent
		int* ID = new int();
		int* continentNum = new int();
		//int to hold the total number of continents
		int* numOfCountries = new int(count(input.begin(), input.end(), '\n') + 1);
		//map tostore the continent objects in
		map<int, Country*>* countryMap = new map<int, Country*>();
		//country pointer that points to the country we wish to add to the map/vector
		Country* addedCountry;

		for (int i = 0; i < *numOfCountries - 1; i++) {		//-1 is importan. We want to deal with the last line seperately 

			//calculating indexes of idEnd, nameEnd, and continentEnd
			*idEnd = input.find(' ', *startLine);
			*nameEnd = input.find(' ', *idEnd + 1);
			*continentEnd = input.find(' ', *nameEnd + 1);

			//checking if the line is a comment
			if (input.substr(*startLine, 1).compare(";") == 0) {
				*startLine = input.find('\n', *startLine + 1);
				continue;
			}
			*ID = stoi(trim(input.substr(*startLine, *idEnd - *startLine)));

			//converting the continent number from string to int and storing it in the continentNum pointer
			*continentNum = stoi(trim(input.substr(*nameEnd, *continentEnd - *nameEnd)));

			*countryName = trim(input.substr(*idEnd, *nameEnd - *idEnd));

			//constructing the country object we wish to add to both the vector and map
			addedCountry = new Country(*countryName, *ID, *continentNum, 0);
			//loading the country and the key into the map
			(*countryMap).emplace((* ID), addedCountry);
			contVec->at(*continentNum - 1)->addCountry(addedCountry);
			//recalculating startline
			*startLine = input.find('\n', *startLine + 1);
		}


		//Manualy recalculating indexes of the last line an adding the last object to the vector

		*idEnd = input.find(' ', *startLine);
		*nameEnd = input.find(' ', *idEnd + 1);
		*continentEnd = input.find(' ', *nameEnd + 1);
		//converting the ID and  continent number ffrom string to int and storign them in their variables
		*ID = stoi(trim(input.substr(*startLine, *idEnd - *startLine)));
		*continentNum = stoi(trim(input.substr(*nameEnd, *continentEnd - *nameEnd)));
		//loading the country name from the input string to its variable
		*countryName = trim(input.substr(*idEnd, *nameEnd - *idEnd));
		//loading the last country intothe map
		(*countryMap).emplace((*ID), new Country(*countryName, *ID, *continentNum-1, 0));

		contVec->at(*continentNum - 1)->addCountry(new Country(*countryName, *ID, *continentNum, 0));
		//TODO:delete pointers
		delete(startLine);
		delete(idEnd);
		delete(nameEnd);
		delete(continentEnd);
		delete(countryName);
		delete(ID);
		delete(continentNum);
		delete(numOfCountries);

		return countryMap;
	}

	bool MapLoader::addBorders(string input, map<int, Country*>* country) {
		input = trim(input);
		//int pointer to keep track of how many lines we have
		int* numOflines = new int(count(input.begin(), input.end(), '\n') + 1);
		//int pointer that keeps track of the beggining of a single line
		int* startLine = new int(0);
		//int pointer that keeps track of the end of a single line
		int* endLine = new int();
		//int pointer that holds the number of borders are being added to a country
		int* borders = new int();
		//int pointer that holds the index before the country id number
		int* beforeNumber = new int(0);
		//int pointer that holds the index after the country id number
		int* afterNumber = new int();
		//int pointer that holds the id of the country being added
		int* borderID = new int();
		//int pointer that holds the id of the country we're addind the borders to
		int* currentCountryId = new int();
		//string pointer that contains 1 line of borders
		string* line = new string();


		for (int i = 0; i < *numOflines - 1; i++) {
			//pointer to keep track of the end of the line
			*endLine = input.find('\n', *startLine + 1);
			*line = trim(input.substr(*startLine, *endLine - *startLine));
			*borders = count((*line).begin(), (*line).end(), ' ');
			*beforeNumber = (*line).find(' ');

			//checking if the line is a comment
			if (input.substr(*startLine, 1).compare(";") == 0) {
				*startLine = input.find('\n', *startLine + 1);
				continue;
			}

			*currentCountryId = stoi(trim((*line).substr(0, *beforeNumber)));

			for (int j = 0; j < *borders; j++) {

				*afterNumber = (*line).find(' ', *beforeNumber + 1);
				//retreiving the border ID
				*borderID = stoi(trim((*line).substr(*beforeNumber, *afterNumber - *beforeNumber)));

				//adding the border to the selected country
				//country->at(*currentCountryId).addCountry(country-> at(*borderID));
				country->at(*currentCountryId)->addCountry(country->at(*borderID));
				*beforeNumber = *afterNumber;
			}
			*startLine = *endLine;
		}
		*endLine = input.length();
		*line = trim(input.substr(*startLine, *endLine - *startLine));
		*borders = count((*line).begin(), (*line).end(), ' ');
		*beforeNumber = (*line).find(' ');
		*currentCountryId = stoi(trim((*line).substr(0, *beforeNumber)));
		for (int j = 0; j < *borders; j++) {
			*afterNumber = (*line).find(' ', *beforeNumber + 1);
			*borderID = stoi(trim((*line).substr(*beforeNumber, *afterNumber - *beforeNumber)));
			//country.at(*currentCountryId - 1).addBorder(country.at(*borderID));
			country->at(*currentCountryId)->addCountry(country->at(*borderID));
			*beforeNumber = *afterNumber;
		}

		return true;
	}

//trims any whitespace from both sides of the string 
static inline string trim(string input) {
	string* returnStr = new string(input);
	while ((*returnStr)[(*returnStr).length() - 1] == ' ' || (*returnStr)[(*returnStr).length() - 1] == '\n') {
		(*returnStr) = (*returnStr).substr(0, (*returnStr).length() - 1);
	}
	while ((*returnStr)[0] == ' ' || (*returnStr)[0] == '\n') {
		(*returnStr) = (*returnStr).substr(1, (*returnStr).length());
	}
	return *returnStr;
}