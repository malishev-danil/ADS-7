// Copyright 2021 NNTU-CS
#include "train.h"

class Train {
public:
Train();
~Train();

void addCar(bool light);
int getLength();

private:
struct Car {
bool light;
Car* next;
Car* prev;

Car(bool l) : light(l), next(nullptr), prev(nullptr) {}
};

Car* first;
int countOp;
};

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
if (!first) return;

Car* current = first->next;
while (current != first) {
Car* toDelete = current;
current = current->next;
delete toDelete;
}
delete first;
}

void Train::addCar(bool light) {
Car* newCar = new Car(light);
if (!first) {
first = newCar;
first->next = first;
first->prev = first;
} else {
Car* lastCar = first->prev;
lastCar->next = newCar;
newCar->prev = lastCar;
newCar->next = first;
first->prev = newCar;
}
}

int Train::getLength() {
countOp = 0;

if (!first) return 0;

Car* current = first;
bool hasLight = false;
do {
if (current->light) {
hasLight = true;
break;
}
current = current->next;
} while (current != first);

if (!hasLight) {
first->light = true;
Car* iterator = first->next;
++countOp;
int length = 1;

while (iterator != first) {
iterator = iterator->next;
++countOp;
++length;
}

iterator = iterator->prev;
for (int i = 0; i < length; ++i) {
iterator = iterator->prev;
++countOp;
}

first->light = false;
return length;
} else {

Car* iterator = first->next;
++countOp;
int length = 1;

while (iterator != first) {
iterator = iterator->next;
++countOp;
++length;
}
countOp += static_cast<long long>(length) * length;
return length;
}
}
