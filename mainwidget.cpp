#include "mainwidget.h"
#include "./ui_mainwidget.h"

#include <QDebug>


MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(ui->btnShowStep,SIGNAL(clicked()),this,SLOT(isShowStep()));
    this->m_pieces = new QList<Piece*>;
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_pieces;
}

void MainWidget::isShowStep(){
    this->m_showStep = !this->m_showStep;
    update();
}


void MainWidget::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);  //抗锯齿

    //自适应比例
    int scale = qMin(this->width(),this->height());

    m_origin = 50;
    m_interval = (scale-m_origin*2)/15;
    m_pieceR = m_interval/2;
    int size = 15*m_interval;


    for(int i = 0; i <= 15; i++)
        painter.drawLine(m_origin+i*m_interval,m_origin,
                         m_origin+i*m_interval,m_origin+size);

    for(int i = 0; i <= 15; i++)
        painter.drawLine(m_origin,m_origin+i*m_interval,
                         m_origin+size,m_origin+i*m_interval);

    updatePices();
    paintPices(painter);

}

void MainWidget::paintPices(QPainter &painter){
    if(m_pieces->empty()) return;
    for(Piece *p:*m_pieces){
        painter.setPen(Qt::black); // 设置画笔颜色

        if(p->m_color==Piece::m_emcolor::black) painter.setBrush(Qt::black);// 设置画刷颜色
        else painter.setBrush(Qt::white);

        painter.drawEllipse(*p->m_point,m_pieceR,m_pieceR);  //绘制棋子

        if(m_showStep){
//            qDebug()<<this->m_step;
            if(p->m_color==Piece::m_emcolor::black) painter.setPen(Qt::white);
            else painter.setPen(Qt::black);
            painter.setFont(QFont("FangSong", m_interval * 5 / 12, 2700));
            QRect rect(QPoint(p->m_point->x()-m_pieceR/2,p->m_point->y()-m_pieceR/2),QSize(m_pieceR,m_pieceR));
            painter.drawText(rect, QString::number(p->m_step), QTextOption(Qt::AlignCenter));
        }
    }
}

void MainWidget::updatePices(){
    if(m_pieces->empty()) return;
    for(Piece *p:*m_pieces){
        int qx = p->m_x*m_interval+m_origin;
        int qy = p->m_y*m_interval+m_origin;
        p->m_point->setX(qx);
        p->m_point->setY(qy);
    }
}


void MainWidget::mouseReleaseEvent(QMouseEvent *ev)
{

    QPoint pt= ev->pos() ; //获取当前鼠标位置坐标

    int x = pt.x();
    int y = pt.y();
    float transX = qRound((x-m_origin)/(m_interval+0.0));
    float transY = qRound((y-m_origin)/(m_interval+0.0));
    int qx = transX*m_interval+m_origin;
    int qy = transY*m_interval+m_origin;


    if(transX<0||transX>15||transY<0||transY>15) return;


    QPoint *point = new QPoint(qx,qy);
    Piece *p = new Piece(point,this->m_color,m_step++,transX,transY);
    m_pieces->append(p);

    update();

    if(this->m_step%2==1) this->m_color = Piece::m_emcolor::black;
    else this->m_color = Piece::m_emcolor::white;
}

