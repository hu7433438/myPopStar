//
//  Star_menu.cpp
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "Star_menu.h"
#include "Star_layer.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameMenu::scene()
{
    CCScene *scene = CCScene::create();
    
    GameMenu *layer = GameMenu::create();
    
    scene->addChild(layer);
    
    return scene;
}

void GameMenu::onEnter()
{
    CCLayer::onEnter();
}

void GameMenu::onExit()
{
    CCLayer::onExit();
}

bool GameMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //获取屏幕大小
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //初始化背景
    CCSprite *bg = CCSprite::create("Default-568h@2x.png");
    bg->setPosition(ccp(size.width/2, size.height/2));

    this->addChild(bg,0);
    
    
    //初始化k开始游戏按钮
    CCMenuItemImage *newGame_item = CCMenuItemImage::create("play_zh.png", "play_zh.png", this, menu_selector(GameMenu::newGame_Callback));
    newGame_item->setPosition(ccp(size.width/2, size.height/4));

    CCMenu *mainmenu = CCMenu::create(newGame_item, NULL);
    mainmenu->setPosition(ccp(0, 0));
    this->addChild(mainmenu,1,1);
    

    
    return true;
}

void GameMenu::menuEnter()
{
    //菜单进入后，菜单项点击有效
    CCNode* mainmenu = this->getChildByTag(1);
    CCArray* temp = mainmenu->getChildren();
    for(int i = 0;i < temp->count();i ++)
        ((CCMenuItemImage *)temp->objectAtIndex(i))->setEnabled(true);
}

void GameMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//开始游戏
void GameMenu::newGame_Callback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(StarLayer::scene());
}

