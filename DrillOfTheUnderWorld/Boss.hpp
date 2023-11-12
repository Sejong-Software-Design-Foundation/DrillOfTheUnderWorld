#ifndef __BOSS_
#define __BOSS_

#include "NPC.hpp"

class Boss : public NPC {
public:
	Boss(int x, int y);

	void move(ImageLayer* il);
	void attack();
};

Boss::Boss(int x, int y) : NPC(x, y, 100, 50, 1) {}

 void Boss::move(ImageLayer* il) {
	if (PCNear(imageLayer)) {
		 attack();
		 return;
	}

	// ���� ������ �ʿ� ������
	int curPosX = imageLayer.images[0].x;
	int curPosY = imageLayer.images[0].y;

	double angle = atan2(curPosY - y, curPosX - x);

	// �̵��� �Ÿ��� ���
	double dx = SPEED * cos(angle);
	double dy = SPEED * sin(angle);

	if (collisionCheck(x + dx, y + dy)) {
		return;
	}

	// BOSS ��ǥ�� ������Ʈ
	imageLayer.images[2].x += dx;
	imageLayer.images[2].y += dy;

	x = imageLayer.images[2].x;
	y = imageLayer.images[2].y;
}

void Boss::attack() {
	SetCurrentCurPos(0, 0);
	printf("BOSS attacking PC!\n");

	// ���� ����
	// PC.HP -= attack_damage;
	// hp -= PC.attack_damage;

	// ������ ��
	if (NPCDead()) {
		return;
	}
}

#endif