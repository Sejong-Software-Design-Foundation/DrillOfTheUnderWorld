#pragma once
extern "C" {
#include <Windows.h>
}

class PC {
private:
	int HP = 100, O_2 = 100, ATK = 1;
	char* bmpPCName;
	PC() {
		bmpPCName = _strdup("PlayerCharacter.bmp");
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
	void setHP(int hp);
	void setOxygen(int o2);
	void setATK(int atk);
	void dig(int x, int y);
};