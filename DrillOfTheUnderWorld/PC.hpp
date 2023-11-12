#pragma once
extern "C" {
#include <Windows.h>
}

class PC {
private:
	int HP = 100, O_2 = 100, ATK = 1, curDirection = 0;
	int dir[4][2] = { {1,0},{0,1},{-1,0}, {0,-1} };
	char* bmpPCName;
	char* bmpPCLeftName;
	char* bmpPCRightName;
	char* bmpPCDownName;
	char* bmpPCUpName;

	PC() {
		bmpPCName = _strdup("PlayerCharacter.bmp");
		bmpPCLeftName = _strdup("PC_left.bmp");
		bmpPCRightName = _strdup("PC_right.bmp");
		bmpPCDownName = _strdup("PC_down.bmp");
		bmpPCUpName = _strdup("PC_up.bmp");
	}
	PC(const PC& pc_ref) {
	}
	PC& operator=(const PC& pc_ref) {
	}
	~PC() {
	}
public:
	static PC& getPC();
	void vibe();
	COORD getCurPos();
	int getHP();
	int getOxygen();
	int getATK();
	int getDir();
	COORD getPosAfterMove(int x, int y);
	void setHP(int hp);
	void setOxygen(int o2);
	void setATK(int atk);
	void setDirRight();
	void setDirLeft();
	void setDirDown();
	void setDirUp();
	void move();
	void dig(int x, int y);
};