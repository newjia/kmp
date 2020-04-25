//
//  main.c
//  kkmmpp
//
//  Created by 李佳 on 2020/4/24.
//  Copyright © 2020 李佳. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef int Status;
#define MAXSIZE 100 /* 存储空间初始分配量 */
#define ERROR 0 /* 存储空间初始分配量 */
#define OK 1 /* 存储空间初始分配量 */
typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */

// 字符串与字符的转化
Status StrAssign(String T,char *chars)
{
    int i;
    if(strlen(chars)>MAXSIZE)
        return ERROR;
    else
    {
        T[0]=strlen(chars);
        for(i=1;i<=T[0];i++)
            T[i]=*(chars+i-1);
        return OK;
    }
}


// 获取普通的next 数组
void get_nextArray(String T, int *next)
{
      int i, j;
      i = 1;
      j = 0;
      next[1] = 0;        // 这是第一种情况，初始为0
  
      while ( i < T[0])     // 循环上限为模式串的长度
    {
          // 比较模式串 T 的前缀后缀俩字符,
        //若相等，分别递增
          if( j == 0 || T[i] == T[j])
        {
           ++i;
           ++j;
            
            next[i] = j;
        }
               else
        {
          // 如果不相等， j 回溯回当前
          j = next[j]    ;
        }
    }
}

// 改进版KMP next 数组
void get_nextVal(String T, int *nextVal)
{
      int i, j;
      i = 1;
      j = 0;
      nextVal[1] = 0;        // 这是第一种情况，初始为0
  
      while ( i < T[0])     // 循环上限为模式串的长度
    {
          // 比较模式串 T 的前缀后缀俩字符,
        //若相等，分别递增
          if( j == 0 || T[i] == T[j])
        {
           ++i;
           ++j;
            if (T[i] == T[j])
                nextVal[i] = nextVal[j];
            else
                nextVal[i] = j;
            
        }
               else
        {
          // 如果不相等， j 回溯回当前
          j = nextVal[j] ;
        }
    }
}

// KMP 业务代码实现
int getKMP(String S, String T, int pos)
{
       // s         = 主串
       // T         = 模式串
       // pos     = 最终符合需求的位置
    
      int i = pos;
      int j = 1;
        
      // next 数组的初始化
      int next[255];
  
      // 根据模式串，定义出next
      get_nextArray(T, next);
  
      // 开始判断
      while (i <= S[0] && j <= T[0])
    {
          // 主串与字串如果相等，继续
          if (j == 0 || S[i] == T[j])
        {
              ++i;
              ++j;
        }else{
          
              // 两者不相等， j 回溯，具体位置为数组中的值
              j = next[j];
        }
        }
      // 如果 j 的长度大于模式串长度，即已经取得成功
      if (j > T[0])
          return i - T[0];
      else
          return 0;
}

// 优化版的KMP 代码实现
int advancedKMP(String S, String T, int pos)
{
       // s         = 主串
       // T         = 模式串
       // pos     = 最终符合需求的位置
    
      int i = pos;
      int j = 1;
        
      // next 数组的初始化
      int next[255];
  
      // 根据模式串，定义出next
      get_nextArray(T, next);
  
      // 开始判断
      while (i <= S[0] && j <= T[0])
    {
          // 主串与字串如果相等，继续
          if (j == 0 || S[i] == T[j])
        {
              ++i;
              ++j;
        }else{
          
              // 两者不相等， j 回溯，具体位置为数组中的值
              j = next[j];
        }
        }
      // 如果 j 的长度大于模式串长度，即已经取得成功
      if (j > T[0])
          return i - T[0];
      else
          return 0;
}

// 遍历循环 数组
void showArray(int next[], int length)
{
    if (next == NULL&& next[0] == 0) {
        return;
    }
    int i;
    for (i = 1; i < length; i++) {
        printf("%d", next[i]);
    }
    printf("\n");
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    printf("第一次查询\n\n");
    String S, T;
    StrAssign(S, "cccaababcabc");
    StrAssign(T, "abc");
    
    int i = S[0];
    int *p = (int *)malloc((i + 1) * sizeof(int));
    get_nextArray(S, p);
    printf("普通的next 数组为：");
    showArray(p, S[0]);
    
    int result = getKMP(S, T, 1);
    if (result > 0) {
        printf("查找成功!在里面的序号为:     %d\n\n", result);
    }else{
        printf("查找失败，主串并无匹配的模式串!\n\n");
    }
    
 
    
    printf("************************\n第二次查询\n\n");
    String S2, T2;
    StrAssign(S2, "aaaaacaaaaabc");
    StrAssign(T2, "aaaaab");
    
    int ii = S2[0];
    int *pp = (int *)malloc((ii + 1) * sizeof(int));
    get_nextVal(S2, pp);
    printf("改进版的next 数组为：");
    showArray(pp, S2[0]);
    
    int result2 = advancedKMP(S2, T2, 1);
    if (result2 > 0) {
        printf("查找成功!在里面的序号为:     %d\n\n", result2);
    }else{
        printf("查找失败，主串并无匹配的模式串!\n\n");
    }
    
    
    
    return 0;
}
 
