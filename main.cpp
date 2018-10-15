#include <iostream>
#include <getopt.h>
#include "./constants.h"

using namespace std;

int main(int argc,char** argv) {
    string inputfd, queryfd, outputfd="" ;
    int c;
    int k=-1;
    int L=-1;

    /* Reading Arguments from command line */

    while(( c = getopt(argc,argv,"d:q:k:L:o:"))){
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
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n", optopt);
                return 1;
        }
    }
    if (k==-1) k=const_lsh::k;
    if (L==-1) L=const_lsh::L;
    if (outputfd.size()==0) outputfd = "./output.txt";
    cout<< "aaaa";
    cout << "L: " << L << endl;
    cout << "k: " << k << endl;
    cout << "in: " << inputfd  << endl;
    cout << "qr: " << queryfd  << endl;
    cout << "ou: " << outputfd << endl;

    return 0;
}