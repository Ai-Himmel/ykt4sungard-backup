package org.king.task;

import java.text.ParseException;
import java.util.Date;
import java.util.List;

import org.apache.log4j.Logger;
import org.king.host.domain.MonitorHost;
import org.king.host.service.MonitorHostService;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.monitor.MonitorHostJob;
import org.king.monitor.MonitorInfoJob;
import org.king.monitor.MonitorServiceJob;
import org.king.monitor.MonitorTermdevJob;
import org.king.monitor.MonitorTermserviceJob;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorTermdevTemplate;
import org.king.template.service.TemplateService;
import org.king.template.web.action.TermdevTemplateAction;
import org.king.termdev.service.TermdevService;
import org.king.utils.DateUtil;
import org.quartz.CronExpression;
import org.quartz.CronTrigger;
import org.quartz.JobDetail;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.SchedulerFactory;
import org.quartz.SimpleTrigger;
import org.quartz.impl.StdSchedulerFactory;


public class MonitorTaskDelegate {
	
	private static MonitorSupportService monitorSupportService;
	private static MonitorHostService monitorHostService;
	private static MonitorHostserviceService monitorHostserviceService;
	private static TermdevService termdevService;
	private static TemplateService templateService;
	
	public void setMonitorSupportService(MonitorSupportService monitorSupportService) {
		MonitorTaskDelegate.monitorSupportService = monitorSupportService;
	}
	

	public void setMonitorHostService(MonitorHostService monitorHostService) {
		MonitorTaskDelegate.monitorHostService = monitorHostService;
	}

	public void setMonitorHostserviceService(
			MonitorHostserviceService monitorHostserviceService) {
		MonitorTaskDelegate.monitorHostserviceService = monitorHostserviceService;
	}

	public void setTermdevService(TermdevService termdevService) {
		MonitorTaskDelegate.termdevService = termdevService;
	}


	public void setTemplateService(TemplateService templateService) {
		MonitorTaskDelegate.templateService = templateService;
	}


	private static final Logger logger = Logger.getLogger(MonitorTaskDelegate.class);

	private static MonitorTaskDelegate instance = null;
	private static Object mutex = new Object();
	public static Scheduler sched = null;
	/**
	 * 任务分组，主机组别
	 */
	private String HOST_GROUP="host_group";
	/**
	 * 任务分组，主机服务组别
	 */
	private String HOSTSERVICE_GROUP="hostservice_group";
	//
	/**
	 * 任务分组，终端设备分组
	 */
	private String TERMDEV_GROUP="termdev_group";
	
	/**
	 * 任务分组，终端服务分组
	 */
	private String TERMSERVICE_GROUP="termservice_group";
	
	/**
	 * 任务分组，邮件任务
	 */
	private String MAIL_SERVICE="mail_service";
	
	/**
	 * 任务分组，统计任务
	 */
	private String CALC_SERVICE="calc_service";
	
	private String[] JOB_GROUP_NAME = {"",HOST_GROUP,HOSTSERVICE_GROUP,TERMDEV_GROUP,TERMSERVICE_GROUP,MAIL_SERVICE};
	private String[] TRIGGER_GROUP_NAME = JOB_GROUP_NAME;
	private Class[] JOB_CLASS_NAME = {null,MonitorHostJob.class,MonitorServiceJob.class,MonitorTermdevJob.class,MonitorTermserviceJob.class,MonitorInfoJob.class};
	
	public static MonitorTaskDelegate getinstance(){
		if (instance == null) {
			synchronized (mutex) {
				if (instance == null) {
					instance = new MonitorTaskDelegate();
				}
			}
		}
		return instance;
	}
	
	public void LoadAllMonitorTask() throws Exception{
		if (logger.isDebugEnabled()) {
			logger.debug("LoadAllMonitorTask() - start");
		}
		
		SchedulerFactory sf = new StdSchedulerFactory();
		sched = sf.getScheduler();
		
		List queueList = monitorSupportService.initMonitorTask();
		for(int i=0;i<queueList.size();i++){
			MonitorTimedeventqueue mqueue =  (MonitorTimedeventqueue)queueList.get(i);
			JobDetail jobdetail = getJobDetail(mqueue);
			jobdetail.getJobDataMap().put("mqueue", mqueue);
			SimpleTrigger trigger =  getSimpleTrigger(mqueue);
			if(jobdetail!=null&&trigger!=null){
				//sched.addJob(jobdetail, true);
				try {
					sched.scheduleJob(jobdetail, trigger);
				} catch (SchedulerException e) {
					// TODO: handle exception
					logger.error(jobdetail.getFullName() +
			                " scheduler err! SchedulerException message:"+e.getMessage());
				}
				
				logger.info(jobdetail.getFullName() +
		                " will run at: " + trigger.getStartTime() +  
		                " and repeat: " + trigger.getRepeatCount() + 
		                " times, every " + trigger.getRepeatInterval() / 1000 + " seconds");
			}else{
				logger.error("EventType "+mqueue.getEventType() +"Objectid="+ mqueue.getObjectId() +" hasn't been scheduled because of NULL jobdetail or trigger");
			}
		}		
		
		//mail trigger
		
	}
	
	private CronTrigger getCronTrigger(MonitorTimedeventqueue mqueue){
		CronTrigger trigger = null;
		Integer eventtype = mqueue.getEventType();
		if(eventtype<TRIGGER_GROUP_NAME.length&&eventtype>0){
			String triggerName = TRIGGER_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String triggerGroupName = TRIGGER_GROUP_NAME[eventtype];
			String jobName=JOB_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String jobGroupName = JOB_GROUP_NAME[eventtype];
			try {
				String cronExpression = getCronExpression(mqueue);
				if(!"".equals(cronExpression)){
					trigger = new CronTrigger(triggerName,triggerGroupName,jobName,jobGroupName,cronExpression);
				}
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return trigger;		
	}
	private SimpleTrigger getSimpleTrigger(MonitorTimedeventqueue mqueue){
		SimpleTrigger trigger = null;
		Integer eventtype = mqueue.getEventType();
		if(eventtype<TRIGGER_GROUP_NAME.length&&eventtype>0){
			String triggerName = TRIGGER_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String triggerGroupName = TRIGGER_GROUP_NAME[eventtype];
			String jobName=JOB_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String jobGroupName = JOB_GROUP_NAME[eventtype];
			try {
				Date startTime = DateUtil.getDate(mqueue.getScheduledTime(), "yyyyMMddHHmmss");
				long repeatInterval = getrepeatInterval(mqueue,0);
				trigger = new SimpleTrigger(triggerName, triggerGroupName, jobName, jobGroupName, startTime, null, SimpleTrigger.REPEAT_INDEFINITELY, repeatInterval);
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}
		return trigger;		
	}
	private JobDetail getJobDetail(MonitorTimedeventqueue mqueue){
		
		JobDetail jobdetail = null;
		
		Integer eventtype = mqueue.getEventType();
		if(eventtype<JOB_GROUP_NAME.length&&eventtype>0){
			String jobName=JOB_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String jobGroupName = JOB_GROUP_NAME[eventtype];
			Class jobClass = JOB_CLASS_NAME[eventtype];
			jobdetail = new JobDetail(jobName, jobGroupName, jobClass);
		}
		return jobdetail;
		
	}
	
	private String getCronExpression(MonitorTimedeventqueue mqueue){
		//从数据库中读取周期，每个都不同
		String cronExpression = "";
		Integer eventtype = mqueue.getEventType();
		Double checkinterval = null;
		switch (eventtype) {
		case 1:
			//主机
			MonitorHost mhost = monitorHostService.getMonitorHost(mqueue.getObjectId());
			if(mhost!=null){
				checkinterval = mhost.getCheckInterval();
			}
			cronExpression = formatCronExpression(checkinterval,eventtype);
			break;
		case 2:
			MonitorService mservice =  monitorHostserviceService.getMonitorService(mqueue.getObjectId());
			if(mservice!=null){
				checkinterval = mservice.getCheckInterval();
			}
			cronExpression = formatCronExpression(checkinterval,eventtype);
			break;
		case 3:
			cronExpression = formatCronExpression(checkinterval,eventtype);
			break;
		case 4:
			cronExpression = formatCronExpression(checkinterval,eventtype);
			break;
		default:
			break;
		}		
		
		return cronExpression;
		
	}
	
	/**
	* Description: 
	* @param @param mqueue
	* @param @param flag 0:checkinterval  1:retryinterval
	* @param @return
	* @return long
	* Modify History: 2010-8-5 Linqing.He create
	*/
	private long getrepeatInterval(MonitorTimedeventqueue mqueue,int flag){
		long repeatInterval = 5*60*1000;//默认5分钟
		Integer eventtype = mqueue.getEventType();
		Double checkinterval = null;
		switch (eventtype) {
		case 1:
			//主机
			MonitorHost mhost = monitorHostService.getMonitorHost(mqueue.getObjectId());
			if(mhost!=null){
				if(flag==0){
					checkinterval = mhost.getCheckInterval();				
				}else{
					checkinterval = mhost.getRetryInterval();
				}				
				repeatInterval = (long)(checkinterval*60*1000);
			}			
			break;
		case 2:
			MonitorService mservice =  monitorHostserviceService.getMonitorService(mqueue.getObjectId());
			if(mservice!=null){
				if(flag==0){
					checkinterval = mservice.getCheckInterval();				
				}else{
					checkinterval = mservice.getRetryInterval();
				}				
				repeatInterval = (long)(checkinterval*60*1000);
			}
			break;
		case 3:
			 MonitorTermdevTemplate mtermdevtemplate = templateService.findMonitorTermdevTemplateById(mqueue.getObjectId());
			 if(mtermdevtemplate!=null){
				 if(flag==0){
						checkinterval = mtermdevtemplate.getCheckInterval();				
					}else{
						checkinterval = mtermdevtemplate.getRetryInterval();
					}				
					repeatInterval = (long)(checkinterval*60*1000);
			 }
			break;
		case 4:
			break;
		default:
			break;
		}		
		
		return repeatInterval;
	}
	
	private String formatCronExpression(Double checkinterval,Integer eventtype){
		String cronExpression ="";
		String second = "*";
		String minuter = " *";
		String hour = " *";
		String day = " *";
		String month = " *";
		String week = " ?";
		String year = " *";
		if(checkinterval==null||checkinterval<=0){
			switch (eventtype) {
			case 1:
				cronExpression = (int)(Math.random()*60)+" 0/2 * * * ?";
				break;
			case 2:
				cronExpression = (int)(Math.random()*60)+" 0/3 * * * ?";
				break;
			case 3:
				cronExpression = (int)(Math.random()*60)+" 0/5 * * * ?";
				break;
			case 4:
				cronExpression = (int)(Math.random()*60)+" 0/30 * * * ?";
				break;
			default:
				break;
			}	
			return cronExpression;
		}
		if(checkinterval<1){
			//秒级别
			second = String.valueOf(checkinterval*60);
			second = "0/"+second.substring(0, second.indexOf("."));
		}else if(checkinterval<60){
			minuter =  String.valueOf(checkinterval);
			minuter = " 0/"+minuter.substring(0, minuter.indexOf("."));
		}else if(checkinterval<24*60){
			hour =  String.valueOf(checkinterval/60);
			hour = " 0/"+hour.substring(0, hour.indexOf("."));
		}else if(checkinterval<30*24*60){
			day = String.valueOf(checkinterval/60/24);
			day = " 0/"+day.substring(0, day.indexOf("."));
		}else if(checkinterval <12*30*24*60){
			month = String.valueOf(checkinterval/60/24/30);
			month = " 0/"+month.substring(0, month.indexOf("."));
		}else{
			year = String.valueOf(checkinterval/60/24/30/12);
			year = " 0/"+year.substring(0, year.indexOf("."));
		}
		cronExpression = second+minuter+hour+day+month+week+year;
		return cronExpression;
		
		
	}
	
	/**
	* Description: 修改trigger，如果两次trigger 时间相同，则不作修改
	* @param @param mqueue
	* @param @param startTime
	* @param @param flag 0:checkinterval  1:retryinterval
	* @param @return
	* @return boolean
	* Modify History: 2010-8-6 Linqing.He create
	*/
	public synchronized boolean changeTrigger(MonitorTimedeventqueue mqueue,Date startTime,int flag){
		
		SimpleTrigger newTrigger = null;
		Integer eventtype = mqueue.getEventType();
		if(eventtype<TRIGGER_GROUP_NAME.length&&eventtype>0){
			String triggerName = TRIGGER_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String triggerGroupName = TRIGGER_GROUP_NAME[eventtype];
			String jobName=JOB_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String jobGroupName = JOB_GROUP_NAME[eventtype];
			try {
				long repeatInterval = getrepeatInterval(mqueue,flag);
				SimpleTrigger oldtrigger = (SimpleTrigger)sched.getTrigger(triggerName, triggerGroupName);
				long oldrepeatInterval = oldtrigger.getRepeatInterval();
				if(repeatInterval==oldrepeatInterval){
					//nochange
					return true;
				}
				newTrigger = new SimpleTrigger(triggerName, triggerGroupName, jobName, jobGroupName, startTime, null, SimpleTrigger.REPEAT_INDEFINITELY, repeatInterval);
				sched.rescheduleJob(triggerName, triggerGroupName, newTrigger);
				return true;
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}		
		return false;
	}
	
	public synchronized boolean addTrigger(MonitorTimedeventqueue mqueue,Date startTime,int flag){
		JobDetail jobdetail = getJobDetail(mqueue);
		jobdetail.getJobDataMap().put("mqueue", mqueue);
		SimpleTrigger trigger =  getSimpleTrigger(mqueue);
		if(jobdetail!=null&&trigger!=null){
			//sched.addJob(jobdetail, true);
			try {
				sched.scheduleJob(jobdetail, trigger);
				return true;
			} catch (SchedulerException e) {
				// TODO: handle exception
				logger.error(jobdetail.getFullName() +
		                " scheduler err! SchedulerException message:"+e.getMessage());
			}
			
			logger.info(jobdetail.getFullName() +
	                " will run at: " + trigger.getStartTime() +  
	                " and repeat: " + trigger.getRepeatCount() + 
	                " times, every " + trigger.getRepeatInterval() / 1000 + " seconds");
		}else{
			logger.error("EventType "+mqueue.getEventType() +"Objectid="+ mqueue.getObjectId() +" hasn't been scheduled because of NULL jobdetail or trigger");
		}
		
		return false;
	}
	
	public synchronized boolean deleteTrigger(MonitorTimedeventqueue mqueue){
		Integer eventtype = mqueue.getEventType();
		if(eventtype<TRIGGER_GROUP_NAME.length&&eventtype>0){
			String triggerName = TRIGGER_GROUP_NAME[eventtype]+mqueue.getObjectId();
			String triggerGroupName = TRIGGER_GROUP_NAME[eventtype];
			try {
				return sched.unscheduleJob(triggerName, triggerGroupName);
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}		
		return false;
	}
}
