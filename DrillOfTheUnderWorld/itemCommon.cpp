#include "itemCommon.hpp"

// item vector
std::vector<Item*> ownedItems;
std::vector<Item*> sRankItems;
std::vector<Item*> aRankItems;
std::vector<Item*> bRankItems;
std::vector<Item*> cRankItems;
std::vector<Item*> eRankItems; // -�Ҹ���
std::vector<Item*> nRankItems; // -�ν�Ʈ��
std::vector<Item*> fRankItems; // -��

void initSRankItems(){
	sRankItems.push_back(new AncientVirus());
}