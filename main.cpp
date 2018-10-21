#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <getopt.h>
#include "./constants.h"
#include "./utilities.h"
#include "./Key.h"
#include "Hash_table.h"

using namespace std;

int main(int argc, char** argv) {
    string input="", query="", output="";
    string func_name = "";
    bool read_query;
    int c;
    int k=-1;
    int L=-1;

    /* Reading Arguments from command line */
    while(( c = getopt(argc,argv,"d:q:k:L:o:f:h")) !=-1 ){
        switch (c) {
            case 'd':
                input = optarg;
                break;
            case 'q':
                query = optarg;
                break;
            case 'k':
                k = atoi(optarg);
                break;
            case 'L':
                L = atoi(optarg);
                break;
            case 'o':
                output = optarg;
                break;
            case 'f':
                func_name = optarg;
                if ((func_name != "cosine") || (func_name!="euclidean")) {
                    cerr << "Invalid function name" << endl;
                }
                break;
            case 'h':
                cout << "\nlsh - Locality Sensitive Hashing\n" << endl <<
                     "Mandatory options\n\t-d data feed file\n\n"
                     "Optional flags\n"
                     "\t-q query data file\n"
                     "\t-k num of random probes\n"
                     "\t-L num of hash tables\n"
                     "\t-o output file\n"
                     "\t-f function to use (euclidean and cosine similarity available)" << endl;
                return 0;
            case '?':
                cerr << "Unknown option character " << char(optopt) << endl;
                return 1;
            default:
                abort();
        }
    }
    if (input.size()==0) {
        cerr << "Data file was not defined!" << endl ;
    }
    if (k==-1) k=const_lsh::k;
    if (L==-1) L=const_lsh::L;
    if (query.size()==0) read_query=true;
    if (output.size()==0) output = "./output.txt";
    if (func_name.size()==0) func_name = const_lsh::def_func;

    cout << "L: " << L << endl;
    cout << "k: " << k << endl;
    cout << "in: " << input  << endl;
    cout << "qr: " << query  << endl;
    cout << "ou: " << output << endl;
    cout << "fn: " << func_name << endl;

    ifstream inputfd;
    string line;
    int num_lines = 0;
    int d;
    inputfd.open (input);
    if (inputfd.is_open()){
        getline(inputfd,line);
        d = num_columns(line);
        num_lines++;
        while ( getline(inputfd,line) ){
            num_lines++;
        }
        inputfd.close();
    }else{
        cerr << "Unable to open file: " << input << endl;
    }

    cout << "d: " << d << endl;
    cout << "num lines: " << num_lines << endl;

    Hash_table ht = Hash_table(num_lines/const_lsh::table_size,func_name);
    Key a ,b , c1, d1;
    a.dim = { 1 , 2 , 3};
    b.dim = { 1 , 2 , 4};
    c1.dim = { 1 , 2 , 5};
    d1.dim = { 1 , 2 , 6};
    ht.add_item(a,"item1");
    ht.add_item(b,"item2");
    ht.add_item(c1,"item3");
    ht.add_item(d1,"item4");

    //unordered_map<Key,string> hash_tb;
    /*Key a ,b , c1, d1;
    a.dim = { 1 , 2 , 3};
    hash_tb[a]="item1";
    b.dim = { 1 , 2 , 4};
    hash_tb[b]="item2";
    c1.dim = { 1 , 2 , 5};
    hash_tb[c1]="item3";
    d1.dim = { 1 , 2 , 6};
    hash_tb[d1]="item4";*/



    return 0;

}