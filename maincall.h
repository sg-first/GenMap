//-----本文件是游戏中的一些函数调用的实现，引擎的三层封装-----
#pragma once
#include "library.h"
#include "game.h"

class maincall : public library
{
Q_OBJECT
public:
    //入口函数
    void StartGame();
    //在此继续添加
    game* g;
    Item* promptInfo=nullptr;
    RGBColor black=RGBColor(0,0,0);
    void setInfo(String info)
    {
        this->RemoveItem(this->promptInfo);
        this->promptInfo=this->AddTextItem(info,"Times New Roman",14,this->black,960,600);
    }

    Item* stat[2]={nullptr,nullptr};
    void updateStat(player* p)
    {
        this->RemoveItem(this->stat[0]);
        this->RemoveItem(this->stat[1]);
        this->stat[0]=this->AddTextItem("level:"+String::number(p->getLevel()),
                                      "Times New Roman",20,this->black,970,190);
        this->stat[1]=this->AddTextItem("life:"+String::number(p->getLife()),
                                      "Times New Roman",20,this->black,970,230);
    }
	
public slots:
    //此处容纳事件处理与线程函数
    void shang();
    void xia();
    void zuo();
    void you();
};
