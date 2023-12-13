#include "itemCommon.hpp"
#include "common.hpp"

// item vector
std::vector<Item*> ownedItems;
std::vector<Item*> shopItems;

std::vector<Item*> sRankItems;
std::vector<Item*> aRankItems;
std::vector<Item*> bRankItems;
std::vector<Item*> cRankItems;
std::vector<Item*> eRankItems; // -소모형
std::vector<Item*> nRankItems; // -부스트류
std::vector<Item*> fRankItems; // -디벞
std::vector<Item*> treasureItems;


void initItems() {
	initSRankItems();
	initARankItems();
	initBRankItems();
	initCRankItems();
	initERankItems();
	initNRankItems();
	initFRankItems();
	initFTreasureItems();
}

void initSRankItems(){
	sRankItems.push_back(new MetalDetector());
	sRankItems.push_back(new ThornCrown());
	sRankItems.push_back(new BeggarDoll());
	sRankItems.push_back(new Orichalcum());
}

void initARankItems() {
	aRankItems.push_back(new TwoHearts());
	aRankItems.push_back(new LuckyCharm());
}

void initBRankItems() {
	bRankItems.push_back(new Disassembler()); //  todo
	bRankItems.push_back(new BatFang());
	bRankItems.push_back(new MoleClaw());
	bRankItems.push_back(new Dice());
}
void initCRankItems() {
	cRankItems.push_back(new LuckStone());
	cRankItems.push_back(new BloodBag());
	cRankItems.push_back(new SupplyOxygenTank());
	cRankItems.push_back(new FreshBrewedCoffee());
}
void initERankItems() {
	eRankItems.push_back(new EnergyBar());
	eRankItems.push_back(new PortableOxygenCan());
}
void initNRankItems() {
	nRankItems.push_back(new AttackBoost());
	nRankItems.push_back(new AttackSpeedBoost());
	nRankItems.push_back(new MovementSpeedBoost());
}
void initFRankItems() {
	fRankItems.push_back(new PrisonerShackles());
	fRankItems.push_back(new CursedTotem());
	fRankItems.push_back(new AncientVirus());
	fRankItems.push_back(new CaveSnake());
}

void initFTreasureItems() {
	treasureItems.push_back(new PrisonerShackles());
	treasureItems.push_back(new CursedTotem());
	treasureItems.push_back(new AncientVirus());
	treasureItems.push_back(new CaveSnake());

	treasureItems.push_back(new MetalDetector());
	treasureItems.push_back(new ThornCrown());
	treasureItems.push_back(new BeggarDoll());

	treasureItems.push_back(new TwoHearts());
	treasureItems.push_back(new LuckyCharm());

	treasureItems.push_back(new BatFang());
	treasureItems.push_back(new MoleClaw());
}