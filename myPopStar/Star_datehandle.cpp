//
//  Star_datehandle.cpp
//  myPopStar
//
//  Created by Colin on 14-10-15.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "Star_datehandle.h"
//#include <list.h>

//初始化棋盘
void StarDataHandle::initDateHandleWith(int _column,int _row,float _width,float _height)
{
    //行列个数
    total_x = _column;
    total_y = _row;
    total_count = _column * _row;
    
    //stateArray 存放棋盘中每个格子的状态
    //pointArray 存放棋盘中每个格子的ccpoint
    stateArray = new int[total_count]();
    memset(stateArray, 0, sizeof(int)*total_count);
    pointArray = new CCPoint[total_count]();
    
    
    
    float _halfWi = _width * 0.5f;
    float _halfHe = _height * 0.5f;
    
    //pointArray数组中写入各个位置的坐标
    for (int y = 0; y<total_y; y++)
    {
        for (int x = 0; x<total_x; x++)
        {
            
            int _index = (y * total_x) + x;
            
            if (_index<0 || _index>=total_count)
            {
                continue;
            }
            
            CCPoint pos = CCPoint(_width*x + _halfWi,_height*y + _halfHe);
            
            pointArray[_index] = pos;
        }
    }
}

//返回该下标处棋子的状态。  0表示空，非0表示该位置有棋子了。
int StarDataHandle::SD_getStateAtIndex(int _index)
{
    return stateArray[_index];
}

//在相应下标位置设置棋盘上棋子种类。
void StarDataHandle::SD_resetStateAtIndex(int _index,int _value)
{
    stateArray[_index] = _value;
}

//返回棋子下标。  利用棋子行列数返回棋子下标
int StarDataHandle::SD_getIndexAt(const StarProperty & _p)
{
    int _index = _p.y * total_x + _p.x;
    if (_index<0 ||_index>=total_count)
    {
        return -1;
    }
    return _index;
}

//返回对应下标处棋子格子的坐标
CCPoint StarDataHandle::SD_getPositionAtIndex(int _index)
{
    return pointArray[_index];
}

//通过传来的坐标，和宽度，返回棋子下标
int StarDataHandle::SD_getIndexAtPosition(CCPoint _pos,float _diatance)
{
    int _index=-1;
    for (int i=0; i<total_count; i++)
    {
        //与每个棋子都做比较，如果满足近似的， 就返回该棋子下标  这里近似值_diatance为棋子宽度一半
        CCPoint pos = pointArray[i];
        if (ccpDistance(pos, _pos)<=_diatance)
        {
            _index = i;
            break;
        }
    }
    return _index;
}

//返回选中棋子的具体行数列数。   参数为棋子下标
StarProperty StarDataHandle::SD_convertIndexToLinesProperty(int _index)
{
    StarProperty _pro;
    _pro.x = _index % total_x;
    _pro.y = (int)(_index/total_x);
    return _pro;
}

//检查函数
int StarDataHandle::SD_check_total( int _index, int type ,bool style_check)
{
    is_gameover_check = style_check;
    total_same_color = 1;
    now_index = _index;
    now_type = type;
    now_w = _index % total_x;
    now_h = _index / total_x;
    
    SD_check_up(now_index+total_x, now_type);
    
    SD_check_down(now_index-total_x, now_type);
    
    SD_check_left(now_index-1, now_type);
    
    SD_check_right(now_index+1, now_type);
    
    return total_same_color;
    
}
void StarDataHandle::SD_check_up( int _index, int type )
{
    if (_index >= 0 && _index < total_count && (_index / total_x >= now_h) && SD_getStateAtIndex(_index) == type)
    {
        if (!is_gameover_check)
        {
            SD_resetStateAtIndex(_index, 0);
        }
        total_same_color++;
        SD_check_up(_index+total_x, type);
        
        SD_check_left(_index-1, type);
        
        SD_check_right(_index+1, type);
    }
}
void StarDataHandle::SD_check_down( int _index, int type )
{
    if (_index >= 0 && _index < total_count && (_index / total_x <= now_h) &&SD_getStateAtIndex(_index) == type)
    {
        if (!is_gameover_check)
        {
            SD_resetStateAtIndex(_index, 0);
        }
        //        CCLog("%d", _index);
        total_same_color++;
        
        SD_check_left(_index-1, type);
        
        SD_check_right(_index+1, type);
        
        SD_check_down(_index-total_x, type);
    }
}
void StarDataHandle::SD_check_left( int _index, int type )
{
    if (_index >= 0 && _index < total_count && (_index % total_x <= now_w) && SD_getStateAtIndex(_index) == type)
    {
        if (!is_gameover_check)
        {
            SD_resetStateAtIndex(_index, 0);
        }
        //        CCLog("%d", _index);
        total_same_color++;
        
        SD_check_left(_index-1, type);
        
        SD_check_up(_index+total_x, type);
        
        SD_check_down(_index-total_x, type);
    }
}
void StarDataHandle::SD_check_right( int _index, int type )
{
    if (_index >= 0 && _index < total_count && (_index % total_x >= now_w) && SD_getStateAtIndex(_index) == type )
    {
        if (!is_gameover_check)
        {
            SD_resetStateAtIndex(_index, 0);
        }
        //        CCLog("%d", _index);
        total_same_color++;
        
        SD_check_right(_index+1, type);
        
        SD_check_up(_index+total_x, type);
        
        SD_check_down(_index-total_x, type);
    }
    
}


//构造函数  初始化
StarDataHandle::StarDataHandle()
{
    stateArray = NULL;
    pointArray = NULL;
}

//析构函数
StarDataHandle::~StarDataHandle()
{
    delete [] stateArray;
    delete [] pointArray;
}