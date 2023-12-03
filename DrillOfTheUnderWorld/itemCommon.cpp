#include "itemCommon.hpp"

// item vector
std::vector<Item*> ownedItems;
std::vector<Item*> sRankItems;
std::vector<Item*> aRankItems;
std::vector<Item*> bRankItems;
std::vector<Item*> cRankItems;
std::vector<Item*> eRankItems; // -소모형
std::vector<Item*> nRankItems; // -부스트류
std::vector<Item*> fRankItems; // -디벞

void initSRankItems(){
	sRankItems.push_back(new AncientVirus());
}