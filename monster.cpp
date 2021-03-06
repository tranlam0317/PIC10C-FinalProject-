#include "monster.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include "game.h"

extern Game * game; 

monster::monster(QGraphicsItem *parent) QObject(), QGraphicsPixmapItem(parent){
     //set random position 
    int random_number = rand() % 700; 
    setPos(random_number,0);
    
    //draw the enemy
    setPixmap(QPixmap(":/images/Monster.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //beam moves every 50 milisec
    timer->start(50);
}

void monster::move(){
    //move monster down
    setPos(x(),y() + 5);

    //delete beam if it does out of view
    if(pos().y() > 600){
        //decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
    }

}
