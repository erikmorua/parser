#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#pragma once

class parser {
public:
	void readFile();
	vector<string> pickStatement(vector<string>);
	vector<string> validateAssignment(vector<string>);
	vector<string> validateExpression(vector<string>);
	bool checkID(string);
	bool checkChar(char);
	bool checkDigit(char);
	bool checkOps(char);

private:
};
