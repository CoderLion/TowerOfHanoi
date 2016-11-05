#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    resize(this->width() + 200, this->height());
    for(int i = 0; i < AmountOfPlates; i++){
        pole[left].plates[i] = AmountOfPlates-i;
        pole[left].height = AmountOfPlates;
        pole[middle].plates[i] = 0;
        pole[middle].height = 0;
        pole[right].plates[i] = 0;
        pole[right].height = 0;
    }
    focus.pole = left;
    focus.plate = 0;

    maxPlateWidth = 150;
    minPlateWidth = 70;
    plateHeight = 40;
    poleMargin = 50;
}

MainWindow::~MainWindow()
{
}


void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    for(int i = 0; i < AmountOfPlates; i++){
        painter.fillRect(calculatePlateRect(left  , i, pole[left]  .plates[i]), calculatePlateColor(pole[left]  .plates[i]));
        painter.drawRect(calculatePlateRect(left  , i, pole[left]  .plates[i]));

        painter.fillRect(calculatePlateRect(middle, i, pole[middle].plates[i]), calculatePlateColor(pole[middle].plates[i]));
        painter.drawRect(calculatePlateRect(middle, i, pole[middle].plates[i]));

        painter.fillRect(calculatePlateRect(right , i, pole[right] .plates[i]), calculatePlateColor(pole[right] .plates[i]));
        painter.drawRect(calculatePlateRect(right , i, pole[right] .plates[i]));
    }

    QPair<QLine, QRect> focusUI = calculateFocusUI();
    painter.drawLine(focusUI.first);
    painter.fillRect(focusUI.second, calculatePlateColor(focus.plate));
    painter.drawRect(focusUI.second);

    QWidget::paintEvent(e);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    int currentPole = focus.pole;
    if(e->key() == Qt::Key_Up){
        if(focus.plate == 0){
            if(pole[currentPole].height >= 1 && focus.plate == 0){
                focus.plate = pole[currentPole].plates[pole[currentPole].height - 1];
                pole[currentPole].plates[pole[currentPole].height - 1] = 0;
                pole[currentPole].height--;
            }
        }
    }
    else if(e->key() == Qt::Key_Down){
        if(focus.plate != 0){
            if(pole[currentPole].height == 0 || pole[currentPole].plates[pole[currentPole].height - 1] > focus.plate){
                pole[currentPole].plates[pole[currentPole].height] = focus.plate;
                focus.plate = 0;
                pole[currentPole].height++;
            }
        }
    }
    else if(e->key() == Qt::Key_Right){
        if(currentPole <= 1){
            focus.pole++;
        }
    }
    else if(e->key() == Qt::Key_Left){
        if(currentPole >= 1){
            focus.pole--;
        }
    }

    this->update();
}

QRect MainWindow::calculatePlateRect(int poleLocation, int plateLocation, int plateSize){
    int x, y, w, h;

    int LowerRightX, LowerRightY;
    LowerRightX = (this->width() - 3*maxPlateWidth - 2*poleMargin) / 2 + poleLocation*(maxPlateWidth+poleMargin);
    LowerRightY = this->height() - 100;

    LowerRightY -= plateLocation*plateHeight;
    int succeedingPlateWidthDifference= (maxPlateWidth - minPlateWidth) / (2*AmountOfPlates);
    LowerRightX += succeedingPlateWidthDifference * (AmountOfPlates - plateSize);

    x = LowerRightX;
    y = LowerRightY - plateHeight;
    if(plateSize == 0){
        h = 0;
        w = 0;
    }
    else{
        h = plateHeight;
        w = maxPlateWidth - 2 * ((AmountOfPlates - plateSize) * succeedingPlateWidthDifference);
    }

    return QRect(x,y,w,h);

}

QPair<QLine, QRect> MainWindow::calculateFocusUI(){
    int yOffset = 75;
    QRect plateRect = calculatePlateRect(focus.pole, 0, focus.plate);
    QRect protoLineRect = calculatePlateRect(focus.pole, 0, AmountOfPlates);

    QLine poleLine(protoLineRect.x(), protoLineRect.y() + yOffset,
                   protoLineRect.x() + maxPlateWidth, protoLineRect.y() + yOffset);

    plateRect.moveTop(100);

    return QPair<QLine, QRect>(poleLine, plateRect);
}

QColor MainWindow::calculatePlateColor(int plateSize){
    int h = (360 - (AmountOfPlates - plateSize) * 360 / AmountOfPlates) % 360;
    return QColor::fromHsv(h, 255, 255);
}
