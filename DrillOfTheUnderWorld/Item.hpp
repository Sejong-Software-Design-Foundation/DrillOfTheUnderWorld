#ifndef __ITEM_
#define __ITEM_

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

class Item{
protected:
    std::string name;
    char rank;
    int price;
    std::string imageName;
    std::string info;
    int imageidx;

public:
    Item();
    std::string getName();
    char getRank();
    int getPrice();
    std::string getInfo();
    virtual void use() = 0;
};

#endif