//
// Created by kosti on 10/20/2018.
//

#ifndef UNTITLED_HASH_TABLE_H
#define UNTITLED_HASH_TABLE_H
#include <unordered_map>
#include <iostream>
#include "./Key.h"
#include "./hash_func.h"

using namespace std;

class Hash_table {
private:
    int d;
    int k;
    hash_func *hfunc;
    unordered_map<string,Key> hash_tb;
public:
    Hash_table(int, int, int, string);
    ~Hash_table();
    void add_item( string ,Key );
    //vector<string,Key> get_bucket_of(string);
    void print_stats();
};


#endif //UNTITLED_HASH_TABLE_H
