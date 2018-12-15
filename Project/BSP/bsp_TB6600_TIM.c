/* 包含头文件 ----------------------------------------------------------------*/
#include "bsp_TB6600_TIM.h"

/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
__IO uint16_t prescaler[4]={800,1200,1600,2000};
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: 配置TIMx复用输出PWM时用到的I/O
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
static void TB6600_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* 使能定时器通道引脚GPIO时钟 */
  TB6600_TIM_GPIO_APBxClock_FUN(TB6600_TIM_GPIO_CLK, ENABLE); 
  
  RCC_APB2PeriphClockCmd(TB6600_DIR1_GPIO_CLK|TB6600_ENA1_GPIO_CLK,ENABLE);
  RCC_APB2PeriphClockCmd(TB6600_DIR2_GPIO_CLK|TB6600_ENA2_GPIO_CLK,ENABLE);
  RCC_APB2PeriphClockCmd(TB6600_DIR3_GPIO_CLK|TB6600_ENA3_GPIO_CLK,ENABLE);
  RCC_APB2PeriphClockCmd(TB6600_DIR4_GPIO_CLK|TB6600_ENA4_GPIO_CLK,ENABLE);
  
  /* 配置定时器通道1输出引脚模式：复用开漏输出模式 */
  GPIO_InitStructure.GPIO_Pin = TB6600_TIM_CH1_PIN|TB6600_TIM_CH2_PIN|TB6600_TIM_CH3_PIN|TB6600_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TB6600_TIM_CH1_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_DIR1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(TB6600_DIR1_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_DIR1_PORT,TB6600_DIR1_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_DIR2_PIN;
  GPIO_Init(TB6600_DIR2_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_DIR2_PORT,TB6600_DIR2_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_DIR3_PIN;
  GPIO_Init(TB6600_DIR3_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_DIR3_PORT,TB6600_DIR3_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_DIR4_PIN;
  GPIO_Init(TB6600_DIR4_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_DIR4_PORT,TB6600_DIR4_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_ENA1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(TB6600_ENA1_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_ENA1_PORT,TB6600_ENA1_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_ENA2_PIN;
  GPIO_Init(TB6600_ENA2_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_ENA2_PORT,TB6600_ENA2_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_ENA3_PIN;
  GPIO_Init(TB6600_ENA3_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_ENA3_PORT,TB6600_ENA3_PIN);
  
  GPIO_InitStructure.GPIO_Pin =TB6600_ENA4_PIN;
  GPIO_Init(TB6600_ENA4_PORT, &GPIO_InitStructure);
  GPIO_ResetBits(TB6600_ENA4_PORT,TB6600_ENA4_PIN);
}


/**
  * 函数功能: 配置TIM3输出的PWM信号的模式，如周期、极性、占空比
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT 重新计数
 *                    TIMx_CCR(电平发生变化)
 * 信号周期=(TIMx_ARR +1 ) * 时钟周期
 * 占空比=TIMx_CCR/(TIMx_ARR +1)
 */
static void TB6600_TIMx_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;  
  /* 定义嵌套向量中断控制器初始化结构体变量 */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 使能定时器始终：设置TIM3CLK 为 72MHZ */
	TB6600_TIM_APBxClock_FUN (TB6600_TIM_CLK, ENABLE);
  
    /* 选择中断优先级配置组为4个抢占式优先级和4个子优先级，可以参考misc.h文件了解相关设置 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 使能KEY1所在的外部中断通道 */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
  /* 设置抢占式优先级为2 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; 
  /* 设置子优先级为3 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  /* 使能外部中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  /* 初始化配置嵌套向量中断控制器 */
  NVIC_Init(&NVIC_InitStructure); 
  
  /* 定时器基本参数始终 */		 
  /* 这里设置为0xFFFF，不需要用到 */
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 
  /* 设置预分频：不预分频，即为72MHz,输出脉冲频率：72MHz/4=18MHz */
  /* 同一个定时器的不同通道PWM的频率只能是相同的，不同通道可以设置为不同的占空比 */
  TIM_TimeBaseStructure.TIM_Prescaler =4-1;
  /* 设置时钟分频系数：不分频(这里用不到) */
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
  /* 向上计数模式 */
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TB6600_TIMx, &TIM_TimeBaseStructure);

  /* 定时器输出通道1模式配置 */
  /* 模式配置：PWM模式1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
  /* 输出状态设置：使能输出 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  /* 设置跳变值，当计数器计数到这个值时，电平发生跳变 */
  TIM_OCInitStructure.TIM_Pulse = prescaler[0];
  /* 当定时器计数值小于CCR1_Val时为高电平 */
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  /* 初始化定时器4个通道输出PWM */
  TIM_OC1Init(TB6600_TIMx, &TIM_OCInitStructure);
  
  TIM_OCInitStructure.TIM_Pulse = prescaler[1];
  TIM_OC2Init(TB6600_TIMx, &TIM_OCInitStructure);
  
  TIM_OCInitStructure.TIM_Pulse = prescaler[2];
  TIM_OC3Init(TB6600_TIMx, &TIM_OCInitStructure);
  
  TIM_OCInitStructure.TIM_Pulse = prescaler[3];
  TIM_OC4Init(TB6600_TIMx, &TIM_OCInitStructure);
  
  /* 定时器比较输出通道1预装载配置：使能预装载 */
  TIM_OC1PreloadConfig(TB6600_TIMx, TIM_OCPreload_Disable);
  /* 定时器比较输出通道2预装载配置：使能预装载 */
  TIM_OC2PreloadConfig(TB6600_TIMx, TIM_OCPreload_Disable);
  /* 定时器比较输出通道3预装载配置：使能预装载 */
  TIM_OC3PreloadConfig(TB6600_TIMx, TIM_OCPreload_Disable);
  /* 定时器比较输出通道4预装载配置：使能预装载 */
  TIM_OC4PreloadConfig(TB6600_TIMx, TIM_OCPreload_Disable);

  TIM_ITConfig(TB6600_TIMx,TIM_IT_CC1,ENABLE);
  TIM_ITConfig(TB6600_TIMx,TIM_IT_CC2,ENABLE);
  TIM_ITConfig(TB6600_TIMx,TIM_IT_CC3,ENABLE);
  TIM_ITConfig(TB6600_TIMx,TIM_IT_CC4,ENABLE);
  /* 使能定时器 */
  TIM_Cmd(TB6600_TIMx, ENABLE);
  
  /* TIM主输出使能 */
  TIM_CtrlPWMOutputs(TB6600_TIMx, ENABLE);
}

/**
  * 函数功能: TIMx 输出PWM信号初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：只要调用这个函数TIMx的四个通道就会有PWM信号输出
  */
void TB6600_TIMx_PWM_Init(void)
{
	TB6600_GPIO_Config();
	TB6600_TIMx_Configuration();	
}

/* 定时比较中断服务函数 */
void TIM1_CC_IRQHandler(void)
{
  uint16_t capture;
  if(TIM_GetITStatus(TB6600_TIMx,TIM_IT_CC1)!=RESET)
  {
    TIM_ClearITPendingBit(TB6600_TIMx,TIM_IT_CC1);
    capture=TIM_GetCapture2(TB6600_TIMx);
    TIM_SetCompare1(TB6600_TIMx,capture+prescaler[0]);
  }
  
  if(TIM_GetITStatus(TB6600_TIMx,TIM_IT_CC2)!=RESET)
  {
    TIM_ClearITPendingBit(TB6600_TIMx,TIM_IT_CC2);
    capture=TIM_GetCapture2(TB6600_TIMx);
    TIM_SetCompare2(TB6600_TIMx,capture+prescaler[1]);
  }
  
  if(TIM_GetITStatus(TB6600_TIMx,TIM_IT_CC3)!=RESET)
  {
    TIM_ClearITPendingBit(TB6600_TIMx,TIM_IT_CC3);
    capture=TIM_GetCapture3(TB6600_TIMx);
    TIM_SetCompare3(TB6600_TIMx,capture+prescaler[2]);
  }
  
  if(TIM_GetITStatus(TB6600_TIMx,TIM_IT_CC4)!=RESET)
  {
    TIM_ClearITPendingBit(TB6600_TIMx,TIM_IT_CC4);
    capture=TIM_GetCapture4(TB6600_TIMx);
    TIM_SetCompare4(TB6600_TIMx,capture+prescaler[3]);
  }
}

