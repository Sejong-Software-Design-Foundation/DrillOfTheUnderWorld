#include "Item.hpp"
#include "common.hpp"

Item::Item(){
    this->imageidx = imageLayer.imageCount;
    this->price = 0;
    this->rank = 'N';
    this->isUniqueHoldableItem = false;
}

std::string Item::getName() {
    return this->name;
}

char Item::getRank() {
    return this->rank;
}

int Item::getPrice() {
    return this->price;
}

std::string Item::getInfo() {
    return this->info;
}

int Item::getImageIndex() {
    return this->imageidx;
}

bool Item::getIsUniqueHoldableItem() {
    return this->isUniqueHoldableItem;
}