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
#include <random>
#include <unistd.h>
#include "./constants.h"
#include "./utilities.h"
#include "./Key.h"
#include "Hash_table.h"
#include "./data_point.h"

void get_data_lenghts(std::string, int&, int&);

void feed_data_set(std::string, data_point<int>* , int);

double true_nn(data_point<int>, data_point<int> *,int,std::string s);

double euclidean_dist(std::vector<int>, std::vector<int>);

double a_nn(std::map<std::string, value_point<int>> map, data_point<int> point,double &time,std::string s);

void range_nn(std::map<std::string, value_point<int>> map, data_point<int> point, int r,std::string s);

double cosine_similarity(std::vector<int> p1,std::vector<int> p2);

using namespace std;



int main(int argc, char** argv) {
    string input = "", query = "", output = "";
    string func_name = "";
    bool read_query;
    int c, R = 200;
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
                if ((func_name != "cosine") && (func_name != "euclidean")) {
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

    std::mt19937 generator;
    generator.seed(std::default_random_engine()());
    std::uniform_int_distribution<int>   int_dist(-99,99);
    vector<int> r;

    if(func_name=="euclidean"){
        for (int i=0;i<k;i++){
            r.push_back(int_dist(generator));
        }
    }


    vector <Hash_table> tables ;
    int table_sz=0;
    if (func_name=="euclidean"){
        table_sz=num_lines/const_lsh::table_size;
    }
    else{
        table_sz = (int) pow(2.0,k);
    }
    for (int i=0; i<L ; i++){
        tables.push_back(Hash_table(table_sz, d, k, func_name));
    }

    for (int j=0;j<tables.size();j++) {
        for (int i = 0; i < num_lines; i++) {
            tables[j].add_item(data_set[i],table_sz,r);
        }
    }

    map<string, value_point<int>> bucks;
    int num_lines_q = 0, dq = 0;
    get_data_lenghts(query, num_lines_q, dq);
    data_point<int> query_set[num_lines_q];
    feed_data_set(query, query_set, dq);
    double t_nn,l_nn,max_app=0.0,time=0.0;
    Key query_key;
    for (int k = 0; k < num_lines_q; k++) {
        cout << "\nQuery Item: " << query_set[k].name <<endl;
        for (int i=0;i<tables.size();i++){
            query_key=tables[i].query_item(query_set[k],table_sz,r);
            tables[i].get_bucket(query_set[k],query_key, bucks,r);
        }
        //range_nn(bucks,query_set[k],R,func_name);
        t_nn=true_nn(query_set[k], data_set, num_lines,func_name);
        l_nn=a_nn(bucks,query_set[k],time,func_name);
        if ((l_nn/t_nn)>max_app){
            max_app = l_nn/t_nn;
        }
        bucks.clear();
    }
    time=time/num_lines_q;
    cout << "\nMax Approximate ratio: " << max_app<<endl;
    cout << "Average search time: " << time;


    r.clear();
    tables.clear();
    bucks.clear();

    for (int i=0;i<num_lines_q;i++){
        query_set[i].point.clear();
    }
    for (int i=0;i<num_lines;i++){
        data_set[i].point.clear();
    }
    return 0;

}

void range_nn(map<string, value_point<int>> bucks, data_point<int> point, int r,std::string s) {
    cout << "R-near neighbors:" << endl;
    if (s=="euclidean"){
        for (auto  it = bucks.begin(); it != bucks.end(); it++ ){
            if ((euclidean_dist(point.point,it->second.p->point)) < (double)r){
                cout << it->first << endl;
            }
        }
    }else{
        for (auto  it = bucks.begin(); it != bucks.end(); it++ ){
            if ((cosine_similarity(point.point,it->second.p->point)) < (double)r){
                cout << it->first << endl;
            }
        }
    }

}

double a_nn(map<string,value_point<int>> bucks, data_point<int> point,double &time,std::string s) {
    double min_dist = 9999999.9;
    double dist=0.0;
    string nn="NONE";
    auto start = chrono::steady_clock::now();
    if (s=="euclidean"){
        for (auto  it = bucks.begin(); it != bucks.end(); it++ ){
            if ((dist=euclidean_dist(point.point,it->second.p->point)) < min_dist){
                min_dist = dist;
                nn = it->first;
            }
        }
    }
    else {
        for (auto  it = bucks.begin(); it != bucks.end(); it++ ){
            if ((dist=cosine_similarity(point.point,it->second.p->point)) < min_dist){
                min_dist = dist;
                nn = it->first;
            }
        }
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end-start;
    if (nn!="NONE"){
        cout << "Nearest neighbor LSH: " << nn << endl
             << "distanceLSH: " << min_dist << " search time: " << diff.count() << " seconds"<< endl;
        time+=diff.count();
    }
    else {
        return 0;
    }


    return min_dist;
}

double true_nn(data_point<int> point, data_point<int> *pPoint,int num_data,std::string s) {
    double min_dist = 999999999.9;
    double dist;
    string nn="NONE";
    auto start = chrono::steady_clock::now();
    if(s=="euclidean"){
        for (int i=0; i<num_data ; i++){
            if ((dist=euclidean_dist(point.point,pPoint[i].point)) < min_dist){
                min_dist = dist;
                nn = pPoint[i].name;
            }
        }
    } else {
        for (int i=0; i<num_data ; i++){
            if ((dist=cosine_similarity(point.point,pPoint[i].point)) < min_dist){
                min_dist = dist;
                nn = pPoint[i].name;
            }
        }
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> diff = end-start;
    if (nn!="NONE"){
        cout << "Nearest neighbor True: " << nn << endl
            << "distanceTrue " << min_dist << ", search time: " << diff.count() << " seconds"<< endl;
    }
    return min_dist;
}

double euclidean_dist(vector<int> p1,vector<int> p2) {
    double sum = 0.0;
    for (int i=0 ; i<p1.size();i++){
        sum+=(p1[i]-p2[i])*(p1[i]-p2[i]);
    }
    sum = sqrt(sum);
    return sum;
}

double cosine_similarity(vector<int> p1,vector<int> p2)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
    for(unsigned int i = 0u; i < p1.size(); i++) {
        dot += p1[i] * p2[i] ;
        denom_a += p1[i] * p1[i] ;
        denom_b += p2[i] * p2[i] ;
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
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
