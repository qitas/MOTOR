
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp/57StepMotor/bsp_TB6600_TIM.h" 
#include "bsp/key/bsp_key.h"
#include "bsp/usart/bsp_debug_usart.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
uint8_t dir=0; // 0 ：顺时针   1：逆时针 
uint8_t ena=0; // 0 ：正常运行 1：停机

/* 扩展变量 ------------------------------------------------------------------*/
extern __IO uint16_t prescaler[4]; /* 步进电机速度控制，可调节范围为 650 -- 3500 ，值越小速度越快 */

/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 主函数.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
int main(void)
{  
  uint8_t key1_count=1;
  /* 初始化按键 */
  KEY_GPIO_Init();
  
  DEBUG_USART_Init();
  printf("4轴步进电机控制，KEY1和KEY2组合调节电机转动\n");
  printf("key1_count:%d\n",key1_count);
  
  /* 初始化定时器PWM输出 */
  TB6600_TIMx_PWM_Init();    
  
  /* 无限循环 */
  while (1)    
  {
    if(KEY1_StateRead()==KEY_DOWN)  // 功能选择
    {
       key1_count++;
       if(key1_count>10)
         key1_count=1;
       printf("key1_count:%d\n",key1_count);
    }
    if(KEY2_StateRead()==KEY_DOWN)  // 功能调节
    {
      printf("key1_count:%d\n",key1_count);
      switch(key1_count)
      {
        case 1:
          prescaler[0]-=100;
          if(prescaler[0]<700)  // 最快速度限制
            prescaler[0]=700;
          printf("prescaler[0]:%d\n",prescaler[0]);
          break;
        case 2:
          prescaler[0]+=100;
          if(prescaler[0]>3500)         // 最慢速度限制
            prescaler[0]=3500;
          printf("prescaler[0]:%d\n",prescaler[0]);
          break;
        case 3:
          prescaler[1]-=100;
          if(prescaler[1]<700)  // 最快速度限制
            prescaler[1]=700;
          printf("prescaler[1]:%d\n",prescaler[1]);
          break;
        case 4:
          prescaler[1]+=100;
          if(prescaler[1]>3500)         // 最慢速度限制
            prescaler[1]=3500;
          printf("prescaler[1]:%d\n",prescaler[1]);
          break;
        case 5:
          prescaler[2]-=100;
          if(prescaler[2]<700)  // 最快速度限制
            prescaler[2]=700;
          printf("prescaler[2]:%d\n",prescaler[2]);
          break;
        case 6:
          prescaler[2]+=100;
          if(prescaler[2]>3500)         // 最慢速度限制
            prescaler[2]=3500;
          printf("prescaler[2]:%d\n",prescaler[2]);
          break;
        case 7:
          prescaler[3]-=100;
          if(prescaler[3]<700)  // 最快速度限制
            prescaler[3]=700;
          printf("prescaler[3]:%d\n",prescaler[3]);
          break;
        case 8:
          prescaler[3]+=100;
          if(prescaler[3]>3500)         // 最慢速度限制
            prescaler[3]=3500;
          printf("prescaler[3]:%d\n",prescaler[3]);
          break;          
        case 9:                // 方向控制
          printf("电机转动方向改变\n");
          if(dir==0)
          {
            GPIO_SetBits(TB6600_DIR1_PORT,TB6600_DIR1_PIN);  // 逆时针
            GPIO_SetBits(TB6600_DIR2_PORT,TB6600_DIR2_PIN);  // 逆时针
            GPIO_SetBits(TB6600_DIR3_PORT,TB6600_DIR3_PIN);  // 逆时针
            GPIO_SetBits(TB6600_DIR4_PORT,TB6600_DIR4_PIN);  // 逆时针
            dir=1;
          }
          else
          {
            GPIO_ResetBits(TB6600_DIR1_PORT,TB6600_DIR1_PIN);  // 顺时针
            GPIO_ResetBits(TB6600_DIR2_PORT,TB6600_DIR2_PIN);  // 顺时针
            GPIO_ResetBits(TB6600_DIR3_PORT,TB6600_DIR3_PIN);  // 顺时针
            GPIO_ResetBits(TB6600_DIR4_PORT,TB6600_DIR4_PIN);  // 顺时针
            dir=0;
          }
          break;  
        case 10:                // 使能控制
          printf("电机转动使能控制\n");
          if(ena==0)
          {
            GPIO_SetBits(TB6600_ENA1_PORT,TB6600_ENA1_PIN); // 停机
            GPIO_SetBits(TB6600_ENA2_PORT,TB6600_ENA2_PIN); // 停机
            GPIO_SetBits(TB6600_ENA3_PORT,TB6600_ENA3_PIN); // 停机
            GPIO_SetBits(TB6600_ENA4_PORT,TB6600_ENA4_PIN); // 停机
            ena=1;
            
          }
          else
          {
            GPIO_ResetBits(TB6600_ENA1_PORT,TB6600_ENA1_PIN);  // 正常运行
            GPIO_ResetBits(TB6600_ENA2_PORT,TB6600_ENA2_PIN);  // 正常运行
            GPIO_ResetBits(TB6600_ENA3_PORT,TB6600_ENA3_PIN);  // 正常运行
            GPIO_ResetBits(TB6600_ENA4_PORT,TB6600_ENA4_PIN);  // 正常运行
            ena=0;
          }
          break;
        default:
          break;          
      }
    }      
  }
}


