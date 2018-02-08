#include <fantomegraphicsitem.h>

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <pacmangraphics.h>
#include <iostream>

using namespace std;

///////////////////////// FANTOME ITEM  ///
FantomeGraphicsItem::FantomeGraphicsItem(int fanId, int sprite_size)
    : fantomeId(fanId),
    m_pix_fan( QApplication::applicationDirPath() + "/data/fantome.png")
{
    m_pix_fan = m_pix_fan.scaled( sprite_size, sprite_size );
}

QRectF FantomeGraphicsItem::boundingRect() const
{
    const PacmanGraphicsScene* sc = static_cast<PacmanGraphicsScene*>(scene());
    int x,y;
    x = sc->jeu().getConstFantome().getX();
    y = sc->jeu().getConstFantome().getY();
    return QRectF(x*m_pix_fan.width(), y*m_pix_fan.height(), m_pix_fan.width(), m_pix_fan.height());
}


void FantomeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    const PacmanGraphicsScene* sc = static_cast<PacmanGraphicsScene*>(scene());
    int x,y;
    x = sc->jeu().getConstFantome().getX();
    y = sc->jeu().getConstFantome().getY();
    painter->drawPixmap( QRect(x*m_pix_fan.width(), y*m_pix_fan.height(), m_pix_fan.width(), m_pix_fan.height())
                         , m_pix_fan
                         , QRect(0,0,m_pix_fan.width(),m_pix_fan.height())
                         );
}



///////////////////////// PACMAN ITEM  ///
PacmanGraphicsItem::PacmanGraphicsItem(int sprite_size) :
    m_pix_pac( QApplication::applicationDirPath() + "/data/pacman.png")
{
    m_pix_pac = m_pix_pac.scaled( sprite_size, sprite_size );
}

QRectF PacmanGraphicsItem::boundingRect() const
{
    const PacmanGraphicsScene* sc = static_cast<PacmanGraphicsScene*>(scene());
    int x,y;
    x = sc->jeu().getConstPacman().getX();
    y = sc->jeu().getConstPacman().getY();
    return QRectF(x*m_pix_pac.width(), y*m_pix_pac.height(), m_pix_pac.width(), m_pix_pac.height());
}


void PacmanGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    const PacmanGraphicsScene* sc = static_cast<PacmanGraphicsScene*>(scene());
    int x,y;
    x = sc->jeu().getConstPacman().getX();
    y = sc->jeu().getConstPacman().getY();
    painter->drawPixmap( QRect(x*m_pix_pac.width(), y*m_pix_pac.height(), m_pix_pac.width(), m_pix_pac.height())
                         , m_pix_pac
                         , QRect(0,0,m_pix_pac.width(),m_pix_pac.height())
                         );
}
