/*
 * ��protothread�ķ�װ
 * ��protothread���з�װ���ṩ�˶�ʱ���Ĺ���
 * 
 *                  Author: Ȩѫ��KarsusNeko  karsus@msn.cn��
 */
#ifndef __PT_THREAD_H
#define __PT_THREAD_H

#include "pt.h"
#include "timer.h"

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
 * @������		pt_thread_init
 * @��������	��ʼ��һ��pt_thread_info����
 * @����˵��
 *		pti		-	����ʼ��������ָ��
 *		ptt		-	��������Ҫ����������ں���
 */
void pt_thread_init(pt_thread_info* pti, pt_thread_t* ptt);

#endif // __PT_THREAD_H
