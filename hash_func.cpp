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
        this->r.push_back(rand()%9999);
        this->t.push_back(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/const_lsh::w)));
        for(int j=0 ; j < dimension ; j++ ){
            temp[j]=distribution(generator);
        }
        v[i]=temp;
    }
}
hash_func::~hash_func(){}

long int hash_func::hash_value(Key& k,int size,int table_size){
    long int sum=0;
    double h=0.0;
    for(int j=0; j<size; j++){
        for (int i=0; i<k.dim.size(); i++){
            h+=this->v[j][i]*k.dim[i];
        }
        h+=this->t[j];
        h=h/const_lsh::w;
        h*=this->r[j];
        sum+=h;
        h=0.0;
    }
    k.hash_val=(((sum%INT_MAX)%table_size)+table_size)%table_size;
    std::cout << "This the hash: " << k.hash_val << std::endl;
    return k.hash_val;
}
