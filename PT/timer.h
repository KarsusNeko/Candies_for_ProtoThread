/*
 * ��ʱ������
 * Ŀǰֻ�ṩ��timeout��ػ���
 * 
 *                  Author: Ȩѫ��KarsusNeko  karsus@msn.cn��
 */
#ifndef __TIMER_H
#define __TIMER_H

/*
 * ͨ��SysTick�����Լ�ticks���ṩ�����ʱ��׼
 */
extern unsigned long ticks;

typedef struct
{
	int	start_tick;
	int	timeout_tick;
} timer_t;

/*
 * @������		timer_set
 * @��������	����һ����ʱ��
 * @����˵��
 *		t		-	�����õĶ�ʱ��ָ��
 *		timeout	-	��ʱʱ��
 */
void	timer_set(timer_t* t, unsigned long timeout);

/*
 * @������		timer_expired
 * @��������	�ж�һ����ʱ���Ƿ�ʱ
 * @����˵��
 *		t		-	���ж϶�ʱ����ָ��
 * @����ֵ		�������ʾ��ʱ������δ��ʱ
 */
int		timer_expired(timer_t* t);

#endif // __TIMER_H
