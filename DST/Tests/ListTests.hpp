//
//  ListTests.hpp
//  DST
//
//  Created by Vic Wan on 2018/9/9.
//  Copyright © 2018 万伟琦. All rights reserved.
//

#ifndef ListTests_hpp
#define ListTests_hpp

#import "List.hpp"

void ListTest()
{
    List<int> l = List<int>();
    
    l.append(3);
    l.append(5);
    
    l.printList();
    l.removeAtIndex(1);
    l.printList();
    
    l.append(34);
    l.append(12);
    l.append(66);
    l.append(54);
    l.append(97);
    l.append(4);
    l.append(9);
    
    l.printList();
    
    l.remove(1, 4);
    l.printList();
    __unused int v = l.removeAtIndex(1);
    l.printList();
//    printf("::%d\n", v);
////    l.removeAll();
////    l.printList();
}

#endif /* ListTests_hpp */
