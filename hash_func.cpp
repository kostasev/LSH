//
// Created by kosti on 10/21/2018.
//

#include "hash_func.h"
#include <climits>
#include <random>
#include "constants.h"

hash_func::hash_func(int dimension, int k){
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,1.0);
    std::vector<float> temp(dimension);
    this->v.resize(k);
    for(int i=0 ; i < k ; i++ ) {
        this->r.push_back(rand()%SHRT_MAX);
        for(int j=0 ; j < dimension ; j++ ){
            temp[j]=distribution(generator);
        }
        v[i]=temp;
    }
}
hash_func::~hash_func(){}

long int hash_func::hash_value(Key& k,int size){
    long int sum=0;
    double h=0.0;
    float r2;
    for(int j=0; j<size; j++){
        for (int i=0; i<k.dim.size(); i++){
            h+=this->v[j][i]*k.dim[i];
        }
        r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/const_lsh::w));
        h+=r2;
        h=h/const_lsh::w;
        sum+=h;
    }
    k.hash_val=((sum%INT_MAX)%250);
    std::cout << "This the hash: " << k.hash_val << std::endl;
    return k.hash_val;
}
