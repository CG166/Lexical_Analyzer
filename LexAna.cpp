#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

//Functions
//This Function checks whether a string is an integer by looping through the string and check each character
bool isInt(string lexeme) {
    bool isint = false; //isInt is defaulted to false
    for(int i = 0; i < lexeme.length(); i++){ //Loops through each char of the lexeme
        if(isdigit(lexeme[i])) { //Checks if a char is an integer
            isint = true; //isInt is set/remains true if the char is an Int
        } else {
            return false; //The entire function immediatly returns false if any char is not an Int
        }
    }
    return isint; //Returns a true isInt if every char of the lexeme is an integer
}

//This function checks if a string/lexeme is a separator, operator, keyword, or identifier and prints out the corresponding message
string analyze(string lexeme) {
    string answer = " ="; //Partial answer format (used for printing purposes only)

    string separators[] = { //Array of strings containing all C++ separators
        ";", ",", ".", ":", "::", "{", "}", "[", "]", "(", ")", "->", "#"
    };
    string operators[] = { //Array of strings containing all C++ operators
        "+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>",
        "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "++", "--", "?", ":",
        "&", "*", "sizeof", ",", "static_cast", "dynamic_cast", "const_cast", "reinterpret_cast"
    };
    std::string keywords[] = { //Array of strings containing all C++ Keywords 
        "if", "else", "switch", "case", "default", "while", "do", "for", "break", "continue", "return", "goto",
        "auto", "register", "static", "extern", "mutable", "thread_local","int", "char", "float", "double", "void",
        "bool", "wchar_t", "long", "short", "signed", "unsigned", "long long", "typedef", "using", "struct", "union", "enum", "class", "template",
        "try", "catch", "throw", "namespace", "new", "delete", "inline", "friend", "virtual", "override", "final", "explicit", "const", "constexpr", "noexcept"
    };

    int Slength = sizeof(separators) / sizeof(separators[0]); //Computes and strores the length of the separator array
    int Olength = sizeof(operators) / sizeof(operators[0]); //Computes and strores the length of the separator array
    int Klength = sizeof(keywords) / sizeof(keywords[0]); //Computes and strores the length of the separator array

    //This checks if the lexeme is an integer
    if(isInt(lexeme)){ //Checks if lexeme is an integer
        return '"' + lexeme + '"' + answer + " integer\n\n"; //Returns message if lexeme is an integer
    }

    //This checks if the lexeme is a separator
    for(int i = 0; i < Slength; i++) { //Iterates through the separator array
        if(lexeme == separators[i]) { //Compares the lexeme to every separator in the separator array
            return '"' + lexeme + '"' + answer + " separator\n\n"; //Returns message if lexeme matches a separator
        }
    }

    //This checks if the lexeme is an operator
    for(int i = 0; i < Olength; i++) { //Iterates through the operator array
        if(lexeme == operators[i]) { //Compares the lexeme to every operator in the operator array
            return '"' + lexeme + '"' + answer + " operator\n\n"; //Returns message if lexeme matches an operator
        }
    }

    //This checks if the lexeme is a keyword
    for(int i = 0; i < Klength; i++) { //Iterates through the keyword array
        if(lexeme == keywords[i]) { //Compares the lexeme to every keyword in the keyword array
            return '"' + lexeme + '"' + answer + " keyword\n\n"; //Returns message if lexeme matches a keyword
        }
    }

    //This sets and returns the message that the lexeme is an identifier if that is the only remaining option
    answer = '"' + lexeme + '"' + answer +  " identifier" + "\n\n";

    return answer;
}

//This is a boolean function that returns true or false if an inputed char is a separator.
bool isSeparator(char c) { //Funtion takes in a char as a parameter
    string separators[] = { //Array of strings containing all C++ separators
        ";", ",", ".", ":", "::", "{", "}", "[", "]", "(", ")", "->", "#"
    };

    int length = sizeof(separators) / sizeof(separators[0]); //Computes and strores the length of the separator array

    for(int i = 0; i < length; i++) { //Iterates through the separator array
        if(string(1, c) == separators[i]) { //Checks if the char matches any separator
            return true; //Returns true if the char matches any separator
        }
    }
    return false; //Returns false if the char matches any separator
}

//The function spits a sentence string into a vector of strings that contains each word of the sentence string (no whitespaces)
vector<string> split(string contents) { //Function takes in a string(sentence as a parameter)
    istringstream stream(contents);
    vector<string> indivs;
    string lexeme;

    while (stream >> lexeme) { //Reads every lexeme(string) from the content sentence(string) (no newlines or whitespaces)
        indivs.push_back(lexeme); //pushes lexeme into vector
    }
    return indivs; //returns vector of lexemes
}

int main(void){
    //Variables
    string filename;
    string content;
    char c;
    char prev = ' ';
    bool iscomment = false;
    vector<string> lexemes;


    //Getting filename from user
    cout << "Filename: "; //Prompts user to input filename
    getline(cin, filename); //Reads user input into filename variable
    cout << "\n";

    //Opening file
    ifstream inFile;
    inFile.open(filename);

    //Error message
    if(inFile.fail()){//Checks if file has failed to open
        cout << "The file has failed to open.\n"; //Prints out error message
        return 1;
    }

    //Reading file content into string
    while(inFile.get(c)) { //Reading in file content one char at a time
        if(c == '/' && content.at(content.length()-1) == '/' || c == '*' && content.at(content.length()-1) == '/') { //Checking if a comment has started
            iscomment = true; //Sets the isComment variable to true
            content.pop_back(); //Removing comment backslash from content string
        }

        //Check if the given char is not part of a comment and is a sepparator
        if(iscomment == false && isSeparator(c) == true) {
            content.push_back(' '); //If the char is a separator a whitespace is pushed into the content string before and after the
            content.push_back(c); //char in order to properly seperate the lexemes within the content string for future separation purposes.
            content.push_back(' '); 
        } else if (iscomment == false && c != '\n') {//Checks if the given char is not part of a comment and not a newline
            content.push_back(c); //Pushes char into content string
        }

        if(iscomment == true && c == '\n' || iscomment == true && c == '/' && prev == '*' ) { //Checking if a comment has ended
            iscomment = false; //Sets the isComment variable to true
        }
        prev = c; //Stores the char before moving on for future comparison purposes
        
    }

    //Breaking up content string into a vector of individual lexemes
    lexemes = split(content);

    //Iterates through the vector of lexemes, tokenizing each lexeme and outputing the corresponding message
    for (const auto& str : lexemes) {
        cout << analyze(str); //Prints out correct messages in "<lexemes> = <tokens>" format
    }

    //Closing file
    inFile.close();

    return 0;
}
