#include "Reader.h";

int main() {
	//initialising the objects infile and stream1
	infile = new ifstream();
	stream1 = new stringstream();

	//openning the file MAKE SURE FILE LOCATION IS CORRECT
	(*infile).open("C:\\Users\\sim\\Desktop\\DiscWorld.map");
	
	//making sure that the file is actually open
	if (!(*infile).is_open()) {
		cout << "problem with openning the map file.\nThe program will now terminate.";
			return 1;
	}
	
	//loading file contents into stream
	*stream1 << (*infile).rdbuf();

	//assigning indata pointer to the newly created string containing the data of the .map file
	indata = new string((*stream1).str());

	//	indata = new string();
	//	getline(*infile, *indata,'\n');

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
		return 1;
	}

	//making sure the countries are listed before borders
	if (*indexBorders <= *indexCountries) {
		cout << "erro : countries have to be listed before the borders" << endl;
		return 1;
	}

	//generating a substring that would contain the list of continents
	strContinents = new string((*indata).substr(*indexContinents, *indexCountries - *indexContinents));	//note that we're doin indexcountrie-indexcontinents because the 2nd parameter takes 

	//making sure the index reflects the actual starting position of the countries rather than the keyword [countries]
	*indexCountries += 11;																									//a character length (from the starting point) rather than an ending index

	//generating a substring that would contain the list of countries
	strCountries = new string((*indata).substr(*indexCountries, *indexBorders - *indexCountries));

	//making sure the index reflects the actual starting position of the borders rather than the keyword [borders]
	*indexBorders += 9;

	//generating a substring that would contain the list of countries
	strBorders = new string((*indata).substr(*indexBorders));

	cout << *strCountries << endl;

	//closing the file stream
	(*infile).close();
	return 0;
}
