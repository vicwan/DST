//
//  main.cpp
//  DST
//
//  Created by 万伟琦 on 2018/9/5.
//  Copyright © 2018年 万伟琦. All rights reserved.
//

// 参考链接：https://dsa.cs.tsinghua.edu.cn/~deng/ds/src_link/

#include <iostream>
#include "Tests/VectorTests.hpp"
#include "Tests/ListTests.hpp"
#include "Tests/StackTests.hpp"
#include "Tests/QueueTests.hpp"

void VectorTest();

int main(int argc, const char * argv[]) {
    
    
    VectorTest();
//    ListTest();
//    StackTest();
    QueueTest();
    
    return 0;
}
