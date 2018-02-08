/*
# Installer Qt5
# Ajouter dans le path le chemin vers bin et vers tools/mingw/bin (voir le chemin exacte suivant la version)
# ouvrir un bash
# qmake
# make
# ./release/pacman_qt
*/


#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include "pacmangraphics.h"

using namespace std;


#if 0

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    PacmanGraphicsView view;
    view.show();

    return app.exec();
}

#else

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow qmw;

    PacmanGraphicsView view(&qmw);
    qmw.setCentralWidget(&view);

    QMenu *menuFichier = qmw.menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", &qmw);
    menuFichier->addAction(actionQuitter);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    actionQuitter->setIcon(QIcon(QApplication::applicationDirPath() + "/data/quitter.png"));

    QToolBar *toolBarFichier  = qmw.addToolBar("Fichier");
    toolBarFichier->addAction(actionQuitter);

    QObject::connect(actionQuitter, SIGNAL(triggered()), &app, SLOT(quit()));

    //view.show();
    qmw.show();

    return app.exec();
}
#endif

