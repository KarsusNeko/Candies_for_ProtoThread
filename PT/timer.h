/*
 * 定时器管理
 * 目前只提供了timeout相关机制
 * 
 *                  Author: 权勋（KarsusNeko  karsus@msn.cn）
 */
#ifndef __TIMER_H
#define __TIMER_H

/*
 * 通过SysTick周期性加ticks来提供软件定时基准
 */
extern unsigned long ticks;

typedef struct
{
	int	start_tick;
	int	timeout_tick;
} timer_t;

/*
 * @函数名		timer_set
 * @功能描述	设置一个定时器
 * @参数说明
 *		t		-	被设置的定时器指针
 *		timeout	-	超时时间
 */
void	timer_set(timer_t* t, unsigned long timeout);

/*
 * @函数名		timer_expired
 * @功能描述	判断一个定时器是否超时
 * @参数说明
 *		t		-	待判断定时器的指针
 * @返回值		返回真表示超时，否则未超时
 */
int		timer_expired(timer_t* t);

#endif // __TIMER_H
