package org.king.host.interceptor;

import java.lang.reflect.Method;

import org.king.host.domain.MonitorHost;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.task.MonitorTaskDelegate;
import org.king.utils.DateUtil;
import org.springframework.aop.AfterReturningAdvice;

public class MonitorHostServiceAfterAdvice implements AfterReturningAdvice {
	
    private MonitorSupportService monitorSupportService;

	public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
		this.monitorSupportService = monitorSupportService;
	}

	public void afterReturning(Object returnValue, Method method, Object[] arg2,
			Object arg3) throws Throwable {
		try {
			if(method.getName().startsWith("save")){
				for(int i=0;i<arg2.length;i++){
					 if (arg2[i] instanceof MonitorHost) {
						 MonitorHost mh = (MonitorHost) arg2[i];
						 	System.out.println("主机信息添加成功，主机id="+mh.getHostId());
						 	MonitorTimedeventqueue newMT = new MonitorTimedeventqueue();
				            newMT.setEventType(1);
				            newMT.setObjectId(mh.getHostId());
				            newMT.setQueueTime(DateUtil.getNow());
				            newMT.setRecurringEvent(1);
				            newMT.setScheduledTime(DateUtil.getNewTime(DateUtil.getNow(), 60));
				            monitorSupportService.saveMonitorTimedeventqueue(newMT);
				            MonitorTaskDelegate.getinstance().addTrigger(newMT, DateUtil.getDate(newMT.getScheduledTime(), "yyyyMMddHHmmss"), 0);
						}
				}
			}else if(method.getName().startsWith("update")){
				for(int i=0;i<arg2.length;i++){
					 if (arg2[i] instanceof MonitorHost) {
						 MonitorHost mh = (MonitorHost) arg2[i];
						 System.out.println("主机信息更新成功，主机id="+mh.getHostId());
						 MonitorTimedeventqueue mqueue =  monitorSupportService.findMonitorTimedeventqueueByObjectAndType(mh.getHostId(), 1);
						 MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(DateUtil.getNewTime(DateUtil.getNow(), 0)), 0);
						}
				}
			}else if(method.getName().startsWith("delete")){
				for(int i=0;i<arg2.length;i++){
					 if (arg2[i] instanceof Integer) {
						 Integer objectId = (Integer) arg2[i];
						 System.out.println("主机信息被删除，主机id="+objectId);
						 MonitorTimedeventqueue mqueue =  monitorSupportService.findMonitorTimedeventqueueByObjectAndType(objectId, 1);
						 if(mqueue!=null){
							 monitorSupportService.deleteMonitorTimedeventqueue(mqueue);
						 }
						 MonitorTaskDelegate.getinstance().deleteTrigger(mqueue);
						}
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		
	  
	}
	
	

}
