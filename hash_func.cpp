//
// Created by kosti on 10/21/2018.
//

#include "hash_func.h"
#include <climits>
#include <random>
#include "constants.h"
#include "data_point.h"


hash_func::hash_func(int dimension, int k){
    std::mt19937 generator;
    generator.default_seed;//(std::random_device()());
    std::normal_distribution<double>         n_distribution(0.0,1.0);
    std::uniform_real_distribution<double>   uint_distW(0,const_lsh::w);
    std::vector<double> temp(dimension);

    for(int i=0 ; i < k ; i++ ) {
        this->t.push_back(uint_distW(generator));
        for(int j=0 ; j < dimension ; j++ ){
            temp[j]=n_distribution(generator);
        }
        v.push_back(temp);
    }
}

hash_func::~hash_func(){
    this->t.clear();
    this->v.clear();
}

value_point<int> hash_func::hash_value(data_point<int>& k,int &f,int size,int table_size,std::vector<int> r){
    value_point<int> point;
    long int sum=0;
    double h=0.0;
    for(int j=0; j<size; j++){
        for (int i=0; i<k.point.size(); i++){
            h+=this->v[j][i]*k.point[i];
        }
        h=h+this->t[j];
        h=h/(double)const_lsh::w;
        point.point.push_back(int(h));
        sum+=int(h)*r[j];
        h=0.0;
    }
    f=int((((sum%INT_MAX-5)%table_size)+table_size)%table_size);
    point.p=&k;
    return point;
}
