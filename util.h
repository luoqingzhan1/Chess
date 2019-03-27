#ifndef UTIL_H
#define UTIL_H
#include <QPoint>
#include <QRect>


class Util
{
public:
    Util();

    static int d;
    static QPoint getStonePoint(int row, int col);
    static QRect getStoneRect(int row, int col);
    static bool getPlateCood(QPoint p, int &row, int &col);

};

#endif // UTIL_H
