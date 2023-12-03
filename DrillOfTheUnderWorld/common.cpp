#include "common.hpp"

PC& pc = PC::getPC();
HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

ImageLayer* targetLayer = NULL;
// stageLayer?Ä ?¥Îãπ ?àÏù¥?¥Ïóê???¨Ïö©?òÎäî Î≥Ä?òÎì§
ImageLayer stageLayer = DEFAULT_IMAGE_LAYER;
Image stageImageArray[40];
int stageInfo[5][5];
// imageLayer?Ä ?¥Îãπ ?àÏù¥?¥Ïóê???¨Ïö©?òÎäî Î≥Ä?òÎì§
ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
Image imageArray[1000];
int blockInfo[1200][1200];
int mapInfo[5][5];
int currentAreaRowIndex;
int currentAreaColIndex;
int NPCSpacePosX;
int NPCSpacePosY;
int NPCSpaceHeight;
int NPCSpaceWidth;
int OrichalcumNum = 0;

// BUTTON
bool isButtonRoomClear = false;
std::vector<int> buttonPressedOrderList;
std::vector<int> buttonPressedOrderAnswerList;
std::vector<std::vector<int>> buttonOrderCaseList = { {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1} };
bool isGenerateMobByQuestionBlock = false;
int questionBlockPosX = 0;
int questionBlockPosY = 0;

// rewardLayer?Ä ?¥Îãπ ?àÏù¥?¥Ïóê???¨Ïö©?òÎäî Î≥Ä?òÎì§
ImageLayer rewardLayer = DEFAULT_IMAGE_LAYER;
Image imagesReward[1000];

// lShopLayer
ImageLayer lShopLayer = DEFAULT_IMAGE_LAYER;
Image lShopImageArray[100];

// rShopLayer
ImageLayer rShopLayer = DEFAULT_IMAGE_LAYER;
Image rShopImageArray[100];

bool isOnSafety = false;
char bmpShopItemBox[] = "Shop_ItemBox.bmp";
char bmpShopItemBoxDisable[] = "Shop_ItemBox_disable.bmp";
char bmpShopItemBoxSelected[] = "Shop_ItemBox_selected.bmp";
char bmpShopStoneBox[] = "Shop_StoneBox.bmp";
char bmpLShopMiner[] = "lShop_miner.bmp";
char bmpLShopMinerSelected[] = "lShop_minerSelected.bmp";
char bmpLShopBalloon[] = "lShop_Balloon.bmp";
char bmpRShopMiner[] = "rShop_miner.bmp";
char bmpRShopMinerSelected[] = "rShop_minerSelected.bmp";
char bmpRShopBalloon[] = "rShop_Balloon.bmp";

ImageLayer safetyLayer = DEFAULT_IMAGE_LAYER;
Image safetyImageArray[100];

// PCÍ∞Ä ?ÑÏû¨ ?¥Îîî???ÑÏπò?òÎäîÏßÄ Ï≤¥ÌÅ¨?òÍ∏∞ ?ÑÌïú bool??Î≥Ä??
bool isOnStage = true;
bool isOnArea = false;
bool isNormalArea = false;
bool isMiniGameArea = false;
bool isButtonArea = false;
bool isFlagArea = false;
bool isBossArea = false;

// Í∞??àÏù¥?¥Îßà???¨Ïö©?òÎäî ?¥Î?ÏßÄ?§Ï? ?òÎÇò??Î∞∞Ïó¥???Ä?•Îê® (ex. imageLayer->imageArray, rewardLayer->imageReward)
// Í∞ôÏ? Î∞∞Ïó¥???Ä?•Îêò???¥Î?ÏßÄ?§Ï? ?¥Î??êÏÑú Î™©Ï†Å???∞Îùº Î¨∂Ïó¨???Ä?•Îê®
// ?ëÍ∑º?òÍ∏∞ ?∏Ìïò?ÑÎ°ù ?òÍ∏∞ ?ÑÌï¥ ?úÏûë Î≤àÌò∏Î•??Ä?•Ìïò??Í¥ÄÎ¶?
int index_StageImages_Start;
int index_Area_PC;
int index_Area_Button_Start;
int index_Area_UI_Start;
int index_Area_UI_HP_Start;
int index_Area_UI_O2_Start;
int index_Area_UI_Map_Start;
int index_Area_UI_blockInfo_Start;
int index_Area_UI_mapTile_Start;
int index_Area_UI_MiniGame_Start;
int index_RewardImages_Start;

// BMP ?åÏùº ?úÏûë

// NULL BMP
char bmpNameNull[] = "";

// STAGE MAP BMP
char bmpNamePC[] = "PlayerCharacter.bmp";
char bmpStageLevel[] = "Stage1.bmp";
char bmpClearedAreaName[] = "clearedArea.bmp";
char bmpNomalAreaName[] = "nomalArea.bmp";
char bmpHiddenAreaName[] = "hiddenArea.bmp";
char bmpMovableAreaName[] = "movableArea.bmp";
char bmpCharacterStatusName[] = "UI_character_status.bmp";
char bmpItem1Name[] = "item1.bmp";
char bmpItem2Name[] = "item2.bmp";
char bmpItem3Name[] = "item3.bmp";

// AREA UI BMP
char bmpNameUIItemBox[] = "UI_itemBox.bmp";
char bmpNameMapPC[] = "UI_mapPC.bmp";
char bmpNameMapX[] = "UI_mapX.bmp";
char bmpNameMapTile[] = "UI_mapTile.bmp";
char bmpNameMapTileCleared[] = "UI_mapTileCleared.bmp";
char bmpNameMapBox[] = "UI_mapBox.bmp";

char bmpNameHP_0pct[] = "UI_HP_0pct.bmp";
char bmpNameHP_10pct[] = "UI_HP_10pct.bmp";
char bmpNameHP_20pct[] = "UI_HP_20pct.bmp";
char bmpNameHP_30pct[] = "UI_HP_30pct.bmp";
char bmpNameHP_40pct[] = "UI_HP_40pct.bmp";
char bmpNameHP_50pct[] = "UI_HP_50pct.bmp";
char bmpNameHP_60pct[] = "UI_HP_60pct.bmp";
char bmpNameHP_70pct[] = "UI_HP_70pct.bmp";
char bmpNameHP_80pct[] = "UI_HP_80pct.bmp";
char bmpNameHP_90pct[] = "UI_HP_90pct.bmp";
char bmpNameHP_100pct[] = "UI_HP_100pct.bmp";
char bmpNameMaxHP[] = "UI_maxHP.bmp";
char bmpNameO2_0pct[] = "UI_O2_0pct.bmp";
char bmpNameO2_10pct[] = "UI_O2_10pct.bmp";
char bmpNameO2_20pct[] = "UI_O2_20pct.bmp";
char bmpNameO2_30pct[] = "UI_O2_30pct.bmp";
char bmpNameO2_40pct[] = "UI_O2_40pct.bmp";
char bmpNameO2_50pct[] = "UI_O2_50pct.bmp";
char bmpNameO2_60pct[] = "UI_O2_60pct.bmp";
char bmpNameO2_70pct[] = "UI_O2_70pct.bmp";
char bmpNameO2_80pct[] = "UI_O2_80pct.bmp";
char bmpNameO2_90pct[] = "UI_O2_90pct.bmp";
char bmpNameO2_100pct[] = "UI_O2_100pct.bmp";
char bmpNameMaxO2[] = "UI_maxO2.bmp";

char bmpNameTimer[] = "UI_Timer.bmp";
char bmpNameStar0[] = "UI_Star0.bmp";
char bmpNameStar1[] = "UI_Star1.bmp";
char bmpNameStar2[] = "UI_Star2.bmp";
char bmpNameStar3[] = "UI_Star3.bmp";

// AREA BLOCK BMP
char bmpStoneBlockName[] = "block_Stage1_Normal.bmp";
char bmpBrokenStoneBlockName[] = "block_Stage1_Broken.bmp";

// ORE BMP
char bmpNameBronzeOre1[] = "block_Stage1_BronzeOre1.bmp";
char bmpNameBronzeOre2[] = "block_Stage1_BronzeOre2.bmp";
char bmpNameSilverOre1[] = "block_Stage1_SilverOre1.bmp";
char bmpNameSilverOre2[] = "block_Stage1_SilverOre2.bmp";
char bmpNameGoldOre1[] = "block_Stage1_GoldOre1.bmp";
char bmpNameGoldOre2[] = "block_Stage1_GoldOre2.bmp";
char bmpNameDiamondOre1[] = "block_Stage1_DiamondOre1.bmp";
char bmpNameDiamondOre2[] = "block_Stage1_DiamondOre2.bmp";
char bmpNameOrichalcumOre1[] = "block_Stage1_OrichalcumOre1.bmp";
char bmpNameOrichalcumOre2[] = "block_Stage1_OrichalcumOre2.bmp";
char bmpNameBrokenBronzeOre[] = "block_Stage1_Broken_BronzeOre1.bmp";
char bmpNameBrokenSilverOre[] = "block_Stage1_Broken_SilverOre1.bmp";
char bmpNameBrokenGoldOre[] = "block_Stage1_Broken_GoldOre1.bmp";
char bmpNameBrokenDiamondOre[] = "block_Stage1_Broken_DiamondOre1.bmp";

// MINERAL BMP
char bmpNameBronzeMineral[] = "block_MineralBronze.bmp";
char bmpNameSilverMineral[] = "block_MineralSilver.bmp";
char bmpNameGoldMineral[] = "block_MineralGold.bmp";
char bmpNameDiamondMineral[] = "block_MineralDiamond.bmp";
char bmpNameOrichalcumMineral[] = "block_MineralOrichalcum.bmp";

// BUTTON BMP
char bmpButton1Name[] = "button1.bmp";
char bmpButton1PressedName[] = "button1Pressed.bmp";
char bmpButton2Name[] = "button2.bmp";
char bmpButton2PressedName[] = "button2Pressed.bmp";
char bmpButton3Name[] = "button3.bmp";
char bmpButton3PressedName[] = "button3Pressed.bmp";

// QUESTIONBLOCK BMP
char bmpQuestionMarkName[] = "questionMark.bmp";
char bmpOzPotionName[] = "ozPotion.bmp";
char bmpHpPotionName[] = "hpPotion.bmp";
char bmpBoomName[] = "boom.bmp";

// FLAG, BEDROCK BMP
char bmpBedrockName[] = "lava.bmp";
char bmpFlagName[] = "flag.bmp";

// NORMAL NPC BMP
char bmpNameBat[] = "Bat.bmp";

// BOSS NPC BMP
char bmpNameMole[] = "Mole.bmp";
char bmpNameFireball[] = "Fireball.bmp";
char bmpNameEmceeTheShyGuy[] = "EmceeTheShyGuy.bmp";
char bmpNameLadder[] = "Ladder.bmp";

// REWARD BMP
char bmpNameNormalRewardSelected[] = "UI_normalEnforceSelected.bmp";
char bmpNameNormalReward[] = "UI_normalEnforce.bmp";
char bmpNameDynamicRewardSelected[] = "UI_dynamicEnforceSelected.bmp";
char bmpNameDynamicReward[] = "UI_dynamicEnforce.bmp";
char bmpNameNormalAtkSelected[] = "UI_rewardAtkSelected.bmp";
char bmpNameNormalAtk[] = "UI_rewardAtk.bmp";
char bmpNameNormalAtkSpdSelected[] = "UI_rewardAtkSpdSelected.bmp";
char bmpNameNormalAtkSpd[] = "UI_rewardAtkSpd.bmp";
char bmpNameNormalSpdSelected[] = "UI_rewardSpdSelected.bmp";	
char bmpNameNormalSpd[] = "UI_rewardSpd.bmp";

// ITEM BMP
char bmpUndergroundTicketName[] = "item_UndergroundTicket.bmp";
char bmpMetalDetectorName[] = "item_MetalDetector.bmp";
char bmpThornCrownName[] = "item_ThornCrown.bmp";
char bmpBeggarDollName[] = "item_BeggarDoll.bmp";
char bmpOrichalcumName[] = "item_Orichalcum.bmp";
char bmpTwoHeartsName[] = "item_TwoHearts.bmp";
char bmpLuckyCharmName[] = "item_LuckyCharm.bmp";
char bmpDisassemblerName[] = "item_Disasemmbler.bmp";
char bmpBatFangName[] = "item_BatFang.bmp";
char bmpMoleClawName[] = "item_MoleClaw.bmp";
char bmpDiceName[] = "item_Dice.bmp";
char bmpLuckStoneName[] = "item_LuckStone.bmp";
char bmpBloodBagName[] = "item_BloodBag.bmp";
char bmpSupplyOxygenTankName[] = "item_SupplyOxygenTank.bmp";
char bmpFreshBrewedCoffeeName[] = "item_FreshBrewedCoffee.bmp";
char bmpPortableOxygenCanName[] = "item_PortableOxygenCan.bmp";
char bmpEnergyBarName[] = "item_EnergyBar.bmp";
char bmpAttackBoostName[] = "item_AttackBoost.bmp";
char bmpAttackSpeedBoostName[] = "item_AttackSpeedBoost.bmp";
char bmpMovementSpeedBoostName[] = "item_MovementSpeedBoost.bmp";
char bmpPrisonerShacklesName[] = "item_PrisonerShackles.bmp";
char bmpCursedTotemName[] = "item_CursedTotem.bmp";
char bmpAncientVirusName[] = "item_AncientVirus.bmp";
char bmpCaveSnakeName[] = "item_CaveSnake.bmp";


//char bmpSafetyBG[] = "safety_bg.bmp";
char bmpSafetyBG[] = "bg.bmp";
char bmpSafetyArrow[] = "safety_arrow.bmp";
char bmpSafetyArrowSelected[] = "safety_arrowSelected.bmp";
int index_Safety_Object_Start;

void initSafetyImage() {
	safetyLayer.images = safetyImageArray;
	safetyLayer.imageCount = 0;

	safetyImageArray[safetyLayer.imageCount++] = { bmpNamePC, 1000, 1450, 2 };
	safetyImageArray[safetyLayer.imageCount++] = { bmpNameUIItemBox, 180, 850, 1 };
	safetyImageArray[safetyLayer.imageCount++] = { bmpCharacterStatusName, 60 , STAGE_ORIGIN_Y, 1 };

	index_Safety_Object_Start = safetyLayer.imageCount;
	safetyImageArray[safetyLayer.imageCount++] = { bmpLShopMiner, 650, 1240, 0.5 };
	safetyImageArray[safetyLayer.imageCount++] = { bmpSafetyArrow, 1000, 1130, 0.5 };
	safetyImageArray[safetyLayer.imageCount++] = { bmpRShopMiner, 1200, 1210, 0.5 };

	safetyImageArray[safetyLayer.imageCount++] = { bmpSafetyBG, 0, 0, 1 }; // ∞°¿Â ∏∂¡ˆ∏∑ø° øÕæﬂ «‘
}

void visitSafety() {
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &safetyLayer;

	safetyImageArray[index_Safety_Object_Start].fileName = bmpLShopMiner;
	safetyImageArray[index_Safety_Object_Start + 1].fileName = bmpSafetyArrow;
	safetyImageArray[index_Safety_Object_Start + 2].fileName = bmpRShopMiner;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	updateCharacterStatus();

	int index = -1;
	int flags = 1;
	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case NUM1:
				index = 0;
				break;
			case NUM2:
				index = 1;
				break;
			case NUM3:
				index = 2;
				break;
			case LEFT:
				if (index == -1) index = 0;
				else if (index != 0) index--;
				break;
			case RIGHT:
				if (index == -1) index = 2;
				else if (index != 2) index++;
				break;
			case SPACE:
				if (index == -1) break;
				else if (index == 0) {
					visitLShop();
				}
				else if (index == 1) {
					//visitLShop();
					flags = 0;
				}
				else if (index == 2) {
					visitRShop();
				}
				break;
			}

			if (index != -1) index %= 3;

			if (index == 0) {
				safetyImageArray[index_Safety_Object_Start].fileName = bmpLShopMinerSelected;
				safetyImageArray[index_Safety_Object_Start + 1].fileName = bmpSafetyArrow;
				safetyImageArray[index_Safety_Object_Start + 2].fileName = bmpRShopMiner;
			}
			else if (index == 1) {
				safetyImageArray[index_Safety_Object_Start].fileName = bmpLShopMiner;
				safetyImageArray[index_Safety_Object_Start + 1].fileName = bmpSafetyArrowSelected;
				safetyImageArray[index_Safety_Object_Start + 2].fileName = bmpRShopMiner;
			}
			else if (index == 2) {
				safetyImageArray[index_Safety_Object_Start].fileName = bmpLShopMiner;
				safetyImageArray[index_Safety_Object_Start + 1].fileName = bmpSafetyArrow;
				safetyImageArray[index_Safety_Object_Start + 2].fileName = bmpRShopMinerSelected;
			}
			if (key) {
				targetLayer->renderAll(targetLayer);
				updateCharacterStatus();
			}
		}
	}

	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &stageLayer;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);
}

void initLShopImage() {
	lShopLayer.images = lShopImageArray;
	lShopLayer.imageCount = 0;

	lShopImageArray[lShopLayer.imageCount++] = { bmpShopStoneBox, 50, 50, 1 };
	lShopImageArray[lShopLayer.imageCount++] = { bmpUndergroundTicketName, LSHOP_ITEMBOX_ORIGIN_X + 200 - 75, 550, 1 };
	lShopImageArray[lShopLayer.imageCount++] = { bmpBatFangName, LSHOP_ITEMBOX_ORIGIN_X + 200 - 75 + 450, 550, 1 };
	lShopImageArray[lShopLayer.imageCount++] = { bmpShopItemBox, LSHOP_ITEMBOX_ORIGIN_X, LSHOP_ITEMBOX_ORIGIN_Y, 1 };
	lShopImageArray[lShopLayer.imageCount++] = { bmpShopItemBox, LSHOP_ITEMBOX_ORIGIN_X + 450, LSHOP_ITEMBOX_ORIGIN_Y, 1 };
	lShopImageArray[lShopLayer.imageCount++] = { bmpLShopMiner, -50, 750, 3 };
	lShopImageArray[lShopLayer.imageCount++] = { bmpLShopBalloon, 600, 1000, 1 };
}

void initRShopImage() {
	rShopLayer.images = rShopImageArray;
	rShopLayer.imageCount = 0;

	rShopImageArray[rShopLayer.imageCount++] = { bmpShopStoneBox, 50, 50, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpUndergroundTicketName, 200 + 50 - 75, 550, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpBatFangName, 200 + 50 - 75 + 450, 550, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpBloodBagName, 200 + 50 - 75 + 900, 550, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpShopItemBox, RSHOP_ITEMBOX_ORIGIN_X, RSHOP_ITEMBOX_ORIGIN_Y, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpShopItemBox, RSHOP_ITEMBOX_ORIGIN_X + 450, RSHOP_ITEMBOX_ORIGIN_Y, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpShopItemBox, RSHOP_ITEMBOX_ORIGIN_X + 900, RSHOP_ITEMBOX_ORIGIN_Y, 1 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpRShopMiner, 1200, 750, 3 };
	rShopImageArray[rShopLayer.imageCount++] = { bmpRShopBalloon, 30, 1000, 1 };
}

void visitLShop() {
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &lShopLayer;

	int item1_price = 100;
	int item2_price = 200;

	// 3, 4π¯¿Ã æ∆¿Ã≈€ 2¡æ¿« π⁄Ω∫
	if (item1_price > pc.getStone()) lShopImageArray[3].fileName = bmpShopItemBoxDisable;
	else lShopImageArray[3].fileName = bmpShopItemBox;
	if (item2_price > pc.getStone()) lShopImageArray[4].fileName = bmpShopItemBoxDisable;
	else lShopImageArray[4].fileName = bmpShopItemBox;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	printStatusInLShop(item1_price, item2_price, 0);

	int index = -1;
	int flags = 1;
	int lastInputKey = 0;
	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			// 1, 2π¯ ¿‘∑¬«œ∏È ∞¢ π⁄Ω∫∞° º±≈√µ«∞Ì, ≥™∏”¡ˆ π⁄Ω∫¥¬ º±≈√ ±‚∫ª¿∏∑Œ ∫Ø∞Ê(º±≈√ «ÿ¡¶)
			case NUM1:
				if (strcmp(lShopImageArray[3].fileName, bmpShopItemBoxDisable) == 0) break;
				lShopImageArray[3].fileName = bmpShopItemBoxSelected;
				if (strcmp(lShopImageArray[4].fileName, bmpShopItemBoxSelected) == 0)
					lShopImageArray[4].fileName = bmpShopItemBox;
				index = 0;
				lastInputKey = 0;
				break;
			case NUM2:
				if (strcmp(lShopImageArray[4].fileName, bmpShopItemBoxDisable) == 0) break;
				lShopImageArray[4].fileName = bmpShopItemBoxSelected;
				if (strcmp(lShopImageArray[3].fileName, bmpShopItemBoxSelected) == 0)
					lShopImageArray[3].fileName = bmpShopItemBox;
				index = 1;
				lastInputKey = 0;
				break;
			// Ω∫∆‰¿ÃΩ∫πŸ ¿‘∑¬«œ∏È æ∆¿Ã≈€ ±∏∏≈
			case SPACE:
				if (index == -1) break;
				else if (index == 0) {
					pc.setStone(pc.getStone() - item1_price);
					lShopImageArray[3].fileName = bmpShopItemBoxDisable;
					if (item2_price > pc.getStone()) lShopImageArray[4].fileName = bmpShopItemBoxDisable;
				}
				else if (index == 1) {
					pc.setStone(pc.getStone() - item2_price);
					lShopImageArray[4].fileName = bmpShopItemBoxDisable;
					if (item1_price > pc.getStone()) lShopImageArray[3].fileName = bmpShopItemBoxDisable;
				}
				index = -1;
				lastInputKey = 1;
				break;
			case ESC:
				flags = 0;
				break;
			}
			if (key) {
				targetLayer->renderAll(targetLayer);
				printStatusInLShop(item1_price, item2_price, lastInputKey);
			}
		}
	}

	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &safetyLayer;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);
}

void printStatusInLShop(int price1, int price2, int num) { // «ˆ¿Á µπ ∞≥ºˆøÕ æ∆¿Ã≈€ ∞°∞›, ∏ª«≥º± √‚∑¬
	printItemTextInLShop(); // æ∆¿Ã≈€ ¿Ã∏ß∞˙ º≥∏Ì √‚∑¬

	wchar_t numStone[20];
	wchar_t numPrice1[20];
	wchar_t numPrice2[20];

	swprintf(numStone, sizeof(numStone) / sizeof(numStone[0]), L"%d", pc.getStone());
	swprintf(numPrice1, sizeof(numPrice1) / sizeof(numPrice1[0]), L"%d", price1);
	swprintf(numPrice2, sizeof(numPrice2) / sizeof(numPrice2[0]), L"%d", price2);

	printText(targetLayer->_consoleDC, 320, 110, 80, 0, RGB(255, 255, 255), TA_CENTER, numStone);
	printText(targetLayer->_consoleDC, 1080, 855, 40, 0, RGB(255, 255, 255), TA_CENTER, numPrice1);
	printText(targetLayer->_consoleDC, 1530, 855, 40, 0, RGB(255, 255, 255), TA_CENTER, numPrice2);

	wchar_t info1[100] = L"º˝¿⁄ ≈∞∏¶ ¥≠∑Ø º±≈√, Spacebar≈∞∏¶ ¥≠∑Ø ±∏∏≈«“ ºˆ ¿÷Ω¿¥œ¥Ÿ. ESC≈∞∏¶ ≈Î«ÿ ªÛ¡°¿ª ≥™∞©¥œ¥Ÿ.";
	wchar_t info2[100] = L"»«∏¢«— º±≈√¿‘¥œ¥Ÿ!";

	if (num == 0) printText(targetLayer->_consoleDC, 900, 1200, 40, 0, RGB(0, 0, 0), TA_LEFT, info1, 500);
	else if (num == 1)  printText(targetLayer->_consoleDC, 900, 1200, 40, 0, RGB(0, 0, 0), TA_LEFT, info2, 500);
}

void printItemTextInLShop() { // æ∆¿Ã≈€ ¿Ã∏ß∞˙ º≥∏Ì √‚∑¬
	wchar_t itemName1[10] = L"¡ˆ«œ ∆ºƒœ";
	wchar_t itemName2[10] = L"π⁄¡„ º€∞˜¥œ";
	wchar_t itemInfo1[100] = L"ªÛ¡°ø°º≠ ∆«∏≈«œ¥¬ æ∆¿Ã≈€¿« ∞°∞›¿Ã 30% «“¿Œµ»¥Ÿ.";
	wchar_t itemInfo2[100] = L"∫∏Ω∫ ∞¯∞›Ω√ ≥∑¿∫ »Æ∑¸∑Œ HP∏¶ ¿œ¡§∑Æ »∏∫π«—¥Ÿ.";

	printText(targetLayer->_consoleDC, 1000, 410, 30, 0, RGB(255, 255, 255), TA_CENTER, itemName1);
	printText(targetLayer->_consoleDC, 900, 730, 30, 0, RGB(255, 255, 255), TA_LEFT, itemInfo1, 190);
	printText(targetLayer->_consoleDC, 1430, 410, 30, 0, RGB(255, 255, 255), TA_CENTER, itemName2);
	printText(targetLayer->_consoleDC, 1350, 730, 30, 0, RGB(255, 255, 255), TA_LEFT, itemInfo2, 190);
}

void visitRShop() {
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &rShopLayer;

	int item1_price = 100;
	int item2_price = 200;
	int item3_price = 300;

	if (item1_price > pc.getStone()) rShopImageArray[4].fileName = bmpShopItemBoxDisable;
	else rShopImageArray[4].fileName = bmpShopItemBox;
	if (item2_price > pc.getStone()) rShopImageArray[5].fileName = bmpShopItemBoxDisable;
	else rShopImageArray[5].fileName = bmpShopItemBox;
	if (item3_price > pc.getStone()) rShopImageArray[6].fileName = bmpShopItemBoxDisable;
	else rShopImageArray[6].fileName = bmpShopItemBox;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	printStatusInRShop(item1_price, item2_price, item3_price, 0);

	int index = -1;
	int flags = 1;
	int lastInputKey = 0;
	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case NUM1:
				if (strcmp(rShopImageArray[4].fileName, bmpShopItemBoxDisable) == 0) break;
				rShopImageArray[4].fileName = bmpShopItemBoxSelected;
				if (strcmp(rShopImageArray[5].fileName, bmpShopItemBoxSelected) == 0)
					rShopImageArray[5].fileName = bmpShopItemBox;
				if (strcmp(rShopImageArray[6].fileName, bmpShopItemBoxSelected) == 0)
					rShopImageArray[6].fileName = bmpShopItemBox;
				index = 0;
				lastInputKey = 0;
				break;
			case NUM2:
				if (strcmp(rShopImageArray[5].fileName, bmpShopItemBoxDisable) == 0) break;
				rShopImageArray[5].fileName = bmpShopItemBoxSelected;
				if (strcmp(rShopImageArray[4].fileName, bmpShopItemBoxSelected) == 0)
					rShopImageArray[4].fileName = bmpShopItemBox;
				if (strcmp(rShopImageArray[6].fileName, bmpShopItemBoxSelected) == 0)
					rShopImageArray[6].fileName = bmpShopItemBox;
				index = 1;
				lastInputKey = 0;
				break;
			case NUM3:
				if (strcmp(rShopImageArray[6].fileName, bmpShopItemBoxDisable) == 0) break;
				rShopImageArray[6].fileName = bmpShopItemBoxSelected;
				if (strcmp(rShopImageArray[4].fileName, bmpShopItemBoxSelected) == 0)
					rShopImageArray[4].fileName = bmpShopItemBox;
				if (strcmp(rShopImageArray[5].fileName, bmpShopItemBoxSelected) == 0)
					rShopImageArray[5].fileName = bmpShopItemBox;
				index = 2;
				lastInputKey = 0;
				break;
			case SPACE:
				if (index == -1) break;
				else if (index == 0) {
					pc.setStone(pc.getStone() - item1_price);
					rShopImageArray[4].fileName = bmpShopItemBoxDisable;
					if (item2_price > pc.getStone()) rShopImageArray[5].fileName = bmpShopItemBoxDisable;
					if (item3_price > pc.getStone()) rShopImageArray[6].fileName = bmpShopItemBoxDisable;
				}
				else if (index == 1) {
					pc.setStone(pc.getStone() - item2_price);
					rShopImageArray[5].fileName = bmpShopItemBoxDisable;
					if (item1_price > pc.getStone()) rShopImageArray[4].fileName = bmpShopItemBoxDisable;
					if (item3_price > pc.getStone()) rShopImageArray[6].fileName = bmpShopItemBoxDisable;
				}
				else if (index == 2) {
					pc.setStone(pc.getStone() - item3_price);
					rShopImageArray[6].fileName = bmpShopItemBoxDisable;
					if (item1_price > pc.getStone()) rShopImageArray[4].fileName = bmpShopItemBoxDisable;
					if (item2_price > pc.getStone()) rShopImageArray[5].fileName = bmpShopItemBoxDisable;
				}
				index = -1;
				lastInputKey = 1;
				break;
			case ESC:
				flags = 0;
				break;
			}
			if (key) {
				targetLayer->renderAll(targetLayer);
				printStatusInRShop(item1_price, item2_price, item3_price, lastInputKey);
			}
		}
	}

	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &safetyLayer;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);
}

void printStatusInRShop(int price1, int price2, int price3, int num) { // «ˆ¿Á µπ ∞≥ºˆøÕ æ∆¿Ã≈€ ∞°∞›, ∏ª«≥º± √‚∑¬
	printItemTextInRShop(); // æ∆¿Ã≈€ ¿Ã∏ß∞˙ º≥∏Ì √‚∑¬

	wchar_t numStone[20];
	wchar_t numPrice1[20];
	wchar_t numPrice2[20];
	wchar_t numPrice3[20];

	swprintf(numStone, sizeof(numStone) / sizeof(numStone[0]), L"%d", pc.getStone());
	swprintf(numPrice1, sizeof(numPrice1) / sizeof(numPrice1[0]), L"%d", price1);
	swprintf(numPrice2, sizeof(numPrice2) / sizeof(numPrice2[0]), L"%d", price2);
	swprintf(numPrice3, sizeof(numPrice3) / sizeof(numPrice3[0]), L"%d", price3);

	printText(targetLayer->_consoleDC, 320, 110, 80, 0, RGB(255, 255, 255), TA_CENTER, numStone);
	printText(targetLayer->_consoleDC, 280, 855, 40, 0, RGB(255, 255, 255), TA_CENTER, numPrice1);
	printText(targetLayer->_consoleDC, 730, 855, 40, 0, RGB(255, 255, 255), TA_CENTER, numPrice2);
	printText(targetLayer->_consoleDC, 1180, 855, 40, 0, RGB(255, 255, 255), TA_CENTER, numPrice3);

	wchar_t info1[100] = L"º˝¿⁄ ≈∞∏¶ ¥≠∑Ø º±≈√, Spacebar≈∞∏¶ ¥≠∑Ø ±∏∏≈«“ ºˆ ¿÷Ω¿¥œ¥Ÿ. ESC≈∞∏¶ ≈Î«ÿ ªÛ¡°¿ª ≥™∞©¥œ¥Ÿ.";
	wchar_t info2[100] = L"»«∏¢«— º±≈√¿‘¥œ¥Ÿ!";

	if (num == 0) printText(targetLayer->_consoleDC, 200, 1200, 40, 0, RGB(0, 0, 0), TA_LEFT, info1, 500);
	else if (num == 1)  printText(targetLayer->_consoleDC, 200, 1200, 40, 0, RGB(0, 0, 0), TA_LEFT, info2, 500);
}

void printItemTextInRShop() // æ∆¿Ã≈€ ¿Ã∏ß∞˙ º≥∏Ì √‚∑¬
{
	wchar_t itemName1[10] = L"¡ˆ«œ ∆ºƒœ";
	wchar_t itemName2[10] = L"π⁄¡„ º€∞˜¥œ";
	wchar_t itemName3[10] = L"∫Ì∑ØµÂ πÈ";
	wchar_t itemInfo1[100] = L"ªÛ¡°ø°º≠ ∆«∏≈«œ¥¬ æ∆¿Ã≈€¿« ∞°∞›¿Ã 30% «“¿Œµ»¥Ÿ.";
	wchar_t itemInfo2[100] = L"∫∏Ω∫ ∞¯∞›Ω√ ≥∑¿∫ »Æ∑¸∑Œ HP∏¶ ¿œ¡§∑Æ »∏∫π«—¥Ÿ.";
	wchar_t itemInfo3[100] = L"PC¿« √÷¥Î √º∑¬¿Ã ¡ı∞°«—¥Ÿ.";

	printText(targetLayer->_consoleDC, 200, 410, 30, 0, RGB(255, 255, 255), TA_CENTER, itemName1);
	printText(targetLayer->_consoleDC, 100, 730, 30, 0, RGB(255, 255, 255), TA_LEFT, itemInfo1, 190);
	printText(targetLayer->_consoleDC, 630, 410, 30, 0, RGB(255, 255, 255), TA_CENTER, itemName2);
	printText(targetLayer->_consoleDC, 550, 730, 30, 0, RGB(255, 255, 255), TA_LEFT, itemInfo2, 190);
	printText(targetLayer->_consoleDC, 1100, 410, 30, 0, RGB(255, 255, 255), TA_CENTER, itemName3);
	printText(targetLayer->_consoleDC, 1000, 730, 30, 0, RGB(255, 255, 255), TA_LEFT, itemInfo3, 190);
}

// ?®Ïàò ?úÏûë

LPCWSTR ConvertToLPCWSTR(const char* ansiStr) {
    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, ansiStr, -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[requiredSize];
    MultiByteToWideChar(CP_UTF8, 0, ansiStr, -1, wideStr, requiredSize);
    return wideStr;
}

void getHandle() {
    CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    WINDOW_HANDLE = GetConsoleWindow();
}

void resizeConsole(int w, int h) {
	char temp[100];
	sprintf(temp, "mode con cols=%d lines=%d", w, h);
	system(temp);
}

void removeCursor() {
    CONSOLE_CURSOR_INFO c;
    c.bVisible = FALSE;
    c.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void initialize() { // Í∏∞Ï¥à?ÅÏù∏ ?¥Îãà?úÎùº?¥Ïßï(ÏΩòÏÜî ?¨Ïù¥Ï¶?ÏßÄ?? ?¨Ïù∏????†ú ??

    getHandle();
    resizeConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    removeCursor();
    srand((unsigned)time(NULL));
}

void initStageImage() { // stageLayer?êÏÑú ?¨Ïö©?òÎäî Î™®Îì† ?¥Î?ÏßÄ ÏµúÏ¥à ?ùÏÑ±
	stageLayer.images = stageImageArray;
	stageLayer.imageCount = 0;

	index_StageImages_Start = stageLayer.imageCount;
	stageImageArray[stageLayer.imageCount++] = { bmpNamePC, STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 2 + 48, STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 2 + 48, 1 };
	stageImageArray[stageLayer.imageCount++] = { bmpCharacterStatusName, 60 , STAGE_ORIGIN_Y, 1 };
	stageImageArray[stageLayer.imageCount++] = { bmpStageLevel, STAGE_ORIGIN_X + AREA_BLOCK_SIZE + 48, 48, 0.2 };

	for (int y = STAGE_ORIGIN_Y; y < STAGE_ORIGIN_Y + AREA_BLOCK_SIZE * 5; y += AREA_BLOCK_SIZE) {
		for (int x = STAGE_ORIGIN_X; x < STAGE_ORIGIN_X + AREA_BLOCK_SIZE * 5; x += AREA_BLOCK_SIZE) {
			stageImageArray[stageLayer.imageCount++] = { bmpNomalAreaName, x, y, 1 };
			stageInfo[(y - STAGE_ORIGIN_Y) / AREA_BLOCK_SIZE][(x - STAGE_ORIGIN_X) / AREA_BLOCK_SIZE] = 1;
		}
	}
	stageImageArray[15].fileName = bmpMovableAreaName;

}

void initItemImages() { // ?ÑÏù¥??Í¥Ä???®Ïàò (Í∞úÎ∞ú ÏßÑÌñâ Ï§?
	std::vector<int> itemList = pc.getitemList();

	for (int i = 0; i < itemList.size(); i++) {
		if (itemList[i] == 1) {
			stageImageArray[stageLayer.imageCount++] = { bmpItem1Name, UI_ITEM_START_POS_X + UI_ITEM_SIZE * ((i + 1) % 2 == 0), UI_ITEM_START_POS_Y + UI_ITEM_SIZE * ((i) / 2), 1 };
		}
		if (itemList[i] == 2) {
			stageImageArray[stageLayer.imageCount++] = { bmpItem2Name, UI_ITEM_START_POS_X + UI_ITEM_SIZE * ((i + 1) % 2 == 0), UI_ITEM_START_POS_Y + UI_ITEM_SIZE * ((i) / 2), 1 };
		}
		if (itemList[i] == 3) {
			stageImageArray[stageLayer.imageCount++] = { bmpItem3Name, UI_ITEM_START_POS_X + UI_ITEM_SIZE * ((i + 1) % 2 == 0), UI_ITEM_START_POS_Y + UI_ITEM_SIZE * ((i) / 2), 1 };
		}
	}
}

void fillBlockImages() { // imageLayer??Î∏îÎ°ù(25x25) ÏµúÏ¥à ?ùÏÑ± 
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			imageArray[imageLayer.imageCount++] = { bmpStoneBlockName, x,y,1 };
			blockInfo[convertPosToInfoY(y)][convertPosToInfoX(x)] = 2;
		}
	}
}

void initAreaUI() // imageLayer??UI ?¥Î?ÏßÄ ÏµúÏ¥à ?ùÏÑ±
{
	index_Area_UI_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameUIItemBox, 30, 30, 1, 1 };
	index_Area_UI_HP_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameHP_0pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_10pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_20pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_30pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_40pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_50pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_60pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_70pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_80pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_90pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameHP_100pct, UI_HP_ORIGIN_X, UI_HP_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameMaxHP, UI_HP_ORIGIN_X - 120, UI_HP_ORIGIN_Y, 1, 1 };

	index_Area_UI_O2_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameO2_0pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_10pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_20pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_30pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_40pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_50pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_60pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_70pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_80pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_90pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameO2_100pct, UI_HP_ORIGIN_X, UI_O2_ORIGIN_Y, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameMaxO2, UI_HP_ORIGIN_X - 120, UI_O2_ORIGIN_Y, 1, 1 };

	index_Area_UI_blockInfo_Start = imageLayer.imageCount;
	index_Area_UI_Map_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameMapPC, 0, 0, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameMapX, 0, 0, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameMapX, 0, 0, 1, 1 };

	index_Area_UI_mapTile_Start = imageLayer.imageCount;
	for (int y = 100; y < 100 + (BLOCKSIZE * 5) + 10; y += (BLOCKSIZE + 2)) {
		for (int x = 1590; x < 1590 + (BLOCKSIZE * 5) + 10; x += (BLOCKSIZE + 2)) {
			imageArray[imageLayer.imageCount++] = { bmpNameMapTile, x, y, 1, 1 };
			mapInfo[(y - 100) / BLOCKSIZE][(x - 1590) / BLOCKSIZE] = 0;
		}
	}

	imageArray[imageLayer.imageCount++] = { bmpNameMapBox, 1508, 0, 1, 1 };

	index_Area_UI_MiniGame_Start = imageLayer.imageCount;
	imageArray[imageLayer.imageCount++] = { bmpNameStar0, 1500, 550, 1, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameOrichalcumMineral, 1580, 1330, 2, 1 };
	imageArray[imageLayer.imageCount++] = { bmpNameTimer, 1600, 1450, 1, 1 };
}

void initRewardImage() { // rewardLayer?êÏÑú ?¨Ïö©?òÎäî Î™®Îì† ?¥Î?ÏßÄ ÏµúÏ¥à ?ùÏÑ±
	rewardLayer.images = imagesReward;
	rewardLayer.imageCount = 0;

	index_RewardImages_Start = rewardLayer.imageCount;
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalRewardSelected, 400, 300, 1, 0 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalReward, 400, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameDynamicRewardSelected, 1100, 300, 1, 0 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameDynamicReward, 1100, 300, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSelected, 0, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtk, 0, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSpdSelected, 660, 150, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalAtkSpd, 660, 150, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalSpdSelected, 1320, 500, 1, 1 };
	imagesReward[rewardLayer.imageCount++] = { bmpNameNormalSpd, 1320, 500, 1, 1 };
}

void updateCharacterStatus() { // PC ?ÅÌÉúÏ∞ΩÏùÑ ?ÖÎç∞?¥Ìä∏
	wchar_t playerStone[20];
	wchar_t playerHp[20];
	wchar_t playerOz[20];
	wchar_t playerAttackPower[20];
	wchar_t playerAttackSpeed[20];
	wchar_t playerMoveSpeed[20];

	swprintf(playerStone, sizeof(playerStone) / sizeof(playerStone[0]), L"%d", pc.getStone());
	swprintf(playerHp, sizeof(playerHp) / sizeof(playerHp[0]), L"%d / %d", pc.getHP(), pc.getMaxHP());
	swprintf(playerOz, sizeof(playerOz) / sizeof(playerOz[0]), L"%d / %d", pc.getOxygen(), pc.getMaxOxygen());
	if (pc.getAtkLev() == 11) swprintf(playerAttackPower, sizeof(playerAttackPower) / sizeof(playerAttackPower[0]), L"Lv.MAX");
	else swprintf(playerAttackPower, sizeof(playerAttackPower) / sizeof(playerAttackPower[0]), L"Lv.%d", pc.getAtkLev());
	if (pc.getAtkSpdLev() == 11) swprintf(playerAttackSpeed, sizeof(playerAttackSpeed) / sizeof(playerAttackSpeed[0]), L"Lv.MAX");
	else swprintf(playerAttackSpeed, sizeof(playerAttackSpeed) / sizeof(playerAttackSpeed[0]), L"Lv.%d", pc.getAtkSpdLev());
	if (pc.getSpdLev() == 11) swprintf(playerMoveSpeed, sizeof(playerMoveSpeed) / sizeof(playerMoveSpeed[0]), L"Lv.MAX");
	else swprintf(playerMoveSpeed, sizeof(playerMoveSpeed) / sizeof(playerMoveSpeed[0]), L"Lv.%d", pc.getSpdLev());

	printText(targetLayer->_consoleDC, 390, 332, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
	printText(targetLayer->_consoleDC, 250, 432, 40, 0, RGB(255, 255, 255), TA_LEFT, playerHp);
	printText(targetLayer->_consoleDC, 250, 498, 40, 0, RGB(255, 255, 255), TA_LEFT, playerOz);
	printText(targetLayer->_consoleDC, 250, 564, 40, 0, RGB(255, 255, 255), TA_LEFT, playerAttackPower);
	printText(targetLayer->_consoleDC, 250, 634, 40, 0, RGB(255, 255, 255), TA_LEFT, playerAttackSpeed);
	printText(targetLayer->_consoleDC, 250, 700, 40, 0, RGB(255, 255, 255), TA_LEFT, playerMoveSpeed);
}

void setMovableStageInfo(int row, int col) { // ?§ÌÖå?¥Ï? ÎßµÏóê???àÎ°≠Í≤??¥Îèô Í∞Ä?•Ìïú ÏßÄ??ùÑ ?úÏãú?òÍ∏∞ ?ÑÌïú ?®Ïàò
	if (row - 1 >= 0) {
		if (stageInfo[row - 1][col] == 1) {
			stageLayer.images[(row - 1) * 5 + col + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row - 1][col] = 0;
		}
	}
	if (row + 1 < 5) {
		if (stageInfo[row + 1][col]) {
			stageLayer.images[(row + 1) * 5 + col + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row + 1][col] = 0;
		}
	}
	if (col - 1 >= 0) {
		if (stageInfo[row][col - 1]) {
			stageLayer.images[(row) * 5 + col - 1 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row][col - 1] = 0;
		}
	}
	if (col + 1 < 5) {
		if (stageInfo[row][col + 1]) {
			stageLayer.images[(row) * 5 + col + 1 + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpMovableAreaName;
			stageInfo[row][col + 1] = 0;
		}
	}
}

void getNewArea() { // ?∏Îßê ?êÏñ¥Î¶¨Ïñ¥(25x25)Î•?Ï¥àÍ∏∞?îÌïò??Î≥Ä??
	// ?êÏñ¥Î¶¨Ïñ¥ ?ÅÏóê??NPCÍ∞Ä ?ùÏÑ±?òÎäî Í≤Ä?Ä Í≥µÍ∞Ñ???¨Í∏∞Î•??§Ï†ï?òÎäî Î≥Ä?òÎì§
	NPCSpaceHeight = getNPCSpaceHeight();
	NPCSpaceWidth = getNPCSpaceWidth();
	// Í≤Ä?Ä Í≥µÍ∞Ñ???ÑÏπòÎ•??Ä?•Ìïò??Î≥Ä??
	NPCSpacePosX = getNPCSpacePosX();
	NPCSpacePosY = getNPCSpacePosY();

	int cnt = 1;
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			if (y == AREA_ORIGIN_Y || y == AREA_ORIGIN_Y + BLOCKSIZE * 24 || x == AREA_ORIGIN_X || x == AREA_ORIGIN_X + BLOCKSIZE * 24) {
				//≈◊µŒ∏Æ∏∏ øÎæœ∫Ì∑œ¿∏∑Œ √§øÏ±‚
				imageArray[cnt++] = { bmpBedrockName, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 99999999;
					}
				}
			}
			// Í≤Ä?Ä Í≥µÍ∞Ñ???§Ï†ú?ÅÏúºÎ°?ÎßåÎìú??Î∞òÎ≥µÎ¨?
			else if (y != AREA_ORIGIN_Y + BLOCKSIZE * 24 && x != AREA_ORIGIN_X + BLOCKSIZE * 24 &&
				y >= NPCSpacePosY && y <= NPCSpacePosY + BLOCKSIZE * NPCSpaceHeight &&
				x >= NPCSpacePosX && x <= NPCSpacePosX + BLOCKSIZE * NPCSpaceWidth) {
				imageArray[cnt++] = { bmpNameNull, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 0;
					}
				}
			}
			// ?§Î•∏ Î∂ÄÎ∂ÑÏ? Í∏∞Î≥∏ ?åÎ°ú Í∑∏Î¶¨Í∏?
			else {
				imageArray[cnt++] = { bmpStoneBlockName, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 2;
					}
				}
			}
		}
	}
	// ?êÏñ¥Î¶¨Ïñ¥?êÏÑú PCÍ∞Ä ?§Ìè∞?òÎäî Ï¥àÍ∏∞ ?ÑÏπò
	imageArray[0].x = AREA_ORIGIN_X + 576;
	imageArray[0].y = AREA_ORIGIN_Y + BLOCKSIZE;
	for (int y = BLOCKSIZE;y < 2*BLOCKSIZE;y++) {
		for (int x = 0;x < BLOCKSIZE;x++) {
			blockInfo[y][576 + x] = 0;
		}
	}
	// ?§Ìè∞?òÎäî ?ÑÏπò??Î∏îÎ°ù ÏßÄ?∞Í∏∞
	imageArray[13 + 25].fileName = bmpNameNull;

	// ?ÑÏû¨ Ï∫êÎ¶≠???§Ìè∞ ?ÑÏπò??Í¥ëÏÑù???ùÏÑ±?????àÎäî Î≤ÑÍ∑∏Í∞Ä Ï°¥Ïû¨??
	// getNewArea() ??Generate~() ?¥ÏÑú Î∞úÏÉù?òÎäî ?ÑÏÉÅ.
}

void getNewMiniGameArea() // ÎØ∏ÎãàÍ≤åÏûÑ ?êÏñ¥Î¶¨Ïñ¥(25x25)Î•?Ï¥àÍ∏∞?îÌïò??Î≥Ä??
{
	int cnt = 1;
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			imageArray[cnt++] = { bmpStoneBlockName, x,y,1 };
			for (int dy = 0;dy < BLOCKSIZE;dy++) {
				for (int dx = 0;dx < BLOCKSIZE;dx++) {
					blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 2;
				}
			}
		}
	}
	// ?êÏñ¥Î¶¨Ïñ¥?êÏÑú PCÍ∞Ä ?§Ìè∞?òÎäî Ï¥àÍ∏∞ ?ÑÏπò
	imageArray[0].x = AREA_ORIGIN_X + 48 * 12;
	imageArray[0].y = AREA_ORIGIN_Y + 48 * 12;
	for (int y = 0;y < BLOCKSIZE;y++) {
		for (int x = 0;x < BLOCKSIZE;x++) {
			blockInfo[576 + y][576 + x] = 0;
		}
	}
	// ?§Ìè∞?òÎäî ?ÑÏπò??Î∏îÎ°ù ÏßÄ?∞Í∏∞
	imageArray[12 * 25 + 13].fileName = bmpNameNull;
}

void drawUI() { // ?êÏñ¥Î¶¨Ïñ¥ UI ?úÏÑ±??
	imageArray[index_Area_UI_Start].isHide = 0; // ?ÑÏù¥??Ï∞ΩÏù¥ Î≥¥Ïù¥?ÑÎ°ù

	imageArray[index_Area_UI_HP_Start + 11].isHide = 0; // HPÎ∞îÍ? Î≥¥Ïù¥?ÑÎ°ù
	pc.setHP(pc.getHP());
	imageArray[index_Area_UI_O2_Start + 11].isHide = 0; // O2Î∞îÍ? Î≥¥Ïù¥?ÑÎ°ù
	pc.setOxygen(pc.getOxygen());
	for (int i = index_Area_UI_Map_Start; i < index_Area_UI_Map_Start + 29; i++) // ÎßµÏù¥ Î≥¥Ïù¥?ÑÎ°ù
		imageArray[i].isHide = 0;

	// ?êÏñ¥Î¶¨Ïñ¥ XÍ∞Ä ÎØ∏Íµ¨?ÑÏù¥Í∏??åÎ¨∏???ÑÏãúÎ°??êÏñ¥Î¶¨Ïñ¥ ÏßÄ?ÑÏóê??XÍ∞Ä ?úÏãú?òÏ? ?äÎèÑÎ°?
	imageArray[index_Area_UI_Map_Start + 1].isHide = 1;
	imageArray[index_Area_UI_Map_Start + 2].isHide = 1;

	int count = 0;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (mapInfo[y][x] == 1) imageArray[index_Area_UI_mapTile_Start + count].fileName = bmpNameMapTileCleared;
			count++;
		}
	}
	imageArray[index_Area_UI_Map_Start].x = 1590 + (BLOCKSIZE + 2) * currentAreaColIndex;
	imageArray[index_Area_UI_Map_Start].y = 100 + (BLOCKSIZE + 2) * currentAreaRowIndex;
	
	if (isMiniGameArea) {
		for (int i = 0; i < 3; i++) {
			imageArray[index_Area_UI_MiniGame_Start + i].isHide = 0;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			imageArray[index_Area_UI_MiniGame_Start + i].isHide = 1;
		}
	}
}

int convertPosToInfoXInStage(int x) {
	if (x - STAGE_ORIGIN_X <= 0) return -1;
	return (x - STAGE_ORIGIN_X) / AREA_BLOCK_SIZE;
}

int convertPosToInfoYInStage(int y) {
	if (y - STAGE_ORIGIN_Y <= 0) return -1;
	return (y - STAGE_ORIGIN_Y) / AREA_BLOCK_SIZE;
}

bool collisionCheckInStage(int x, int y) {
	int infoX = convertPosToInfoXInStage(x);
	int infoY = convertPosToInfoYInStage(y);
	if (infoY < 0 || infoY >= 5 || infoX < 0 || infoX >= 5)
		return 1;
	//return 0;
	return stageInfo[infoY][infoX];
}

int getNPCSpaceHeight() { return (rand() % 8 + 4); }
int getNPCSpaceWidth() { return (rand() % 8 + 4); }
int getNPCSpacePosX() { return((rand() % (NPCSpaceWidth)+1) * BLOCKSIZE + AREA_ORIGIN_X); }
int getNPCSpacePosY() { return ((rand() % (NPCSpaceHeight)+1) * BLOCKSIZE + AREA_ORIGIN_Y) / 2 + 13 * BLOCKSIZE; }

int convertPosToInfoX(int x) {
	return (x - AREA_ORIGIN_X);
}

int convertPosToInfoY(int y) {
	return (y - AREA_ORIGIN_Y);
}

bool collisionCheck(int x, int y) {
	int startX = convertPosToInfoX(x);
	int startY = convertPosToInfoY(y);

	for (int curY = startY; curY < startY + BLOCKSIZE; curY++) {
		for (int curX = startX; curX < startX + BLOCKSIZE; curX++) {
			if (curY < 0 || curY >= 1200 || curX < 0 || curX >= 1200) continue;
			if (blockInfo[curY][curX]) return true;
		}
	}
	return false;
}

void printTimeInMiniGameArea(float t) { // ÎØ∏ÎãàÍ≤åÏûÑ ?êÏñ¥Î¶¨Ïñ¥?êÏÑú ?®Ï? ?úÍ∞Ñ??Ï∂úÎ†•?òÎäî ?®Ïàò
	wchar_t timeLimit[20];
	if (t > 0.0) swprintf(timeLimit, sizeof(timeLimit) / sizeof(timeLimit[0]), L"%.2f", t);
	else swprintf(timeLimit, sizeof(timeLimit) / sizeof(timeLimit[0]), L"%0.00");
	printText(targetLayer->_consoleDC, 1750, 1458, 40, 0, RGB(255, 255, 255), TA_CENTER, timeLimit);
}

void printMyOriInMiniGameArea() { // ÎØ∏ÎãàÍ≤åÏûÑ ?êÏñ¥Î¶¨Ïñ¥?êÏÑú informationÍ≥??çÎìù??Í¥ëÎ¨º ?òÎ? Ï∂úÎ†•?òÎäî ?®Ïàò
	wchar_t info1[30] = L"1 Star (5) = 100 Stones";
	wchar_t info2[30] = L"2 Star(10) = 200 Stones";
	wchar_t info3[30] = L"3 Star(20) = 300 Stones";
	wchar_t numOrichalcum[20];

	printText(targetLayer->_consoleDC, 1610, 670, 40, 0, RGB(255, 255, 255), TA_CENTER, info1);
	printText(targetLayer->_consoleDC, 1610, 730, 40, 0, RGB(255, 255, 255), TA_CENTER, info2);
	printText(targetLayer->_consoleDC, 1610, 790, 40, 0, RGB(255, 255, 255), TA_CENTER, info3);
	swprintf(numOrichalcum, sizeof(numOrichalcum) / sizeof(numOrichalcum[0]), L"%d", OrichalcumNum);
	printText(targetLayer->_consoleDC, 1790, 1358, 40, 0, RGB(255, 255, 255), TA_CENTER, numOrichalcum);
}

void rewardUI() { // ?êÏñ¥Î¶¨Ïñ¥ ?¥Î¶¨????Î≥¥ÏÉÅ???ªÎäî ?®Ïàò
	targetLayer->fadeOut(targetLayer, NULL);
	targetLayer = &rewardLayer;

	imagesReward[0].isHide = 0;
	imagesReward[2].isHide = 0;

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);


	int index1 = -1;
	int flags = 1;
	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case NUM1:
				index1 = 0;
				break;
			case NUM2:
				index1 = 1;
				break;
			case LEFT:
				if (index1 == -1) index1 = 0;
				else if (index1 != 0) index1--;
				break;
			case RIGHT:
				if (index1 == -1) index1 = 1;
				else if (index1 != 1) index1++;
				break;
			case SPACE:
				if (index1 == -1) break;
				flags = 0;
				break;
			}
			if (index1 != -1) index1 %= 2;

			if (index1 == 0) {
				imagesReward[0].isHide = 0;
				imagesReward[1].isHide = 1;
				imagesReward[2].isHide = 1;
				imagesReward[3].isHide = 0;
			}
			else if (index1 == 1) {
				imagesReward[0].isHide = 1;
				imagesReward[1].isHide = 0;
				imagesReward[2].isHide = 0;
				imagesReward[3].isHide = 1;
			}

			if (key) targetLayer->renderAll(targetLayer);
		}
	}

	targetLayer->fadeOut(targetLayer, NULL);
	imagesReward[0].isHide = 1;
	imagesReward[1].isHide = 1;
	imagesReward[2].isHide = 1;
	imagesReward[3].isHide = 1;
	imagesReward[4].isHide = 0;
	imagesReward[5].isHide = 1;
	imagesReward[6].isHide = 0;
	imagesReward[7].isHide = 1;
	imagesReward[8].isHide = 0;
	imagesReward[9].isHide = 1;
	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	int index2 = -1;
	flags = 1;
	while (flags) {
		while (_kbhit() != 0) {
			int key = _getch();

			switch (key) {
			case NUM1:
				index2 = 0;
				break;
			case NUM2:
				index2 = 1;
				break;
			case NUM3:
				index2 = 2;
				break;
			case LEFT:
				if (index2 == -1) index2 = 0;
				else if (index2 != 0) index2--;
				break;
			case RIGHT:
				if (index2 == -1) index2 = 2;
				else if (index2 != 2) index2++;
				break;
			case SPACE:
				if (index2 == -1) break;
				flags = 0;
				break;
			}

			if (index2 != -1) index2 %= 3;

			if (index2 == 0) {
				imagesReward[4].isHide = 0;
				imagesReward[5].isHide = 1;
				imagesReward[6].isHide = 1;
				imagesReward[7].isHide = 0;
				imagesReward[8].isHide = 1;
				imagesReward[9].isHide = 0;
			}
			else if (index2 == 1) {
				imagesReward[4].isHide = 1;
				imagesReward[5].isHide = 0;
				imagesReward[6].isHide = 0;
				imagesReward[7].isHide = 1;
				imagesReward[8].isHide = 1;
				imagesReward[9].isHide = 0;
			}
			else if (index2 == 2) {
				imagesReward[4].isHide = 1;
				imagesReward[5].isHide = 0;
				imagesReward[6].isHide = 1;
				imagesReward[7].isHide = 0;
				imagesReward[8].isHide = 0;
				imagesReward[9].isHide = 1;
			}
			if (key) targetLayer->renderAll(targetLayer);
		}
	}
	targetLayer->fadeOut(targetLayer, NULL);
	// ?§Ïùå RewardUI() ?∏Ï∂ú???ÑÌïú ÏΩîÎìú
	imagesReward[4].isHide = 1;
	imagesReward[5].isHide = 1;
	imagesReward[6].isHide = 1;
	imagesReward[7].isHide = 1;
	imagesReward[8].isHide = 1;
	imagesReward[9].isHide = 1;

	targetLayer = &stageLayer;
	isOnStage = true;
	targetLayer->images[currentAreaRowIndex * 5 + currentAreaColIndex + STAGE_EXTRA_IMAGE_COUNT].fileName = bmpClearedAreaName;
	stageInfo[currentAreaRowIndex][currentAreaColIndex] = 0;
	setMovableStageInfo(currentAreaRowIndex, currentAreaColIndex);

	targetLayer->fadeIn(targetLayer, NULL);
	targetLayer->renderAll(targetLayer);

	int num = 0;
	if (index1 == 0) num = rand() % 3;
	else if (index1 == 1) num = rand() % 11 + (-5);
	if (index2 == 0) pc.setAtkLev(pc.getAtkLev() + num);
	else if (index2 == 1) pc.setAtkSpdLev(pc.getAtkSpdLev() + num);
	else if (index2 == 2) pc.setSpdLev(pc.getSpdLev() + num);
	pc.setStone(pc.getStone() + 100);

	imageArray[index_Area_UI_MiniGame_Start].fileName = bmpNameStar0;
	if (isMiniGameArea) {
		if (OrichalcumNum >= 2) pc.setStone(pc.getStone() + 200);
		else if (OrichalcumNum >= 1) pc.setStone(pc.getStone() + 100);
	}
	OrichalcumNum = 0;
}

bool printButtonStageStatus() {
	wchar_t playerStone[100] = L"Pessed Button List";
	wchar_t pressed_button_info[20] = L"";
	wchar_t pressed_button_status[20] = L"";
	bool isClear = true;
	bool isButtonReset = false;

	if (buttonPressedOrderList.size() == 1) {
		swprintf(pressed_button_info, sizeof(pressed_button_info) / sizeof(pressed_button_info[0]), L"%d", buttonPressedOrderList[0]);
	}
	else if (buttonPressedOrderList.size() == 2) {
		swprintf(pressed_button_info, sizeof(pressed_button_info) / sizeof(pressed_button_info[0]), L"%d -> %d", buttonPressedOrderList[0], buttonPressedOrderList[1]);
	}
	else if (buttonPressedOrderList.size() == 3) {
		swprintf(pressed_button_info, sizeof(pressed_button_info) / sizeof(pressed_button_info[0]), L"%d -> %d -> %d", buttonPressedOrderList[0], buttonPressedOrderList[1], buttonPressedOrderList[2]);

		for (int i = 0; i < 3; i++) {
			if (buttonPressedOrderList[i] != buttonPressedOrderAnswerList[i]) {
				isClear = false;
				break;
			}
		}
		if (isClear) {
			isButtonRoomClear = true;
			swprintf(pressed_button_status, sizeof(pressed_button_status) / sizeof(pressed_button_status[0]), L"Correct Answer!");
			printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
			printText(targetLayer->_consoleDC, 1600, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_info);
			printText(targetLayer->_consoleDC, 1600, 800, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_status);
		}
		else {
			imageArray[0].y = imageArray[0].y + 96;
			isButtonReset = true;
			buttonPressedOrderList.clear();
			swprintf(pressed_button_status, sizeof(pressed_button_status) / sizeof(pressed_button_status[0]), L"Not Correct Answer!");
			printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
			printText(targetLayer->_consoleDC, 1600, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_info);
			printText(targetLayer->_consoleDC, 1600, 800, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_status);
			Sleep(300);
		}
		
		swprintf(pressed_button_status, sizeof(pressed_button_status) / sizeof(pressed_button_status[0]), L"");
	}

	printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerStone);
	printText(targetLayer->_consoleDC, 1600, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_info);
	printText(targetLayer->_consoleDC, 1600, 800, 40, 0, RGB(255, 255, 255), TA_CENTER, pressed_button_status);

	return isButtonReset;
 }

void printFlagStageStatus(int curFlagCnt) {
	wchar_t playerFlagInfo[100] = L"Your Current Flag Count : ";
	wchar_t playerFlagCount[20] = L"";
	swprintf(playerFlagCount, sizeof(playerFlagCount) / sizeof(playerFlagCount[0]), L"%d", curFlagCnt);
	printText(targetLayer->_consoleDC, 1600, 600, 40, 0, RGB(255, 255, 255), TA_CENTER, playerFlagInfo);
	printText(targetLayer->_consoleDC, 1800, 700, 40, 0, RGB(255, 255, 255), TA_CENTER, playerFlagCount);
}

void setBedrock(int max) {
	while (max) {
		int bedrockX = (rand() % 21) * BLOCKSIZE + AREA_ORIGIN_X;
		int bedrockY = (rand() % 12) * BLOCKSIZE + AREA_ORIGIN_Y;
		if (blockInfo[convertPosToInfoY(bedrockY)][convertPosToInfoX(bedrockX)] != 2) continue;
		bool ok = true;
		for (int i = 1;i < 4;i++) {
			if (blockInfo[convertPosToInfoY(bedrockY)][convertPosToInfoX(bedrockX+i*BLOCKSIZE)] != 2) {
				ok = false;
				break;
			}
		}
		if (ok) {
			for (int i = 0;i < 4;i++) {
				int imageIndex = convertPosToInfoY(bedrockY) / BLOCKSIZE * 25 + convertPosToInfoX(bedrockX+i * BLOCKSIZE) / BLOCKSIZE + 1;
				imageArray[imageIndex].fileName = bmpBedrockName;
				blockInfo[convertPosToInfoY(bedrockY)][convertPosToInfoX(bedrockX+i * BLOCKSIZE)] = 999999;
			}
			max--;
		}
	}
}

void setFlag(int cnt) {
	while (cnt) {
		int flagX = (rand() % 23) * BLOCKSIZE + BLOCKSIZE + AREA_ORIGIN_X;
		int flagY = (rand() % 20) * BLOCKSIZE + 3*BLOCKSIZE + AREA_ORIGIN_Y;
		//flagX = cnt*BLOCKSIZE + AREA_ORIGIN_X;
		//flagY = cnt*BLOCKSIZE + AREA_ORIGIN_Y;
		if (blockInfo[convertPosToInfoY(flagY)][convertPosToInfoX(flagX)] != 2) continue;
		int imageIndex = convertPosToInfoY(flagY) / BLOCKSIZE * 25 + convertPosToInfoX(flagX) / BLOCKSIZE + 1;
		imageArray[imageIndex].fileName = bmpFlagName;

		int infoX = convertPosToInfoX(flagX);
		int infoY = convertPosToInfoY(flagY);
		if (infoY < 0 || infoY >= 1200 || infoX < 0 || infoX >= 1200) return;
		for (int curY = infoY; curY < infoY + BLOCKSIZE; curY++) {
			for (int curX = infoX; curX < infoX + BLOCKSIZE; curX++) {
				if (blockInfo[curY][curX])
					blockInfo[curY][curX] = 1;
			}
		}
		cnt--;
	}
}



void getNewBossArea() {
	int cnt = 1;
	for (int y = AREA_ORIGIN_Y;y < AREA_ORIGIN_Y + BLOCKSIZE * 25;y += BLOCKSIZE) {
		for (int x = AREA_ORIGIN_X;x < AREA_ORIGIN_X + BLOCKSIZE * 25;x += BLOCKSIZE) {
			// Í≤Ä?Ä Í≥µÍ∞Ñ???§Ï†ú?ÅÏúºÎ°?ÎßåÎìú??Î∞òÎ≥µÎ¨?
			if (y==AREA_ORIGIN_Y || y == AREA_ORIGIN_Y + BLOCKSIZE * 24 || x==AREA_ORIGIN_X || x == AREA_ORIGIN_X + BLOCKSIZE * 24) {
				//≈◊µŒ∏Æ∏∏ øÎæœ∫Ì∑œ¿∏∑Œ √§øÏ±‚
				imageArray[cnt++] = { bmpBedrockName, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 99999999;
					}
				}
			}
			// ≥™∏”¡ˆ¥¬ ¿¸∫Œ ∫Û∞¯∞£
			else { 
				imageArray[cnt++] = { bmpNameNull, x,y,1 };
				for (int dy = 0;dy < BLOCKSIZE;dy++) {
					for (int dx = 0;dx < BLOCKSIZE;dx++) {
						blockInfo[convertPosToInfoY(y + dy)][convertPosToInfoX(x + dx)] = 0;
					}
				}
			}
		}
	}
}

void printStoneStatus(int curStone) {
	wchar_t playerFlagInfo[100] = L"∫∏¿Ø¡ﬂ¿Œ STONE : ";
	wchar_t playerFlagCount[20] = L"";
	swprintf(playerFlagCount, sizeof(playerFlagCount) / sizeof(playerFlagCount[0]), L"%d", curStone);
	printText(targetLayer->_consoleDC, 500,200, 40, 0, RGB(255, 255, 255), TA_CENTER, playerFlagInfo);
	printText(targetLayer->_consoleDC, 700,200, 40, 0, RGB(255, 255, 255), TA_CENTER, playerFlagCount);
}