#pragma once

#include <list>

class Observer;

class Subject {
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notify();

private:
	std::list<Observer*> observers_;
};

