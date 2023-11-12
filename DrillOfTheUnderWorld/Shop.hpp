#ifndef __Shop_
#define __Shop_

#include "NPC.hpp"

class Shop : public NPC {
public:
    Shop(int x, int y);

    void move(ImageLayer* il);
    void attack();
};

Shop::Shop(int x, int y) : NPC(x, y, 0, 0, 1) {}

void Shop::move(ImageLayer* il) {
    // no movement for shop
    // just checking if PCisNear

    if (PCNear(imageLayer)) {
        attack();
        return;
    }
    return;
}

void Shop::attack() {
    // Implementation of attack function goes here
    SetCurrentCurPos(0, 0);
    printf("PC wants to shop!\n");

    // Example code for attacking, update as needed
    // PC.HP -= attack_damage;
    // hp -= PC.attack_damage;

    // Check if either the Shop or PC is dead
    // if (NPCDead()) {
    //    return;
    // }
}

#endif