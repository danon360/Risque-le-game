#include "Reader.h";
class continent {
public:
	int number,bonus;
	string name;

	continent() {
		number = 0;
		name = "";
	}
	continent(int numb, string str,int Bonus) {
		number = number;
		name = str;
		bonus = Bonus;
	}
	string toString() {
		return this->name;
	}
	int getBonus() {
		return this->bonus;
	}
};
class country {
	string name;
	int continent,ID;
public:
	country() {
		name= string(" ");
	}
	country(int id, string nm, int cont) {
		ID = id;
		name = nm;
		continent = cont;
	}
	string toString() {
		return this->name;
	}
	int getId() {
		return this->ID;
	}
	int getCont() {
		return this->continent;
	}
	void addBorder(int border) {
		cout << this->ID<< " : added border " << border << endl;
	}
};

int main() {
	ifstream* infile;
	string* indata;
	stringstream* stream1;
	string* strBorders, * strCountries, * strContinents;
	int* indexCountries, * indexContinents, * indexBorders;
	vector<continent>* contVec;
	vector<country>* countryVec;

	//initialising the objects infile and stream1
	infile = new ifstream();
	stream1 = new stringstream();

	//openning the file MAKE SURE FILE LOCATION IS CORRECT
	(*infile).open("C:\\Users\\sim\\Desktop\\artic.map");

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

	//generating a substring that would contain the list of borders
	strBorders = new string((*indata).substr(*indexBorders));
	
	contVec = continentLoader(*strContinents);

	countryVec = countryLoader(*strCountries);
	
	cout << "List of continents : " << endl;
	for (int i = 0; i < (*contVec).size(); i++) {
		cout << (*contVec).at(i).toString()<<" "<< (*contVec).at(i).getBonus() <<endl;
	}
	
	cout << "List of countries : " << endl;
	for (int i = 0; i < (*countryVec).size(); i++) {
		cout << (*countryVec).at(i).getId() <<" "<< (*countryVec).at(i).toString() << " " << (*countryVec).at(i).getCont() << endl;
	}
	
	//addBorders(*strBorders,*countryVec);

	//closing the file stream
	(*infile).close();
	
	return 0;
}


vector<continent>* continentLoader(string input) {

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
	vector<continent>* contVec = new vector<continent>();

	for (int i = 0; i < *numOfContinents - 1; i++) {		//-1 is importan. We want to deal with the last line seperately 

		//calculating indexes of wordEnd and bonusEnd
		*wordEnd = input.find(' ', *startLine);
		*bonusEnd = input.find(' ', *wordEnd + 1);

		//converting bonus from string to int and saving it into the bonus pointer
		*bonus = stoi(trim(input.substr(*wordEnd, *bonusEnd - *wordEnd)));

		*contName = trim(input.substr(*startLine, *wordEnd - *startLine));

		(*contVec).push_back(continent(i, *contName, *bonus));

		//recalculating startline and endline
		*startLine = input.find('\n', *startLine + 1);
		
	}

	//Manualy recalculating indexes of the last line an adding the last object to the vectot
	*wordEnd = input.find(' ', *startLine);
	*bonusEnd = input.find(' ', *wordEnd + 1);
	//converting the bonus from string to int and saving it into the bonus pointer
	*bonus = stoi(trim(input.substr(*wordEnd, *bonusEnd - *wordEnd)));
	(*contVec).push_back(continent(*numOfContinents - 1, trim(input.substr(*startLine, *wordEnd - *startLine)), *bonus));

	//removing any unused allocations
	(*contVec).shrink_to_fit();

	//TODO:delete pointers

	return contVec;
}


vector<country>* countryLoader(string input) {

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
	//vector tostore the continent objects in
	vector<country>* countryVec = new vector<country>();

	for (int i = 0; i < *numOfCountries - 1; i++) {		//-1 is importan. We want to deal with the last line seperately 

		//calculating indexes of idEnd, nameEnd, and continentEnd
		*idEnd = input.find(' ', *startLine);
		*nameEnd = input.find(' ', *idEnd + 1);
		*continentEnd = input.find(' ', *nameEnd + 1);

		*ID = stoi(trim(input.substr(*startLine, *idEnd - *startLine)));

		//converting the continent number from string to int and storing it in the continentNum pointer
		*continentNum= stoi(trim(input.substr(*nameEnd, *continentEnd - *nameEnd)));

		*countryName = trim(input.substr(*idEnd, *nameEnd - *idEnd));

		(*countryVec).push_back(country(*ID, *countryName, *continentNum));

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
	(*countryVec).push_back(country(*ID,*countryName,*continentNum));

	//removing any unused allocations
	(*countryVec).shrink_to_fit();

	//TODO:delete pointers

	return countryVec;
}

bool addBorders(string input,vector<country> country) {
	input = trim(input);
	int* numOflines = new int(count(input.begin(), input.end(), '\n') + 1);
	int* startLine = new int(0);
	int* endLine = new int();
	int* borders = new int();
	int* firstSpace = new int();
	int* beforeNumber = new int(0);
	int* afterNumber = new int();
	int* borderID = new int();
	int* currentCountryId = new int();
	string* line = new string();


	for (int i = 0; i < *numOflines - 1; i++) {
		*endLine = input.find('\n', *startLine + 1);
		*line = trim(input.substr(*startLine, *endLine - *startLine));
		*borders = count((*line).begin(), (*line).end(), ' ');
		*beforeNumber = (*line).find(' ');
		*currentCountryId = stoi(trim((*line).substr(0, *beforeNumber)));
		for (int j = 0; j < *borders; j++) {
			
			*afterNumber = (*line).find(' ', *beforeNumber + 1);
			*borderID = stoi(trim((*line).substr(*beforeNumber,*afterNumber - *beforeNumber)));
			country.at(*currentCountryId-1).addBorder(*borderID);
			*beforeNumber = *afterNumber;
		}
		*startLine = *endLine;
	}
	*endLine = input.length() ;
	*line = trim(input.substr(*startLine, *endLine - *startLine));
	*borders = count((*line).begin(), (*line).end(), ' ');
	*beforeNumber = (*line).find(' ');
	*currentCountryId = stoi(trim((*line).substr(0, *beforeNumber)));
	for (int j = 0; j < *borders; j++) {
		*afterNumber = (*line).find(' ', *beforeNumber + 1);
		*borderID = stoi(trim((*line).substr(*beforeNumber, *afterNumber - *beforeNumber)));
		country.at(*currentCountryId - 1).addBorder(*borderID);
		*beforeNumber = *afterNumber;
	}
	
	return true;
}

//trims any whitespace from both sides of the string 
string trim(string input) {
	string *returnStr = new string(input);
	while ((*returnStr)[(*returnStr).length() - 1] == ' '|| (*returnStr)[(*returnStr).length() - 1] == '\n') {
		(*returnStr) = (*returnStr).substr(0, (*returnStr).length() - 1);
	}
	while ((*returnStr)[0] == ' '|| (*returnStr)[0] == '\n') {
		(*returnStr) = (*returnStr).substr(1, (*returnStr).length());
	}
	return *returnStr;
}

