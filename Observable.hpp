//
//  Observable.hpp
//  Assignment3
//
//  Created by mushfiqur anik on 2019-11-17.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

#pragma once
#include <list>
using namespace std;

class Observer;

class Observable
{
public:
    virtual ~Observable() {};
    virtual void Attach(Observer *) = 0;
    virtual void Detach(Observer *) = 0;
    virtual void Notify() = 0;
    virtual void Notify(int playerID, string phase, string action) = 0; // This is for the PhaseObserver View 
protected:
    Observable() {};
private:
    list<Observer*> _observers;
};
