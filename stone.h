#ifndef STONE_H
#define STONE_H

#include <QPainter>
#include "util.h"

class Stone
{
public:
    Stone();

    enum Type {JIANG,SHI,XIANG,MA,CHE,PAO,BING};
    int row;
    int col;
    int id; //0-15是红色 16-31是黑色

    Type type;
    bool dead;
    int d;

    void draw(QPainter &p,int selectId);

};

#endif // STONE_H
