//
//  Star_layer.h
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#ifndef __PopStar__Star_layer__
#define __PopStar__Star_layer__

#include <iostream>
#include "cocos2d.h"
#include "Star_sprite.h"
#include "Star_datehandle.h"
#include "GameMarkScene.h"

using namespace cocos2d;
class StarDataHandle;
class StarSprite;

class StarLayer :public cocos2d::CCLayer
{
    
    //游戏分数
    GameMark *gamemark;
    //棋盘状态
    StarDataHandle *dataHandle;
    
    //当前选中棋子
    StarSprite * currentSelectSprite;
    
    //作为所有已经加入到棋盘中棋子的父结点
    CCNode * starsSpriteParent;
    
    //大小为图片大小的两倍。  （格子的长宽）
    float width;
    float height;
    
    //网格的长宽个数
    int wid_num;
    int hei_num;
    
    //格子总个数
    int count_num;
    
    //是否在重新排列过程，若是，则不可移动
    bool can_click;
    
    //是否选中
    bool  isClick;
    
    //选中的类型
    int preType;
    
    //选中的分数
    int preMark;
    
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void onEnterTransitionDidFinish(void);
    
    //网格划线
    virtual void draw(void);
    
    //初始化游戏
    void SL_StarGame();
    
    //触屏逻辑函数
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
    //获取当前星星精灵
    StarSprite* SL_getCurrentSelectLinesSprite(const StarProperty &_pro);
    
    //遍历选中不要的精灵
    void  SL_clearupUnusedSpriteAd();
    
    //真正清除。
    void SL_moveUnusedStar();
    
    //恢复选中前状态
    void SL_resume();
    
    //检查是否可以向下移动星星
    void SL_downcheck_move();
    
    //检查是否可以向右移动星星
    void SL_leftcheck_move();
    
    //检查完后移动精灵
    void SL_aftercheck_move( int after_move, int before_move );
    
    //改变是否可触摸
    void SL_can_touch();
    
    //检查游戏是否结束
    void SL_is_gameover();
    
    void GameOver();
    
    //游戏结束逻辑
    void menuBackCallback();
    
    CREATE_FUNC(StarLayer);
};
#endif /* defined(__PopStar__Star_layer__) */
