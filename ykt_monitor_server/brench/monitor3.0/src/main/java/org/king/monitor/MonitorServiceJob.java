package org.king.monitor;

import org.king.host.domain.MonitorHost;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceAll;
import org.king.hostservice.domain.MonitorServiceCheck;
import org.king.hostservice.domain.MonitorServiceStatus;
import org.king.hostservice.service.MonitorHostserviceService;
import org.king.monitor.util.MonitorJobUtil;
import org.king.monitor.util.MonitorUtils;
import org.king.support.domain.MonitorNotifications;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.task.MonitorTaskDelegate;
import org.king.topo.service.TopoCalculatorService;
import org.king.utils.DateUtil;
import org.quartz.JobDataMap;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;
import org.quartz.StatefulJob;

public class MonitorServiceJob implements StatefulJob {
	
	private static MonitorHostserviceService monitorHostserviceService;
	private static MonitorSupportService monitorSupportService;
	private static TopoCalculatorService topoCalculatorService;
	public  void setTopoCalculatorService(
			TopoCalculatorService topoCalculatorService) {
		MonitorServiceJob.topoCalculatorService = topoCalculatorService;
	}
	
	public void setMonitorHostserviceService(MonitorHostserviceService monitorHostserviceService) {
		MonitorServiceJob.monitorHostserviceService = monitorHostserviceService;
	}
	public void setMonitorSupportService(
			MonitorSupportService monitorSupportService) {
		MonitorServiceJob.monitorSupportService = monitorSupportService;
	}
	
	private String STATUS_OK ="OK";
	
	private String STATUS_WARNING="WARNING";
	
	private String STATUS_CRITICAL="CRITICAL";
	
	private String STATUS_UNKNOW = "UNKNOW";
	
	private String[] STATUS_ARR ={"Service Recovery","Service Warning","Service Critical","Service Unknow"};
	
	/**
	 * 0=no notification as default
	 * 1=service  recovery
	 * 2=service first warning
	 * 3=service still warning
	 * 4=service first critical
	 * 5=service still critical
	 * 6=service first unknow
	 * 7=service still unknow
	 */
	private int notification =0;
	
	/**
	 * 0= not in downtime
	 * 1= service in downtime include host downtime
	 */
	private int downtime = 0; 

	public void execute(JobExecutionContext context)
			throws JobExecutionException {
		String jobName = context.getJobDetail().getFullName();
		JobDataMap data = context.getJobDetail().getJobDataMap();
		
		MonitorTimedeventqueue mqueue =  (MonitorTimedeventqueue)data.get("mqueue");
		if(mqueue!=null){
			Integer objectid = mqueue.getObjectId();
			MonitorServiceAll monitorservice = monitorHostserviceService.getMonitorServiceAll(objectid);
			MonitorServiceStatus servicestatus = monitorHostserviceService.getMonitorServiceStatus(objectid);
			MonitorHost monitorhost = monitorservice.getMonitorHost();
			
			if(monitorservice==null){
				System.out.println("主机服务，id="+objectid+"似乎被删除，无法找到");
				return;
			}

			//判断是否监控
			if((monitorservice.getActiveChecksEnabled()==null)||(monitorservice.getActiveChecksEnabled()==0)){
				System.out.println("主机信息，id="+objectid+"ActiveCheck is set to false");
				//set hostservice checkflag = 0
				if(monitorservice.getCheckFlag()==null||monitorservice.getCheckFlag()==1){
					monitorservice.setCheckFlag(0);
					monitorHostserviceService.updateMonitorServiceAll(monitorservice);			
				}
				return;
			}
			
			//判断是否在监控工作时间以内
			if(monitorservice.getCheckTimeperiod()!=null){
				if(!MonitorJobUtil.checkinWorktime(DateUtil.getNow(), monitorservice.getCheckTimeperiod().getTimerangers())){
					//set hostservice checkflag = 0
					if(monitorservice.getCheckFlag()==null||monitorservice.getCheckFlag()==1){
						monitorservice.setCheckFlag(0);
						monitorHostserviceService.updateMonitorServiceAll(monitorservice);			
					}
					return;
				}
			}
			
			downtime = 0;
			//判断是否在downtime时间内
			if(monitorSupportService.checkHostserviceDowntime(objectid, DateUtil.getNow())){
				downtime=1;
			}
			//宿主服务器downtime时间内
			if(monitorSupportService.checkHostDowntime(monitorhost.getHostId(), DateUtil.getNow())){
				downtime=1;
			}
			notification = 0;

			
			
			String hostAddress = monitorhost.getHostAddress();
			String commandLine = monitorservice.getCheckCommand().getCommandLine();
			String commandName = monitorservice.getCheckCommand().getCommandName();
			String commandArgs = monitorservice.getCheckCommandArgs();
			try {
				String checkedbeftime = DateUtil.getNow();
				String message ="";
				//String message = "PING OK - Packet loss = 0%, RTA = 2.25 ms|rta=2.253000ms;3000.000000;5000.000000;0.000000 pl=0%;80;100;0";
				message = MonitorUtils.commandExec(hostAddress, commandLine, commandArgs);
				System.out.println(message);
				String checkedafttime = DateUtil.getNow();
				//check whether first check
				if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){
					//continue to check from uncheck as first check
					//1、update last history record's endtime to last check time
					MonitorServiceCheck servicecheck =  monitorHostserviceService.getLattestMonitorServiceCheck(monitorservice.getServiceId());
					if(servicecheck!=null){
						if(servicestatus!=null){
						servicecheck.setEndTime(servicestatus.getStatusUpdateTime());
						}else{
							servicecheck.setEndTime(checkedafttime);
						}
						monitorHostserviceService.updateMonitorServiceCheck(servicecheck);		
					}																
				}
				
				if(message.indexOf(STATUS_OK)!=-1){
					//update 0:ok  1:warning 2:critical 3:unknow
					if(servicestatus!=null){
						if(servicestatus.getCurrentState()==0){							
							//no change
							servicestatus.setLastCheck(checkedbeftime);
							servicestatus.setStatusUpdateTime(checkedafttime);
							servicestatus.setLastTimeOk(checkedbeftime);
							if(message.indexOf("|")!=-1){
								servicestatus.setOutput(message.substring(0, message.indexOf("|")));
								servicestatus.setPerfdata(message.substring(message.indexOf("|")+1));
							}else{
								servicestatus.setOutput(message);
							}
							servicestatus.setCurrentCheckAttempt(1);
							servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
							servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
							servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
							servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
							monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
							if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){
								//add new check to history record
								MonitorServiceCheck MScheck = new MonitorServiceCheck();
								MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
								MScheck.setCheckType(0);
								MScheck.setCommandArgs(commandArgs);
								MScheck.setCommandLine(commandLine);
								MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
								MScheck.setExecutionTime(Double.valueOf(0));
								MScheck.setLatency(Double.valueOf(0));
								MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								MScheck.setServiceId(monitorservice.getServiceId());
								MScheck.setOutput(servicestatus.getOutput());
								MScheck.setPerfdata(servicestatus.getPerfdata());
								MScheck.setReturnCode(0);
								MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
								MScheck.setState(servicestatus.getCurrentState());
								MScheck.setStateType(0);
								MScheck.setTimeout(0);
								monitorHostserviceService.saveMonitorServiceCheck(MScheck);			
							}
						}else{
							//1、update last history record's endtime to last check time
							MonitorServiceCheck servicecheck =  monitorHostserviceService.getLattestMonitorServiceCheck(monitorservice.getServiceId());
							if(servicecheck!=null){
								if(servicecheck.getState()!=0){
									//truely recovery not from retrying
									servicecheck.setEndTime(checkedafttime);
									monitorHostserviceService.updateMonitorServiceCheck(servicecheck);
								}
							}
							//changed status							
							servicestatus.setLastTimeOk(checkedafttime);
							switch (servicestatus.getCurrentState()) {
							case 0:
								servicestatus.setLastTimeWarning(servicestatus.getStatusUpdateTime());
								break;
							case 1:
								servicestatus.setLastTimeWarning(servicestatus.getStatusUpdateTime());
								break;
							case 2:
								servicestatus.setLastTimeCritical(servicestatus.getStatusUpdateTime());
								break;
							case 3:
								servicestatus.setLastTimeUnknow(servicestatus.getStatusUpdateTime());
								break;
							default:
								break;
							}
							servicestatus.setCurrentCheckAttempt(1);
							servicestatus.setLastCheck(checkedbeftime);
							if(message.indexOf("|")!=-1){
								servicestatus.setOutput(message.substring(0, message.indexOf("|")));
								servicestatus.setPerfdata(message.substring(message.indexOf("|")+1));
							}else{
								servicestatus.setOutput(message);
							}
							servicestatus.setStatusUpdateTime(checkedafttime);
							servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
							servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
							servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(servicestatus.getNormalCheckInterval()*60)));
							servicestatus.setLastHardState(servicestatus.getCurrentState());
							servicestatus.setLastStateChange(checkedafttime);
							servicestatus.setLastHardStateChange(checkedafttime);
							if(servicestatus.getStateType()==0){
								MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 0);
							}
							servicestatus.setStateType(1);
							servicestatus.setCurrentState(0);
							monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
							
							if(servicecheck!=null){
								if(servicecheck.getState()!=0){
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
									
									//service recovery
									if(monitorservice.getNotifyOnRecovery()!=null&&monitorservice.getNotifyOnRecovery()==1){
										notification=1;
									}
								}
							}
							
						}
					}else{
						//save first time
						servicestatus = new MonitorServiceStatus();
						servicestatus.setServiceId(monitorservice.getServiceId());
						servicestatus.setStatusUpdateTime(checkedafttime);
						if(message.indexOf("|")!=-1){
							servicestatus.setOutput(message.substring(0, message.indexOf("|")));
							servicestatus.setPerfdata(message.substring(message.indexOf("|")+1));
						}else{
							servicestatus.setOutput(message);
						}
						servicestatus.setLastCheck(checkedbeftime);
						servicestatus.setLastTimeOk(checkedafttime);
						servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
						servicestatus.setCurrentState(0);
						servicestatus.setHasBeenChecked(1);
						servicestatus.setShouldBeScheduled(1);
						servicestatus.setCurrentCheckAttempt(1);
						servicestatus.setLastTimeWarning("");
						servicestatus.setLastTimeCritical("");
						servicestatus.setLastTimeUnknow("");
						servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());						
						servicestatus.setCheckType(0);
						servicestatus.setLastStateChange(checkedafttime);
						servicestatus.setLastHardStateChange(checkedafttime);
						servicestatus.setLastHardState(0);
						servicestatus.setStateType(1);
						servicestatus.setLastNotification("");
						servicestatus.setNextNotification("");
						servicestatus.setNotificationsEnabled(monitorservice.getNotificationsEnabled());
						servicestatus.setProblemHasBeenAcknowledged(0);
						servicestatus.setAcknowledgementType(0);
						servicestatus.setCurrentNotificationNumber(0);
						servicestatus.setPassiveChecksEnabled(monitorservice.getPassiveChecksEnabled());
						servicestatus.setActiveChecksEnabled(monitorservice.getActiveChecksEnabled());
						servicestatus.setEventHandlerEnabled(monitorservice.getEventHandlerEnabled());
						servicestatus.setFlapDetectionEnabled(monitorservice.getFlapDetectionEnabled());
						servicestatus.setIsFlapping(0);
						servicestatus.setPercentStateChange(Double.valueOf(0));
						servicestatus.setLatency(Double.valueOf(0));
						servicestatus.setExecutionTime(Double.valueOf(0));
						servicestatus.setEventHandler("");
						servicestatus.setCheckCommand(commandName);
						servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
						servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
						servicestatus.setCheckTimeperiodId(monitorservice.getCheckTimeperiod().getTimeperiodId());
						monitorHostserviceService.saveMonitorServiceStatus(servicestatus);		
						
						//first  log history
						MonitorServiceCheck MScheck = new MonitorServiceCheck();
						MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
						MScheck.setCheckType(0);
						MScheck.setCommandArgs(commandArgs);
						MScheck.setCommandLine(commandLine);
						MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
						MScheck.setExecutionTime(Double.valueOf(0));
						MScheck.setLatency(Double.valueOf(0));
						MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
						MScheck.setServiceId(monitorservice.getServiceId());
						MScheck.setOutput(servicestatus.getOutput());
						MScheck.setPerfdata(servicestatus.getPerfdata());
						MScheck.setReturnCode(0);
						MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
						MScheck.setState(servicestatus.getCurrentState());
						MScheck.setStateType(0);
						MScheck.setTimeout(0);
						monitorHostserviceService.saveMonitorServiceCheck(MScheck);
					}
				}else if(message.indexOf(STATUS_WARNING)!=-1){
					if(servicestatus!=null){
						if(servicestatus.getCurrentState()==1){
							//no change
							if(servicestatus.getStateType()==0){
								//retrying
								servicestatus.setLastTimeWarning(checkedbeftime);
								servicestatus.setLastCheck(checkedbeftime);
								servicestatus.setOutput(message);							
								servicestatus.setPerfdata("");
								servicestatus.setStatusUpdateTime(checkedafttime);
								servicestatus.setLastStateChange(checkedafttime);
								servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
								servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
								servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								
								if(servicestatus.getCurrentCheckAttempt()>=servicestatus.getMaxCheckAttempts()){
									//max attempt
									servicestatus.setCurrentCheckAttempt(1);
									servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
									servicestatus.setLastHardState(1);
									servicestatus.setLastHardStateChange(checkedafttime);
									servicestatus.setStateType(1);
									MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 0);
									if((downtime==0)||(monitorservice.getNotifyOnDowntime()!=null&&monitorservice.getNotifyOnDowntime()==1)){
										if(monitorservice.getNotifyOnWarning()!=null&&monitorservice.getNotifyOnWarning()==1){
											notification = 2;//service warning definitely after serval retry check.
										}
									}
								}else{
									//retry attempt
									servicestatus.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt()+1);
									servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getRetryInterval()*60)));
								}								
								monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
								
								if(servicestatus.getStateType()==1){
									//1、update last history record's endtime to last check time
									MonitorServiceCheck servicecheck =  monitorHostserviceService.getLattestMonitorServiceCheck(monitorservice.getServiceId());
									if(servicecheck!=null){
										servicecheck.setEndTime(checkedafttime);
									}
									monitorHostserviceService.updateMonitorServiceCheck(servicecheck);
									
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
								}
								
							}else{
								//nomal check
								servicestatus.setLastTimeWarning(checkedafttime);
								servicestatus.setLastCheck(checkedbeftime);
								servicestatus.setOutput(message);							
								servicestatus.setPerfdata("");
								servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
								servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
								servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								servicestatus.setStatusUpdateTime(checkedafttime);
								servicestatus.setCurrentCheckAttempt(1);
								servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
								monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
								
								if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){		
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
								}
								
								if((downtime==0)||(monitorservice.getNotifyOnDowntime()!=null&&monitorservice.getNotifyOnDowntime()==1)){
									if(monitorservice.getNotifyOnWarning()!=null&&monitorservice.getNotifyOnWarning()==1){
										notification = 3;//service still warning
									}
								}
							}
						}else{
							//status changed								
							switch (servicestatus.getCurrentState()) {
							case 0:
								servicestatus.setLastTimeOk(servicestatus.getStatusUpdateTime());
								break;
							case 1:
								servicestatus.setLastTimeWarning(servicestatus.getStatusUpdateTime());
								break;
							case 2:
								servicestatus.setLastTimeCritical(servicestatus.getStatusUpdateTime());
								break;
							case 3:
								servicestatus.setLastTimeUnknow(servicestatus.getStatusUpdateTime());
								break;
							default:
								break;
							}
							servicestatus.setCurrentCheckAttempt(1);
							servicestatus.setLastCheck(checkedbeftime);
							servicestatus.setStatusUpdateTime(checkedafttime);
							servicestatus.setOutput(message);
							servicestatus.setPerfdata("");
							servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
							servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
							servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
							servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getRetryInterval()*60)));
							servicestatus.setLastStateChange(checkedafttime);
							servicestatus.setStateType(0);//retry attempt
							servicestatus.setCurrentState(1);
							monitorHostserviceService.updateMonitorServiceStatus(servicestatus);	
							MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 1);
						}
					}else{
						//save first time
						servicestatus = new MonitorServiceStatus();
						servicestatus.setServiceId(monitorservice.getServiceId());
						servicestatus.setStatusUpdateTime(checkedafttime);
						if(message.indexOf("|")!=-1){
							servicestatus.setOutput(message.substring(0, message.indexOf("|")));
							servicestatus.setPerfdata(message.substring(message.indexOf("|")+1));
						}else{
							servicestatus.setOutput(message);
						}
						servicestatus.setLastCheck(checkedbeftime);
						servicestatus.setLastTimeOk("");
						servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
						servicestatus.setCurrentState(1);
						servicestatus.setHasBeenChecked(1);
						servicestatus.setShouldBeScheduled(1);
						servicestatus.setCurrentCheckAttempt(1);
						servicestatus.setLastTimeWarning(checkedafttime);
						servicestatus.setLastTimeCritical("");
						servicestatus.setLastTimeUnknow("");
						servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());						
						servicestatus.setCheckType(0);
						servicestatus.setLastStateChange(checkedafttime);
						servicestatus.setLastHardStateChange(checkedafttime);
						servicestatus.setLastHardState(1);
						servicestatus.setStateType(1);
						servicestatus.setLastNotification("");
						servicestatus.setNextNotification("");
						servicestatus.setNotificationsEnabled(monitorservice.getNotificationsEnabled());
						servicestatus.setProblemHasBeenAcknowledged(0);
						servicestatus.setAcknowledgementType(0);
						servicestatus.setCurrentNotificationNumber(0);
						servicestatus.setPassiveChecksEnabled(monitorservice.getPassiveChecksEnabled());
						servicestatus.setActiveChecksEnabled(monitorservice.getActiveChecksEnabled());
						servicestatus.setEventHandlerEnabled(monitorservice.getEventHandlerEnabled());
						servicestatus.setFlapDetectionEnabled(monitorservice.getFlapDetectionEnabled());
						servicestatus.setIsFlapping(0);
						servicestatus.setPercentStateChange(Double.valueOf(0));
						servicestatus.setLatency(Double.valueOf(0));
						servicestatus.setExecutionTime(Double.valueOf(0));
						servicestatus.setEventHandler("");
						servicestatus.setCheckCommand(commandName);
						servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
						servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
						servicestatus.setCheckTimeperiodId(monitorservice.getCheckTimeperiod().getTimeperiodId());
						monitorHostserviceService.saveMonitorServiceStatus(servicestatus);							
						//first  log history
						MonitorServiceCheck MScheck = new MonitorServiceCheck();
						MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
						MScheck.setCheckType(0);
						MScheck.setCommandArgs(commandArgs);
						MScheck.setCommandLine(commandLine);
						MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
						MScheck.setExecutionTime(Double.valueOf(0));
						MScheck.setLatency(Double.valueOf(0));
						MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
						MScheck.setServiceId(monitorservice.getServiceId());
						MScheck.setOutput(servicestatus.getOutput());
						MScheck.setPerfdata(servicestatus.getPerfdata());
						MScheck.setReturnCode(0);
						MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
						MScheck.setState(servicestatus.getCurrentState());
						MScheck.setStateType(0);
						MScheck.setTimeout(0);
						monitorHostserviceService.saveMonitorServiceCheck(MScheck);
					}
					
				}else if(message.indexOf(STATUS_CRITICAL)!=-1){
					if(servicestatus!=null){
						if(servicestatus.getCurrentState()==2){
							//no change
							if(servicestatus.getStateType()==0){
								//retrying
								servicestatus.setLastTimeCritical(checkedbeftime);
								servicestatus.setLastCheck(checkedbeftime);
								servicestatus.setOutput(message);							
								servicestatus.setPerfdata("");
								servicestatus.setStatusUpdateTime(checkedafttime);
								servicestatus.setLastStateChange(checkedafttime);
								servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
								servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
								servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								if(servicestatus.getCurrentCheckAttempt()>=servicestatus.getMaxCheckAttempts()){
									//max attempt
									servicestatus.setCurrentCheckAttempt(1);
									servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
									servicestatus.setLastHardState(2);
									servicestatus.setLastHardStateChange(checkedafttime);
									servicestatus.setStateType(1);
									MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 0);
									if((downtime==0)||(monitorservice.getNotifyOnDowntime()!=null&&monitorservice.getNotifyOnDowntime()==1)){
										if(monitorservice.getNotifyOnCritical()!=null&&monitorservice.getNotifyOnCritical()==1){
											notification = 4;//service critical definitely after serval retry check.
										}
									}
								}else{
									//retry attempt
									servicestatus.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt()+1);
									servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getRetryInterval()*60)));
								}								
								monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
	
								if(servicestatus.getStateType()==1){
									//1、update last history record's endtime to last check time
									MonitorServiceCheck servicecheck =  monitorHostserviceService.getLattestMonitorServiceCheck(monitorservice.getServiceId());
									if(servicecheck!=null){
										servicecheck.setEndTime(checkedafttime);
									}
									monitorHostserviceService.updateMonitorServiceCheck(servicecheck);
									
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
								}
								
							}else{
								//nomal check
								servicestatus.setLastTimeCritical(checkedafttime);
								servicestatus.setLastCheck(checkedbeftime);
								servicestatus.setOutput(message);							
								servicestatus.setPerfdata("");
								servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
								servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
								servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								servicestatus.setStatusUpdateTime(checkedafttime);
								servicestatus.setCurrentCheckAttempt(1);
								servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
								monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
								
								if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){	
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
								}
								
								if((downtime==0)||(monitorservice.getNotifyOnDowntime()!=null&&monitorservice.getNotifyOnDowntime()==1)){
									if(monitorservice.getNotifyOnCritical()!=null&&monitorservice.getNotifyOnCritical()==1){
										notification = 5;//service critical definitely after serval retry check.
									}
								}
							}
						}else{							
							//status changed								
							switch (servicestatus.getCurrentState()) {
							case 0:
								servicestatus.setLastTimeOk(servicestatus.getStatusUpdateTime());
								break;
							case 1:
								servicestatus.setLastTimeWarning(servicestatus.getStatusUpdateTime());
								break;
							case 2:
								servicestatus.setLastTimeCritical(servicestatus.getStatusUpdateTime());
								break;
							case 3:
								servicestatus.setLastTimeUnknow(servicestatus.getStatusUpdateTime());
								break;
							default:
								break;
							}
							servicestatus.setCurrentCheckAttempt(1);
							servicestatus.setLastCheck(checkedbeftime);
							servicestatus.setStatusUpdateTime(checkedafttime);
							servicestatus.setOutput(message);
							servicestatus.setPerfdata("");
							servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
							servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
							servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
							servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getRetryInterval()*60)));
							servicestatus.setLastStateChange(checkedafttime);
							servicestatus.setStateType(0);//retry attempt
							servicestatus.setCurrentState(2);
							monitorHostserviceService.updateMonitorServiceStatus(servicestatus);		
							MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 1);
						}
					}else{
						//save first time
						servicestatus = new MonitorServiceStatus();
						servicestatus.setServiceId(monitorservice.getServiceId());
						servicestatus.setStatusUpdateTime(checkedafttime);
						if(message.indexOf("|")!=-1){
							servicestatus.setOutput(message.substring(0, message.indexOf("|")));
							servicestatus.setPerfdata(message.substring(message.indexOf("|")+1));
						}else{
							servicestatus.setOutput(message);
						}
						servicestatus.setLastCheck(checkedbeftime);
						servicestatus.setLastTimeOk("");
						servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
						servicestatus.setCurrentState(2);
						servicestatus.setHasBeenChecked(1);
						servicestatus.setShouldBeScheduled(1);
						servicestatus.setCurrentCheckAttempt(1);
						servicestatus.setLastTimeWarning("");
						servicestatus.setLastTimeCritical(checkedafttime);
						servicestatus.setLastTimeUnknow("");
						servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());						
						servicestatus.setCheckType(0);
						servicestatus.setLastStateChange(checkedafttime);
						servicestatus.setLastHardStateChange(checkedafttime);
						servicestatus.setLastHardState(0);
						servicestatus.setStateType(1);
						servicestatus.setLastNotification("");
						servicestatus.setNextNotification("");
						servicestatus.setNotificationsEnabled(monitorservice.getNotificationsEnabled());
						servicestatus.setProblemHasBeenAcknowledged(0);
						servicestatus.setAcknowledgementType(0);
						servicestatus.setCurrentNotificationNumber(0);
						servicestatus.setPassiveChecksEnabled(monitorservice.getPassiveChecksEnabled());
						servicestatus.setActiveChecksEnabled(monitorservice.getActiveChecksEnabled());
						servicestatus.setEventHandlerEnabled(monitorservice.getEventHandlerEnabled());
						servicestatus.setFlapDetectionEnabled(monitorservice.getFlapDetectionEnabled());
						servicestatus.setIsFlapping(0);
						servicestatus.setPercentStateChange(Double.valueOf(0));
						servicestatus.setLatency(Double.valueOf(0));
						servicestatus.setExecutionTime(Double.valueOf(0));
						servicestatus.setEventHandler("");
						servicestatus.setCheckCommand(commandName);
						servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
						servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
						servicestatus.setCheckTimeperiodId(monitorservice.getCheckTimeperiod().getTimeperiodId());
						monitorHostserviceService.saveMonitorServiceStatus(servicestatus);	
						//first  log history
						MonitorServiceCheck MScheck = new MonitorServiceCheck();
						MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
						MScheck.setCheckType(0);
						MScheck.setCommandArgs(commandArgs);
						MScheck.setCommandLine(commandLine);
						MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
						MScheck.setExecutionTime(Double.valueOf(0));
						MScheck.setLatency(Double.valueOf(0));
						MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
						MScheck.setServiceId(monitorservice.getServiceId());
						MScheck.setOutput(servicestatus.getOutput());
						MScheck.setPerfdata(servicestatus.getPerfdata());
						MScheck.setReturnCode(0);
						MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
						MScheck.setState(servicestatus.getCurrentState());
						MScheck.setStateType(0);
						MScheck.setTimeout(0);
						monitorHostserviceService.saveMonitorServiceCheck(MScheck);
					}
				}else{
					if(servicestatus!=null){
						if(servicestatus.getCurrentState()==3){
							//no change
							if(servicestatus.getStateType()==0){
								//retrying
								servicestatus.setLastTimeUnknow(checkedbeftime);
								servicestatus.setLastCheck(checkedbeftime);
								servicestatus.setOutput(message);							
								servicestatus.setPerfdata("");
								servicestatus.setStatusUpdateTime(checkedafttime);
								servicestatus.setLastStateChange(checkedafttime);
								servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
								servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
								servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								if(servicestatus.getCurrentCheckAttempt()>=servicestatus.getMaxCheckAttempts()){
									//max attempt
									servicestatus.setCurrentCheckAttempt(1);
									servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
									servicestatus.setLastHardState(3);
									servicestatus.setLastHardStateChange(checkedafttime);
									servicestatus.setStateType(1);
									MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 0);
									if((downtime==0)||(monitorservice.getNotifyOnDowntime()!=null&&monitorservice.getNotifyOnDowntime()==1)){
										if(monitorservice.getNotifyOnUnknown()!=null&&monitorservice.getNotifyOnUnknown()==1){
											notification = 6;//service unknow definitely after serval retry check.
										}
									}
								}else{
									//retry attempt
									servicestatus.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt()+1);
									servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getRetryInterval()*60)));
								}								
								monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
								if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){
									monitorservice.setCheckFlag(1);
									monitorHostserviceService.updateMonitorServiceAll(monitorservice);	
								}
								
								if(servicestatus.getStateType()==1){
									//1、update last history record's endtime to last check time
									MonitorServiceCheck servicecheck =  monitorHostserviceService.getLattestMonitorServiceCheck(monitorservice.getServiceId());
									if(servicecheck!=null){
										servicecheck.setEndTime(checkedafttime);
									}
									monitorHostserviceService.updateMonitorServiceCheck(servicecheck);
									
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
								}
							}else{
								//nomal check
								servicestatus.setLastTimeUnknow(checkedafttime);
								servicestatus.setLastCheck(checkedbeftime);
								servicestatus.setOutput(message);							
								servicestatus.setPerfdata("");
								servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
								servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
								servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
								servicestatus.setStatusUpdateTime(checkedafttime);
								servicestatus.setCurrentCheckAttempt(1);
								servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
								monitorHostserviceService.updateMonitorServiceStatus(servicestatus);
								
								if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){	
									//first  log history
									MonitorServiceCheck MScheck = new MonitorServiceCheck();
									MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
									MScheck.setCheckType(0);
									MScheck.setCommandArgs(commandArgs);
									MScheck.setCommandLine(commandLine);
									MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
									MScheck.setExecutionTime(Double.valueOf(0));
									MScheck.setLatency(Double.valueOf(0));
									MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
									MScheck.setServiceId(monitorservice.getServiceId());
									MScheck.setOutput(servicestatus.getOutput());
									MScheck.setPerfdata(servicestatus.getPerfdata());
									MScheck.setReturnCode(0);
									MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
									MScheck.setState(servicestatus.getCurrentState());
									MScheck.setStateType(0);
									MScheck.setTimeout(0);
									monitorHostserviceService.saveMonitorServiceCheck(MScheck);
								}
								if((downtime==0)||(monitorservice.getNotifyOnDowntime()!=null&&monitorservice.getNotifyOnDowntime()==1)){
									if(monitorservice.getNotifyOnCritical()!=null&&monitorservice.getNotifyOnCritical()==1){
										notification = 7;//service still unkow
									}
								}
							}
						}else{
							//status changed								
							switch (servicestatus.getCurrentState()) {
							case 0:
								servicestatus.setLastTimeOk(servicestatus.getStatusUpdateTime());
								break;
							case 1:
								servicestatus.setLastTimeWarning(servicestatus.getStatusUpdateTime());
								break;
							case 2:
								servicestatus.setLastTimeCritical(servicestatus.getStatusUpdateTime());
								break;
							case 3:
								servicestatus.setLastTimeUnknow(servicestatus.getStatusUpdateTime());
								break;
							default:
								break;
							}
							servicestatus.setCurrentCheckAttempt(1);
							servicestatus.setLastCheck(checkedbeftime);
							servicestatus.setStatusUpdateTime(checkedafttime);
							servicestatus.setOutput(message);
							servicestatus.setPerfdata("");
							servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
							servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
							servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
							servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getRetryInterval()*60)));
							servicestatus.setLastStateChange(checkedafttime);
							servicestatus.setStateType(0);//retry attempt
							servicestatus.setCurrentState(3);
							monitorHostserviceService.updateMonitorServiceStatus(servicestatus);	
							MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(servicestatus.getNextCheck(), "yyyyMMddHHmmss"), 1);
						}			
					}else{
						//save first time
						servicestatus = new MonitorServiceStatus();
						servicestatus.setServiceId(monitorservice.getServiceId());
						servicestatus.setStatusUpdateTime(checkedafttime);
						if(message.indexOf("|")!=-1){
							servicestatus.setOutput(message.substring(0, message.indexOf("|")));
							servicestatus.setPerfdata(message.substring(message.indexOf("|")+1));
						}else{
							servicestatus.setOutput(message);
						}
						servicestatus.setLastCheck(checkedbeftime);
						servicestatus.setLastTimeOk("");
						servicestatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorservice.getCheckInterval()*60)));
						servicestatus.setCurrentState(3);
						servicestatus.setHasBeenChecked(1);
						servicestatus.setShouldBeScheduled(1);
						servicestatus.setCurrentCheckAttempt(1);
						servicestatus.setLastTimeWarning("");
						servicestatus.setLastTimeCritical("");
						servicestatus.setLastTimeUnknow(checkedbeftime);
						servicestatus.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());						
						servicestatus.setCheckType(0);
						servicestatus.setLastStateChange(checkedafttime);
						servicestatus.setLastHardStateChange(checkedafttime);
						servicestatus.setLastHardState(0);
						servicestatus.setStateType(1);
						servicestatus.setLastNotification("");
						servicestatus.setNextNotification("");
						servicestatus.setNotificationsEnabled(monitorservice.getNotificationsEnabled());
						servicestatus.setProblemHasBeenAcknowledged(0);
						servicestatus.setAcknowledgementType(0);
						servicestatus.setCurrentNotificationNumber(0);
						servicestatus.setPassiveChecksEnabled(monitorservice.getPassiveChecksEnabled());
						servicestatus.setActiveChecksEnabled(monitorservice.getActiveChecksEnabled());
						servicestatus.setEventHandlerEnabled(monitorservice.getEventHandlerEnabled());
						servicestatus.setFlapDetectionEnabled(monitorservice.getFlapDetectionEnabled());
						servicestatus.setIsFlapping(0);
						servicestatus.setPercentStateChange(Double.valueOf(0));
						servicestatus.setLatency(Double.valueOf(0));
						servicestatus.setExecutionTime(Double.valueOf(0));
						servicestatus.setEventHandler("");
						servicestatus.setCheckCommand(commandName);
						servicestatus.setNormalCheckInterval(monitorservice.getCheckInterval());
						servicestatus.setRetryCheckInterval(monitorservice.getRetryInterval());
						servicestatus.setCheckTimeperiodId(monitorservice.getCheckTimeperiod().getTimeperiodId());
						monitorHostserviceService.saveMonitorServiceStatus(servicestatus);		
						//first  log history
						MonitorServiceCheck MScheck = new MonitorServiceCheck();
						MScheck.setCommandId(monitorservice.getCheckCommand().getCommandId());
						MScheck.setCheckType(0);
						MScheck.setCommandArgs(commandArgs);
						MScheck.setCommandLine(commandLine);
						MScheck.setCurrentCheckAttempt(servicestatus.getCurrentCheckAttempt());
						MScheck.setExecutionTime(Double.valueOf(0));
						MScheck.setLatency(Double.valueOf(0));
						MScheck.setMaxCheckAttempts(monitorservice.getMaxCheckAttempts());
						MScheck.setServiceId(monitorservice.getServiceId());
						MScheck.setOutput(servicestatus.getOutput());
						MScheck.setPerfdata(servicestatus.getPerfdata());
						MScheck.setReturnCode(0);
						MScheck.setStartTime(servicestatus.getStatusUpdateTime());							
						MScheck.setState(servicestatus.getCurrentState());
						MScheck.setStateType(0);
						MScheck.setTimeout(0);
						monitorHostserviceService.saveMonitorServiceCheck(MScheck);
					}					
				}
				
				if(monitorservice.getCheckFlag()!=null&&monitorservice.getCheckFlag()==0){
					monitorservice.setCheckFlag(1);
					monitorHostserviceService.updateMonitorServiceAll(monitorservice);	
				}				
				
				//修改timed event
				mqueue.setScheduledTime(servicestatus.getNextCheck());
				monitorSupportService.updateMonitorTimedeventqueue(mqueue);
				//notification about
				/**
				 * 0=no notification as default
				 * 1=service  recovery
				 * 2=service first warning
				 * 3=service still warning
				 * 4=service first critical
				 * 5=service still critical
				 * 6=service first unknow
				 * 7=service still unknow
				 */
				if(notification>0){
					//need notification
					if((notification==1)||(notification==2)||(notification==4)||(notification==6)){
						MonitorNotifications mn = new MonitorNotifications();
						mn.setContactGroup(monitorservice.getContactGroups());
						mn.setNotificationTime(DateUtil.getNow());
						mn.setNotificationType(2);//service
						mn.setObjectId(monitorservice.getServiceId());
						mn.setOutput(servicestatus.getOutput());
						mn.setOutput("<pre>时间:"+servicestatus.getStatusUpdateTime()+"		主机:"+monitorhost.getDisplayName()+"	服务:"+monitorservice.getServiceName()+"		状态:"+STATUS_ARR[servicestatus.getCurrentState()]+"		返回信息：["+servicestatus.getOutput()+"|"+servicestatus.getPerfdata()+"]</pre>");
						mn.setSendOrNot(0);
						switch (notification) {
						case 1:
							mn.setState(0);	
							break;
						case 2:
							mn.setState(1);	
							break;
						case 4:
							mn.setState(2);	
							break;
						case 6:
							mn.setState(3);	
							break;
						default:
							break;
						}
						monitorSupportService.saveMonitorNotifications(mn);
					}				
				}
				
				topoCalculatorService.calculateTopoServerStatistic(1);
				
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
			
		}

	}

}
