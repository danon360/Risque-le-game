//
//  Subject.cpp
//  PracticingObserverPattern
//
//  Created by mushfiqur anik on 2019-11-16.
//  Copyright © 2019 mushfiqur anik. All rights reserved.
//

#include "Subject.hpp"
#include "Observer.hpp"

// Constructor
Subject::Subject() {
    _observers = new list<Observer*>;
}

// Destructor
Subject::~Subject() {
    delete _observers;
}

// Attaching a new observer
void Subject::Attach(Observer* o) {
    _observers->push_back(o);
}

// Removing the observer
void Subject::Detach(Observer* o) {
    _observers->remove(o);
}

// Notify call update() on each observer
void Subject::Notify() {
    list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); ++i)
        (*i)->Update();
}
