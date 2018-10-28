//
// Created by kosti on 10/24/2018.
//

#ifndef UNTITLED_DATA_POINT_H
#define UNTITLED_DATA_POINT_H
#include <iostream>
#include <vector>

template <typename T>
struct data_point {
    std::vector<T>  point;
    std::string     name;
};
#endif //UNTITLED_DATA_POINT_H
