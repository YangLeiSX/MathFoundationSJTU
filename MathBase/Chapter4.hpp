//
//  Chapter4.hpp
//  MathBase
//
//  第四章 二次同余式与平方剩余
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter4_hpp
#define Chapter4_hpp

//雅可比符号的计算
int JacobiSignal(int up, int down){
    //求模
    up = up % down;
    //递归终点
    if(up == 1 || up == 0)
        return 1;
    //保证上方为正的奇整数
    if(up % 2 == 0){
        //2/p的计算
        return JacobiSignal(up/2, down) * pow(-1,(down * down -1 )/8);
    }else if(up < 0){
        //-1/p的计算
        return JacobiSignal(-up, down) * pow(-1,(down *down -1)/2);
    }else{
        //二次互反律
        return JacobiSignal(down, up) * pow(-1, (up - 1)*(down - 1)/4);
    }
    
    return 0;
}
#endif /* Chapter4_hpp */
