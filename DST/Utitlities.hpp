//
//  Utitlities.hpp
//  DST
//
//  Created by 万伟琦 on 2018/9/7.
//  Copyright © 2018年 万伟琦. All rights reserved.
//

#ifndef Utitlities_hpp
#define Utitlities_hpp

#include <iostream>

template <typename T>
void util_swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

#endif /* Utitlities_hpp */
