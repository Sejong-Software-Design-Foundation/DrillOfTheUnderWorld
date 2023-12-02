#pragma once
extern "C" {
#include <Windows.h>
}
#include <vector>

class PC {
private:
	bool hasBatFang = false; // "���� ���ݽ� ���� Ȯ���� HP�� ������ ȸ���Ѵ�.";
	bool hasBeggarDoll = false; // "PC ���ݼӵ��� ����������, ���ݽø��� ���� �Ҹ�ȴ�."
	bool hasLuckStone = false; // "������ ���� �� ���� ���� �湮 �� ���Ű��� 2�踦 �����ش�.";
	bool hasLuckCharm = false; // "������ �̸��� ������ 1ȸ ����Ѵ�."; - OK
	bool hasMetalDetector = false; // "������ �� ���� �����Ѵ�.";
	bool hasMoleClaw = false; // "���� �ı��� ��ȭ ȹ�淮�� �����Ѵ�.";
	bool hasThronCrown = false; // "PC ���ݷ��� ����������, 2���� ���ظ� �԰� �ȴ�.";
	bool hasTwoHearts = false; // "��� ������ ���ҷ��� �����Ѵ�.";
	bool hasUndergroundTicket = false; //"�������� �Ǹ��ϴ� �������� ������ 30%  ���εȴ�.";
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