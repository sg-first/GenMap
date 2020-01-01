#pragma once
#include "map.h"

enum moveResult { MeetCat,MeetTrap,MeetCheese,SuccessMove,FailMove }; //遭遇猫、遭遇陷阱、遭遇奶酪、成功移动、非法移动

class game
{
private:
    gameMap m;

public:
    moveResult movePlayer(int dx=0,int dy=0)
    {
        player* p=this->getPlayer();

        int x=p->x+dx;
        int y=p->y+dy;

        if(!m.canMove(p->x,p->y,dx,dy))
            return FailMove;
        else if(m.m[x][y]=='m' || m.m[x][y]=='x')
        {
            p->subLife();
            p->reset();
            if(m.m[x][y]=='m')
                return MeetCat;
            else
                return MeetTrap;
        }
        else if(m.m[x][y]=='n')
        {
            p->addLevel();
            p->set(x,y);
            m.m[x][y]='0';
            return MeetCheese;
        }
        else
        {
            p->set(x,y);
            return SuccessMove;
        }
    }

    gameMap& getMap() { return this->m; }
    player* getPlayer() { return this->m.p; }
};
