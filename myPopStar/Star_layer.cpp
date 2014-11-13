//
//  Star_layer.cpp
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

//isExisted判断是否已经存在记录
//maxMark_total 总的最高分
//maxMark_first 第一关最高分
//maxMark_first_now 当前分数
//maxMark_second 第二关最高分
//maxMark_second_now 当前分数
#include "Star_layer.h"
#include "Star_menu.h"

using namespace cocos2d;

CCScene* StarLayer::scene()
{
    CCScene *scene = CCScene::create();
    
    StarLayer *layer = StarLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

void StarLayer::onEnter()
{
    CCLayer::onEnter();
    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);
}

void StarLayer::onExit()
{
    CCLayer::onExit();
}

void StarLayer::onEnterTransitionDidFinish(void)
{
    CCLayer::onEnterTransitionDidFinish();
}

// 网格划线，利用格子长宽
void StarLayer::draw(void)
{
    CCLayer::draw();
    // 横线
    for (int x=0; x<=10; x++)
    {
        CCPoint pos1 = ccp( 0, height*x );
        CCPoint pos2 = ccp( wid_num*width, height*x );
        ccDrawLine(pos1, pos2);
    }

    //竖线
    for (int y=0; y<=10; y++)
    {
        CCPoint pos1 = ccp( width*y, 0 );
        CCPoint pos2 = ccp( width*y, hei_num*height );
        ccDrawLine(pos1, pos2);
    }
    
}

bool StarLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->SL_StarGame();
    return true;
}


//初始化游戏
void StarLayer::SL_StarGame()
{
    
    //数据存储
    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isExisted"))
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey("isExisted", true);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("maxMark_first", 0);
    }
    
    char inf_c[256];
    sprintf(inf_c, "最高分：%d",CCUserDefault::sharedUserDefault()->getIntegerForKey("maxMark_first"));
    CCLabelTTF *mark_ = CCLabelTTF::create(inf_c, "Marker Felt", 50);
    mark_->setPosition(ccp(320,780));
    this->addChild(mark_);
    
    
    if (dataHandle)
    {
        delete dataHandle;
        dataHandle = NULL;
    }
    
    //定义声明棋盘对象
    dataHandle = new StarDataHandle();
    
    //贴图
    CCTexture2D *textture = CCTextureCache::sharedTextureCache()->addImage("blue.png");
    
    //设置格子长宽
    width = textture->getPixelsWide() * 2;
    height = textture->getPixelsHigh() * 2;

    //设置格子个数
    wid_num = 10;
    hei_num = 10;
    
    count_num = wid_num * hei_num;
    
    //初始化棋盘
    dataHandle->initDateHandleWith(wid_num, hei_num, width, height);
    
    //作为所有已经加入到棋盘中棋子的父结点
    starsSpriteParent = CCNode::create();
    this->addChild(starsSpriteParent);
    starsSpriteParent->setAnchorPoint(ccp(0,0));
    starsSpriteParent->setPosition(0, 0);
    
    //添加棋子。
    for (int i = 0; i<count_num; i++)
    {
        int _type = arc4random() % 5 + 1;
        
        StarSprite *_sprite = StarSprite::create();
        _sprite->initWith( dataHandle->SD_convertIndexToLinesProperty(i), _type );
        _sprite->setPosition(dataHandle->SD_getPositionAtIndex(i));
        
        starsSpriteParent->addChild(_sprite);
        dataHandle->SD_resetStateAtIndex(i, _type);
    }
    
    //初始化可移动
    can_click = true;
    
    //被选中
    isClick = false;
    
    preMark = 0;
    
    preType = 0;

    
        
    //分数
    gamemark = new GameMark();
    this->addChild(gamemark);
    
    
}

//获取当前星星
StarSprite* StarLayer::SL_getCurrentSelectLinesSprite(const StarProperty &_pro)
{
    CCObject * _obj = NULL;
    StarSprite * _sprite = NULL;
    CCARRAY_FOREACH(starsSpriteParent->getChildren(), _obj)
    {
        _sprite = dynamic_cast<StarSprite*>(_obj);
        if (_sprite)
        {
            //找到相符的精灵
            if ((_sprite->s_property.x == _pro.x &&
                 _sprite->s_property.y == _pro.y))
            {
                break;
            }
        }
    }
    return _sprite;
}

void StarLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
    
}

//触摸事件
bool StarLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if ( !can_click )
    {
        return false;
    }
    
    //获得触摸点坐标
    CCPoint touchLocation = pTouch->getLocation();
    
    //A->convertToNodeSpace(touchLocation);转换成A坐标系中的点。  这里是this，其实没什么用
    CCPoint local = this->convertToNodeSpace(touchLocation);
    
    // _index 是星星的下标   －1表示不存在，>=0则是棋盘中的某个位置
    //LD_getIndexAtPosition：通过传来的坐标，和宽度一半，返回星星下标  宽度一半是近似值
    int _index = dataHandle->SD_getIndexAtPosition(local, width/2);
    
    if (_index >=0)
    {
        int _type = dataHandle->SD_getStateAtIndex(_index);
        
        if (_type > 0)
        {
            
            //  StarProperty _pro  棋子的具体位置。  行列x，y
            StarProperty _pro = dataHandle->SD_convertIndexToLinesProperty(_index);
            
            //获得当前精灵。
            currentSelectSprite = SL_getCurrentSelectLinesSprite(_pro);
            
            //如果是选中状态并且 现在选中的是已经选中的其中一个，则删除掉
            if (currentSelectSprite->isChoose == true && isClick == true)
            {
                 dataHandle->SD_resetStateAtIndex(_index, 1001);
                SL_moveUnusedStar();
                SL_moveUnusedStar();
                SL_moveUnusedStar();
                
                gamemark->addnumber(preMark);
                //检查是否可以向下移动
                SL_downcheck_move();
                SL_downcheck_move();
                
                //延时1.5秒后检测是否向右移动
                CCDelayTime *waiting=CCDelayTime::create(1.5f);
                CCFiniteTimeAction* actions= CCSequence::create(waiting,CCCallFunc::create(this, callfunc_selector(StarLayer::SL_leftcheck_move)),NULL);
                this->runAction(actions);
                
                return false;  //直接返回，不进入下面的。
            }
            else  // 否则，恢复选中前状态
            {
                SL_resume();
            }
            
            //纪录一共消去多少个星星，  最少1.
            int count__;
            count__ = dataHandle->SD_check_total(_index, _type, false);
            
            //大于1，表示有消去
            if (count__ > 1)
            {
                
                dataHandle->SD_resetStateAtIndex(_index, 0);
                SL_clearupUnusedSpriteAd();
                SL_clearupUnusedSpriteAd();  //多清除几次，避免遗漏
                SL_clearupUnusedSpriteAd();
                isClick = true;   // 表示选中
                preType = _type;  //选中的类型
                preMark = count__ * count__ * 5; //如果消去能获得的分数
                
                //1001为自己设置的，不冲突就好。。  标记选中
                dataHandle->SD_resetStateAtIndex(_index, 1001);  //设置当前节点下标为1001
                
            }
        }
    }
    
    
    
    return false;
}


//遍历选中的不要的星星
void StarLayer::SL_clearupUnusedSpriteAd()
{
    currentSelectSprite = NULL;
    CCObject * _obj = NULL;
    
    for (unsigned int i=0; i<starsSpriteParent->getChildrenCount(); i++)
    {
        
        _obj    = starsSpriteParent->getChildren()->objectAtIndex(i);
        
        StarSprite * _sprite = dynamic_cast<StarSprite*>(_obj);
        
        if(!_sprite)
        {
            continue;
        }
        
        int _index = dataHandle->SD_getIndexAt(_sprite->s_property);
        
        if(_index<0 )
        {
            CCLOG("error !!!!!!_index<0");
        }
        
        int _value = dataHandle->SD_getStateAtIndex(_index);
        
        if (_value==0)    //如果是0，表示选中，  设置类型为1001 。。  自己定义的。
        {
            _sprite->Star_selected();
            _sprite->type = 1001;
            _sprite->isChoose = true;
            dataHandle->SD_resetStateAtIndex(_index, 1001);
        }
    }

}

//真正清除
void StarLayer::SL_moveUnusedStar()
{
    currentSelectSprite = NULL;
    CCObject * _obj = NULL;
    
    for (unsigned int i=0; i<starsSpriteParent->getChildrenCount(); i++)
    {
        
        _obj    = starsSpriteParent->getChildren()->objectAtIndex(i);
        
        StarSprite * _sprite = dynamic_cast<StarSprite*>(_obj);
        
        if(!_sprite)
        {
            continue;
        }
        
        int _index = dataHandle->SD_getIndexAt(_sprite->s_property);
        
        if(_index<0 )
        {
            CCLOG("error !!!!!!_index<0");
        }
        
        int _value = dataHandle->SD_getStateAtIndex(_index);
        
        if (_value==1001 || _value == 0)  //状态置0，并且消去。
        {
            dataHandle->SD_resetStateAtIndex(_index, 0);
             _sprite->Star_disappear();
        }
    }
    
    isClick = false;

}

//恢复选中前状态
void StarLayer::SL_resume()
{
    currentSelectSprite = NULL;
    CCObject * _obj = NULL;
    
    for (unsigned int i=0; i<starsSpriteParent->getChildrenCount(); i++)
    {
        
        _obj    = starsSpriteParent->getChildren()->objectAtIndex(i);
        
        StarSprite * _sprite = dynamic_cast<StarSprite*>(_obj);
        
        if(!_sprite)
        {
            continue;
        }
        
        int _index = dataHandle->SD_getIndexAt(_sprite->s_property);
        
        if(_index<0 )
        {
            CCLOG("error !!!!!!_index<0");
        }
        
        int _value = dataHandle->SD_getStateAtIndex(_index);
        
        if (_value==1001 || _value == 0)  //找到选中的。恢复选择之前的状态
        {
            _sprite->isChoose = false;
            dataHandle->SD_resetStateAtIndex(_index, preType);
            _sprite->Star_stop();
            _sprite->type = preType;
        }
    }
    
    isClick = false;
}

//检查是否可以向下移动星星
void StarLayer::SL_downcheck_move()
{
    int i, j;
    
    for (i=0; i<wid_num; i++)   //按列进行遍历
    {
        int start_ = -1, end_ = 0;
        bool is_check = false;  //用来纪录是否能进行检测
        int flag;
        for (j=0; j<hei_num; j++)  
        {
            int now_index = i + j * wid_num;  //获得每列中的各个元素
            
            //找到空白的点，则可以进行检测，并且纪录相对的起始点。
            if(dataHandle->SD_getStateAtIndex(now_index) == 0 && is_check == false)
            {           
                start_ = now_index;
                end_ = now_index;
                is_check = true;
                flag = j;  //标记，下次从这里再开始检测
            }
            
            //找到可以移动的那个星星
            if (dataHandle->SD_getStateAtIndex(now_index) != 0)  
            {
                if (is_check == true && start_ == end_ && start_!= -1)
                {
                    end_ = now_index;
                    if (end_ != start_)
                    {
                        j = flag;
                        
                        //移动到相应位置。
                        SL_aftercheck_move(start_, end_);
                        
                        //初始化，进行下一次判断
                        start_ = -1;
                        end_ = 0;
                        is_check = false;
                    }

                }
            }
            
        }
        start_ = -1;
        end_ = 0;
        is_check = false;
    }
}

//检查是否可以向右移动星星
void StarLayer::SL_leftcheck_move()
{
    int i, j, k;
    for (i=0; i<wid_num; i++)
    {
        if (dataHandle->SD_getStateAtIndex(i) == 0) //如果最低下一个坐标为0，则可以移动
        {
            for (j=i+1; j<wid_num; j++)
            {
                if (dataHandle->SD_getStateAtIndex(j) != 0)  //如果右边的最下面一个坐标不为0，则整列移动
                {
                    for (k=0; k<hei_num; k++)
                    {
                        int index_move = j + k * wid_num;
                        SL_aftercheck_move(index_move-1, index_move);
                    }
                }
                else if(dataHandle->SD_getStateAtIndex(j+1) != 0 && (j+1) < wid_num)
                {
                    for (k=0; k<hei_num; k++)
                    {
                        int index_move = j + 1 + k * wid_num;
                        SL_aftercheck_move(index_move-2, index_move);
                    }
                }
                
                else if(dataHandle->SD_getStateAtIndex(j+2) != 0&& (j+2) < wid_num)
                {
                    for (k=0; k<hei_num; k++)
                    {
                        int index_move = j + 2 + k * wid_num;
                        SL_aftercheck_move(index_move-3, index_move);
                    }
                }
                
                else if(dataHandle->SD_getStateAtIndex(j+3) != 0&& (j+3) < wid_num)
                {
                    for (k=0; k<hei_num; k++)
                    {
                        int index_move = j + 3 + k * wid_num;
                        SL_aftercheck_move(index_move-4, index_move);
                    }
                }
                
            }
        }
    }
    
    //检查游戏是否结束
    SL_is_gameover();
}

//检查完后移动需要移动的精灵
void StarLayer::SL_aftercheck_move( int after_move, int before_move )
{
    CCObject * _obj = NULL;
    
    for (unsigned int i=0; i<starsSpriteParent->getChildrenCount(); i++)
    {
        
        _obj    = starsSpriteParent->getChildren()->objectAtIndex(i);
        
        StarSprite * _sprite = dynamic_cast<StarSprite*>(_obj);
        
        if(!_sprite)
        {
            continue;
        }
        
        int _index = dataHandle->SD_getIndexAt(_sprite->s_property);
        
        if( _index==before_move )
        {
            
            //找到对应的那个星星精灵
            //移动到指定位置
            this->setTouchEnabled(false);
            CCFiniteTimeAction *move_ = CCMoveTo::create(0.2f, dataHandle->SD_getPositionAtIndex(after_move));
            CCFiniteTimeAction* actions= CCSequence::create(move_,CCCallFunc::create(this, callfunc_selector(StarLayer::SL_can_touch)),NULL);
            
            _sprite->runAction(actions);
                        
            //改变对应格子的状态
            dataHandle->SD_resetStateAtIndex(after_move,dataHandle->SD_getStateAtIndex(before_move));
            dataHandle->SD_resetStateAtIndex(before_move, 0);
            
            
            //一句花费了2个小时的遗漏！   wqnmlgb!!!!!!
            //精灵移动后，要改变对应的位置，不然下次检测，遍历精灵数组的时候会把上一次的消去。
            _sprite->Star_pos(dataHandle->SD_convertIndexToLinesProperty(after_move));
            break;
        }
        
    }
}

//设置可触摸
void StarLayer::SL_can_touch()
{
    this->setTouchEnabled(true);
}


//检查游戏是否结束
void StarLayer::SL_is_gameover()
{
    CCObject * _obj = NULL;
    for (unsigned int i=0; i<starsSpriteParent->getChildrenCount(); i++)
    {
        
        _obj    = starsSpriteParent->getChildren()->objectAtIndex(i);
        
        StarSprite * _sprite = dynamic_cast<StarSprite*>(_obj);
        
        if(!_sprite)
        {
            continue;
        }
        
        int _index = dataHandle->SD_getIndexAt(_sprite->s_property);
        int count__;
        count__ = dataHandle->SD_check_total(_index, _sprite->type,true);
        if (count__ > 1)
        {
            break;
        }
        
        if (i == (starsSpriteParent->getChildrenCount()-1))
        {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("maxMark_first_now", gamemark->return_mark());
            
            //设置最高分
            if (gamemark->return_mark() > CCUserDefault::sharedUserDefault()->getIntegerForKey("maxMark_first"))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("maxMark_first", gamemark->return_mark());
            }
            this->GameOver();
            
        }
    }
    

}

void StarLayer::GameOver()
{
    
    this->setTouchEnabled(false);
    this->stopAllActions();
    
    this->unscheduleAllSelectors();
    
    
    char inf_c[256];
    sprintf(inf_c, "游戏结束\n您的得分为：%d\n ",CCUserDefault::sharedUserDefault()->getIntegerForKey("maxMark_first_now"));
    CCLabelTTF *mark_ = CCLabelTTF::create(inf_c, "Marker Felt", 50);
    mark_->setPosition(ccp(320,400));
    this->addChild(mark_);
    this->scheduleOnce(schedule_selector(StarLayer::menuBackCallback), 2.0);
    
}


void StarLayer::menuBackCallback()
{
    CCScene *pScene = GameMenu::scene();
    CCTransitionFade* transitionScene = CCTransitionFade::create(1.0, pScene,ccWHITE);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
}


