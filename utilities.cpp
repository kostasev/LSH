//
// Created by kosti on 10/20/2018.
//
#include <iostream>
using namespace std;


int num_columns(string line) {
    char prev=' ';
    int words=0;
    for(int i=0;i<line.size(); i++){
        if ((isspace(line[i]))&&(!isspace(prev))){
            words++;
        }
        prev = line[i];
    }
    if (!isspace(prev)) {
        words += 1;
    }
    cout << "IS: " << isspace('\n') << " " << prev <<endl;
    return words;
}

