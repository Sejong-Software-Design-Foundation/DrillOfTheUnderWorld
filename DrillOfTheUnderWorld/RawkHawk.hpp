#ifndef __RAWK_HAWK_
#define __RAWK_HAWK_

#define RAWKHAWK_NORMAL_SPEED 8
#define RAWKHAWK_TRACK_SPEED 24

#include "NPC.hpp"

/// <summary>
/// === RawkHawk INFO ===
/// HP : 100
/// AD : 30
/// MOVEMENT : NPCPATTERNMOVEMENT && NPCTRACKINGMOVEMENT
/// </summary>

class RawkHawk : public NPC {
public:
	int movecnt;

public:
	RawkHawk(int x, int y);

	void move();
	void attack();

	void NPCHit(int atkLev);
	void AfterDead();
	void updateHPBar();
	bool PCNear();
};

RawkHawk::RawkHawk(int x, int y) : NPC(x, y, 200, 15, 1) {
	movecnt = 0;

	// RawkHawk image save
	this->imageidx = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameRawkHawk, x, y, RAWKHAWK_SCALE };

	// RawkHawk HP BAR image save
	char* curBossHPName = bmpBossHPName;
	if (maxHP > 100) curBossHPName = bmpBossHP_2Name;
	for (int i = 0; i < 100; i++) {
		imageArray[imageLayer.imageCount++] = { curBossHPName, AREA_ORIGIN_X + BLOCKSIZE + BOSS_HP_BAR_WIDTH * i, AREA_ORIGIN_Y - BLOCKSIZE, 1 };
		imageArray[imageLayer.imageCount - 1].isHide = true;
	}

	// RawkHawk HP BAR ICON save
	imageArray[imageLayer.imageCount++] = { bmpNameRawkHawk, AREA_ORIGIN_X, AREA_ORIGIN_Y - BLOCKSIZE,1 };
	imageArray[imageLayer.imageCount - 1].isHide = true;
}

void RawkHawk::move() {
	// 0-5 : 6sec
	if (cnt < 6) {
		NPCPatternMovement(RAWKHAWK_NORMAL_SPEED);
	}
	// 6-26 : 20sec
	else if (cnt < 26) {
		imageArray[imageidx] = { bmpNameRawkHawk_ready, x, y, RAWKHAWK_SCALE };
	}
	// 26-46 : 20sec
	else if (cnt < 46) {
		imageArray[imageidx] = { bmpNameRawkHawk_digging, x, y, RAWKHAWK_SCALE };
		NPCTrackingMovement(RAWKHAWK_TRACK_SPEED);
	}
	// 46-66 : 20sec
	else if (cnt < 66) {
		imageArray[imageidx] = { bmpNameRawkHawk_ready, x, y, RAWKHAWK_SCALE };
	}
	else if (cnt == 66) {
		imageArray[imageidx] = { bmpNameRawkHawk, x, y,RAWKHAWK_SCALE };
		cnt = -1;
	}
	if (PCNear()) attack();
	cnt++;
}

void RawkHawk::attack() {
    int damage = attack_damage;

    if (pc.getHasThronCrown()) {
        damage *= 2;
    }
    pc.setHP(pc.getHP() - damage);
}

void RawkHawk::NPCHit(int atkLev) {
	// if RawkHawk is digging he's not attackable
	if (imageArray[imageidx].fileName == bmpNameRawkHawk_digging) return;

	NPC::NPCHit(atkLev);
	this->updateHPBar();
	char bmpNameHit[] = "RawkHawkHit.bmp";
	imageArray[imageidx].fileName = bmpNameHit;
	imageLayer.renderAll(&imageLayer);
	imageArray[imageidx].fileName = bmpNameRawkHawk;
	imageLayer.renderAll(&imageLayer);

}

void RawkHawk::AfterDead() {
	if (strcmp(imageArray[imageidx].fileName, bmpNameNull) == 0) return;

	char bmpNameHit[] = "RawkHawkHit.bmp";
	imageArray[imageidx].fileName = bmpNameHit;
	imageLayer.renderAll(&imageLayer);
	Sleep(1000);
	for (int i = 0; i < 15; i++) {
		imageArray[imageidx].fileName = bmpExplodeName[i % 5];
		imageArray[imageidx].scale = RAWKHAWK_SCALE;
		imageLayer.renderAll(&imageLayer);
		Sleep(20);
	}
	imageArray[imageidx].fileName = bmpNameNull;
	imageLayer.renderAll(&imageLayer);
}

void RawkHawk::updateHPBar() {
	for (int i = maxHP; i >= hp; i--) {
		if (hp < i) {
			if (i / 100 == 1) {
				//if(strcmp(imageArray[imageidx + i % 100].fileName, bmpBossHPName) != 0) //100~199이면 빨간색으로 대치
				imageArray[imageidx + i % 100 + 1].fileName = bmpBossHPName;
			}
			else {
				//if(strcmp(imageArray[imageidx + i % 100].fileName, bmpNameNull) != 0)
				imageArray[imageidx + i % 100 + 1].fileName = bmpNameNull;
			}
			//0~99이면 nullBMP
		}
		//if (hp < i && strcmp(imageArray[imageidx + i].fileName, bmpNameNull) != 0) imageArray[imageidx + i].fileName = bmpNameNull;
	}
}

bool RawkHawk::PCNear() {
	int PC_X = convertPosToInfoX(imageLayer.images[0].x);
	int PC_Y = convertPosToInfoY(imageLayer.images[0].y);

	int NPC_Y = y;
	int NPC_X = x;

	// printf("(%d %d) (%d %d)", PC_X, PC_Y, NPC_X, NPC_Y);

	int startX = convertPosToInfoX(imageArray[imageidx].x);
	int startY = convertPosToInfoY(imageArray[imageidx].y);
	
	int yScale = RAWKHAWK_SCALE;
	if (strcmp(imageArray[imageidx].fileName, bmpNameRawkHawk_digging) == 0) {
		startY += BLOCKSIZE * RAWKHAWK_SCALE / 2;
		yScale /= 2;
	}
	int xScale = RAWKHAWK_SCALE;
	
	if (startX - BLOCKSIZE <= PC_X && PC_X <= startX + BLOCKSIZE*xScale &&
		startY - BLOCKSIZE <= PC_Y && PC_Y <= startY + BLOCKSIZE * yScale) return true;
	else return false;

	/*for (int curY = startY; curY < startY + BLOCKSIZE * yScale; curY++) {
		for (int curX = startX; curX < startX + BLOCKSIZE * xScale; curX++) {
			for (int dy = 0; dy < BLOCKSIZE; dy++) {
				for (int dx = 0; dx < BLOCKSIZE; dx++) {
					if (curY < 0 || curY >= 1200 || curX < 0 || curX >= 1200) continue;
					if (curX == PC_X + dx && curY == PC_Y + dy) return true;
				}
			}
		}
	}
	return false;*/
}

#endif