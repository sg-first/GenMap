//-----本文件是对于maincall.h中部分函数的实现部分-----
#include "maincall.h"

Item* itemM[gameMap::shape][gameMap::shape];
Item* mouseItem;

void draw(game* g, maincall* mc)
{
    gameMap& m=g->getMap();
    player* p=g->getPlayer();

    for(uint i=0;i<gameMap::shape;i++)
    {
        for(uint j=0;j<gameMap::shape;j++)
        {
            uint pixX=j*gameMap::shape;
            uint pixY=i*gameMap::shape;
            if(i==p->x && j==p->y)
                mouseItem=mc->AddPixmapItem(":/mouse.jpg",pixX,pixY);
            else if(m.m[i][j]=='1')
                itemM[i][j]=mc->AddPixmapItem(":/wall.jpg",pixX,pixY);
            else if(m.m[i][j]=='m')
                itemM[i][j]=mc->AddPixmapItem(":/cat.jpg",pixX,pixY);
            else if(m.m[i][j]=='n')
                itemM[i][j]=mc->AddPixmapItem(":/cheese.jpg",pixX,pixY);
        }
    }
    mc->updateStat(p);
    //操作按钮
    mc->AddPixmapItem(":/wall.jpg",1000,670,"shang");
    mc->AddPixmapItem(":/wall.jpg",1000,830,"xia");
    mc->AddPixmapItem(":/wall.jpg",960,760,"zuo");
    mc->AddPixmapItem(":/wall.jpg",1050,760,"you");
}

void prompt(moveResult r,maincall* mc)
{
    game* g=mc->g;
    player* p=g->getPlayer();

    auto updateMouse=[=]() {
        mc->updateStat(p);
        mc->RemoveItem(mouseItem);
        mouseItem=mc->AddPixmapItem(":/mouse.jpg",p->y*gameMap::shape,p->x*gameMap::shape);
    };

    if(r==K)
        updateMouse();
    else if(r==M)
    {
        mc->setInfo("Meet Cat");
        updateMouse();
    }
    else if(r==X)
    {
        mc->setInfo("Meet Trap");
        updateMouse();
    }
    else if(r==N)
    {
        mc->setInfo("Get Cheese");
        mc->RemoveItem(itemM[p->x][p->y]); //p的新位置就是原来奶酪位置
        updateMouse();
    }
    else if(r==F)
        mc->setInfo("Move Failed");

    if(p->isDie())
        mc->AddTextItem("You are Lose","Times New Roman",80,RGBColor(255,0,0),140,400);
    if(p->isWin())
        mc->AddTextItem("You are Win","Times New Roman",80,RGBColor(255,0,0),140,400);
}

void maincall::shang()
{
    moveResult r=g->movePlayer(-1);
    prompt(r,this);
}

void maincall::xia()
{
    moveResult r=g->movePlayer(1);
    prompt(r,this);
}

void maincall::zuo()
{
    moveResult r=g->movePlayer(0,-1);
    prompt(r,this);
}

void maincall::you()
{
    moveResult r=g->movePlayer(0,1);
    prompt(r,this);
}

void maincall::StartGame()//入口函数
{
    Rand::initRand();
    this->g=new game;
    draw(g,this);
}
