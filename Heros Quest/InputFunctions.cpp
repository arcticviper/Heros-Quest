#include "InputFunctions.h"
using namespace std;

std::string makeStringChoice(std::string strQuestion){
	string choice = "";
	cout << strQuestion << endl;
	getline(cin, choice);
	while (choice.length() == 0) {
		cout << "Did you enter anything? (String input please)" << endl;
		getline(cin, choice);
	}
	return choice;
}

int makeIntChoice(std::string strQuestion, int lowerLimit, int upperLimit)
{
	int intPlayerOption;
	int boolValidChoice = false;
	while (boolValidChoice == false) {
		intPlayerOption = stoi(makeStringChoice(strQuestion));
		if ((intPlayerOption >= lowerLimit) && (intPlayerOption <= upperLimit)) {
			boolValidChoice = true;
		}
	}
	return intPlayerOption;
}

char makeCharChoice(std::string strQuestion)
{
	string choiceReturn;
	char charChoice;
	choiceReturn = makeStringChoice(strQuestion);

	while (choiceReturn.length() != 1) {
		choiceReturn = makeStringChoice(strQuestion);
		if (choiceReturn.length() == 0) {
			cout << "Did you enter anything? (Character input please)" << endl;
		}
		else if (choiceReturn.length() > 1) {
			cout << "Single Character Please" << endl;
		}

	}
	charChoice = choiceReturn[0];
	return charChoice;
}
