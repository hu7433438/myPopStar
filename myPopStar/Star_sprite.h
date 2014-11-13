//
//  Star_sprite.h
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#ifndef __PopStar__Star_sprite__
#define __PopStar__Star_sprite__

#include <iostream>
#include "cocos2d.h"
#include "Star_datehandle.h"

using namespace cocos2d;

class StarSprite : public CCSprite
{
public:
    //星星种类
    int type;
    
    bool isChoose;
    
    //星星在棋盘中的位置
    
    StarProperty s_property;
    
    //初始化星星 
    void initWith( StarProperty _p, int _type );
    
    //选择动作
    void Star_selected();
    
    //停止动作
    void Star_stop();
    
    //消失动作
    void Star_disappear();
    
    //设置精灵位置。
    void Star_pos(StarProperty new_pro);
    
    virtual bool init( void );
    virtual void draw( void );
    
    CREATE_FUNC(StarSprite);
};


#endif /* defined(__PopStar__Star_sprite__) */
