#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include "stone.h"
#include "util.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void drawPlate(QPainter &p);
    void drawCross(QPainter &p,int row, int col);
    void mousePressEvent(QMouseEvent *ev);

    int getStoneId(int row,int col);

    void selectStone(int select);
    void moveStone(int select,int kill,int row,int col);

    bool canMoveStone(int select, int kill, int row, int col);

    bool isStoneJiang(int select, int kill, int row, int col);
    bool isStoneShi(int select, int kill, int row, int col);
    bool isStoneXiang(int select, int kill, int row, int col);
    bool isStoneChe(int select, int kill, int row, int col);
    bool isStoneMa(int select, int kill, int row, int col);
    bool isStonePao(int select, int kill, int row, int col);
    bool isStoneBing(int select, int kill, int row, int col);

    int getStoneCount(int row1,int col1,int row2, int col2);

    int selectId;//如果selectId= -1 没有选择，如果有，走棋

    bool redTurn;
    Stone s[32];

    int &d;
signals:

public slots:

};

#endif // BOARD_H
