//
//  Star_datehandle.h
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#ifndef __PopStar__Star_datehandle__
#define __PopStar__Star_datehandle__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

//星星在棋盘中的位置
struct StarProperty
{
    int x = 0;
    int y = 0;
};

//对应的标示
enum tag_
{
    yellow_star = 1,
    green_star = 2,
    red_star = 3,
    blue_star = 4,
    pink_star = 5,
    
};

class StarDataHandle
{
    bool is_gameover_check;
    //宽，高格子个数和总的
    int total_x;
    int total_y;
    int total_count;
    
    //棋盘中各个位置状态
    int *stateArray;
    
    //棋盘中各个位置坐标
    CCPoint *pointArray;
    
    //纪录消去的星星个数
    int total_same_color;
    
    //纪录当前要判断星星的状态
    int now_index;
    int now_type;
    int now_w;
    int now_h;
    
public:
    
    //初始化棋盘
    void initDateHandleWith(int _column,int _row,float _width,float _height);
    
    //返回该下标处棋子的状态。  0表示空，非0表示该位置有棋子了。
    int SD_getStateAtIndex(int _index);
    
    //在相应下标位置设置棋盘上棋子种类。
    void SD_resetStateAtIndex(int _index,int _value);
    
    //返回棋子下标。  利用棋子行列数返回棋子下标
    int SD_getIndexAt(const StarProperty & _p);
    
    //返回对应下标处棋子格子的坐标
    CCPoint SD_getPositionAtIndex(int _index);
    
    //通过传来的坐标，和宽度，返回棋子下标
    int SD_getIndexAtPosition(CCPoint _pos,float _diatance);
    
    //返回选中棋子的具体行数列数。   参数为棋子下标
    StarProperty SD_convertIndexToLinesProperty(int _index);
    
    //监测函数
    int SD_check_total( int _index, int type ,bool style_check);
    void SD_check_up( int _index, int type );
    void SD_check_down( int _index, int type );
    void SD_check_left( int _index, int type );
    void SD_check_right( int _index, int type );
    
    //析构函数
    ~StarDataHandle();
    
    //构造函数
    StarDataHandle();
};

#endif /* defined(__PopStar__Star_datehandle__) */
