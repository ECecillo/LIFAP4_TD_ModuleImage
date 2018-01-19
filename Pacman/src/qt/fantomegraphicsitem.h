#ifndef FANTOMEGRAPHICSITEM_H
#define FANTOMEGRAPHICSITEM_H


#include <QColor>
#include <QGraphicsItem>

class FantomeGraphicsItem : public QGraphicsItem
{
public:
    FantomeGraphicsItem(int fanId, int sprite_size);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    int fantomeId;
    QPixmap m_pix_fan;
};


class PacmanGraphicsItem : public QGraphicsItem
{
public:
    PacmanGraphicsItem(int sprite_size);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
protected:
    QPixmap m_pix_pac;
};

#endif // FANTOMEGRAPHICSITEM_H
