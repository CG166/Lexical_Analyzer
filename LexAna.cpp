#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string analyze() {
    string separators[] = {
        ";", ",", ".", ":", "::", "{", "}", "[", "]", "(", ")", "<>", 
    };
}

int main(void){
    //Variables
    string filename;
    string content;
    char c;
    char prev;
    bool iscomment = false;

    //Getting filename from user
    cout << "Filename: ";
    getline(cin, filename);

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

        if(iscomment == true && c == '\n' || iscomment == true && c == '/' && prev = '*' ) { //Checking if a comment has ended
            iscomment = false;
        }

        if(iscomment == false) {
                content.push_back(c);
        }
        prev = c;
        
    }

    //Printing out file content for debugging purposes
    cout << content;

    //Closing file
    inFile.close();

    return 0;
}
