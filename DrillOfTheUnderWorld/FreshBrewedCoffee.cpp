#include "FreshBrewedCoffee.hpp"
#include "common.hpp"

FreshBrewedCoffee::FreshBrewedCoffee() : Item() {
    this->name = "갓 끓인 커피";
    this->info = "PC의 최대 산소게이지가 10% 증가한다.";
    this->rank = 'C';
    this->price = C_RANK_PRICE;
    imageArray[imageLayer.imageCount++] = { bmpFreshBrewedCoffeeName, -1, -1, 1, 1 };
}

void FreshBrewedCoffee::use() {
    pc.setMaxOxygen(pc.getMaxOxygen() * 1.1);
}