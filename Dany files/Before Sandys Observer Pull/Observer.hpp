//
//  Observer.hpp
//  PracticingObserverPattern
//
//  Created by mushfiqur anik on 2019-11-16.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

#include<string>
#include <stdio.h>
using namespace std;

class Observer {
    
public:
    Observer();
    ~Observer();
    virtual void Update() = 0;
    virtual void Update(int playerID, string phase, string action) = 0;
};

#endif /* Observer_hpp */
