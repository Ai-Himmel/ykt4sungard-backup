package org.king.template.interceptor;

import java.lang.reflect.Method;

import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.task.MonitorTaskDelegate;
import org.king.template.domain.MonitorTermdevTemplate;
import org.king.utils.DateUtil;
import org.springframework.aop.AfterReturningAdvice;

public class TemplateServiceAfterAdvice implements AfterReturningAdvice {
	
    private MonitorSupportService monitorSupportService;

	public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
		this.monitorSupportService = monitorSupportService;
	}

	public void afterReturning(Object returnValue, Method method, Object[] arg2,
			Object arg3) throws Throwable {
		try {
			if(method.getName().startsWith("save")){
				for(int i=0;i<arg2.length;i++){
					 if (arg2[i] instanceof MonitorTermdevTemplate) {
						 	MonitorTermdevTemplate mtt = (MonitorTermdevTemplate) arg2[i];
						 	System.out.println("设备模板添加成功，模板id="+mtt.getTemplateName()+"["+mtt.getTemplateId()+"]");
						 	MonitorTimedeventqueue newMT = new MonitorTimedeventqueue();
				            newMT.setEventType(3);
				            newMT.setObjectId(mtt.getTemplateId());
				            newMT.setQueueTime(DateUtil.getNow());
				            newMT.setRecurringEvent(1);
				            newMT.setScheduledTime(DateUtil.getNewTime(DateUtil.getNow(), 180));
				            monitorSupportService.saveMonitorTimedeventqueue(newMT);
				            MonitorTaskDelegate.getinstance().addTrigger(newMT, DateUtil.getDate(newMT.getScheduledTime(), "yyyyMMddHHmmss"), 0);
						}
				}
			}else if(method.getName().startsWith("update")){
				for(int i=0;i<arg2.length;i++){
					 if (arg2[i] instanceof MonitorTermdevTemplate) {
						 MonitorTermdevTemplate mtt = (MonitorTermdevTemplate) arg2[i];
						 System.out.println("设备模板跟新成功，模板id="+mtt.getTemplateName()+"["+mtt.getTemplateId()+"]");
						 MonitorTimedeventqueue mqueue =  monitorSupportService.findMonitorTimedeventqueueByObjectAndType(mtt.getTemplateId(), 3);
						 MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(DateUtil.getNewTime(DateUtil.getNow(), 0)), 0);
						}
				}
			}else if(method.getName().startsWith("deleteMonitorTermdevTemplate")){
				for(int i=0;i<arg2.length;i++){
					 if (arg2[i] instanceof Integer) {
						 Integer objectId = (Integer) arg2[i];
						 System.out.println("设备模板被删除，模板id="+objectId);
						 MonitorTimedeventqueue mqueue =  monitorSupportService.findMonitorTimedeventqueueByObjectAndType(objectId, 3);
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
