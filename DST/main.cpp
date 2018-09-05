//
//  main.cpp
//  DST
//
//  Created by 万伟琦 on 2018/9/5.
//  Copyright © 2018年 万伟琦. All rights reserved.
//

// 参考链接：https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/

#include <iostream>
#include "Vector.hpp"

void VectorTest();

int main(int argc, const char * argv[]) {
    
    
    VectorTest();
    
    
    return 0;
}

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
    v.remove(2, 4);
    v.printVector();
    v.removeAtIndex(3);
    v.printVector();
    v.find(5);
}
