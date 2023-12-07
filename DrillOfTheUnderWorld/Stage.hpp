#ifndef STAGE_HPP
#define STAGE_HPP

extern "C" {
#include <Windows.h>
}
#include "Area.hpp"
#include "common.hpp"
#include <vector>

class Stage {
private:
    int stageLevel;
    //std::vector<std::vector<Area>> areaList;
public:
    Stage();
    void initAreasPos();
    int getLevel();
    void setLevel(int level);
    //Area& getArea(int row, int col);
};
z
#endif // STAGE_HPP