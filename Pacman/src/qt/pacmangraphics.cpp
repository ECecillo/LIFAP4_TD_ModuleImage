#include "pacmangraphics.h"
#include <fantomegraphicsitem.h>
#include <iostream>

using namespace std;


PacmanGraphicsScene::PacmanGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_sprite_size = 32;
    setSceneRect(0, 0, m_jeu.getConstTerrain().getDimX()*m_sprite_size, m_jeu.getConstTerrain().getDimY()*m_sprite_size);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    PacmanGraphicsItem *pac = new PacmanGraphicsItem(m_sprite_size);
    pac->setPos( m_jeu.getConstPacman().getX(),m_jeu.getConstPacman().getY());
    addItem(pac);

    for (int i = 0; i <m_jeu.getNombreDeFantome(); ++i)
    {
        FantomeGraphicsItem *fan = new FantomeGraphicsItem(i,m_sprite_size);
        fan->setPos( m_jeu.getConstFantome().getX(),m_jeu.getConstFantome().getY());
        addItem(fan);
    }
}


void PacmanGraphicsScene::advance()
{
    m_jeu.actionsAutomatiques();
    update();
    invalidate( QRectF(0,0,m_sprite_size*m_jeu.getConstTerrain().getDimX()+64, m_sprite_size*m_jeu.getConstTerrain().getDimY()+64) );
}



void PacmanGraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
{
    //cout<<"key"<<endl;
    switch(keyEvent->key())
    {
        case Qt::Key_Left:
                m_jeu.actionClavier('g');
                cout<<"g"<<endl;
                break;
        case Qt::Key_Right:
                m_jeu.actionClavier('d');
                cout<<"d"<<endl;
                break;
        case Qt::Key_Up:
                m_jeu.actionClavier('b');
                cout<<"h"<<endl;
                break;
        case Qt::Key_Down:
                m_jeu.actionClavier('h');
                cout<<"b"<<endl;
                break;
    }
    update();
    invalidate( QRectF(0,0,m_sprite_size*m_jeu.getConstTerrain().getDimX()+64, m_sprite_size*m_jeu.getConstTerrain().getDimY()+64) );
}




////////////////////// PacmanGraphicsView

PacmanGraphicsView::PacmanGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_pix_mur( QApplication::applicationDirPath() + "/data/mur.png"),
    m_pix_pastille( QApplication::applicationDirPath() + "/data/pastille.png")
{
    setScene(&m_pacScene);

    m_pix_mur = m_pix_mur.scaled( m_pacScene.sprite_size(), m_pacScene.sprite_size() );
    m_pix_pastille = m_pix_pastille.scaled( m_pacScene.sprite_size(), m_pacScene.sprite_size() );

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Pacman"));
    //view.resize( scene.width()+64, scene.height()+64);
    //    cout<<"image mur: "<<m_pix_mur.width()<<" "<<m_pix_mur.height()<<endl;
    //    cout<<"image pastille: "<<m_pix_pastille.width()<<" "<<m_pix_pastille.height()<<endl;

    QObject::connect(&m_timer, SIGNAL(timeout()), &m_pacScene, SLOT(advance()));
    m_timer.start(1000 / 15);
}


void PacmanGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    int i,j;
    const PacmanGraphicsScene* sc = static_cast<PacmanGraphicsScene*>(scene());
    const Jeu& jeu = sc->jeu();

    painter->setBrush(Qt::white);
    painter->drawRect(0,0,sc->sprite_size()*jeu.getConstTerrain().getDimX(), sc->sprite_size()*jeu.getConstTerrain().getDimY() );
    for(i=0;i<jeu.getConstTerrain().getDimX();++i)
        for(j=0;j<jeu.getConstTerrain().getDimY();++j)
        {
            if (jeu.getConstTerrain().getXY(i,j)=='#')
                painter->drawPixmap( QRect(i*sc->sprite_size(), j*sc->sprite_size(), sc->sprite_size(), sc->sprite_size())
                                     , m_pix_mur
                                     , QRect(0,0,sc->sprite_size(),sc->sprite_size())
                                     );
            else
            if (jeu.getConstTerrain().getXY(i,j)=='.')
                painter->drawPixmap( QRect(i*sc->sprite_size(), j*sc->sprite_size(), sc->sprite_size(), sc->sprite_size())
                                     , m_pix_pastille
                                     , QRect(0,0,sc->sprite_size(),sc->sprite_size())
                                     );


        }
    //cout<<"view : drawBackground"<<endl;
}
