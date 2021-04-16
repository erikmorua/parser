/*
Erik Morua, cssc3051, Red ID: 816670615
cs530 Systems Programming
Fall 2020, Prof. Guy
Program 3 Parser
Description: A parser that recognizes valid statements to develop a grammar.
Program will prompt during execution for a file holding statements.
Program will break up the statements and check each line to identify an assignment or an expression.
Based on this, it will either be identified as valid or not valid.
*/
#include "parser.h"
#include<string>
#include<iostream>
using namespace std;

const struct ops opTable[] = {
    {'+'},{'-'},{'*'},{'/'},{'%'}
}; // end struct with operands

//struct to hold digits allowed
struct digit dTable[] = {
    {'0'},{'1'},{'2'},{'3'},{'4'},{'5'},{'6'},{'7'},{'8'},{'9'}
};
//struct to hold all characters that can be chars when being ID'd
struct chars cTable[] = {
    { 'a' },   { 'b' },    { 'c' },    { 'd' },
    { 'e' },   { 'f' },    { 'g' },    { 'h' },
    { 'i' },   { 'j' },    { 'k' },    { 'l' },
    { 'm' },   { 'n' },    { 'o' },    { 'p' },
    { 'q' },   { 'r' },    { 's' },    { 't' },
    { 'u' },   { 'v' },    { 'w' },    { 'x' },
    { 'y' },   { 'z' },    { 'A' },    { 'B' },
    { 'C' },   { 'D' },    { 'E' },    { 'F' },
    { 'G' },   { 'H' },    { 'I' },    { 'J' },
    { 'K' },   { 'L' },    { 'M' },    { 'N' },
    { 'O' },   { 'P' },    { 'Q' },    { 'R' },
    { 'S' },   { 'T' },    { 'U' },    { 'V' },
    { 'W' },   { 'X' },    { 'Y' },    { 'Z' }
};
// checks input against digit table
bool checkDigit(char digit) {
    for (int i = 0; i < 10; i++) {
        if (dTable[i].d == digit)
            return true;
    }
    return false;
}

//checks input against operand table
bool checkOps(char ops) {
    for (int i = 0; i < 5; i++) {
        if (opTable[i].op == ops)
            return true;
    }
    return false;
}

// makes sure the letters input are part of the allowed letters
bool checkChar(char letter) {
    for (int i = 0; i <= 51; i++)
        if (cTable[i].c == letter)
            return true;
    return false;
}

// check the ID to make sure each one is valid
bool checkID(string id) {
    // check if first char is a letter
    if (checkChar(id[0])) {
        for (int i = 1; i < id.length(); i++) {

            if (checkChar(id[i]))
                continue;

            else if (checkDigit(id[i])) 
                continue;

            else 
                return false;
        }
        return true;
    }
    return false;
}
//function checks to make sure the expression is valid
vector<string> validateExpression(vector<string> token) {
    vector<string> res(2);
    // check if first token is an expression
    if (token[0] != " " && checkID(token[0])) {
        // since its an expression, we need to see if the first is an operation
        if (token[1].length() == 1 && checkOps(token[1][0])) {
            // check if last token is ID
            if (checkID(token[token.size() - 1])) {
                for (int i = 2; i < token.size() - 1; i++) {
                    // returning -1 to signify not valid id
                    if (!(checkID(token[i]))) {
                        res[0] = "0";
                        res[1] = "-1";
                            return res;
                    }
                    i++;
                    if (!(checkOps(token[i][0]))) {
                        res[0] = "0";
                        res[1] = "-1";
                        return res;
                    }
                }
                res[0] = "1";
                res[1] = " ";
                return res;
            }
            // not valid ID
            res[0] = "0";
            res[1] = "-1";
            return res;
        }
        // not valid OP
        res[0] = "0";
        res[1] = "-1";
        return res;
    }
    // not valid ID
    res[0] = "0";
    res[1] = "-1";
        return res;
}

//function will check to see if the assignment is valid or not
vector<string> validateAssignment(vector<string> token) {
vector<string> res(2);
    //checking if ID 
    if (checkID(token[0])) {
        // check for = sign
        if (token[1] == "=") {
            // checking for the last token
            if (token[token.size() - 1][0] == ';') {
                vector<string> last;
                for (int i = 2; i < token.size() - 1; i++) {
                    last.push_back(token[i]);
                }
                return validateExpression(last);
            }
            else {
                // if not semicolon
                res[0] = "0";
                res[1] = token[0];
                return res;
            }
        }
        // not valid
        res[0] = "0";
        res[1] = token[1];
        return res;
    }
}

/*
Parser begins reading file. Allocates space and copies into buffer.
statements will be the file passed in main function as argv[].
*/
void readFile() {
    char* in = new char[50000]();
    char* file = new char[50000]();
    char* fname = new char[10000]();
    string res;
    vector<string> stateText;
    cout << "Enter file containing statements to be parsed.";
    // statements passed in
    if (fgets(in, 50000, stdin) != NULL) {
        scanf(in, "%s", file);
    }
    else {
        cout << "File could not be processed." << endl;
    }

    strcat(file, fname);
    strcat(file, ".txt");

    ifstream statementFile(file);
    if (statementFile.is_open()) {
        while (statementFile.good()) {
            getline(statementFile, res);
            stateText.push_back(res);
        }
        statementFile.close();
        runParse(stateText);
    }
    //error checking in case file can't open
    else {
        cout << "Cannot open text file." << endl;
    }
}
//parses the statement.
void runParse(vector<string> statement) {
    // output files
    char* out = new char[]();
    strcat(out, "parsed.txt");
    ofstream outfile(out);

    FILE* outFile = fopen(out, "wb");

    bool valid = true;
    vector<string> token;
    //checks to make sure the string is not empty. pushes it onto a new vector token
    for (int i = 0; i < statement.size(); i++) {
        if (statement[i].empty() == false) {

            string str;
            token.push_back(statement[i]);

        }
        //validating and sending to the output file.
        vector<string>temp = pickStatement(token);
        fprintf(outFile, "%3d: %-60s  %-20s  %-20s \n", i, statement[i].c_str(), temp[0].c_str(), temp[1].c_str());

        if (temp[0].length() > 16) {
            valid = false;
        }
        else {
            fprintf(outFile, "%3d: \n", i);
        }
        fprintf(outFile, "\n -> File Validation: %s", valid ? "Valid" : "Not Valid");
    }
    outfile.close();
}
   
//function picks if statement is an assignment or expression
vector<string> pickStatement(vector<string> token) {
    vector<string> res(2);
    vector<string> temp(2);

    parser* statement = new parser;
    //running through the input. 
    for (int i = 0; i < token.size(); i++) {
        //if the input contains a = then it is an assignment
        if (token[i] == "=") {
            temp = statement->validateAssignment(token);
            if (temp[0] == "1") {
                res[0] = "Assignment is not Valid";
                res[1] = " ";
                return res;
            }
            else {
                res[0] = "Assignment is not Valid";
                res[1] = temp[1];
                return res;
            }
        }
        //if statement isn't an assignment then it is an expression
        else {
            temp = statement->validateExpression(token);
            if (temp[0] == "1") {
                res[0] = "Expression is Valid";
                res[1] = " ";
                return res;
            }
            else {
                res[0] = "Expression is Not Valid";
                res[1] = " ";
                return res;
            }
        }
    }           
}

struct digit {
    char d;
};
struct ops {
    char op;
};
struct chars {
    char c;
};
int main(int argc, const char* argv[]) {

    parser* statements = new parser();
    statements->readFile();
    return 0;
}