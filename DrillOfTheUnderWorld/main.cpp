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

       // initialize my areaLayer
    areaLayer.initialize(&areaLayer);

   imageArray[0] = {bmpNamePC, AREA_ORIGIN_X + 576, AREA_ORIGIN_Y - BLOCKSIZE, 1};
   imageLayer.images = imageArray;
   imageLayer.imageCount = 1;

   initUIImage();
   initStageImage();
   fillBlockImages();
   initSafetyImage();
   initRShopImage();
   initLShopImage();

   Button *button1 = new Button(1);
   Button *button2 = new Button(2);
   Button *button3 = new Button(3);
   imageArray[button1->imageidx].fileName = bmpButton1Name;
   imageArray[button2->imageidx].fileName = bmpButton2Name;
   imageArray[button3->imageidx].fileName = bmpButton3Name;
   imageArray[button1->imageidx].isHide = 1;
   imageArray[button2->imageidx].isHide = 1;
   imageArray[button3->imageidx].isHide = 1;
   index_Area_Button_Start = button1->imageidx;

   initAreaUI();
   initRewardImage();

   // ??嚙赭都諞蕭??頩精� ???嚙蝓????嚙趣隅 ??嚙?????嚙趟�鋆??鵀恨???嚙踝蕭?嚙?
   /*pc.addItem(1);
   pc.addItem(2);
   pc.addItem(3);*/
   initItems();

   // ?????瘣寨車嚙?????????????嚙??????????嚙赭野窱亦??窸�???瞈～??
   clock_t start_time = clock();
   clock_t end_time;
   clock_t timee;
   clock_t minigameStartTime = clock();
   double duration;

   // Mole* mole = new Mole(AREA_ORIGIN_X + BLOCKSIZE * 10, AREA_ORIGIN_Y + BLOCKSIZE * 10);
   std::vector<Bat *> generatedBatList;
   Bat *bat = new Bat(-48, -48);
   Ladder *ladder = new Ladder(-48, -48);
   NPC *Boss;
   if (stageLevel == 1)
      Boss = new EmceeTheShyGuy(-BLOCKSIZE * EMCEE_SCALE, -BLOCKSIZE * EMCEE_SCALE);
   else if (stageLevel == 2)
      Boss = new RawkHawk(-BLOCKSIZE * RAWKHAWK_SCALE, -BLOCKSIZE * RAWKHAWK_SCALE);
   else if (stageLevel == 3)
      Boss = new Charizard(-BLOCKSIZE * CHARIZARD_SCALE, -BLOCKSIZE * CHARIZARD_SCALE);
   else
      Boss = new EmceeTheShyGuy(-BLOCKSIZE * EMCEE_SCALE, -BLOCKSIZE * EMCEE_SCALE);
   Mole *mole = new Mole(-48, -48);

   
   /*
   
   targetLayer = &stageLayer;
   targetLayer->fadeIn(targetLayer, NULL);
   targetLayer->renderAll(targetLayer);
   
   */

   //while (1) { printf("1"); }
   if (stageLevel == 1) printGameStart();
   else {
       targetLayer = &stageLayer;
       targetLayer->fadeIn(targetLayer, NULL);
       targetLayer->renderAll(targetLayer);
   }
   playBGM(bgmStage);

   updateCharacterStatus();
   pc.setFatigue(pc.getMaxFatigue());
   pc.setHP(pc.getHP());
   pc.setOxygen(pc.getOxygen());
   while (1)
   {
      if (isOnStage)
      { // PC??嚙趟? ????嚙蝓??? 鵀恨??嚙踝蕭?嚙赭窖??賳蕭????瞈～嚙??諢表�???
          for (int i = 0;i < generatedBatList.size();i++) {
              imageArray[generatedBatList[i]->imageidx].fileName = bmpNameNull;
         }
         generatedBatList.clear();
         imageArray[ladder->imageidx].isHide = 0;
         imageArray[button1->imageidx].isHide = 1;
         imageArray[button2->imageidx].isHide = 1;
         imageArray[button3->imageidx].isHide = 1;

         //updateCharacterStatus(); // PC ???嚙赭�?嚙趟�嚙??嚙趣??????嚙趟炙??鋡嚙?
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
               { // ?嚙?嚙踝蕭?嚙賜??????瘣寨車嚙?魽樺�?鵀恨????
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
                  Mineral *mineral = new Mineral();
                  setBedrock(3);
                  mineral->getCluster();
                  mineral->getCluster();
               }
               else if (num == 1)
               { // 嚙?嚙踝蕭篥塚坎?頧嚙?????????瘣寨車嚙?魽樺�?鵀恨????
                  isNormalArea = false;
                  isMiniGameArea = true;
                  isButtonArea = false;
                  isFlagArea = false;
                  isBossArea = false;
                  getNewMiniGameArea();
                  // Emcee->NPCSetPosition(-48, -48);
                  ladder->NPCSetPosition(-48, -48);
                  minigameStartTime = clock();
                  Mineral *mineral = new Mineral(); // stageLevel ????
               }
               else if (num == 2)
               { // ?嚙?嚙????????瘣寨車嚙?魽樺�?鵀恨????
                  isNormalArea = false;
                  isMiniGameArea = false;
                  isButtonArea = true;
                  isFlagArea = false;

                  imageArray[button1->imageidx].isHide = 0;
                  imageArray[button2->imageidx].isHide = 0;
                  imageArray[button3->imageidx].isHide = 0;

                  isButtonRoomClear = false;
                  int randomNumber = rand() % 6; // 0 ?????6 ???????嚙?嚙?
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
                  Mineral *mineral = new Mineral(); // stageLevel ????
                  setBedrock(3);
                  mineral->getCluster();
                  mineral->getCluster();
               }
               else if (num == 3)
               { // ?????嚙趣�??????瘣寨車嚙?魽樺�?鵀恨????
                  isNormalArea = false;
                  isMiniGameArea = false;
                  isButtonArea = false;
                  isFlagArea = true;
                  isBossArea = false;

                  pc.initFlagCnt();
                  getNewArea();
                  Mineral *mineral = new Mineral();
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
                //  updateCharacterStatus();
            }
         }
      }
      else if (isOnArea)
      { // PC??嚙趟? ?????瘣寨車嚙???????嚙趣� ?諢表�???
         //targetLayer->renderAll(targetLayer);
         thread renderThread(&renderTargetLayer);
         renderThread.join();
         drawUI();
         if (isNormalArea)
         { // PC??嚙趟? ?嚙? ?????瘣寨車嚙???????嚙趣� ?諢表�???
            // QuestionBlock ?篨拘�頦售嚙???隢�?????嚙蝓???鋡???
            if (isGenerateMobByQuestionBlock)
            {
               generatedBatList.push_back(new Bat(questionBlockPosX, questionBlockPosY));
               isGenerateMobByQuestionBlock = false;
            }
            if (!generatedBatList.empty())
            {
               for (Bat *mob : generatedBatList)
               {
                  mob->move();
               }
            }
            // NPC????鵀恨??????嚙趟�?????嚙????
            // mole->move();
            bat->move();
            ladder->move();
            if (stageLevel > 1) mole->move();
            // Emcee->move();
            //  ????嚙踫�??????嚙趣� ???嚙趟車嚙?
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
                  //if (key && key != S)
                     //updateCharacterStatusInArea();
               }
               Sleep(5);
            }
         }
         else if (isMiniGameArea)
         {                              // PC??嚙趟? 嚙?嚙踝蕭篥塚坎?頧嚙?????????瘣寨車嚙???????嚙趣� ?諢表�???
            printMyOriInMiniGameArea(); // 嚙?嚙踝蕭篥塚坎?頧嚙?????????瘣寨車嚙??????information??????嚙趟?????嚙踫嚙???? ??嚙趣恢�???瞈～嚙???嚙??
            // ????嚙踫�??????嚙趣� ???嚙趟車嚙?
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
                  //if (key && key != S)
                     //updateCharacterStatusInArea();
               }
               Sleep(5);
            }
            timee = clock();
            float remain_time = 31.0 - (double)(timee - minigameStartTime) / CLOCKS_PER_SEC;
            printTimeInMiniGameArea(remain_time);
            if (remain_time < 0.0)
            {
               Sleep(3000);
               rewardUI();
            }
         }
         else if (isButtonArea)
         { // PC??嚙趟? ?嚙?嚙????????瘣寨車嚙???????嚙趣� ?諢表�???

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
               for (Bat *mob : generatedBatList)
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
                  //if (key && key != S)
                     //updateCharacterStatusInArea();
               }
               Sleep(5);
            }
         }
         else if (isFlagArea)
         { // PC??嚙趟? ?????嚙趣�??????瘣寨車嚙???????嚙趣� ?諢表�???
            printFlagStageStatus(pc.getFlagCnt());
            // mole->move();
            bat->move();
            ladder->move();
            if (stageLevel > 1) mole->move();
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
                  //if (key && key != S)
                    // updateCharacterStatusInArea();
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
                  ((EmceeTheShyGuy *)Boss)->AfterDead();
               else if (stageLevel == 2)
                  ((RawkHawk *)Boss)->AfterDead();
               else if (stageLevel == 3)
                  ((Charizard *)Boss)->AfterDead();
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
                  //if (key && key != S)
                    // updateCharacterStatusInArea();
               }
               Sleep(5);
            }
         }
         // 鵀恨?嚙賜雁????????瘣寨車嚙??????嚙趣器????嚙踝蕭?????嚙趣捧???瞈～嚙??鋡???
         // 3?嚙?嚙?嚙踝蕭?????嚙蝓?嚙踫 ?諢表�???嚙趟�????1????嚙趟�??????嚙踝蕭???鋡???
         end_time = clock();
         duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
         if (duration > 3.0)
         {
            pc.setOxygen(pc.getOxygen() - 1);
            start_time = end_time;
         }
      }
   }
   return 0;
}