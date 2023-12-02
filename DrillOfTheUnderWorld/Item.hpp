#ifndef __ITEM_
#define __ITEM_

#include "NPC.hpp"
#include <iostream>
#include <string>

enum ItemPrice {
    S_RANK_PRICE = 1000,
    A_RANK_PRICE = 500,
    B_RANK_PRICE = 300,
    C_RANK_PRICE = 100,
    E_RANK_PRICE = 300,
    N_RANK_PRICE = 0,
    F_RANK_PRICE = 0
};

class Item : public NPC {
protected:
    std::string name;
    char rank;
    int price;
    std::string imageName;
    std::string info;

public:
    Item();
    std::string getName();
    char getRank();
    int getPrice();
    std::string getInfo();
    virtual void use() = 0;
};

Item::Item() : NPC(-1, -1, 0, 0, 1){
    this->imageidx = imageLayer.imageCount;
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

#endif