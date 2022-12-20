#include "piece.h"
#include <qDebug>

Piece::Piece(){

}

Piece::~Piece(){
    if(m_point!=nullptr){
        delete m_point;
        m_point = nullptr;
    }
}

Piece::Piece(QPoint *p,m_emcolor color,int step,int x,int y){
    this->m_point = p;
    this->m_color = color;
    this->m_step = step;
    this->m_x = x;
    this->m_y = y;
}

void Piece::test() const{
//    qDebug()<<"x:"<<m_x<<",y:"<<m_y<<",point:"<<m_point;
    qDebug() << "Piece(" << this->m_x << ", " << this->m_y
          << ", "<< this->m_color << ", "<< this->m_step
          << ", "<< *this->m_point
          << ")";
}

