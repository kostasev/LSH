//
// Created by kosti on 10/20/2018.
//

#ifndef UNTITLED_HASH_TABLE_H
#define UNTITLED_HASH_TABLE_H
#include <unordered_map>
#include <iostream>
#include "./Key.h"
#include "./hash_func.h"


class Hash_table {
private:
    int d;
    int k;
    hash_func *hfunc;
    std::unordered_map<Key,std::string> hash_tb;
public:
    Hash_table(int, int, int, std::string);
    ~Hash_table();
    void add_item(std::string ,Key,int);
    //vector<string,Key> get_bucket_of(string);
    void print_stats();
};


#endif //UNTITLED_HASH_TABLE_H
