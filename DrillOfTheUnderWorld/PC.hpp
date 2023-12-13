#pragma once
extern "C" {
#include <Windows.h>
}
#include <vector>
#include <time.h>

class PCBullet {
private:
	int x, y;
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };
	int dir;
	int speed=48;
	int imageidx;

	static char bmpPCBulletLeftName[];
	static char bmpPCBulletRightName[];
	static char bmpPCBulletUpName[];
	static char bmpPCBulletDownName[];

public:
	PCBullet();
	PCBullet(int x, int y, int dir);
	bool move();
	bool checkBulletHit(int bossX, int bossY);
};

class PC {
private:
	bool hasBatFang = false; // "?�쏙?�占?�옙 ?�쏙?�占?�쏙???�쏙?�占?�옙 ?�占?�옙?�쏙??HP?�쏙???�쏙?�占?�옙?�쏙???�占?�옙?�싼?�옙.";
	bool hasBeggarDoll = false; // "PC ?�쏙?�占?�속?�옙?�쏙???�쏙?�占?�옙?�쏙?�占?�옙?�쏙?? ?�쏙?�占?�시몌옙?�쏙???�쏙?�占?�옙 ?��?몌옙?�占?"
	bool hasLuckStone = false; // "?�쏙?�占?�옙?�쏙???�쏙?�占?�옙 ?�쏙???�쏙?�占?�옙 ?�쏙?�占?�옙 ?�썸�??�쏙???�쏙?�占?�곤?�占?�옙 2?�썼�??�쏙?�占?�옙?�쌔?�옙.";
	bool hasLuckCharm = false; // "?�쏙?�占?�옙?�쏙???�싱몌옙?�쏙???�쏙?�占?�옙?�쏙??1???�쏙?�占?�옙�?��?"; - OK
	bool hasMetalDetector = false; // "?�쏙?�占?�옙?�쏙???�쏙???�쏙?�占?�옙 ?�쏙?�占?�옙?�싼?�옙.";
	bool hasMoleClaw = false; // "?�쏙?�占?�옙 ?�식깍옙?�쏙???�쏙?�화 ?�占?�량?�쏙???�쏙?�占?�옙?�싼?�옙.";
	bool hasThronCrown = false; // "PC ?�쏙?�占?�뤄?�占?�옙 ?�쏙?�占?�옙?�쏙?�占?�옙?�쏙?? 2?�쏙?�占?�옙 ?�쏙?�占?�몌???�쌉곤옙 ?�싫?�옙.";
	bool hasTwoHearts = false; // "?�쏙?�占??�쏙?�占?�옙?�쏙???�쏙?�占?�뤄옙?�쏙???�쏙?�占?�옙?�싼?�옙.";
	bool hasUndergroundTicket = false; //"?�쏙?�占?�옙?�쏙?�占?�옙 ?�실몌옙?�싹?�옙 ?�쏙?�占?�옙?�쏙?�占?�옙 ?�쏙?�占?�옙?�쏙??30%  ?�쏙?�占?�된?�옙.";
	int luckStoneStage = 0;

	//std::vector<Item*> ownedItemList;
	int usableEnergyBarCount = 0, usablePortableOxygenCanCount = 0;

	int MAX_HP = 100, MAX_O2 = 100, MAX_FATIGUE = 10;
	int AtkLev = 11, AtkSpdLev = 11, SpdLev = 11;
	int flagCnt = 0;
	int lastAttackTime;
	clock_t lastHitTime = 0;

	int HP = 100, O2 = 100, FATIGUE = 10, ATK = 20, curDirection = 0;
	int stone = 10000;
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };
	std::vector<int> itemList;
	std::vector<PCBullet>pcBullets;

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
		lastAttackTime = 0;
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
	int getFatigue();
	int getMaxHP();
	int getMaxOxygen();
	int getMaxFatigue();
	int getATK();
	int getDir();
	COORD getPosAfterMove(int x, int y);
	void setStone(int stone);
	COORD getTargetPos(int x, int y);
	void setHP(int hp);
	void setOxygen(int o2);
	void setFatigue(int ft);
	void setMaxHP(int maxHp);
	void setMaxOxygen(int maxOxygen);
	void setMaxFatigue(int maxFt);
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

	void attack(clock_t t);


	void setLastAttackTime(clock_t t);
	std::vector<PCBullet>& getBulletList();

};