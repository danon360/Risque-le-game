//
//  Subject.hpp
//  PracticingObserverPattern
//
//  Created by mushfiqur anik on 2019-11-16.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp

// Using libraries
#include <stdio.h>
#include <list>
using namespace std;
#include "Observable.hpp"

class Observer; // Forwar Declaration

class Subject : public Observable {
    
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    virtual void Notify(int playerID, string phase, string action); // This is for the PhaseObserverView
    Subject();
    ~Subject();
    
private:
    list <Observer*> *_observers;
};

#endif /* Subject_hpp */
