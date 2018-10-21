//
// Created by kosti on 10/20/2018.
//

#ifndef UNTITLED_KEY_H
#define UNTITLED_KEY_H
#include <iostream>
#include <vector>

using namespace std;

struct Key {
    vector<int> dim ;

    bool operator==(const Key& lhs) const
    {
        if (lhs.dim.size() != dim.size()) return false;
        for (int i = 0 ; i < lhs.dim.size() ; i++) {
            if (lhs.dim[i]!=dim[i]){
                return false;
            }
        }
        return true;
    }
};

/*namespace std {
    template <>
    struct hash<Key>{
        size_t operator()(const Key &k) const {
            int sum = 0;
            for (int i = 0; i < k.dim.size(); i++) {
                sum += k.dim[i];
            }
            cout << "Hash is: " << (sum % 2) << " of sum: " << sum << endl;
            return (sum % 2);
        }
    };
}*/

#endif //UNTITLED_KEY_H
