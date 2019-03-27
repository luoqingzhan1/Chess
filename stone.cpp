#include "stone.h"
#include <QDebug>
Stone::Stone():d(Util::d)
{
    dead = false;
}

void Stone::draw(QPainter &p, int selectId)
{

    //死掉的棋子不用画
    if(dead)return;
    //画圆
    QPoint center = Util::getStonePoint(row,col);
    p.setPen(QPen(Qt::black));
    if(selectId == id)
    {
        p.setBrush(Qt::gray);
    }
    else
    {
        p.setBrush(Qt::yellow);
    }

    p.drawEllipse(center,d/2,d/2);


    //画字

    QString text("帅仕相马车炮兵将士象马车炮卒");

    int index = 7 * (id > 16) +(int)type;

    QChar ch = text.at(index);

    if(id < 16)
    {
        p.setPen(QPen(Qt::red));
    }
    else
    {
         p.setPen(QPen(Qt::black));
    }
    p.setFont(QFont("宋体",d/2));
    p.drawText(Util::getStoneRect(row,col),Qt::AlignCenter,QString(ch));


}
