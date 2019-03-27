#include <QApplication>
#include "board.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    Board b;
    b.show();

    return app.exec();
}
