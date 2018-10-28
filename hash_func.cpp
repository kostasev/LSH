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
    generator.seed(std::random_device()());
    std::normal_distribution<double>        n_distribution(0.0,1.0);
    std::uniform_int_distribution<int>      uint_dist10(0,20);
    std::uniform_real_distribution<float>   uint_distW(0,const_lsh::w);
    std::vector<double> temp(dimension);
    this->v.resize(k);
    for(int i=0 ; i < k ; i++ ) {
        this->r.push_back(uint_dist10(generator));
        this->t.push_back(uint_distW(generator));
        for(int j=0 ; j < dimension ; j++ ){
            temp[j]=n_distribution(generator);
        }
        v[i]=temp;
    }
    for(int i=0 ; i < k ; i++ ) {
        std::cout<< i << " r " << this->r[i] <<std::endl;
    }
    for(int i=0 ; i < k ; i++ ) {
        std::cout<< i << " t " << this->t[i] <<std::endl;
        for(int j=0 ; j < dimension ; j++ ){
            temp[j]=n_distribution(generator);
        }
        v[i]=temp;
    }
    for(int i=0 ; i < k ; i++ ) {
        for(int j=0 ; j < dimension ; j++ ) {
            std::cout << i << j << " v  " << this->v[i][j] << std::endl;
        }
    }

}

hash_func::~hash_func(){}

value_point<int> hash_func::hash_value(data_point<int>& k,int &f,int size,int table_size){
    value_point<int> point;
    long int sum=0;
    double h=0.0;
    for(int j=0; j<size; j++){
        for (int i=0; i<k.point.size(); i++){
            h+=this->v[j][i]*k.point[i];
        }
        h+=this->t[j];
        h=h/const_lsh::w;
        point.point.push_back(int(h));
        h*=this->r[j];
        sum+=h;
        h=0.0;
    }
    f=(((sum%INT_MAX)%table_size)+table_size)%table_size;
    point.p=&k;
    return point;
}
