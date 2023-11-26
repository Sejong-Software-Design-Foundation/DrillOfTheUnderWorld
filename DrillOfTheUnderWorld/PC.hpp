#pragma once
extern "C" {
#include <Windows.h>
}
#include <vector>

class PC {
private:

	int MAX_HP = 100, MAX_O2 = 100;
	int AtkLev = 1, AtkSpdLev = 1, SpdLev = 1;

	int HP = 100, O2 = 100, ATK = 1, curDirection = 0;
	int stone = 0;
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };

	std::vector<int> itemList;

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
	std::vector<int> getitemList();
	void addItem(int itemIndex);
	int getStone();
	int getHP();
	int getOxygen();
	int getMaxHP();
	int getMaxOxygen();
	int getATK();
	int getDir();
	COORD getPosAfterMove(int x, int y);
	void setStone(int stone);
	COORD getTargetPos(int x, int y);
	void setHP(int hp);
	void setOxygen(int o2);
	void setATK(int atk);
	void setDirRight();
	void setDirLeft();
	void setDirDown();
	void setDirUp();
	void move();
	void dig(int x, int y);
	void moveInStage();

	int getAtkLev();
	int getAtkSpdLev();
	int getSpdLev();
	void setAtkLev(int lev);
	void setAtkSpdLev(int lev);
	void setSpdLev(int lev);
	bool isDigable(int x, int y);


	void updateDigResultReward(int digY, int digX, int infoY, int infoX, int imageIndex);
	void applyDigReward(int targerImageIndex, int delay);
	void digQuestionBlock(int digY, int digX, int infoY, int infoX, int imageIndex);
	void boom(int digY, int digX, int infoY, int infoX, int imageIndex);
};