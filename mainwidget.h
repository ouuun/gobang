#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "Piece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
     ~MainWidget();


    virtual void paintEvent(QPaintEvent *);//绘画棋盘
    virtual void mouseReleaseEvent(QMouseEvent *ev); // 鼠标释放事件


    void paintPices(QPainter &painter); //绘制棋子
    void updatePices(); //更新棋子pointer

public slots:
    void isShowStep();

private:
    Ui::MainWidget *ui;

    int m_origin;//原点
    int m_interval;//间隔
    int m_pieceR; //棋子半径
    int m_step = 1; //当前步数
    Piece::m_emcolor m_color = Piece::m_emcolor::black;//当前棋子颜色
    bool m_showStep = true;//是否显示步数
    QList<Piece*> *m_pieces;//以下棋子
};
#endif // MAINWIDGET_H
