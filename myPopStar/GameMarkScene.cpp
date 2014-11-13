//
//  GameMarkScene.cpp
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "GameMarkScene.h"
GameMark::GameMark(void)
{
}

GameMark::~GameMark(void)
{
}
void GameMark::onExit()
{
    CCNode::onExit();
}
void GameMark::onEnter()
{
    CCNode::onEnter();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    bits = CCArray::createWithCapacity(5);
    //分数标题
    CCSprite *title = CCSprite::create("score.png");
    title->setPosition(ccp(size.width/2 + 40,size.height - 85));
    title->setScale(1.5);
    addChild(title);
    //数字按位设置
    for(int i = 0;i < 5;i ++){
        CCSprite * shu = CCSprite::create("shu.png");
        ui = shu->getTexture();
        shu->setScale(1.5);
        shu->setTextureRect(CCRectMake(234,0,26,31));
        shu->setPosition(ccp(size.width - 30 - i * 30,size.height - 85));
        bits->addObject(shu);
        addChild(shu);
    }
    bits->retain();
    mark = 0;
}
void GameMark::addnumber(int var){
    //分数，按位设置数字
    mark += var;
    int temp = mark % 10;
    if(temp > 0){
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(0))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));
    }else{
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(0))->setTextureRect(CCRectMake(234,0,26,31));
    }
    temp = (mark % 100) / 10;
    if(temp > 0){
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(1))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));
        
    }else{
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(1))->setTextureRect(CCRectMake(234,0,26,31));
    }
    temp = (mark % 1000) / 100;
    if(temp > 0){
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(2))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));
        
    }else{
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(2))->setTextureRect(CCRectMake(234,0,26,31));
    }
    temp = (mark % 10000) / 1000;
    if(temp > 0){
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(3))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));
        
    }else{
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(3))->setTextureRect(CCRectMake(234,0,26,31));
    }
    temp = mark / 10000;
    if(temp > 0){
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(4))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));
        
    }else{
        ((CCSprite *)bits->objectAtIndex(0))->setTexture(ui);
        ((CCSprite *)bits->objectAtIndex(4))->setTextureRect(CCRectMake(234,0,26,31));
    }
    
    char inf[256];
    if ( var > 0)
    {
        int score = var;
        sprintf(inf, "+%d",score);
    }
    if ( var < 0)
    {
        int score = -var;
        sprintf(inf, "-%d",score);
    }
    
    mark_label = CCLabelTTF::create(inf, "Marker Felt", 60);
    mark_label->setPosition(ccp(550,830));
    this->addChild(mark_label);
    
    CCActionInterval *fadeout_action = CCFadeOut::create(1.0f);
    
    CCActionInterval *moveto_action = CCMoveTo::create(1.0f, ccp(mark_label->getPositionX()+20, mark_label->getPositionY()+40));
    CCActionInterval *total_action = CCSpawn::create(fadeout_action,moveto_action,NULL);
    
    CCFiniteTimeAction *func_action = CCSequence::create(total_action,CCCallFunc::create(this, callfunc_selector(GameMark::remove_score)),NULL);
    mark_label->runAction(func_action);
}


//删除该分数图标。
void GameMark::remove_score( CCLabelTTF *pSender )
{
    this->removeChild(mark_label);
}

//返回分数
int GameMark::return_mark()
{
    return mark;
}
