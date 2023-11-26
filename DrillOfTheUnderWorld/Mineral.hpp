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
	void GenerateBronze(int x, int y);
	void GenerateSilver(int x, int y);
	void GenerateGold(int x, int y);
	void GenerateDiamond(int x, int y);
	void getCluster();
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
				for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
					for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
						blockInfo[curY][curX] = BRONZE;
					}
				}
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
				for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
					for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
						blockInfo[curY][curX] = SILVER;
					}
				}
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
				for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
					for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
						blockInfo[curY][curX] = GOLD;
					}
				}
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
				for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
					for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
						blockInfo[curY][curX] = DIAMOND;
					}
				}
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
				for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
					for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
						blockInfo[curY][curX] = QUESTION_MARK;
					}
				}
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

void Mineral::GenerateBronze(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

	blockInfo[infoY][infoX] = BRONZE;
	imageLayer.images[imageIndex].fileName = bmpNameBronzeOre;
}

void Mineral::GenerateSilver(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

	blockInfo[infoY][infoX] = SILVER;
	imageLayer.images[imageIndex].fileName = bmpNameSilverOre;
}
void Mineral::GenerateGold(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

	blockInfo[infoY][infoX] = GOLD;
	imageLayer.images[imageIndex].fileName = bmpNameGoldOre;
}

void Mineral::GenerateDiamond(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;

	blockInfo[infoY][infoX] = DIAMOND;
	imageLayer.images[imageIndex].fileName = bmpNameDiamondOre;
}
void Mineral::getCluster() {
	int clusterX;
	int clusterY;
	while (true) {
		clusterX = (rand() % 22) * BLOCKSIZE + AREA_ORIGIN_X;
		clusterY = (rand() % 13) * BLOCKSIZE + AREA_ORIGIN_Y + 10 * BLOCKSIZE;
		bool ok = true;
		for (int i = 0;i < 3;i++) {
			for (int j = 0;j < 3;j++) {
				if (!blockInfo[convertPosToInfoY(clusterY + i * BLOCKSIZE)][clusterX + j * BLOCKSIZE]) {
					ok = false;
					break;
				}
			}
		}
		if (ok) break;
	}
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			int r = rand() % 4;
			int x = clusterX + j * BLOCKSIZE;
			int y = clusterY + i * BLOCKSIZE;
			switch (r) {
			case 0: GenerateBronze(x, y); break;
			case 1: GenerateSilver(x, y); break;
			case 2: GenerateGold(x, y); break;
			case 3: GenerateDiamond(x, y); break;
			}
		}
	}
}
#endif