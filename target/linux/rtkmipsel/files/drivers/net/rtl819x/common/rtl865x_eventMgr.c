/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*/  
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include "rtl_errno.h"
//#include "rtl_utils.h"
#include "rtl865x_eventMgr.h"
#include "rtl865x_vlan.h"
#include <linux/seq_file.h>
    
/*record the allocated memory pool pointer, 
it can be used when event management module destroyed*/ 
static char eventMgrInitFlag = FALSE;





{
	
	
	
		
		
		
		
	
	else
		
		
			
			
			
		
		else if (param->eventCnt == 0)
			
			
			
		
		else
			
			
			
		
			
			
			
		
		else if (param->eventListCnt == 0)
			
			
			
		
		else
			
			
			
		
	
	
	
	
	    //#ifdef __KERNEL__
	    
	
	    //#else
	    //eventPool= (rtl865x_event_t *)malloc(eventMgrParam.eventCnt * sizeof(rtl865x_event_t)); 
	    //#endif
	    if (eventPool != NULL)
		
		
			eventMgrParam.eventCnt * sizeof(rtl865x_event_t));
		
	
	else
		
		
		
	
	    //#ifdef __KERNEL__
	    TBL_MEM_ALLOC(eventLayerListPool, rtl865x_eventLayerList_t,
			  eventMgrParam.eventListCnt);
	
	    //#else
	    //eventLayerListPool=(rtl865x_eventLayerList_t *)malloc(eventMgrParam.eventListCnt * sizeof(rtl865x_eventLayerList_t)); 
	    //#endif        
	    if (eventLayerListPool != NULL)
		
		
			eventMgrParam.eventListCnt *
			sizeof(rtl865x_eventLayerList_t));
		
	
	else
		
		
		
	
		
		
				    &eventPool[i], next);
		
	
		
		
				    &eventLayerListPool[i], next);
		
	
	



					      eventLayerList) 
{
	
	
	
		
		
		
	
	
		
		
		
		
		
		
		
				    next);
		
		
	



{
	
	
	
		
		
		
	
	    TAILQ_FIRST(&eventsTables.inuseList.eventLayerListHead);
	
		
		
		
		
				 eventLayerList, next);
		
		
		
				    eventLayerList, next);
		
	



{
	
		
		
		
	
	
#ifdef __KERNEL__
	    if (eventPool != NULL)
		
		
		
		
	
		
		
		
		
	
#else /* 
	    if (eventPool != NULL)
		
		
		
		
	
		
		
		
		
	
#endif /* 
	    
	



    * rtl865x_searchEventLayerList(rtl865x_event_Param_t * eventParam) 
{
	
	
			&eventsTables.inuseList.eventLayerListHead, next) 
		
			
			
			
	
	



					       eventList,
					       rtl865x_event_Param_t *
					       eventParam) 
{
	
	
		
		
		
	
		
		     &&(event->eventPriority == eventParam->eventPriority) 
		     &&(event->event_action_fn == eventParam->event_action_fn))
			
			
			
	
	



					    eventLayerList) 
{
	
	
		
		
		
	
			  &eventsTables.inuseList.eventLayerListHead, next) 
		
		     eventLayerList->eventLayerId)
			
			
					      eventLayerListHead,
					      tmpEventLayerList, eventLayerList,
					      next);
			
			
	
	
		
		
				    eventLayerList, next);
		
	



				   rtl865x_event_t * event) 
{
	
	
		
		
		
	
		
		       ((tmpEvent->eventId == event->eventId)
			&& (tmpEvent->eventPriority >= event->eventPriority)))
			
			
					      tmpEvent, event, next);
			
			
	
	
		
		
		
	



{
	
	
	
		
		
		
	
		
		
		
	
		
		
		
	
	
		
		
		    CTAILQ_FIRST(&eventsTables.freeList.eventLayerListHead);
		
			
			
			
		
			       eventLayerList, next);
		
		
		
		
	
	       (eventParam->eventId > MAX_SYSTEM_EVENT_ID) || 
	       (eventParam->event_action_fn == NULL))
		
	
	    /*check duplicate entry */ 
	    event = rtl865x_searchEvent(eventLayerList, eventParam);
	
		
		
		
	
	else
		
		
		
			
			
			
		
		
		
		
		
		
	



{
	
	
	
		
		
		
	
		
		
		
	
	
		
		
		
	
	       (eventParam->eventId > MAX_SYSTEM_EVENT_ID) || 
	       (eventParam->event_action_fn == NULL))
		
	
	
		
		
		
		
		
		
				    next);
		
			
			
				       eventLayerListHead, eventLayerList,
				       next);
			
			
			
					    eventLayerListHead, eventLayerList,
					    next);
			
		
		
	
	else
		
		
		
	



{
	
	
	
	
		
		
		
	
			  &eventsTables.inuseList.eventLayerListHead, next) 
		
			
				
				
					
					
					do
						
						
						    event->event_action_fn
						    (actionParam);
					
					
						
					
						
					
						
					
						
						
					
				
		
	
	



{
	
	
	
	
	
			&eventsTables.inuseList.eventLayerListHead, next) 
		
		
		
		    (" No.%d eventLayerList:eventLayerId:%d \n", eventListCnt,
		     eventLayerList->eventLayerId);
		
			
			
			    (" \tNo.%d event:eventId:%d,priority:%d,action_fn is 0x%x\n",
			     eventCnt, event->eventId, event->eventPriority,
			     (unsigned int)(event->event_action_fn));
	



#ifdef CONFIG_RTL865X_EVENT_PROC_DEBUG
#ifdef CONFIG_RTL_PROC_NEW
    int32 rtl865x_event_proc_read(struct seq_file * s, void *v)
{
	
	
	
	
	
	
			  &eventsTables.inuseList.eventLayerListHead, next) 
		
		
		
			    eventListCnt, eventLayerList->eventLayerId);
		
			
			
				    " \tNo.%d event:eventId:0x%x,priority:%d,action_fn is 0x%x\n",
				    eventCnt, event->eventId,
				    event->eventPriority,
				    (unsigned int)(event->event_action_fn));
	
}
#else
    int32 rtl865x_event_proc_read(char *page, char **start, off_t off,
				  int count, int *eof, void *data)
{
	
	
	
	
	
	
	
			  &eventsTables.inuseList.eventLayerListHead, next) 
		
		
		
		    sprintf(page + len,
			    " No.%d eventLayerList:eventLayerId:0x%x \n",
			    eventListCnt, eventLayerList->eventLayerId);
		
			
			
			    sprintf(page + len,
				    " \tNo.%d event:eventId:0x%x,priority:%d,action_fn is 0x%x\n",
				    eventCnt, event->eventId,
				    event->eventPriority,
				    (unsigned int)(event->event_action_fn));
	
		
		
		
	
	len -= off;
	
		
		
		
	
		
		
		
	
}
#endif

int32 rtl865x_event_proc_write(struct file * filp, const char *buff,
			       unsigned long len, void *data)
{
	
}


#endif /* 
    