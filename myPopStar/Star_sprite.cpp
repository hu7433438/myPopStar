//
//  Star_sprite.cpp
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "Star_sprite.h"

bool StarSprite::init( void )
{
    if ( !CCSprite::init())
    {
        return false;
    }
    
    return true;
}

void StarSprite::draw( void )
{
    CCSprite::draw();
}

//初始化棋子状态
void StarSprite::initWith( StarProperty _p, int _type )
{
    //设置星星坐标
    s_property = _p;
    
    //设置星星状态
    type = _type;
    
    isChoose = false;
    
    //背景图片
    std::string background_pic;
    
    switch (_type)
    {
        case yellow_star:
            background_pic = "orange.png";
            break;
        case blue_star:
            background_pic = "blue.png";
            break;
        case red_star:
            background_pic = "red.png";
            break;
        case green_star:
            background_pic = "green.png";
            break;
        case pink_star:
            background_pic = "purple.png";
            break;
            
        default:
            break;
    }
    
    this->initWithFile(background_pic.c_str());
    this->setScale(1.3);
}


//棋子被选中时候执行的动作。
void StarSprite::Star_selected()
{
    this->stopAllActions();
    
    CCScaleTo * scaleTo = CCScaleTo::create(0.5, 1.2);
    CCScaleTo * scaleBack = CCScaleTo::create(0.5, 2);
    CCSequence * sequence = CCSequence::create(scaleTo,scaleBack,NULL);
    CCRepeatForever * repeateF = CCRepeatForever::create(sequence);
    
    this->getActionManager()->addAction(repeateF, this, false);
}


//停止星星动作
void StarSprite::Star_stop()
{
    this->setScale(1.3);
    this->stopAllActions();
}

void StarSprite::Star_disappear()
{
    this->removeFromParent();
}

//设置精灵位置。
void StarSprite::Star_pos(StarProperty new_pro)
{
    s_property = new_pro;
}