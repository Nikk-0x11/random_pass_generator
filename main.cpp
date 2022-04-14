#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int checkPassLen(string str) {
    // err check for passLen
    int passLen;

    try {
        passLen = stoi(str);
    }
    catch (...) {
        cout << "Invalid password length." << endl;
        return -1;
    }

    if (passLen<1||passLen>50) {
        cout << "Invalid password length." << endl;
        return -1;
    }
    return passLen;
}

int getPassLen() {
    string str;
    
    cout << "Password length: ";
    getline(cin, str);

    return checkPassLen(str);
}

set<int> getOptions() {
    cout << "Character set options:" << endl;
    cout << " [abcdef]      Lowercase  -> LC " << endl;
    cout << " [ABCDEF]      Uppercase  -> UC " << endl;
    cout << " [012345]      Digits     -> DG " << endl;
    cout << " [!@<{, ]      Symbols    -> SM " << endl;
    cout << " [LC,UC,DG,SM] All        -> AL " << endl << endl;

    cout << "choose all the desired options separated by a space and press enter." << endl << endl;
    cout << "Option(s): ";

    string optionInput;
    getline(cin, optionInput);

    // interpret input
    set<int> options;
    
    istringstream iss(optionInput);
    string token;
    while (iss >> token) {
        if (token=="LC"||token=="lc") {
            options.insert(1);
        }
        else if (token=="UC"||token=="uc") {
            options.insert(2);
        }
        else if (token=="DG"||token=="dg") {
            options.insert(3);
        }
        else if (token=="SM"||token=="sm") {
            options.insert(4);
        }
        else if (token=="AL"||token=="al") {
            options.insert(0);
        }
        else {
            cout << "Invalid option." << endl;
            exit(1);
        }
    }

    return options;
}

string generateRandCharSet(set<int>* options, int passLen) {
    string characterSets = "";

    while (characterSets.length()!=passLen) {
        int result = 1 + (rand() % 4);

        if (result==1&&(options->find(1)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=to_string(result);
        }
        else if (result==2&&(options->find(2)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=to_string(result);
        }
        else if (result==3&&(options->find(3)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=to_string(result);
        }
        else if (result==4&&(options->find(4)!=options->end()||options->find(0)!=options->end())) {
            characterSets+=to_string(result);
        }
    }

    return characterSets;
}

string generatePassword(set<int>* options, int passLen) {

    string characterSets;

    // generate a string with the length of passLen
    bool error = true;
    while (error) {
        characterSets = generateRandCharSet(options, passLen);
        
        error = false;
        if ((options->find(1)!=options->end()||options->find(0)!=options->end())&&characterSets.find("1")==string::npos) {
            error = true;
        }
        if ((options->find(2)!=options->end()||options->find(0)!=options->end())&&characterSets.find("2")==string::npos) {
            error = true;
        }
        if ((options->find(3)!=options->end()||options->find(0)!=options->end())&&characterSets.find("3")==string::npos) {
            error = true;
        }
        if ((options->find(4)!=options->end()||options->find(0)!=options->end())&&characterSets.find("4")==string::npos) {
            error = true;
        }
    }
    
    string lowercase = "abcdefghijklmnopqrstuvwxyz";
    string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string digits = "0123456789";
    string symbols = " ~!@#$%^&*()-=+[{]}\\;:'""/?.>,<";

    // generate pass by choosing a rand char from each char case
    string password = "";
    for (int i = 0; i < passLen; i++) {
        if (characterSets[i]=='1') {
            password+=lowercase[rand() % lowercase.length()];
        }
        else if (characterSets[i]=='2') {
            password+=uppercase[rand() % uppercase.length()];
        }
        else if (characterSets[i]=='3') {
            password+=digits[rand() % digits.length()];
        }
        else if (characterSets[i]=='4') {
            password+=symbols[rand() % symbols.length()];
        }
    }

    return password;
}

int main(int argc, char* argv[]) {

    int passLen;

    if (argc>1) {
        passLen = checkPassLen(argv[1]);
    }
    else {
        passLen = getPassLen();
    }

    if (passLen==-1) {
        return 1;
    }

    set<int> options = getOptions();

    srand((unsigned) time(0));

    cout << endl;
    for (int i = 0; i < 10; i++) {
      cout << "Password -> ";
        cout << generatePassword(&options, passLen) << endl;
    }

    return 0;
}