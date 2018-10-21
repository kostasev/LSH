//
// Created by kosti on 10/20/2018.
//

#ifndef UNTITLED_HASH_TABLE_H
#define UNTITLED_HASH_TABLE_H
#include <vector>
#include <unordered_map>
#include <iostream>
#include "./Key.h"
#include "./hash_func.h"

using namespace std;

struct euc_hash {
    int a = rand();
    int b = rand();
    size_t operator()(const Key &k) const {
        int sum = 0;
        for (int i = 0; i < k.dim.size(); i++) {
            sum += k.dim[i];
        }
        cout << "AAAA is : " << a << " BBBB is : " << b << endl;
        cout << "Hash is: " << (sum % 2) << " of sum: " << sum << endl;
        return (sum % 2);
    }
};

class Hash_table {
private:
    euc_hash a;
    unordered_map<Key,string,euc_hash> hash_tb;
public:
    Hash_table(int, string);
    ~Hash_table();
    void add_item(Key,string);
    vector<Key,string> get_bucket_of(Key);
    void print_stats();
};


#endif //UNTITLED_HASH_TABLE_H
