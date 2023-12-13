#ifndef ITEM_COMMON_HPP
#define ITEM_COMMON_HPP
#define _CRT_SECURE_NO_WARNINGS

#include "UndergroundTicket.hpp"
#include "MetalDetector.hpp"
#include "ThronCrown.hpp"
#include "BeggarDoll.hpp"
#include "Orichalcum.hpp"
#include "TwoHearts.hpp"
#include "LuckyCharm.hpp"
#include "Disassembler.hpp"
#include "BatFang.hpp"
#include "MoleClaw.hpp"
#include "Dice.hpp"
#include "LuckStone.hpp"
#include "BloodBag.hpp"
#include "SupplyOxygenTank.hpp"
#include "FreshBrewedCoffee.hpp"
#include "PortableOxygenCan.hpp"
#include "EnergyBar.hpp"
#include "AttackBoost.hpp"
#include "AttackSpeedBoost.hpp"
#include "MovementSpeedBoost.hpp"
#include "PrisonerShackles.hpp"
#include "CursedTotem.hpp"
#include "AncientVirus.hpp"
#include "CaveSnake.hpp"
#include <vector>

// item vector
extern std::vector<Item*> ownedItems;
extern std::vector<Item*> shopItems;

extern std::vector<Item*> sRankItems;
extern std::vector<Item*> aRankItems;
extern std::vector<Item*> bRankItems;
extern std::vector<Item*> cRankItems;
extern std::vector<Item*> eRankItems; // -소모형
extern std::vector<Item*> nRankItems; // -부스트류
extern std::vector<Item*> fRankItems; // -디벞
extern std::vector<Item*> treasureItems;

void initItems();
void initSRankItems();
void initARankItems();
void initBRankItems();
void initCRankItems();
void initERankItems();
void initNRankItems();
void initFRankItems();
void initFTreasureItems();

#endif ITEM_COMMON_HPP