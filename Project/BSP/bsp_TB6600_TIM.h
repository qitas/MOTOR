#ifndef __TB6600_TIM_H__
#define __TB6600_TIM_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include <stm32f10x.h>

/* 类型定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/
#define TB6600_TIMx                         TIM1
#define TB6600_TIM_APBxClock_FUN            RCC_APB2PeriphClockCmd
#define TB6600_TIM_CLK                      RCC_APB2Periph_TIM1

#define TB6600_TIM_GPIO_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define TB6600_TIM_GPIO_CLK                 (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO )

/* 第一路*/
#define TB6600_TIM_CH1_PORT                 GPIOA                 // 对应TB6600的PUL+，
#define TB6600_TIM_CH1_PIN                  GPIO_Pin_8            // 而PLU-直接接开发板的GND

#define TB6600_DIR1_GPIO_CLK                RCC_APB2Periph_GPIOB  // 电机旋转方向控制
#define TB6600_DIR1_PORT                    GPIOB                 // 对应TB6600的DIR+，
#define TB6600_DIR1_PIN                     GPIO_Pin_13           // 而DIR-直接接开发板的GND

#define TB6600_ENA1_GPIO_CLK                RCC_APB2Periph_GPIOG  // 电机使能控制，该引脚可不接悬空
#define TB6600_ENA1_PORT                    GPIOG                 // 对应TB6600的ENA+，
#define TB6600_ENA1_PIN                     GPIO_Pin_6           // 而ENA-直接接开发板的GND

/* 第二路*/
#define TB6600_TIM_CH2_PORT                 GPIOA                 // 对应TB6600的PUL+，
#define TB6600_TIM_CH2_PIN                  GPIO_Pin_9            // 而PLU-直接接开发板的GND

#define TB6600_DIR2_GPIO_CLK                RCC_APB2Periph_GPIOB  // 电机旋转方向控制
#define TB6600_DIR2_PORT                    GPIOB                 // 对应TB6600的DIR+，
#define TB6600_DIR2_PIN                     GPIO_Pin_14           // 而DIR-直接接开发板的GND

#define TB6600_ENA2_GPIO_CLK                RCC_APB2Periph_GPIOG  // 电机使能控制，该引脚可不接悬空
#define TB6600_ENA2_PORT                    GPIOG                // 对应TB6600的ENA+，
#define TB6600_ENA2_PIN                     GPIO_Pin_7           // 而ENA-直接接开发板的GND

/* 第三路*/
#define TB6600_TIM_CH3_PORT                 GPIOA                 // 对应TB6600的PUL+，
#define TB6600_TIM_CH3_PIN                  GPIO_Pin_10            // 而PLU-直接接开发板的GND

#define TB6600_DIR3_GPIO_CLK                RCC_APB2Periph_GPIOB  // 电机旋转方向控制
#define TB6600_DIR3_PORT                    GPIOB                 // 对应TB6600的DIR+，
#define TB6600_DIR3_PIN                     GPIO_Pin_15          // 而DIR-直接接开发板的GND

#define TB6600_ENA3_GPIO_CLK                RCC_APB2Periph_GPIOG  // 电机使能控制，该引脚可不接悬空
#define TB6600_ENA3_PORT                    GPIOG                 // 对应TB6600的ENA+，
#define TB6600_ENA3_PIN                     GPIO_Pin_8           // 而ENA-直接接开发板的GND


/* 第四路*/
#define TB6600_TIM_CH4_PORT                 GPIOA                 // 对应TB6600的PUL+，
#define TB6600_TIM_CH4_PIN                  GPIO_Pin_11            // 而PLU-直接接开发板的GND

#define TB6600_DIR4_GPIO_CLK                RCC_APB2Periph_GPIOB  // 电机旋转方向控制
#define TB6600_DIR4_PORT                    GPIOB                 // 对应TB6600的DIR+，
#define TB6600_DIR4_PIN                     GPIO_Pin_12          // 而DIR-直接接开发板的GND

#define TB6600_ENA4_GPIO_CLK                RCC_APB2Periph_GPIOG  // 电机使能控制，该引脚可不接悬空
#define TB6600_ENA4_PORT                    GPIOG                 // 对应TB6600的ENA+，
#define TB6600_ENA4_PIN                     GPIO_Pin_9           // 而ENA-直接接开发板的GND


/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void TB6600_TIMx_PWM_Init(void);

#endif	/* __TB6600_TIM_H__ */
/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
