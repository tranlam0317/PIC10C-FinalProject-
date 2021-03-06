#include "beam.h"
#include "monster.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

extern Game * game;

beam::beam(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{    //draw graphics
    setPixmap(QPixmap(":/images/Laser beam.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //beam moves every 50 milisec
    timer->start(50);
}

void beam::move(){
     //if beam collides w/ enemy: destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(monster)) {
            //increase the score
            game->score->increase();
            
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }
    }
   
    //move beam up
    setPos(x(),y() - 10);
   
    //delete beam if it does out of view
    if(pos().y() + rect().height() < 0){
        scene()->removeItem(this);
        delete this;
    }
   
}
