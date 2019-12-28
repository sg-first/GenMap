#pragma once
#include <tuple>
#include <list>
#include <vector>
#include "help.h"
using namespace std;

typedef tuple<uint,uint> pos;

class player
{
private:
    uint level=0;
    uint life=10;
    uint startX;
    uint startY;
    uint maxLevel;

public:
    uint x;
    uint y;

    void subLife()
    {
        if(this->life!=0)
            this->life--;
    }

    bool isDie()
    {
        return this->life==0;
    }

    bool isWin()
    {
        return this->level==this->maxLevel;
    }

    void addLevel() { this->level++; }
    uint getLevel() { return this->level; }
    uint getLife() { return this->life; }

    void reset()
    {
        this->x=this->startX;
        this->y=this->startY;
    }

    void set(uint x,uint y)
    {
        this->x=x;
        this->y=y;
    }

    player(uint startX,uint startY,uint maxLevel) : startX(startX), startY(startY), maxLevel(maxLevel)
    {
        this->reset();
    }
};


class gameMap
{
private:
    const static uint genCheese=5;
    const static uint avgMoveStep=20;
    const static uint extraCheeseProb=5;

    pos genPath()
    {
        uint startX=Rand::randRange(shape);
        uint startY=Rand::randRange(shape);
        this->m[startX][startY]='p';
        pos startPos=make_tuple(startX,startY);

        auto isRepeat=[=](pos p, list<pos> path) {
            for(pos pi : path)
            {
                if(pi==p)
                    return true;
            }
            return false;
        };

        auto getCanMoveNextPos=[=](int nowX,int nowY, list<pos> path) {
            vector<pos> result;
            pos p1=make_tuple(nowX+1,nowY);
            pos p2=make_tuple(nowX-1,nowY);
            pos p3=make_tuple(nowX,nowY+1);
            pos p4=make_tuple(nowX,nowY-1);
            if(canMove(nowX,nowY,1) && !isRepeat(p1,path) && this->m[nowX+1][nowY]!='n')
                result.push_back(p1);
            if(canMove(nowX,nowY,-1) && !isRepeat(p2,path) && this->m[nowX-1][nowY]!='n')
                result.push_back(p2);
            if(canMove(nowX,nowY,0,1) && !isRepeat(p3,path) && this->m[nowX][nowY+1]!='n')
                result.push_back(p3);
            if(canMove(nowX,nowY,0,-1) && !isRepeat(p4,path) && this->m[nowX][nowY-1]!='n')
                result.push_back(p4);
            return result;
        };

        for(uint _i=0;_i<genCheese;_i++)
        {
            uint nowX=startX;
            uint nowY=startY;
            list<pos> path;
            path.push_back(startPos);
            do
            {
                vector<pos> allNextPos=getCanMoveNextPos(nowX,nowY,path);
                if(allNextPos.empty())
                    break;
                else
                {
                    uint selectSub=Rand::randRange(allNextPos.size()); //随机选一个可以走的作为路径下个节点
                    path.push_back(allNextPos[selectSub]);
                    tie(nowX,nowY)=allNextPos[selectSub];
                    this->m[nowX][nowY]='0';
                }
            }
            while(Rand::randRange(avgMoveStep)!=0);
            this->m[nowX][nowY]='n'; //路径终点放置奶酪
        }

        return startPos;
    }

    void genOther()
    {
        auto isNotInit=[this](uint i,uint j) {
            return this->m[i][j]=='-';
        };
        //生成剩余部分
        for(uint i=0;i<shape;i++)
        {
            for(uint j=0;j<shape;j++)
            {
                if(isNotInit(i,j))
                {
                    if(Rand::rand01()) //非规划路径有一半可能是致死物体
                    {
                        if(Rand::rand01()) //猫
                            this->m[i][j]='m';
                        else //陷阱
                            this->m[i][j]='x';
                    }
                    else //另一半是剩下的
                    {
                        if(Rand::rand01()) //另一半里一半是墙
                            this->m[i][j]='1';
                        else
                        {
                            if(Rand::randRange(extraCheeseProb)==0)
                                this->m[i][j]='n'; //奶酪
                            else
                                this->m[i][j]='0'; //空地
                        }
                    }
                }
            }
        }
    }

    void initM()
    {
        for(uint i=0;i<shape;i++)
            for(uint j=0;j<shape;j++)
                this->m[i][j]='-';
    }

public:
    const static uint shape=31;
    char m[shape][shape];
    player *p;

    bool canMove(int oldx, int oldy, int dx=0,int dy=0)
    {
        int x=oldx+dx;
        int y=oldy+dy;
        return abs(dx)<=1 && abs(dy)<=1 && //每次只能走一步
                m[x][y]!='1' && //不能走墙里
                x>=0&&x<gameMap::shape && y>=0&&y<gameMap::shape; //不能超范围
    }

    gameMap()
    {
        this->initM();
        uint startX,startY;
        tie(startX,startY)=this->genPath();
        this->p=new player(startX,startY,genCheese);
        this->genOther();
        this->m[startX][startY]='0'; //p换0
    }

    ~gameMap() { delete p; }
};

