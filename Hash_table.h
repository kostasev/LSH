//
// Created by kosti on 10/20/2018.
//

#ifndef UNTITLED_HASH_TABLE_H
#define UNTITLED_HASH_TABLE_H
#include <vector>
#include <unordered_map>
#include <iostream>
#include "./Key.h"

using namespace std;

class Hash_table {
private:
    vector<int> f;
    unordered_map<Key,string> hash_tb;
public:
    Hash_table(int buck);
    ~Hash_table();
    void add_item(Key,string);
    vector<Key,string> get_bucket_of(Key);
};


#endif //UNTITLED_HASH_TABLE_H
