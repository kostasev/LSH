#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <getopt.h>
#include <cstring>
#include <numeric>
#include <cmath>
#include <chrono>
#include "./constants.h"
#include "./utilities.h"
#include "./Key.h"
#include "Hash_table.h"
#include "./data_point.h"

void get_data_lenghts(std::string, int&, int&);

void feed_data_set(std::string, data_point<int>* , int);

void true_nn(data_point<int>, data_point<int> *,int);

double euclidean_dist(std::vector<int>, std::vector<int>);

void a_nn(std::map<std::string, value_point<int>> map, data_point<int> point);

using namespace std;

int main(int argc, char** argv) {
    string input = "", query = "", output = "";
    string func_name = "";
    bool read_query;
    int c, R = 400;
    int k = -1;
    int L = -1;

    /* Reading Arguments from command line */
    while ((c = getopt(argc, argv, "d:q:k:L:o:f:h:R")) != -1) {
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
            case 'R':
                R = atoi(optarg);
                break;
            case 'f':
                func_name = optarg;
                if ((func_name != "cosine") || (func_name != "euclidean")) {
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
    if (input.size() == 0) {
        cerr << "Data file was not defined!" << endl;
    }
    if (k == -1) k = const_lsh::k;
    if (L == -1) L = const_lsh::L;
    if (query.size() == 0) read_query = true;
    if (output.size() == 0) output = "./output.txt";
    if (func_name.size() == 0) func_name = const_lsh::def_func;

    cout << "L: " << L << endl;
    cout << "k: " << k << endl;
    cout << "in: " << input << endl;
    cout << "qr: " << query << endl;
    cout << "ou: " << output << endl;
    cout << "fn: " << func_name << endl;

    int num_lines = 0;
    int d;

    get_data_lenghts(input, num_lines, d);
    data_point<int> data_set[num_lines];
    feed_data_set(input, data_set, d);


    cout << "d: " << d << endl;
    cout << "num lines: " << num_lines << endl;

    //Hash_table ht = Hash_table(num_lines / const_lsh::table_size, d, k, func_name);
    vector <Hash_table> tables ;
    //Hash_table *tables;
    //tables = new Hash_table;
    for (int i=0; i<L ; i++){
        tables.push_back(Hash_table(num_lines/const_lsh::table_size, d, k, func_name));
    }
    //ht.print_stats();
    for (int j=0;j<tables.size();j++) {
        for (int i = 0; i < num_lines; i++) {
            tables[j].add_item(data_set[i], num_lines / const_lsh::table_size);
        }
    }

    map<string, value_point<int>> bucks;
    int num_lines_q = 0, dq = 0;
    get_data_lenghts(query, num_lines_q, dq);
    data_point<int> query_set[num_lines_q];
    feed_data_set(query, query_set, dq);
    cout << " Query Num lines: " << num_lines_q << endl;
    Key query_key;
    for (int k = 0; k < num_lines_q; k++) {
        for (int i=0;i<tables.size();i++){
            query_key=tables[i].query_item(query_set[k],num_lines / const_lsh::table_size);
            tables[i].get_bucket(query_key, bucks);
        }
        cout << "Query Buck : " << bucks.size() <<endl;
        a_nn(bucks,query_set[k]);
        true_nn(query_set[k], data_set, num_lines);
        bucks.clear();
    }



   tables[0].print_stats();

    /*
    ifstream queryfd;
    queryfd.open(query);
    vector<data_point> neighboors,temp;
    while (getline(queryfd,line)) {
        strncpy(cc,line.c_str(),d*sizeof(int));
        char *pch = strtok (cc ," \t");
        while (pch != NULL)
        {
            xx.push_back(atoi(pch));
            pch = strtok (NULL, " \t");
        }
        temp = ht.get_bucket({xx,0});
        cout << "size: " << temp.size();
        neighboors.insert(neighboors.end(),temp.begin(),temp.end());
        for(int z=0;z<temp.size();z++){
            cout << "size: " << temp.size();
            for(int x=0;x<temp.size();x++){
                cout << temp[z].k.dim[x] << " ";
                //cout << neighboors[z].k.dim[x] << " ";
            }
            cout << endl << endl;
        }
        double result;
        for (int z=0;z<neighboors.size();z++){
            result = std::sqrt(std::inner_product(begin(xx), end(xx), begin(neighboors[z].k.dim), 0));
            cout <<"result: "<< result;
        }
        xx.clear();
    }*/

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

void a_nn(map<string,value_point<int>> bucks, data_point<int> point) {
    double min_dist = 999999999.9;
    double dist;
    string nn="NONE";
    auto start = chrono::steady_clock::now();
    for (auto  it = bucks.begin(); it != bucks.end(); it++ ){
        if ((dist=euclidean_dist(point.point,it->second.point)) < min_dist){
            min_dist = dist;
            nn = it->first;
        }
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end-start;
    if (nn!="NONE"){
        cout << "Aproximate NN of query "<< point.name << " ==> " << nn << ", Value ==> " << min_dist << " search time: " << diff.count() << " seconds"<< endl;
    }
}

void true_nn(data_point<int> point, data_point<int> *pPoint,int num_data) {
    double min_dist = 999999999.9;
    double dist;
    string nn="NONE";
    auto start = chrono::steady_clock::now();
    for (int i=0; i<num_data ; i++){
        if ((dist=euclidean_dist(point.point,pPoint[i].point)) < min_dist){
            min_dist = dist;
            nn = pPoint[i].name;
        }
    }
    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end-start;
    if (nn!="NONE"){
        cout << "True NN of query "<< point.name << " ==> " << nn << ", Value ==> " << min_dist << " search time: " << diff.count() << " seconds"<< endl;
    }
}

double euclidean_dist(vector<int> p1,vector<int> p2) {
    double sum = 0.0;
    for (int i=0 ; i<p1.size();i++){
        sum+=(p1[i]-p2[i])*(p1[i]-p2[i]);
    }
    sum = sqrt(sum);
    return sum;
}

void feed_data_set(string input, data_point<int> *pPoint,int d) {
    char cc[1024] ;
    string name;
    string line;
    ifstream inputfd;
    inputfd.open (input);
    int i=0;
    while(getline(inputfd,line)){
        strncpy(cc,line.c_str(),(d+10)*sizeof(int));
        char *pch = strtok (cc ," \t");
        while (pch != NULL)
        {
            pPoint[i].point.push_back(atoi(pch));
            pch = strtok (NULL, " \t");
        }
        pPoint[i].name = "item_"+to_string(i);
        i++;
    }
    inputfd.close();
}

void get_data_lenghts(string input,int& lines, int& d) {
    ifstream inputfd;
    string line;
    inputfd.open (input);
    if (inputfd.is_open()){
        getline(inputfd,line);
        d = num_columns(line);
        lines++;
        while ( getline(inputfd,line) ){
            lines++;
        }
        inputfd.close();
    }else{
        cerr << "Unable to open file: " << input << endl;
    }
    inputfd.close();
}