// Copyright 2021 NNTU-CS
#include "train.h"
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
const Car* iterator = first->next;
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
const Car* iterator = first->next;
++countOp;
int length = 1;
while (iterator != first) {
iterator = iterator->next;
++countOp;
++length;
}
countOp += static_cast<int64_t>(length) * length;
return length;
}
}
