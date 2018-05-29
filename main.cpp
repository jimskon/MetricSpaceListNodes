
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h> 
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

int trans1[] = {0, 1, -1, 2, -2, 3};
int trans2[] = {0, 1, 2, -2, 3};

void displaySig(vector<int> v, ostream& outStream) {

    for (int i = 0; i < v.size(); i++) {
        outStream << v[i];
    }
    //outStream << endl;
}

void displayTuple(vector<int> v, ostream& outStream) {
    outStream << "(";
    for (int i = 0; i < v.size(); i++) {
        outStream << v[i];
        if (i<v.size()-1) {
            outStream << ',';
        }
    }
    outStream << ")" << endl;
}


vector<int> initialSig(int n) {
    vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(0);
    }
    return v;
}

bool nextSig(vector<int> &sig) {
    int l = sig.size() - 1;
    for (int i = l; i >= 0; i--) {
        if (i == l && i > 0) {
            if (sig[i] < 4) {
                sig[i]++;
                return true;
            }
            if (sig[i] == 4) {
                sig[i] = 0;
            }
        } else if (i > 0) {
            if (sig[i] < 5) {
                sig[i]++;
                return true;
            }
            if (sig[i] == 5) {
                sig[i] = 0;
            }
        } else {
            if (sig[l] == 0) {
                sig = initialSig(l + 1);
                sig[0] = 1;
                return false;
            }
        }

    }
    return false;
}

vector<int> sig2Tuple(vector<int> sig) {
    vector<int> tuple;
    int l = sig.size();
    for (int i = 0; i < l; i++) {
        if (i<l-1) {
            tuple.push_back(trans1[sig[i]]);
        } else {
            tuple.push_back(trans2[sig[i]]);
        }
    }
    return tuple;
}

void generateSigs(int n, ostream &outStream) {
    vector<int> sig = initialSig(n);
    bool more = true;
    displaySig(sig, outStream);
    displayTuple(sig2Tuple(sig), outStream);
    while (more) {
        more = nextSig(sig);
        displaySig(sig, outStream);
        displayTuple(sig2Tuple(sig), outStream);
    }
}

// Main

int main() {
    int num;
    string fileName;
    ofstream outStream, displayFile;
    
    cout << "Input levels:";
    cin >> num;
    cin.ignore(256,'\n');
    cout << "File Name?";
    getline(cin,fileName);
    if (fileName.length()<2) {
        generateSigs(num,cout);
    } else {
        outStream.open(fileName);
        generateSigs(num,outStream);
    }
        
    
    return 0;
}

