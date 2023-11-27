#ifndef __Mineral_
#define __Mineral_

class Mineral {
private:
	// change stagelevel in constructor for tests
	int stagelevel;
	// value is the hit counts
	enum MineralHP { BRONZE = 3, SILVER = 6, GOLD = 9, DIAMOND = 12, ORICHALCUM = 2, QUESTION_MARK = 3 };

public:
	Mineral();
	Mineral(int n);

	void GenerateBronze();
	void GenerateSilver();
	void GenerateGold();
	void GenerateDiamond();
  void GenerateOrichalcum();
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
              for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
                  for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
                      blockInfo[curY][curX] = BRONZE;
                  }
              }
              if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameBronzeOre1;
              else imageLayer.images[imageIndex].fileName = bmpNameBronzeOre2;
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
              
                if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameSilverOre1;
                else imageLayer.images[imageIndex].fileName = bmpNameSilverOre2;
              
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
              if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameGoldOre1;
              else imageLayer.images[imageIndex].fileName = bmpNameGoldOre2;
              break;
            }
        }
    }
};

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
              if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameDiamondOre1;
              else imageLayer.images[imageIndex].fileName = bmpNameDiamondOre2;
              break;
            }
        }
    }
}

void Mineral::GenerateOrichalcum() {
	srand(static_cast<unsigned int>(time(nullptr)));

	int num;

	if (isOnMiniGameArea == 1) num = 100;
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
				if (i % 2)	imageLayer.images[imageIndex].fileName = bmpNameOrichalcumOre1;
				else imageLayer.images[imageIndex].fileName = bmpNameOrichalcumOre2;
				break;
			}
		}
	}
}

void Mineral::GenerateQuestionMark() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int num = 10;
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
	GenerateOrichalcum();
  GenerateQuestionMark();
}

#endif