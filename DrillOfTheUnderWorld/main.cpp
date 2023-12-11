#include "common.hpp"
#include "Mole.hpp"
#include "EmceeTheShyGuy.hpp"
#include "Mineral.hpp"
#include "Ladder.hpp"
#include "Bat.hpp"
#include "Button.hpp"
#include "itemCommon.hpp"
#include "RawkHawk.hpp"
#include "Charizard.hpp"
#include <thread>

int main()
{
   initialize();
   uiLayer.initialize(&uiLayer);

	gameStartLayer.initialize(&gameStartLayer);
	gameOverLayer.initialize(&gameOverLayer);
	stageLayer.initialize(&stageLayer);
	imageLayer.initialize(&imageLayer);
	rewardLayer.initialize(&rewardLayer);
	safetyLayer.initialize(&safetyLayer);
	rShopLayer.initialize(&rShopLayer);
	lShopLayer.initialize(&lShopLayer);
	progressLayer.initialize(&progressLayer);

       // initialize my areaLayer
    areaLayer.initialize(&areaLayer);

   imageArray[0] = {bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1};
   imageLayer.images = imageArray;
   imageLayer.imageCount = 1;

   initUIImage();
	initProgressImage();
   initStageImage();
   fillBlockImages();
   initSafetyImage();
   initRShopImage();
   initLShopImage();

	Button* button1 = new Button(1);
	Button* button2 = new Button(2);
	Button* button3 = new Button(3);
	imageArray[button1->imageidx].fileName = bmpButton1Name;
	imageArray[button2->imageidx].fileName = bmpButton2Name;
	imageArray[button3->imageidx].fileName = bmpButton3Name;
	imageArray[button1->imageidx].isHide = 1;
	imageArray[button2->imageidx].isHide = 1;
	imageArray[button3->imageidx].isHide = 1;
	index_Area_Button_Start = button1->imageidx;

	//initAreaUI();
	initRewardImage();

	// ??�곣뫗�??蹂κ땁 ???�????�춨 ??�?????�룇裕녻??嶺뚯???��?�?
	/*pc.addItem(1);
	pc.addItem(2);
	pc.addItem(3);*/
	initItems();

	// ?????洹먮�?????????????�??????????�곥굥由??곌떠???濡リ??
	clock_t start_time = clock();
	clock_t end_time;
	double duration;

	// Mole* mole = new Mole(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
	std::vector<Bat*> generatedBatList;
	Bat* bat = new Bat(-48, -48);
	Ladder* ladder = new Ladder(-48, -48);
	NPC* Boss;
	if (stageLevel == 1)
		Boss = new EmceeTheShyGuy(-BLOCKSIZE * EMCEE_SCALE, -BLOCKSIZE * EMCEE_SCALE);
	else if (stageLevel == 2)
		Boss = new RawkHawk(-BLOCKSIZE * RAWKHAWK_SCALE, -BLOCKSIZE * RAWKHAWK_SCALE);
	else if (stageLevel == 3)
		Boss = new Charizard(-BLOCKSIZE * CHARIZARD_SCALE, -BLOCKSIZE * CHARIZARD_SCALE);
	else
		Boss = new EmceeTheShyGuy(-BLOCKSIZE * EMCEE_SCALE, -BLOCKSIZE * EMCEE_SCALE);
	Mole* mole = new Mole(-48, -48);


	/*

	targetLayer = &stageLayer;
	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	*/
	//drawProgress();
	//while (1) { printf("1"); }
	if (stageLevel == 1) printGameStart();
	else {
		targetLayer = &stageLayer;
		targetLayer->fadeIn(targetLayer, NULL);
		targetLayer->renderAll(targetLayer);
	}
	drawProgress();
	//targetLayer = &stageLayer;
	playBGM(bgmStage);
	pc.setFatigue(pc.getFatigue());
	pc.setHP(pc.getHP());
	pc.setOxygen(pc.getOxygen());
	while (1)
	{
		//drawProgress();
		if (isOnStage)
		{ // PC??�럾? ????�??? 嶺뚮??��?�굢??브�????濡ル�??롪퍔???
			for (int i = 0;i < generatedBatList.size();i++) {
				imageArray[generatedBatList[i]->imageidx].fileName = bmpNameNull;
			}
			generatedBatList.clear();
			imageArray[ladder->imageidx].isHide = 0;
			imageArray[button1->imageidx].isHide = 1;
			imageArray[button2->imageidx].isHide = 1;
			imageArray[button3->imageidx].isHide = 1;

			//updateCharacterStatus(); // PC ???�객?�띄�??�윪??????�몥??袁⑤�?
			while (_kbhit() != 0)
			{
				int key = _getch();
				int curPosX = stageLayer.images[0].x;
				int curPosY = stageLayer.images[0].y;

				switch (key)
				{
				case S:
				{
					currentAreaRowIndex = convertPosToInfoYInStage(curPosY);
					currentAreaColIndex = convertPosToInfoXInStage(curPosX);
					int num = rand() % 4;
					//num = 1;
					if (currentAreaColIndex == bossAreaPos[1] && currentAreaRowIndex == bossAreaPos[0])
					{
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = true;
						getNewBossArea();
						Boss->NPCSetPosition(AREA_ORIGIN_X + BLOCKSIZE / 2 * 25 - BLOCKSIZE * BOSS_SCALE / 2, AREA_ORIGIN_Y + BLOCKSIZE / 2 * 25 - BLOCKSIZE * BOSS_SCALE);
						imageArray[0].x = AREA_ORIGIN_X + BLOCKSIZE / 2 * 25;
						imageArray[0].y = AREA_ORIGIN_Y + BLOCKSIZE * 23;
						ladder->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
						bat->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
						mole->NPCSetPosition(-BLOCKSIZE, -BLOCKSIZE);
						for (int i = 1; i <= Boss->getMaxHP() + 1; i++)
						{
							imageArray[Boss->imageidx + i].isHide = false;
						} // MaxHP
					}
					else if (num == 0)
					{ // ?�?��?�異??????洹먮�?졾슖?嶺뚯????
						isNormalArea = true;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = false;
						getNewArea();
						// Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						if (stageLevel > 1) {
							getMoleSpace();
							mole->NPCSetPosition(molePosX, molePosY);
						}
						Mineral* mineral = new Mineral();
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
					}
					else if (num == 1)
					{ // �?��꼶梨?轅⑥�?????????洹먮�?졾슖?嶺뚯????
						isNormalArea = false;
						isMiniGameArea = true;
						isButtonArea = false;
						isFlagArea = false;
						isBossArea = false;
						getNewMiniGameArea();
						// Emcee->NPCSetPosition(-48, -48);
						ladder->NPCSetPosition(-48, -48);
						Mineral* mineral = new Mineral(); // stageLevel ????
						progressImageArray[29].isHide = 0;
						for (int i = index_Timer_Start; i < index_Timer_Start + 15; i++)
							progressImageArray[i].isHide = 0;
					}
					else if (num == 2)
					{ // ?�?�????????洹먮�?졾슖?嶺뚯????
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = true;
						isFlagArea = false;

						imageArray[button1->imageidx].isHide = 0;
						imageArray[button2->imageidx].isHide = 0;
						imageArray[button3->imageidx].isHide = 0;

						isButtonRoomClear = false;
						int randomNumber = rand() % 6; // 0 ?????6 ???????�?�?
						buttonPressedOrderAnswerList = buttonOrderCaseList[randomNumber];
						getNewArea();

						button1->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 - BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button2->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);
						button3->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2 + BLOCKSIZE * 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2 - BLOCKSIZE * 2);

						// Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						if (stageLevel > 1) {
							getMoleSpace();
							mole->NPCSetPosition(molePosX, molePosY);
						}
						imageArray[ladder->imageidx].isHide = 1;
						Mineral* mineral = new Mineral(); // stageLevel ????
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
					}
					else if (num == 3)
					{ // ?????�윜??????洹먮�?졾슖?嶺뚯????
						isNormalArea = false;
						isMiniGameArea = false;
						isButtonArea = false;
						isFlagArea = true;
						isBossArea = false;

						pc.initFlagCnt();
						getNewArea();
						Mineral* mineral = new Mineral();
						// Emcee->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						ladder->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						bat->NPCSetPosition(NPCSpacePosX + NPCSpaceWidth * BLOCKSIZE / 2, NPCSpacePosY + NPCSpaceHeight * BLOCKSIZE / 2);
						if (stageLevel > 1) {
							getMoleSpace();
							mole->NPCSetPosition(molePosX, molePosY);
						}
						setBedrock(3);
						mineral->getCluster();
						mineral->getCluster();
						setFlag(3);
					}
					mapInfo[currentAreaRowIndex][currentAreaColIndex] = 1;

					isOnStage = false;
					isOnArea = true;
					targetLayer->fadeOut(targetLayer, NULL);
					targetLayer = &imageLayer;
					stopBGM();
					targetLayer->fadeIn(targetLayer, NULL);
					targetLayer->renderAll(targetLayer);
					drawProgress();
					if(isFlagArea) printFlagStageStatus(pc.getFlagCnt());
					if (isBossArea) playBGM(bgmBoss);
					else playBGM(bgmArea);
				}
				break;
				case LEFT:
					pc.setDirLeft();
					if (!collisionCheckInStage(curPosX - AREA_BLOCK_SIZE, curPosY))
						pc.moveInStage();
					break;
				case RIGHT:
					pc.setDirRight();
					if (!collisionCheckInStage(curPosX + AREA_BLOCK_SIZE, curPosY))
						pc.moveInStage();
					break;
				case UP:
					pc.setDirUp();
					if (!collisionCheckInStage(curPosX, curPosY - AREA_BLOCK_SIZE))
						pc.moveInStage();
					break;
				case DOWN:
					pc.setDirDown();
					if (!collisionCheckInStage(curPosX, curPosY + AREA_BLOCK_SIZE))
						pc.moveInStage();
					break;
				case ESC:
					visitSafety();
					break;
				}
				if (key)
				{
					targetLayer->renderAll(targetLayer);
					//if (key != S)
						//updateCharacterStatus();
				}
			}
		}
		else if (isOnArea)
		{ // PC??�럾? ?????洹먮�???????�츎 ?롪퍔???
		   //targetLayer->renderAll(targetLayer);
			thread renderThread(&renderTargetLayer);
			renderThread.join();
			//drawUI();
			if (isNormalArea)
			{ // PC??�럾? ?�? ?????洹먮�???????�츎 ?롪퍔???
			   // QuestionBlock ?꾩룆踰▼�???諛댁?????�???袁⑤???
				if (isGenerateMobByQuestionBlock)
				{
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}
				if (!generatedBatList.empty())
				{
					for (Bat* mob : generatedBatList)
					{
						mob->move();
					}
				}
				// NPC????嶺뚯??????�붋?????�????
				// mole->move();
				bat->move();
				ladder->move();
				if (stageLevel > 1) mole->move();
				// Emcee->move();
				//  ????�텠??????�졑 ???�먮�?
				for (int i = 0; i < 10; i++)
				{
					if (_kbhit() != 0)
					{
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key)
						{
						case S:
							stopBGM();
							playBGM(bgmStage);
							isOnStage = true;
							isOnArea = false;
							isNormalArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
							drawProgress();
							break;
						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case ESC:
							stopBGM();
							rewardUI();
							break;
						case SPACE:
						{
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							thread digThread(&PC::dig, &pc, targetPos.X, targetPos.Y);
							digThread.detach();
							//pc.dig(targetPos.X, targetPos.Y);
						}
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
			else if (isMiniGameArea)
			{                              // PC??�럾? �?��꼶梨?轅⑥�?????????洹먮�???????�츎 ?롪퍔???
				//printMyOriInMiniGameArea(); // �?��꼶梨?轅⑥�?????????洹먮�??????information??????�덫?????�탮�???? ??�쀫츊???濡ル�???�??
				// ????�텠??????�졑 ???�먮�?
				for (int i = 0; i < 10; i++)
				{
					if (_kbhit() != 0)
					{
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key)
						{
						case S:
							stopBGM();
							playBGM(bgmStage);
							isOnStage = true;
							isOnArea = false;
							isMiniGameArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
							OrichalcumNum = 0;
							progressImageArray[29].fileName = bmpNameStar0;
							timerIndex = 11;
							progressImageArray[29].isHide = 1;
							for (int i = index_Timer_Start; i < index_Timer_Start + 15; i++)
								progressImageArray[i].isHide = 1;
							drawProgress();
							break;
						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case ESC:
							stopBGM();
							rewardUI();
							break;
						case SPACE:
						{
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							thread digThread(&PC::dig, &pc, targetPos.X, targetPos.Y);
							digThread.detach();
							//pc.dig(targetPos.X, targetPos.Y);
						}
						break;
						}
					}
					Sleep(5);
				}
			}
			else if (isButtonArea)
			{ // PC??�럾? ?�?�????????洹먮�???????�츎 ?롪퍔???

				if (button1->getIsPressed())
				{
					imageArray[button1->imageidx].fileName = bmpButton1PressedName;
				}
				if (button2->getIsPressed())
				{
					imageArray[button2->imageidx].fileName = bmpButton2PressedName;
				}
				if (button3->getIsPressed())
				{
					imageArray[button3->imageidx].fileName = bmpButton3PressedName;
				}
				if (printButtonStageStatus())
				{
					button1->setIsPressed(false);
					imageArray[button1->imageidx].fileName = bmpButton1Name;
					button2->setIsPressed(false);
					imageArray[button2->imageidx].fileName = bmpButton2Name;
					button3->setIsPressed(false);
					imageArray[button3->imageidx].fileName = bmpButton3Name;
				}
				if (isGenerateMobByQuestionBlock)
				{
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}
				if (!generatedBatList.empty())
				{
					for (Bat* mob : generatedBatList)
					{
						mob->move();
					}
				}
				if (isButtonRoomClear)
				{
					imageArray[ladder->imageidx].isHide = 0;
					ladder->move();
				}
				bat->move();
				if (stageLevel > 1) mole->move();
				// Emcee->move();
				button1->move();
				button2->move();
				button3->move();

				for (int i = 0; i < 10; i++)
				{
					if (_kbhit() != 0)
					{
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key)
						{
						case S:
							stopBGM();
							playBGM(bgmStage);
							isOnStage = true;
							isOnArea = false;
							isBossArea = false;
							isButtonArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
							drawProgress();
							break;
						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case ESC:
							stopBGM();
							rewardUI();
							break;
						case SPACE:
						{
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							thread digThread(&PC::dig, &pc, targetPos.X, targetPos.Y);
							digThread.detach();
							//pc.dig(targetPos.X, targetPos.Y);
						}
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
			else if (isFlagArea)
			{ // PC??�럾? ?????�윜??????洹먮�???????�츎 ?롪퍔???
				// mole->move();
				bat->move();
				ladder->move();
				if (stageLevel > 1) mole->move();
				if (isGenerateMobByQuestionBlock)
				{
					generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
					isGenerateMobByQuestionBlock = false;
				}
				if (!generatedBatList.empty())
				{
					for (Bat* mob : generatedBatList)
					{
						mob->move();
					}
				}
				// Emcee->move();
				for (int i = 0; i < 10; i++)
				{
					if (_kbhit() != 0)
					{
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key)
						{
						case S:
							stopBGM();
							playBGM(bgmStage);
							isOnStage = true;
							isOnArea = false;
							isFlagArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
							drawProgress();
							break;
						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case ESC:
							stopBGM();
							rewardUI();
							break;
						case SPACE:
						{
							COORD targetPos = pc.getTargetPos(curPosX, curPosY);
							thread digThread(&PC::dig, &pc, targetPos.X, targetPos.Y);
							digThread.detach();
							//pc.dig(targetPos.X, targetPos.Y);
						}
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
			else if (isBossArea)
			{
				if (Boss->NPCDead() == false)
				{
					Boss->move();
				}
				else
				{
					if (stageLevel == 1)
						((EmceeTheShyGuy*)Boss)->AfterDead();
					else if (stageLevel == 2)
						((RawkHawk*)Boss)->AfterDead();
					else if (stageLevel == 3)
						((Charizard*)Boss)->AfterDead();
					ladder->NPCSetPosition(AREA_ORIGIN_X + BLOCKSIZE * 25 / 2, AREA_ORIGIN_Y + BLOCKSIZE * 25 / 2);
					if (ladder->goSafety())
						return main();
				}
				// vector<PCBullet>::iterator itr;
				for (auto itr = pc.getBulletList().begin(); itr != pc.getBulletList().end();)
				{
					if (Boss->NPCDead() == false && itr->checkBulletHit(Boss->x, Boss->y))
					{
						Boss->NPCHit(pc.getATK());
						itr = pc.getBulletList().erase(itr);
					}
					else if (!(itr->move()))
						itr = pc.getBulletList().erase(itr);
					else
						itr++;
				}
				printWarning(Boss->hp);
				for (int i = 0; i < 10; i++)
				{
					if (_kbhit() != 0)
					{
						int key = _getch();
						int curPosX = imageLayer.images[0].x;
						int curPosY = imageLayer.images[0].y;
						COORD afterMovedPos;

						switch (key)
						{
						case S:
							isOnStage = true;
							isOnArea = false;
							isFlagArea = false;
							isBossArea = false;
							targetLayer->fadeOut(targetLayer, NULL);
							targetLayer = &stageLayer;
							targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
							stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
							setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);
							targetLayer->fadeIn(targetLayer, NULL);
							drawProgress();
							break;
						case LEFT:
							pc.setDirLeft();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case RIGHT:
							pc.setDirRight();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case UP:
							pc.setDirUp();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case DOWN:
							pc.setDirDown();
							afterMovedPos = pc.getPosAfterMove(curPosX, curPosY);
							if (!collisionCheck(afterMovedPos.X, afterMovedPos.Y))
								pc.move();
							break;
						case ESC:
							stopBGM();
							rewardUI();
							break;
						case SPACE:
							if (Boss->NPCDead() == false)
								pc.attack(clock());
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
			// 嶺뚮?�維????????洹먮�??????�쾹????��?????�챷???濡ル�??袁⑤???
			// 3?�?�?��?????�?�틬 ?롪퍓???�묒????1????�룆??????��???袁⑤???
			end_time = clock();
			duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
			if (duration > 3.0)
			{
				pc.setOxygen(pc.getOxygen() - 1);
				if (isMiniGameArea) {
					timerIndex--;
					drawProgress();
					if (!timerIndex) rewardUI();
				}
				start_time = end_time;
			}
		}
	}
	return 0;
}