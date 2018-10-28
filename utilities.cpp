//
// Created by kosti on 10/20/2018.
//
#include <iostream>

int num_columns(std::string line) {
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
    return words;
}

