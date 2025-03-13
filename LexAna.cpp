#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void){
    //Variables
    string filename;
    string content;
    char c;
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
        if(c != ' ') {//Eliminating whitespace
            if(c == '/' && content.at(content.length()-1) == '/') { //Checking if a comment has started
                iscomment = true;
                content.pop_back();
            }

            if(iscomment == true && c == '\n') { //Checking if a comment has ended
                iscomment = false;
            }

            if(iscomment == false && c != '\n') { //Eliminating newlines
                content.push_back(c);
            }
        }
    }

    //Printing out file content for debugging purposes
    cout << content;

    //Closing file
    inFile.close();

    return 0;
}
