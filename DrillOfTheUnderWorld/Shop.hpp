#ifndef __Shop_

#define __Shop_




#include "NPC.hpp"




class Shop : public NPC {

public:

    Shop(int x, int y);




    void move(ImageLayer* il);

    void attack();

};




Shop::Shop(int x, int y) : NPC(x, y, 0, 0, 1) {
    int infoX = convertPosToInfoX(x);
    int infoY = convertPosToInfoY(y);

    int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

    // render 출력을 위한 image 번호 저장
    // image에 객체 이미지 추가
    this->imageidx = imageIndex;
    imageLayer.images[imageIndex].fileName = bmpNameShop;
}




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

    setCurrentCurPos(0, 0);

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