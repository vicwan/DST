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
}

#endif /* ListTests_hpp */
