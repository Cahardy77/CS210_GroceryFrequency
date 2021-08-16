#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
//initialize and declare variables, vectors, and streams
using namespace std;
ifstream groceryList; 
ofstream produceData;
ifstream frequencyDataIn;
int menuInput = 0;
string userInput = "null";
string groceryItem = "null";
int groceryItemQuantity = 0;
vector<string> listVector;
vector<int> listCounter;

// build vectors with information from input file and write information to frequency.dat
void BuildVectors(){
	//open initial grocery list
	groceryList.open("CS210_Project_Three_Input_File.txt");
	
	// loop until end of file is reached
	while (!groceryList.fail()){
		groceryList >> groceryItem;
		
		// check if item is in vector, if not, add it
		if(find(listVector.begin(), listVector.end(), groceryItem) == listVector.end()){
			listVector.push_back(groceryItem);
			// add quantity 1 to adjacent list representing each items quantity
			listCounter.push_back(1);
		}
		
		// if item is already accounted for, add 1 to the items quantity
		else{
			auto iterator = find(listVector.begin(), listVector.end(), groceryItem);
			int index = iterator - listVector.begin();
			listCounter[index] += 1;
		}
	}
	
	// create and open frequency.dat
	produceData.open("frequency.dat");
	 // for each item in listVector that holds the grocery names, output to file with name followed by frequency
	for(int i = 0; i<(int)listVector.size(); ++i){
		produceData << listVector[i] << " " << listCounter[i] << endl;
	}
	
	// close files
	produceData.close();
	groceryList.close();
}

// list all items in grocery list and the respective frequency
void ListAll(){
	for(int i = 0; i<(int)listVector.size(); ++i){
		cout << listVector[i] << " " << listCounter[i] << endl;
	}
}

// list the frequency of a specific item user inputs
void ListFrequency(){
	cout << "Please type item name to find frequency(Case Sensitive): ";
	cin >> userInput;
	
	//iterate through list to see if item is available
	auto iterator = find(listVector.begin(), listVector.end(), userInput);
	int index = iterator - listVector.begin();
	
	if(find(listVector.begin(), listVector.end(), userInput) != listVector.end()){
		cout << "Frequency " << listCounter[index] << endl;
	}
	else{
		cout << "Invalid grocery name." << endl;
	}	
	
}

// create a histogram by reading the previously created frequency.dat
void Histogram(){
	//open frequency.dat
	frequencyDataIn.open("frequency.dat");
	
	// until end of file is reached read name and quantity
	while (!frequencyDataIn.eof()){
		frequencyDataIn >> groceryItem;
		frequencyDataIn >> groceryItemQuantity;
		
		//print histogram
		if (!frequencyDataIn.eof()){
			cout << groceryItem;
			for (int i = 0; i < groceryItemQuantity; ++i){
				cout << " *";
			}
			cout << endl;
		}
	}
	
	//close frequency.dat
	frequencyDataIn.close();
	
}

// menu selector
void Menu(){
	// build data from sources
	BuildVectors();
	
	//user menu
	while(menuInput != 4){
		try{
			cout << endl;
			cout << "1: Produce list of all items and frequency bought today." << endl;
			cout << "2: Produce frequency of specific item bought today." << endl;
			cout << "3: Produce a histogram based off of item frequency." << endl;
			cout << "4: Exit program and close files." << endl;
			cout << "User input: ";
			cin >> menuInput;
			switch(menuInput){
				case 1:
					ListAll();
					break;
				case 2:
					ListFrequency();
					break;
				case 3:
					Histogram();
					break;
				case 4:
					cout << "Exiting program and closing files" << endl;
					break;
				// if user inputs invalid option clear cin and output invalid option
				default:
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid input" << endl;
					menuInput = 0;
			}
			
		}
	

		catch(...){
			cout << "I'm sorry you broke me" << endl;
		}
	}
}



//program run :)
int main(){
	Menu();
	return 0;
}
