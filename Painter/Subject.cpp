#include "Subject.h"
#include "Observer.h"

void Subject::addObserver(Observer* observer) {
	if (observer != nullptr) {
		observers_.push_back(observer);
	}
}

void Subject::removeObserver(Observer* observer) {
	observers_.remove(observer);
}

void Subject::notify() {
	for (Observer* observer : observers_) {
		observer->update();
	}
}