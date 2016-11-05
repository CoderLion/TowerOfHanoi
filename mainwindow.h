#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPainter>
#include <QWidget>
#include <QKeyEvent>
#include <QRect>
#include <QLine>
#include <QPair>
#include <QColor>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    struct Focus{
        int pole;
        int plate;
    };

private:
    static const int left = 0, middle = 1, right = 2;
    static const int AmountOfPlates = 6;

    int maxPlateWidth, minPlateWidth, plateHeight, poleMargin;

    struct Pole{
        int plates[AmountOfPlates];
        int height;
    };



    Pole pole[3];
    Focus focus;

    QColor calculatePlateColor(int plateSize);
    QRect calculatePlateRect(int poleLocation, int plateLocation, int plateSize);
    QPair<QLine, QRect> calculateFocusUI();

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);

};

#endif // MAINWINDOW_H
