#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

bool isInt(string lexeme) {
    bool isint = false;

    for(int i = 0; i < lexeme.length(); i++){
        if(isdigit(lexeme[i])) {
            isint = true;
        } else {
            return false;
        }
    }
    return isint;
}

string analyze(string lexeme) {
    string answer = " =";

    string separators[] = {
        ";", ",", ".", ":", "::", "{", "}", "[", "]", "(", ")", "->", "#"
    };
    string operators[] = {
        "+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>",
        "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "++", "--", "?", ":",
        "&", "*", "sizeof", ",", "static_cast", "dynamic_cast", "const_cast", "reinterpret_cast"
    };
    std::string keywords[] = {
        "if", "else", "switch", "case", "default", "while", "do", "for", "break", "continue", "return", "goto",
        "auto", "register", "static", "extern", "mutable", "thread_local","int", "char", "float", "double", "void",
        "bool", "wchar_t", "long", "short", "signed", "unsigned", "long long", "typedef", "using", "struct", "union", "enum", "class", "template",
        "try", "catch", "throw", "namespace", "new", "delete", "inline", "friend", "virtual", "override", "final", "explicit", "const", "constexpr", "noexcept"
    };

    int Slength = sizeof(separators) / sizeof(separators[0]);
    int Olength = sizeof(operators) / sizeof(operators[0]);
    int Klength = sizeof(keywords) / sizeof(keywords[0]);

    if(isInt(lexeme)){
        return '"' + lexeme + '"' + answer + " integer.\n\n";
    }

    for(int i = 0; i < Slength; i++) {
        if(lexeme == separators[i]) {
            return /*answer =*/ '"' + lexeme + '"' + answer + " separator.\n\n";
        }
    }

    for(int i = 0; i < Olength; i++) {
        if(lexeme == operators[i]) {
            return '"' + lexeme + '"' + answer + "operator.\n\n";
        }
    }

    for(int i = 0; i < Klength; i++) {
        if(lexeme == keywords[i]) {
            return '"' + lexeme + '"' + answer + " keyword.\n\n";
        }
    }


    answer = '"' + lexeme + '"' + answer +  " identifier" + "\n\n";

    return answer;
}

bool isSeparator(char c) {
    string separators[] = {
        ";", ",", ".", ":", "::", "{", "}", "[", "]", "(", ")", "->", "#"
    };

    int length = sizeof(separators) / sizeof(separators[0]);

    for(int i = 0; i < length; i++) {
        if(string(1, c) == separators[i]) {
            return true;
        }
    }
    return false;
}

vector<string> split(string contents) {
    istringstream stream(contents);
    vector<string> indivs;
    string lexeme;

    while (stream >> lexeme) {
        indivs.push_back(lexeme);
    }
    return indivs;
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
    cout << "Filename: ";
    getline(cin, filename);
    cout << "\n";

    //Opening file
    ifstream inFile;
    inFile.open(filename);

    //Error message
    if(inFile.fail()){
        cout << "The file has failed to open.\n";
        return 1;
    }

    //Reading file content into string
    while(inFile.get(c)) {
        if(c == '/' && content.at(content.length()-1) == '/' || c == '*' && content.at(content.length()-1) == '/') { //Checking if a comment has started
            iscomment = true;
            content.pop_back();
        }

        if(iscomment == true && c == '\n' || iscomment == true && c == '/' && prev == '*' ) { //Checking if a comment has ended
            iscomment = false;
        }

        if(iscomment == false && isSeparator(c) == true) {
            content.push_back(' ');
            content.push_back(c);
            content.push_back(' ');
        } else if (iscomment == false && c != '\n') {
            content.push_back(c);
        }
        prev = c;
        
    }

    //Breaking up content string into a vector of individual lexemes
    lexemes = split(content);

    //Analyzing lexemes
    for (const auto& str : lexemes) {
        cout << analyze(str);
    }



    //Closing file
    inFile.close();

    return 0;
}
