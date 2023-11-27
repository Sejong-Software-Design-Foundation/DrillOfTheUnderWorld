#include "common.hpp"
#include "Mole.hpp"
#include "EmceeTheShyGuy.hpp"
#include "Mineral.hpp"
#include "Ladder.hpp"
#include "Bat.hpp"

int main() {
	initialize(); // �������� �̴ϼȶ���¡(�ܼ� ������ ����, ������ ���� ��)

	// ���̾� �̴ϼȶ���¡
	// �� ���̾ ���� NUM ����
	stageLayer.initialize(&stageLayer);
	stageLayer.NUM = 1;
	imageLayer.initialize(&imageLayer); // imageLayer�� ����� ���̾��� ���� ��
	imageLayer.NUM = 2;
	rewardLayer.initialize(&rewardLayer);
	rewardLayer.NUM = 3;

	// ���� ���
	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1 }; // PC�� imageLayer 0���� ����
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;

	initStageImage();				// stageLayer���� ����ϴ� ��� �̹��� ���� ����
	fillBlockImages();				// imageLayer�� ���(25x25) ���� ���� 
	initAreaUI();					// imageLayer�� UI �̹��� ���� ����
	initRewardImage();				// rewardLayer���� ����ϴ� ��� �̹��� ���� ����

	// �����۰� ���õ� �Լ���(���� ���� ��)
	pc.addItem(1);
	pc.addItem(2);
	pc.addItem(3);
	initItemImages();

	// ����� ���ο��� �ð��� ��� ���� ������
	clock_t start_time = clock();
	clock_t end_time;
	clock_t timee;
	clock_t minigameStartTime = clock();
	double duration;

	// NPC �̴ϼȶ���¡(���� ��ġ�� ȭ��󿡼� ������ �ʵ��� �ʱ�ȭ)
	//Mole* mole = new Mole(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	Bat* bat = new Bat(-48, -48);
	Ladder* ladder = new Ladder(-48, -48);
	EmceeTheShyGuy* Emcee = new EmceeTheShyGuy(-48, -48);

	// ���Ŀ� gameStartLayer(���� ���� �� ó�� ������ ���ѷα� ���� ����) ����� �Ʒ� �ڵ� changeLayer�� ȣ��ǵ��� ����
	targetLayer = &stageLayer;
	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	while (1) {
		if (isOnStage) { // PC�� �������� �ʿ� �����ϴ� ���
			updateCharacterStatus(); // PC ����â�� ������Ʈ
			while (_kbhit() != 0) {
				int key = _getch();
				// PC ��ġ ������ ������Ʈ�ϴ� ������(�ȼ� ������)
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;

				switch (key) {
				case S:
				{
					// ���� ������ ����Ͽ� � ���������� ������ �� ���ϴ� �ڵ�
					int num = rand() % 2;
					if (num == 0) {
						isOnNormalArea = true;
						isOnMiniGameArea = false;
						getNewArea();
						Emcee->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
					}
					else {
						isOnNormalArea = false;
						isOnMiniGameArea = true;
						getNewMiniGameArea();
						Emcee->setNewPosition(-48, -48);
						ladder->setNewPosition(-48, -48);
						minigameStartTime = clock();
					}
					Mineral* mineral = new Mineral(1); // stageLevel ����

					// ����� �ʿ��� ���� PC ��ġ�� ��� ǥ���ϵ��� �ϴ� �ڵ�
					currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
					currentAreaColIndex = convertPosToInfoXInStage(curPosX);
					mapInfo[currentAreaRowIndex][currentAreaColIndex] = 1;
					
					// ���̾� ����
					changeLayer(stageLayer, imageLayer);
				}
					break;

				case LEFT:
					pc.setDirLeft();
					if (!collisionCheckInStage(curPosX - AREA_BLOCK_SIZE, curPosY)) pc.moveInStage();
					break;
				case RIGHT:
					pc.setDirRight();
					if (!collisionCheckInStage(curPosX + AREA_BLOCK_SIZE, curPosY)) pc.moveInStage();
					break;
				case UP:
					pc.setDirUp();
					if (!collisionCheckInStage(curPosX, curPosY - AREA_BLOCK_SIZE)) pc.moveInStage();
					break;
				case DOWN:
					pc.setDirDown();
					if (!collisionCheckInStage(curPosX, curPosY + AREA_BLOCK_SIZE)) pc.moveInStage();
					break;
				}
				if (key) targetLayer->renderAll(targetLayer);
			}
		}
		else if (isOnArea) { // PC�� �븻 ���� �ִ� ���
			targetLayer->renderAll(targetLayer);
			drawUI(); // ����� UI�� �׸��� �Լ�
			if (isOnNormalArea) {
				// NPC�� ������ �ο�(Ȱ��ȭ)
				//mole->move();
				bat->move();
				ladder->move();
				Emcee->move();

				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							changeLayer(imageLayer, stageLayer);
							break;

						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case ESC:
							isOnArea = false;
							isOnReward = true;
							break;
						case SPACE:
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							pc.dig(targetPos.X, targetPos.Y);
							break;

						case O:
							pc.setHP(pc.getHP() - 10);
							break;
						case P:
							pc.setHP(pc.getHP() + 10);
							break;

						}
					}
					Sleep(5);
				}
			}
			else if (isOnMiniGameArea) { // PC�� �̴ϰ��� ���� �ִ� ���
				printMyOriInMiniGameArea();
				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							changeLayer(imageLayer, stageLayer);
							break;
						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y)) pc.move();
							break;
						case ESC:
							isOnArea = false;
							isOnReward = true;
							break;
						case SPACE:
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							pc.dig(targetPos.X, targetPos.Y);
							break;
						}
					}
					Sleep(5);
				}
				timee = clock();
				float remain_time = 31.0 - (double)(timee - minigameStartTime) / CLOCKS_PER_SEC;
				printTimeInMiniGameArea(remain_time);
				if (remain_time < 0.0) {
					Sleep(3000);
					isOnArea = false;
					isOnReward = true;
				}	
			}
			// 3�ʸ��� ��� �������� 1�� ���ҽ�Ű�� �ڵ�
			end_time = clock();
			duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
			if (duration > 3.0) {
				pc.setOxygen(pc.getOxygen() - 1);
				start_time = end_time;
			}
		}
		else if (isOnReward) { // PC�� ���� Ŭ�����ϰ� ������ ȹ���ϴ� ���
			changeLayer(imageLayer, rewardLayer);
			rewardUI();
			changeLayer(rewardLayer, stageLayer);
		}
	}
	return 0;
}