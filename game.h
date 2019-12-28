#pragma once
#include "map.h"

enum moveResult { M,X,N,K,F }; //遭遇猫、遭遇陷阱、遭遇奶酪、成功移动、非法移动

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
            return F;
        else if(m.m[x][y]=='m' || m.m[x][y]=='x')
        {
            p->subLife();
            p->reset();
            if(m.m[x][y]=='m')
                return M;
            else
                return X;
        }
        else if(m.m[x][y]=='n')
        {
            p->addLevel();
            p->set(x,y);
            m.m[x][y]='0';
            return N;
        }
        else
        {
            p->set(x,y);
            return K;
        }
    }

    gameMap& getMap() { return this->m; }
    player* getPlayer() { return this->m.p; }
};
