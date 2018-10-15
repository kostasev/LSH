#include <iostream>
#include <getopt.h>
#include "./constants.h"

using namespace std;

int main(int argc,char** argv) {
    string inputfd, queryfd, outputfd="";
    bool read_query;
    int c;
    int k=-1;
    int L=-1;

    /* Reading Arguments from command line */

    while(( c = getopt(argc,argv,"d:q:k:L:o:")) !=-1 ){

        switch (c) {
            case 'd':
                inputfd = optarg;
                break;
            case 'q':
                queryfd = optarg;
                break;
            case 'k':
                k = atoi(optarg);
                break;
            case 'L':
                L = atoi(optarg);
                break;
            case 'o':
                outputfd = optarg;
                break;
            case '?':
                cerr << "Unknown option character " << char(optopt) << endl;
                return 1;
            default:
                abort();
        }
    }
    if (inputfd.size()==0) {
        cerr << "Data file was not defined!" << endl ;
    }
    if (k==-1) k=const_lsh::k;
    if (L==-1) L=const_lsh::L;
    if (queryfd.size()==0) read_query=true;
    if (outputfd.size()==0) outputfd = "./output.txt";

    cout << "L: " << L << endl;
    cout << "k: " << k << endl;
    cout << "in: " << inputfd  << endl;
    cout << "qr: " << queryfd  << endl;
    cout << "ou: " << outputfd << endl;

    return 0;
}