#ifndef __Mineral_
#define __Mineral_

class Mineral {
private:
	// change stagelevel in constructor for tests
	int stagelevel;
	// value is the hit counts
	enum MineralHP { BRONZE = 3, SILVER = 6, GOLD = 9, DIAMOND = 12, QUESTION_MARK = 3 };

public:
	Mineral();

	void GenerateBronze();
	void GenerateSilver();
	void GenerateGold();
	void GenerateDiamond();
	void GenerateQuestionMark();
};

void Mineral::GenerateBronze() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stagelevel == 1) num = 4;
	else if (stagelevel == 2) num = 3;
	else if (stagelevel == 3) num = 0;

	for (int i = 0; i < num; i++) {
		while (1) {
			int x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 25);
			int y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 25);

			int infoX = convertPosToInfoX(x);
			int infoY = convertPosToInfoY(y);

			int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

			if (blockInfo[infoY][infoX] == 2) {
				blockInfo[infoY][infoX] = BRONZE;
				imageLayer.images[imageIndex].fileName = bmpNameBronzeOre;
				break;
			}
		}
	}
}

void Mineral::GenerateSilver() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stagelevel == 1) num = 5;
	else if (stagelevel == 2) num = 3;
	else if (stagelevel == 3) num = 3;

	for (int i = 0; i < num; i++) {
		while (1) {
			int x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 25);
			int y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 25);

			int infoX = convertPosToInfoX(x);
			int infoY = convertPosToInfoY(y);

			int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

			if (blockInfo[infoY][infoX] == 2) {
				blockInfo[infoY][infoX] = SILVER;
				imageLayer.images[imageIndex].fileName = bmpNameSilverOre;
				break;
			}
		}
	}
}
void Mineral::GenerateGold() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stagelevel == 1) num = 1;
	else if (stagelevel == 2) num = 3;
	else if (stagelevel == 3) num = 4;

	for (int i = 0; i < num; i++) {
		while (1) {
			int x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 25);
			int y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 25);

			int infoX = convertPosToInfoX(x);
			int infoY = convertPosToInfoY(y);

			int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

			if (blockInfo[infoY][infoX] == 2) {
				blockInfo[infoY][infoX] = GOLD;
				imageLayer.images[imageIndex].fileName = bmpNameGoldOre;
				break;
			}
		}
	}
}

void Mineral::GenerateDiamond() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stagelevel == 1) num = 0;
	else if (stagelevel == 2) num = 1;
	else if (stagelevel == 3) num = 3;

	for (int i = 0; i < num; i++) {
		while (1) {
			int x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 25);
			int y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 25);

			int infoX = convertPosToInfoX(x);
			int infoY = convertPosToInfoY(y);

			int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

			if (blockInfo[infoY][infoX] == 2) {
				blockInfo[infoY][infoX] = DIAMOND;
				imageLayer.images[imageIndex].fileName = bmpNameDiamondOre;
				break;
			}
		}
	}
}

void Mineral::GenerateQuestionMark() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num = 2;


	for (int i = 0; i < num; i++) {
		while (1) {
			int x = AREA_ORIGIN_X + BLOCKSIZE * (rand() % 25);
			int y = AREA_ORIGIN_Y + BLOCKSIZE * (rand() % 25);

			int infoX = convertPosToInfoX(x);
			int infoY = convertPosToInfoY(y);

			int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

			if (blockInfo[infoY][infoX] == 2) {
				blockInfo[infoY][infoX] = QUESTION_MARK;
				imageLayer.images[imageIndex].fileName = bmpQuestionMarkName;
				break;
			}
		}
	}
}

Mineral::Mineral() {

	stagelevel = 3;

	GenerateBronze();
	GenerateSilver();
	GenerateGold();
	GenerateDiamond();
	GenerateQuestionMark();
}

#endif