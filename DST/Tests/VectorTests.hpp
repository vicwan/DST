//
//  VectorTests.hpp
//  DST
//
//  Created by Vic Wan on 2018/9/7.
//  Copyright © 2018 万伟琦. All rights reserved.
//

#ifndef VectorTests_hpp
#define VectorTests_hpp

#include "Vector.hpp"

void VectorTest()
{
    Vector<int> v = Vector<int>();
    v.append(1);
    v.append(2);
    v.append(3);
    v.append(2);
    v.insert(1, 5);
    v.insert(4, 9);
    v.append(32);
    v.printVector();
    
    v.removeAtIndex(2);
    v.printVector();
    //    v.remove(2, 4);
    v.printVector();
    //    v.removeAtIndex(3);
    v.printVector();
    v.find(2);
    //    v.sort_bubble(0, 6);
    //    v.sort_bubble_fast(0, 6);
    v.sort_merge(0, 6);
    v.printVector();
}

#endif /* VectorTests_hpp */
