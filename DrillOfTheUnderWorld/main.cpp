#include "common.hpp"
#include "Mole.hpp"
#include "EmceeTheShyGuy.hpp"
#include "Mineral.hpp"
#include "Ladder.hpp"
#include "Bat.hpp"
#include "Button.hpp"

int main() {
	initialize(); // 기초적인 이니셜라이징(콘솔 사이즈 지정, 포인터 삭제 등)
	// 레이어 이니셜라이징
	// 각 레이어에 고유 NUM 지정
	stageLayer.initialize(&stageLayer);
	stageLayer.NUM = 1;
	imageLayer.initialize(&imageLayer); // imageLayer는 에어리어 레이어라고 보면 됨
	imageLayer.NUM = 2;
	rewardLayer.initialize(&rewardLayer);
	rewardLayer.NUM = 3;

	// 음악 재생
	char bgmName[] = "start_bgm.wav";
	playBGM(bgmName);

	imageArray[0] = { bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1 }; // PC는 imageLayer 0번에 지정
	imageLayer.images = imageArray;
	imageLayer.imageCount = 1;

	initStageImage();				// stageLayer에서 사용하는 모든 이미지 최초 생성
	fillBlockImages();				// imageLayer의 블록(25x25) 최초 생성 
	Button* button1 = new Button(1);
	Button* button2 = new Button(2);
	Button* button3 = new Button(3);
	imageArray[button1->imageidx].fileName = bmpButton1Name;
	imageArray[button2->imageidx].fileName = bmpButton2Name;
	imageArray[button3->imageidx].fileName = bmpButton3Name;
	imageArray[button1->imageidx].isHide = 1;
	imageArray[button2->imageidx].isHide = 1;
	imageArray[button3->imageidx].isHide = 1;
	button1ImageIndex = button1->imageidx;

	initAreaUI();					// imageLayer의 UI 이미지 최초 생성
	initRewardImage();				// rewardLayer에서 사용하는 모든 이미지 최초 생성

	// 아이템과 관련된 함수들(개발 진행 중)
	pc.addItem(1);
	pc.addItem(2);
	pc.addItem(3);
	initItemImages();

	// 에어리어 내부에서 시간을 재기 위한 변수들
	clock_t start_time = clock();
	clock_t end_time;
	clock_t timee;
	clock_t minigameStartTime = clock();
	double duration;

	// NPC 이니셜라이징(최초 위치는 화면상에서 보이지 않도록 초기화)
	//Mole* mole = new Mole(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	std::vector<Bat*> generatedBatList;
	Bat* bat = new Bat(-48, -48);
	Ladder* ladder = new Ladder(-48, -48);
	EmceeTheShyGuy* Emcee = new EmceeTheShyGuy(-48, -48);

	// 추후에 gameStartLayer(게임 실행 시 처음 나오는 프롤로그 등을 포함) 만들면 아래 코드 changeLayer로 호출되도록 수정
	targetLayer = &stageLayer;
	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	while (1) {
		if (isOnStage) { // PC가 스테이지 맵에 존재하는 경우
			generatedBatList.clear();
			imageArray[ladder->imageidx].isHide = 0;
			updateCharacterStatus(); // PC 상태창을 업데이트
			while (_kbhit() != 0) {
				int key = _getch();
				// PC 위치 정보를 업데이트하는 변수들(픽셀 정보로)
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;

				switch (key) {
				case S:
				{
					// 랜덤 변수를 사용하여 어떤 스테이지로 진입할 지 정하는 코드
					int num = rand() % 3;
					if (num == 0) { // normal
						isOnNormalArea = true;
						isOnMiniGameArea = false;
						getNewArea();
						Emcee->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
					}
					else if (num == 1) { // minigame
						isOnNormalArea = false;
						isOnMiniGameArea = true;
						isButtonArea = false;
						getNewMiniGameArea();
						Emcee->setNewPosition(-48, -48);
						ladder->setNewPosition(-48, -48);
						minigameStartTime = clock();
					}
					else if (num == 2) { // button
						isOnNormalArea = false;
						isButtonArea = true;
						isOnMiniGameArea = false;
						imageArray[button1->imageidx].isHide = 0;
						imageArray[button2->imageidx].isHide = 0;
						imageArray[button3->imageidx].isHide = 0;

						isButtonRoomClear = false;
						int randomNumber = rand() % 6; // 0 에서 6 사이의 난수
						buttonPressedOrderAnswerList = buttonOrderCaseList[randomNumber];
						getNewArea();

						button1->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 - BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button2->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button3->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 + BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);

						Emcee->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->setNewPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);

						imageArray[ladder->imageidx].isHide = 1;
					}

					Mineral* mineral = new Mineral(); // stageLevel 대입

					// 에어리어 맵에서 현재 PC 위치를 밝게 표시하도록 하는 코드
					currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
					currentAreaColIndex = convertPosToInfoXInStage(curPosX);
					mapInfo[currentAreaRowIndex][currentAreaColIndex] = 1;

					// 레이어 변경
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
		else if (isOnArea) { // PC가 노말 에어리어에 있는 경우

			targetLayer->renderAll(targetLayer);
			drawUI(); // 에어리어 UI를 그리는 함수
			if (isOnNormalArea) {
				if (isGenerateMobByQuestionBlock) {
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}

				if (!generatedBatList.empty()) {
					for (Bat* mob : generatedBatList) {
						mob->move();
					}
				}
				// NPC에 움직임 부여(활성화)
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
			else if (isOnMiniGameArea) { // PC가 미니게임 에어리어에 있는 경우
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
			else if (isButtonArea) {

				if (button1->getIsPressed()) {
					imageArray[button1->imageidx].fileName = bmpButton1PressedName;
				}
				if (button2->getIsPressed()) {
					imageArray[button2->imageidx].fileName = bmpButton2PressedName;
				}
				if (button3->getIsPressed()) {
					imageArray[button3->imageidx].fileName = bmpButton3PressedName;
				}
				if (printButtonStageStatus()) {
					button1->setIsPressed(false);
					imageArray[button1->imageidx].fileName = bmpButton1Name;
					button2->setIsPressed(false);
					imageArray[button2->imageidx].fileName = bmpButton2Name;
					button3->setIsPressed(false);
					imageArray[button3->imageidx].fileName = bmpButton3Name;
				}
				if (isGenerateMobByQuestionBlock) {
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}

				if (!generatedBatList.empty()) {
					for (Bat* mob : generatedBatList) {
						mob->move();
					}
				}

			
				//mole->move();
				if (isButtonRoomClear) {
					imageArray[ladder->imageidx].isHide = 0;
					ladder->move();
				}
				bat->move();
				Emcee->move();
				button1->move();
				button2->move();
				button3->move();
				for (int i = 0; i < 10; i++) {
					if (_kbhit() != 0) {
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key) {
						case S:
							targetLayer->fadeOut(targetLayer, NULL);
							if (isOnStage) {
								targetLayer = &imageLayer;
								isOnStage = false;
								currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
								currentAreaColIndex = convertPosToInfoXInStage(curPosX);
								targetLayer->fadeIn(targetLayer, NULL);
							}
							else {
								targetLayer->fadeOut(targetLayer, NULL);
								targetLayer = &stageLayer;
								isOnStage = true;
								targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
								stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
								setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
								targetLayer->fadeIn(targetLayer, NULL);
							}
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
							rewardUI();
							break;
						case SPACE:
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							pc.dig(targetPos.X, targetPos.Y);
							//pc.setOxygen(pc.getOxygen() - 1);
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

			// 3초마다 산소 게이지를 1씩 감소시키는 코드
			end_time = clock();
			duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
			if (duration > 3.0) {
				pc.setOxygen(pc.getOxygen() - 1);
				start_time = end_time;
			}
		}
		else if (isOnReward) { // PC가 에어리어를 클리어하고 보상을 획득하는 경우
			changeLayer(imageLayer, rewardLayer);
			rewardUI();
			changeLayer(rewardLayer, stageLayer);
		}
	}
	return 0;
}