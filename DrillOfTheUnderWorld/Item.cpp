#include "Item.hpp"
#include "common.hpp"

Item::Item(){
    this->imageidx = imageLayer.imageCount;
    this->price = 0;
    this->rank = 'N';
    imageArray[this->imageidx].isHide = 1;
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