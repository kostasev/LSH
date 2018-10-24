//
// Created by kosti on 10/20/2018.
//

#include "Hash_table.h"


Hash_table::Hash_table( int buck, int dimension, int k, std::string func){
    this->k=k;
    this->d=dimension;
    hash_tb.rehash(buck);
    hash_tb.max_load_factor(1000);
    if (func == "euclidean") {
        hfunc = new hash_func(dimension, k);
    }
}
Hash_table::~Hash_table() {
}

void Hash_table::add_item(std::string name,Key k,int tb_size){
    this->hfunc->hash_value(k,this->k,tb_size);
    this->hash_tb[k]=name;
}

std::vector<data_point> Hash_table::get_bucket(Key k){
    size_t pos = this->hash_tb.equal_range({k,0});
    std::vector<data_point> bucks;
    for ( auto ii = hash_tb.begin(pos) ; ii != hash_tb.end(pos) ; ii++ ){
        std::cout << ii->first.dim.size()
             << " "
             << ii->second;
        bucks.push_back({ii->first,ii->second});
    }
    return bucks;
}

void Hash_table::print_stats(){
    std::cout << "Number of buckets: " << hash_tb.bucket_count() << std::endl;
    std::cout << "Number of  Max buckets: " << hash_tb.max_bucket_count() << std::endl;
    std::cout << "Hash table size: " << hash_tb.size() << std::endl;
    for (unsigned i=0; i<hash_tb.bucket_count(); i++) {
        std::cout << "bucket #" << i << " has " << hash_tb.bucket_size(i) << " elements.\n";
    }

    /*for ( auto ii = hash_tb.begin() ; ii != hash_tb.end() ; ii++ )
        cout << ii->first.dim.size()
             << " "
             << ii->second
             << endl
             << endl;
    */
}