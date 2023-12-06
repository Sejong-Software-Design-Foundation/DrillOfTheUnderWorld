#ifndef __Mineral_
#define __Mineral_

class Mineral {
private:
	// value is the hit counts
	enum MineralHP { BRONZE = 3, SILVER = 6, GOLD = 9, DIAMOND = 12, ORICHALCUM = 3, QUESTION_MARK = 3 };

public:
	Mineral();
	Mineral(int n);

	void GenerateBronze();
	void GenerateSilver();
	void GenerateGold();
	void GenerateDiamond();
	void GenerateOrichalcum();
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

	if (stageLevel == 1) num = 4;
	else if (stageLevel == 2) num = 3;
	else if (stageLevel == 3) num = 0;

	if (isMiniGameArea == 1) num = 0;

	if (pc.getHasMetalDetector()) {
		num *= 2;
	}

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
				if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameBronzeOre1[stageLevel - 1];
				else imageLayer.images[imageIndex].fileName = bmpNameBronzeOre2[stageLevel - 1];
				break;
			}
		}
	}
}

void Mineral::GenerateSilver() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stageLevel == 1) num = 5;
	else if (stageLevel == 2) num = 3;
	else if (stageLevel == 3) num = 3;

	if (isMiniGameArea == 1) num = 0;

	if (pc.getHasMetalDetector()) {
		num *= 2;
	}

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
				if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameSilverOre1[stageLevel - 1];
				else imageLayer.images[imageIndex].fileName = bmpNameSilverOre2[stageLevel - 1];

				break;
			}
		}
	}
}
void Mineral::GenerateGold() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stageLevel == 1) num = 1;
	else if (stageLevel == 2) num = 3;
	else if (stageLevel == 3) num = 4;

	if (isMiniGameArea == 1) num = 0;

	if (pc.getHasMetalDetector()) {
		num *= 2;
	}

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
				if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameGoldOre1[stageLevel - 1];
				else imageLayer.images[imageIndex].fileName = bmpNameGoldOre2[stageLevel - 1];
				break;
			}
		}
	}
};

void Mineral::GenerateDiamond() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (stageLevel == 1) num = 0;
	else if (stageLevel == 2) num = 1;
	else if (stageLevel == 3) num = 3;

	if (isMiniGameArea == 1) num = 0;

	if (pc.getHasMetalDetector()) {
		num *= 2;
	}

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
				if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameDiamondOre1[stageLevel - 1];
				else imageLayer.images[imageIndex].fileName = bmpNameDiamondOre2[stageLevel - 1];
				break;
			}
		}
	}
}

void Mineral::GenerateOrichalcum() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (isMiniGameArea == 1) num = 100;
	else num = 0;

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
						blockInfo[curY][curX] = ORICHALCUM;
					}
				}
				if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameOrichalcumOre1[stageLevel - 1];
				else imageLayer.images[imageIndex].fileName = bmpNameOrichalcumOre2[stageLevel - 1];
				break;
			}
		}
	}
}

void Mineral::GenerateQuestionMark() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num = 10;
	if (isMiniGameArea == 1) num = 0;

	if (pc.getHasMetalDetector()) {
		num *= 2;
	}

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
	GenerateBronze();
	GenerateSilver();
	GenerateGold();
	GenerateDiamond();
	GenerateOrichalcum();
	GenerateQuestionMark();
}

void Mineral::GenerateBronze(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			blockInfo[curY][curX] = BRONZE;
		}
	}

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;
	imageLayer.images[imageIndex].fileName = bmpNameBronzeOre2[stageLevel - 1];
}

void Mineral::GenerateSilver(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			blockInfo[curY][curX] = SILVER;
		}
	}

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;
	imageLayer.images[imageIndex].fileName = bmpNameSilverOre1[stageLevel - 1];
}
void Mineral::GenerateGold(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			blockInfo[curY][curX] = GOLD;
		}
	}

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;
	imageLayer.images[imageIndex].fileName = bmpNameGoldOre2[stageLevel - 1];
}

void Mineral::GenerateDiamond(int x, int y) {
	int infoX = convertPosToInfoX(x);
	int infoY = convertPosToInfoY(y);
	for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
		for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
			blockInfo[curY][curX] = DIAMOND;
		}
	}

	int imageIndex = (infoY / BLOCKSIZE) * 25 + (infoX / BLOCKSIZE) + 1;
	imageLayer.images[imageIndex].fileName = bmpNameDiamondOre1[stageLevel - 1];
}
void Mineral::getCluster() {
	int clusterX;
	int clusterY;
	while (true) {
		clusterX = (rand() % 22) * BLOCKSIZE + AREA_ORIGIN_X;
		clusterY = (rand() % 13 + 10) * BLOCKSIZE + AREA_ORIGIN_Y;
		bool ok = true;
		for (int i = 0;i < 3;i++) {
			for (int j = 0;j < 3;j++) {
				int infoX = convertPosToInfoX(clusterX + j * BLOCKSIZE);
				int infoY = convertPosToInfoY(clusterY + i * BLOCKSIZE);
				if (!blockInfo[infoY][infoX]
					|| infoX <= 0 || infoX >= 1200-BLOCKSIZE || infoY <= 0 || infoY >= 1200-BLOCKSIZE) {
					ok = false;
					break;
				}
			}
		}
		if (ok) break;
	}
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			int r = rand() % 100;
			int x = clusterX + j * BLOCKSIZE;
			int y = clusterY + i * BLOCKSIZE;
			if (stageLevel == 1) {
				if (0<=r && r<=40) GenerateBronze(x, y);
				else if (r <= 70) GenerateSilver(x, y);
				else GenerateGold(x, y);
			}
			else if (stageLevel == 2) {
				if (0 <= r && r <= 20) GenerateBronze(x, y);
				else if (r <= 50) GenerateSilver(x, y);
				else if (r <= 80) GenerateGold(x, y);
				else GenerateDiamond(x, y);
			}
			else if (stageLevel == 3) {
				if (r <= 30) GenerateSilver(x, y);
				else if (r <= 60) GenerateGold(x, y);
				else GenerateDiamond(x, y);
			}
		}
	}
}

#endif