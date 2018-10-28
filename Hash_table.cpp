//
// Created by kosti on 10/20/2018.
//

#include "Hash_table.h"
#include "Value.h"

Hash_table::Hash_table( int buck, int dimension, int k, std::string func){
    this->k=k;
    this->d=dimension;
    this->hash_tb.rehash(buck);
    this->hash_tb.max_load_factor(10000);
    //if (func == "euclidean") {
    std::cout << " AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA " <<std::endl;
        hfunc = new hash_func(dimension, k);
    //}
}
Hash_table::~Hash_table() {
}

void Hash_table::add_item(data_point<int>& k,int tb_size){
    Key f;
    value_point<int> point = this->hfunc->hash_value(k,f.hash_val,this->k,tb_size);
    this->hash_tb.insert({f,point});
}

Key Hash_table::query_item(data_point<int>& k,int tb_size){
    Key f;
    this->hfunc->hash_value(k,f.hash_val,this->k,tb_size);
    return f;
}

void Hash_table::get_bucket(Key k, std::map<std::string,value_point<int>>& mp){
    auto range=this->hash_tb.equal_range(k);
    for(auto it = range.first; it != range.second ; it++ ){
        mp.insert({it->second.p->name,it->second});
    }
}

void Hash_table::print_stats(){
    std::cout << "Number of buckets: " << hash_tb.bucket_count() << std::endl;
    std::cout << "Number of  Max buckets: " << hash_tb.max_bucket_count() << std::endl;
    std::cout << "Hash table size: " << hash_tb.size() << std::endl;
    for (unsigned i=0; i<hash_tb.bucket_count(); i++) {
        std::cout << "bucket #" << i << " has " << hash_tb.bucket_size(i) << " elements.\n";
    }
}