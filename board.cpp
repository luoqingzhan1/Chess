#include "board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),d(Util::d)
{

    struct {
        Stone::Type type;
        int row;
        int col;
    }p[16]=
    {
    {Stone::CHE,9,8},
    {Stone::MA,9,7},
    {Stone::XIANG,9,6},
    {Stone::SHI,9,5},
    {Stone::JIANG,9,4},
    {Stone::CHE,9,0},
    {Stone::MA,9,1},
    {Stone::XIANG,9,2},
    {Stone::SHI,9,3},
    {Stone::PAO,7,1},
    {Stone::PAO,7,7},
    {Stone::BING,6,0},
    {Stone::BING,6,2},
    {Stone::BING,6,4},
    {Stone::BING,6,6},
    {Stone::BING,6,8}
};

    for(int i=0;i<32;++i)
    {
        s[i].id=i;
        if(i<16)
        {
            s[i].type = p[i].type;
            s[i].row = p[i].row;
            s[i].col = p[i].col;
        }
        else
        {
            s[i].type = p[i-16].type;
            s[i].row = 9 - p[i-16].row;
            s[i].col = 8 - p[i-16].col;
        }

    }
    selectId = -1;
    redTurn=true;
}

void Board::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    drawPlate(p);

    drawCross(p,2,1);
    drawCross(p,2,7);

    drawCross(p,3,0);
    drawCross(p,3,2);
    drawCross(p,3,4);
    drawCross(p,3,6);
    drawCross(p,3,8);

    drawCross(p,6,0);
    drawCross(p,6,2);
    drawCross(p,6,4);
    drawCross(p,6,6);
    drawCross(p,6,8);
    drawCross(p,7,1);
    drawCross(p,7,7);


    for(int i=0;i<32;++i)
    {
        s[i].draw(p,selectId);
    }
}

void Board::drawPlate(QPainter &p)
{

    for(int i=1;i<=10;++i)
    {
        p.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }
    for(int i=1;i<=9;++i)
    {
        if(i == 1 || i ==9)
        {
            p.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        }
        else
        {
            p.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            p.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }

    }

    p.drawLine(QPoint(4*d,d),QPoint(6*d,3*d));
    p.drawLine(QPoint(4*d,3*d),QPoint(6*d,d));


    p.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    p.drawLine(QPoint(4*d,10*d),QPoint(6*d,8*d));
}

void Board::drawCross(QPainter &p, int row, int col)
{
    QPoint center = Util::getStonePoint(row,col);

    QPoint origin;
    if(col == 8)
    {
        //左上角
        origin = center +QPoint(-d/6,-d/6);
        p.drawLine(origin,origin + QPoint(0,-d/3));
        p.drawLine(origin,origin + QPoint(-d/3,0));

        //左下角
        origin = center +QPoint(-d/6,d/6);
        p.drawLine(origin,origin + QPoint(-d/3,0));
        p.drawLine(origin,origin + QPoint(0,d/3));
    }
    else if(col == 0)
    {
        //右上角
        origin = center +QPoint(d/6,-d/6);
        p.drawLine(origin,origin + QPoint(0,-d/3));
        p.drawLine(origin,origin + QPoint(d/3,0));

        //右下角
        origin = center +QPoint(d/6,d/6);
        p.drawLine(origin,origin + QPoint(0,d/3));
        p.drawLine(origin,origin + QPoint(d/3,0));
    }
    else
    {
        //右下角
        origin = center +QPoint(d/6,d/6);
        p.drawLine(origin,origin + QPoint(0,d/3));
        p.drawLine(origin,origin + QPoint(d/3,0));

        //左下角
        origin = center +QPoint(-d/6,d/6);
        p.drawLine(origin,origin + QPoint(-d/3,0));
        p.drawLine(origin,origin + QPoint(0,d/3));

        //右上角
        origin = center +QPoint(d/6,-d/6);
        p.drawLine(origin,origin + QPoint(0,-d/3));
        p.drawLine(origin,origin + QPoint(d/3,0));

        //左上角
        origin = center +QPoint(-d/6,-d/6);
        p.drawLine(origin,origin + QPoint(0,-d/3));
        p.drawLine(origin,origin + QPoint(-d/3,0));
    }


}

void Board::mousePressEvent(QMouseEvent *ev)
{
    //右键无效
    if(ev->button() == Qt::RightButton) return;
    QPoint center = ev->pos();

    int row = -1;
    int col = -1;

    //判断位置
    if(!Util::getPlateCood(center,row,col))
    {
        //点到棋盘外，无效
        return;
    }
    //获取选择棋子id
    int clickId = getStoneId(row,col);
    if(selectId == -1)
    {
        selectStone(clickId);
    }
    else
    {
        if(clickId !=-1 &&(selectId <16 == clickId <16))
        {
            selectStone(clickId);
            return;
        }

        if(!canMoveStone(selectId,clickId,row,col))return;

        moveStone(selectId,clickId,row,col);
        if(s[clickId].type == Stone::JIANG && s[clickId].dead)
        {
            if(s[clickId].id <16)
            {
                QMessageBox::information(this,"胜利","黑色棋子获得胜利");
            }
            else
            {
                QMessageBox::information(this,"胜利","红色棋子获得胜利");
            }
        }
    }

}

int Board::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(s[i].row == row && s[i].col == col && !s[i].dead)
        {
            return i;
        }
    }
    return -1;
}

void Board::selectStone(int select)
{
    if(redTurn != select <16) return;
    selectId = select;
    update();
}

void Board::moveStone(int select, int kill, int row, int col)
{
    //move 走棋
    s[select].row = row;
    s[select].col = col;
    if(kill !=-1)
    {
        s[kill].dead = true;

    }
    selectId = -1;
    redTurn = !redTurn;
    update();
}

bool Board::canMoveStone(int select, int kill, int row, int col)
{
    bool flag = true;
    switch (s[select].type) {
    case Stone::JIANG:
        flag =  isStoneJiang(select,kill,row,col);
        break;
    case Stone::SHI:
        flag =  isStoneShi(select,kill,row,col);
        break;
    case Stone::XIANG:
        flag =  isStoneXiang(select,kill,row,col);
        break;
    case Stone::CHE:
        flag =  isStoneChe(select,kill,row,col);
        break;
    case Stone::MA:
        flag =  isStoneMa(select,kill,row,col);
        break;
    case Stone::PAO:
        flag =  isStonePao(select,kill,row,col);
        break;
    case Stone::BING:
        flag =  isStoneBing(select,kill,row,col);
        break;
    default:
        break;
    }


    return flag;
}


/*
1.只能走九宫格
2.飞将

*/
bool Board::isStoneJiang(int select, int kill, int row, int col)
{

    // 照面跟车是一样的
    if(kill != -1 && s[kill].type == Stone::JIANG)
    {
        int ret = getStoneCount(s[select].row, s[select].col, row, col);
        if(ret == 0)
            return true;
    }

    // 解决只能走一步问题
    int dRow = qAbs(s[select].row - row);
    int dCol = qAbs(s[select].col - col);
    if(dRow + dCol != 1)
        return false;

    // 目标只能在九宫内
    if(col < 3 || col > 5) return false;
    if(s[select].id < 16)
    {
        if(row < 7 || row > 9) return false;
    }
    else
    {
        if(row < 0 || row > 2) return false;
    }

    return true;
}

bool Board::isStoneShi(int select, int kill, int row, int col)
{

    // 目标只能在九宫内
    if(col < 3 || col > 5) return false;
    if(s[select].id < 16)
    {
        if(row < 7 || row > 9) return false;
    }
    else
    {
        if(row < 0 || row > 2) return false;
    }

    // 斜着走
    int dRow = qAbs(s[select].row - row);
    int dCol = qAbs(s[select].col - col);
    if(dRow * 10 + dCol != 11)
        return false;

    return true;
}

/*
1.不能过河
2.象走田

*/
bool Board::isStoneXiang(int select, int kill, int row, int col)
{

    // 不能过河
    if(s[select].id < 16)
    {
        if(row < 5) return false;
    }
    else
    {
        if(row > 4) return false;
    }

    // 相飞田
    int dRow = qAbs(s[select].row - row);
    int dCol = qAbs(s[select].col - col);
    if(dRow * 10 + dCol != 22)
        return false;

    // 象眼不能有子
    int eRow = (s[select].row + row)/2;
    int eCol = (s[select].col + col)/2;
    int eye = getStoneId(eRow, eCol);
    if(eye != -1)
        return false;
    return true;
}

/*
1.走直线
2.可以做多步
*/

bool Board::isStoneChe(int select, int kill, int row, int col)
{

    int ret = getStoneCount(s[select].row, s[select].col, row, col);
    if(ret != 0) return false;

    return true;
}
/*
1. 马走日
2. 不能碍马腿
*/
bool Board::isStoneMa(int select, int , int row, int col)
{
    // 马走日
    int dRow = qAbs(s[select].row - row);
    int dCol = qAbs(s[select].col - col);
    int d = dRow * 10 + dCol;
    if(d != 21 && d != 12)
        return false;

    // 马腿
    if(d == 21)
    {
        int eRow = (s[select].row + row)/2;
        int eCol = s[select].col;
        if(getStoneId(eRow, eCol) != -1) return false;
    }
    else
    {
        int eRow = s[select].row;
        int eCol = (s[select].col + col)/2;
        if(getStoneId(eRow, eCol) != -1) return false;
    }
    return true;
}

bool Board::isStonePao(int select, int kill, int row, int col)
{
    if(kill == -1)
    {
        int ret = getStoneCount(s[select].row, s[select].col, row, col);
        if(ret != 0) return false;
    }
    else
    {
        int ret = getStoneCount(s[select].row, s[select].col, row, col);
        if(ret != 1) return false;
    }
    return true;
}

/*
1. 只能走一步
2. 过河前不能后退，不能平移
3. 过河后可以平移
*/
bool Board::isStoneBing(int select, int , int row, int col)
{
    // 解决只能走一步问题
    int dRow = qAbs(s[select].row - row);
    int dCol = qAbs(s[select].col - col);
    if(dRow + dCol != 1)
        return false;

    // 红色
    if(s[select].id < 16)
    {
        // 在后退
        if(row > s[select].row) return false;

        // 没过河
        if(s[select].row >= 5)
        {
            if(row == s[select].row ) return false;
        }
    }
    else
    {
        // 在后退
        if(row < s[select].row) return false;

        // 没过河
        if(s[select].row <= 4)
        {
            if(row == s[select].row ) return false;
        }
    }
    return true;
}

int Board::getStoneCount(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1!=col2) return -1;

    if(row1 == row2)
    {
        if(col1 > col2)
        {
            int tmp = col1;
            col1 = col2;
            col2 = tmp;
        }
        for(int col = col1+1; col < col2; ++col)
        {
            if(getStoneId(row1, col) != -1) ret++;
        }
    }
    else // col 相等
    {
        if(row1 > row2)
        {
            int tmp = row1;
            row1 =row2;
            row2 = tmp;
        }
        for(int row = row1+1; row < row2; ++row)
        {
            if(getStoneId(row, col1) != -1) ret++;
        }
    }
    return ret;
}
