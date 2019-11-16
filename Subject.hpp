//
//  Subject.hpp
//  PracticingObserverPattern
//
//  Created by mushfiqur anik on 2019-11-16.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp

#include <stdio.h>
#include <list>
using namespace std;

class Observer; // Declaration

class Subject {
    
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
    
private:
    list <Observer*> *_observers;
};

#endif /* Subject_hpp */
