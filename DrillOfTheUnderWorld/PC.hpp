#pragma once
extern "C" {
#include <Windows.h>
}
#include <vector>

class PC {
private:
	bool hasBatFang = false; // "보스 공격시 낮은 확률로 HP를 일정량 회복한다.";
	bool hasBeggarDoll = false; // "PC 공격속도가 증가하지만, 공격시마다 돌이 소모된다."
	bool hasLuckStone = false; // "아이템 구매 후 다음 상점 방문 시 구매값의 2배를 돌려준다.";
	bool hasLuckCharm = false; // "죽음의 이르는 공격을 1회 방어한다."; - OK
	bool hasMetalDetector = false; // "광물이 더 자주 등장한다.";
	bool hasMoleClaw = false; // "광물 파괴시 재화 획득량이 증가한다.";
	bool hasThronCrown = false; // "PC 공격력이 증가하지만, 2배의 피해를 입게 된다.";
	bool hasTwoHearts = false; // "산소 게이지 감소량이 감소한다.";
	bool hasUndergroundTicket = false; //"상점에서 판매하는 아이템의 가격이 30%  할인된다.";
	int luckStoneStage = 0;

	//std::vector<Item*> ownedItemList;
	int usableEnergyBarCount = 0, usablePortableOxygenCanCount = 0;

	int MAX_HP = 100, MAX_O2 = 100;
	int AtkLev = 1, AtkSpdLev = 1, SpdLev = 1;
	int flagCnt = 0;

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
	char* bmpPCHitLeftName;
	char* bmpPCHitRightName;
	char* bmpPCHitDownName;
	char* bmpPCHitUpName;
	char* bmpPCgetHPLeftName;
	char* bmpPCgetHPRightName;
	char* bmpPCgetHPDownName;
	char* bmpPCgetHPUpName;
	char* bmpPCgetOxygenLeftName;
	char* bmpPCgetOxygenRightName;
	char* bmpPCgetOxygenDownName;
	char* bmpPCgetOxygenUpName;
	PC() {
		bmpPCName = _strdup("PlayerCharacter.bmp");
		bmpPCLeftName = _strdup("PC_left.bmp");
		bmpPCRightName = _strdup("PC_right.bmp");
		bmpPCDownName = _strdup("PC_down.bmp");
		bmpPCUpName = _strdup("PC_up.bmp");
		bmpPCHitLeftName = _strdup("PC_left_hit.bmp");
		bmpPCHitRightName = _strdup("PC_right_hit.bmp");
		bmpPCHitDownName = _strdup("PC_down_hit.bmp");;
		bmpPCHitUpName = _strdup("PC_up_hit.bmp");
		bmpPCgetHPLeftName = _strdup("PC_left_getHP.bmp");
		bmpPCgetHPRightName = _strdup("PC_right_getHP.bmp");
		bmpPCgetHPDownName = _strdup("PC_down_getHP.bmp");
		bmpPCgetHPUpName = _strdup("PC_up_getHP.bmp");
		bmpPCgetOxygenLeftName = _strdup("PC_left_getOxygen.bmp");
		bmpPCgetOxygenRightName = _strdup("PC_right_getOxygen.bmp");
		bmpPCgetOxygenDownName = _strdup("PC_down_getOxygen.bmp");
		bmpPCgetOxygenUpName = _strdup("PC_up_getOxygen.bmp");
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
	void setMaxHP(int maxHp);
	void setMaxOxygen(int maxOxygen);
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
	void increaseFlagCnt();
	int getFlagCnt();
	void initFlagCnt();
	void updateDigResultReward(int digY, int digX, int infoY, int infoX, int imageIndex);
	void applyDigReward(int targerImageIndex, int delay);
	void digQuestionBlock(int digY, int digX, int infoY, int infoX, int imageIndex);
	void boom(int digY, int digX, int infoY, int infoX, int imageIndex);
	void hitEffect();
	void getHPEffect();
	void getOxygenEffect();

	//std::vector<Item*> getOwnedItemList();
	void setUsablePortableOxygenCanCount(int count);
	void setUsableEnergyBarCount(int count);
	int getUsablePortableOxygenCanCount();
	int getUsableEnergyBarCount();

	void setHasBatFang(boolean isHas);
	bool getHasBatFang();

	void setHashasBeggarDoll(boolean isHas);
	bool getHashasBeggarDoll();

	void setHasLuckStone(boolean isHas);
	bool getHasLuckStone();

	void setHasLuckCharm(boolean isHas);
	bool getHasLuckCharm();

	void setLuckStoneStage(int luckStoneStage);
	int getLuckStoneStage();

	void setHasMetalDetector(boolean isHas);
	bool getHasMetalDetector();

	void setHasMoleClaw(boolean isHas);
	bool getMoleClaw();

	void setHasThronCrown(boolean isHas);
	bool getHasThronCrown();

	void setHasTwoHearts(boolean isHas);
	bool getHasTwoHearts();

	void setHasUndergroundTicket(boolean isHas);
	bool getHasUndergroundTicket();
};