#ifndef PIECE_H
#define PIECE_H

#include <QPoint>



class Piece
{
public:
    enum m_emcolor{black,white};

    Piece();
    Piece(QPoint *p,m_emcolor color,int step,int x,int y);
    ~Piece();


    void test() const;

    QDebug operator<<(const Piece &p);


public:
    int m_x;
    int m_y;
    int m_step;
    QPoint *m_point;
    m_emcolor m_color;
};

#endif // PIECE_H
