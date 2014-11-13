//
//  Star_menu.h
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#ifndef __PopStar__Star_menu__
#define __PopStar__Star_menu__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameMenu : public cocos2d::CCLayer
{
public:
    
    static cocos2d::CCScene* scene();

    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    void newGame_Callback(CCObject* pSender);
    
    void menuEnter();
    
    void menuCloseCallback(CCObject* pSender);


    
    CREATE_FUNC(GameMenu);
};

#endif /* defined(__PopStar__Star_menu__) */
