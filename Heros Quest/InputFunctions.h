#ifndef INPUTFUNCTIONS_H
#define INPUTFUNCTIONS_H

#include <iostream>
#include <string>

std::string makeStringChoice(std::string strQuestion); //limits input to string allowing the input of a question
int makeIntChoice(std::string strQuestion, int lowerLimit, int upperLimit); //limits input to integer allowing the input of a question & upper/lower limit
char makeCharChoice(std::string strQuestion); //limits input to character

#endif // !INPUTFUNCTIONS_H
