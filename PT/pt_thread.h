/*
 * 对protothread的封装
 * 对protothread进行封装并提供了定时器的功能
 * 
 *                  Author: 权勋（KarsusNeko  karsus@msn.cn）
 */
#ifndef __PT_THREAD_H
#define __PT_THREAD_H

#include "pt.h"
#include "timer.h"

/*
 * 通过pt_thread_info中的某个变量得到整个pt_thread_info的指针
 * 	ptr指该变量的指针，member指该变量在pt_thread_info中对应的成员
 */
#define pt_thread_container(ptr, member)	\
	((pt_thread_info *)((unsigned char *)ptr - (unsigned char *)(&(((pt_thread_info *)0)->member))))
#define container_of(ptr, type, member)	\
	((type *)((unsigned char *)ptr - (unsigned char *)(&(((type *)0)->member))))

typedef int (*pt_thread_t)(struct pt*);

typedef struct
{
	timer_t		timer;
	struct pt	pt;
	pt_thread_t	pt_thread;
} pt_thread_info;

/*
 * @函数名		pt_thread_init
 * @功能描述	初始化一个pt_thread_info容器
 * @参数说明
 *		pti		-	待初始化的容器指针
 *		ptt		-	该容器需要填充的任务入口函数
 */
void pt_thread_init(pt_thread_info* pti, pt_thread_t* ptt);

#endif // __PT_THREAD_H
