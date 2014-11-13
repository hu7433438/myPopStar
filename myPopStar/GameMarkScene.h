//
//  GameMarkScene.h
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#ifndef __Chowhound__GameMarkScene__
#define __Chowhound__GameMarkScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class GameMark : public CCNode
{
public:
    GameMark(void);
    virtual ~GameMark(void);
    virtual void onEnter();
    virtual void onExit();
    CCArray *bits;
    int mark;
    void addnumber(int var);
    CCTexture2D* ui;
    
    CCLabelTTF *mark_label;
    
    //删除该分数图标。
    void remove_score( CCLabelTTF *pSender );
    
    //返回分数
    int return_mark();
};

#endif /* defined(__Chowhound__GameMarkScene__) */
