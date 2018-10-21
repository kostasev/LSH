//
// Created by kosti on 10/20/2018.
//

#include "Hash_table.h"

Hash_table::Hash_table( int buck, int dimension, int k, string func){
    this->k=k;
    this->d=dimension;
    hash_tb.rehash(buck);
    if (func == "euclidean") {
        hfunc = new hash_func(dimension, k);
    }
}
Hash_table::~Hash_table() {
}

void Hash_table::add_item(string name,Key k){
    k.hash_val=this->hfunc->hash_value(k,this->k);
    this->hash_tb[name]=k;
}

/*vector<string,Key> Hash_table::get_bucket_of(string name){
    size_t pos = hash_tb.bucket(name);
    for ( auto ii = hash_tb.begin(pos) ; ii != hash_tb.end(pos) ; ii++ )
        cout << ii->first
             << " "
             << ii->second.dim.size()
             << endl
             << endl;
}*/

void Hash_table::print_stats(){
    cout << "Number of buckets: " << hash_tb.bucket_count() << endl;
    cout << "Number of  Max buckets: " << hash_tb.max_bucket_count() << endl;
    cout << "Hash table size: " << hash_tb.size() << endl;
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