#include "pt_thread.h"

void pt_thread_init(pt_thread_info* pti, pt_thread_t* ptt)
{
	pti->pt_thread = *ptt;
}
