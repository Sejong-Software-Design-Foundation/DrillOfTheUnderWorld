#ifndef __ZOMBIE_

#define __ZOMBIE_




#include "NPC.hpp"




class Zombie : public NPC {

public:

	Zombie(int x, int y);




	void move(ImageLayer* il);

	void attack();

};




Zombie::Zombie(int x, int y) : NPC(x, y, 100, 50, 1) {}




void Zombie::move(ImageLayer* il) {




	if (PCNear(imageLayer)) {

		attack();

		return;

	}




	cnt++;




	srand(static_cast<unsigned int>(time(nullptr)));




	if (cnt == 3) {

		curDirection = rand() % 4;

		cnt = 0;

	}




	if (collisionCheck(imageLayer.images[1].x + dir[curDirection][0] * BLOCKSIZE, imageLayer.images[1].y + dir[curDirection][1] * BLOCKSIZE)) {

		curDirection = rand() % 4;

		cnt = 0;

		return;

	}




	imageLayer.images[1].x += dir[curDirection][0] * BLOCKSIZE;

	imageLayer.images[1].y += dir[curDirection][1] * BLOCKSIZE;




	x = imageLayer.images[1].x;

	y = imageLayer.images[1].y;

}




void Zombie::attack() {

	// Implementation of attack function goes here

	setCurrentCurPos(0, 0);

	printf("NPC attacking PC!\n");




	// Example code for attacking, update as needed

	// PC.HP -= attack_damage;

	// hp -= PC.attack_damage;




	// Check if either the Zombie or PC is dead

	// if (NPCDead()) {

	//    return;

	// }

}

#endif