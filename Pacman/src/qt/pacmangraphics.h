#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H


#include <QApplication>
#include <QPushButton>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include <iostream>

#include <Jeu.h>

class PacmanGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PacmanGraphicsScene(QObject *parent = nullptr);

    const Jeu& jeu() const { return m_jeu; }
    int sprite_size() const { return m_sprite_size; }


public slots:
    void advance();

protected:
    int m_sprite_size;
    Jeu m_jeu;

    void keyPressEvent(QKeyEvent *keyEvent) override;

private:
};



class PacmanGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PacmanGraphicsView(QWidget *parent = nullptr);

    void drawBackground(QPainter *painter, const QRectF &rect) override;

protected:

private:
    QPixmap m_pix_mur;
    QPixmap m_pix_pastille;
    PacmanGraphicsScene m_pacScene;
    QTimer m_timer;
};


#endif // PACMANWINDOW_H
