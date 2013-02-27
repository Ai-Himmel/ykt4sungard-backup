package org.king.monitor;

import org.king.host.domain.MonitorHostAll;
import org.king.host.domain.MonitorHostStatus;
import org.king.host.domain.MonitorHostchecks;
import org.king.host.service.MonitorHostService;
import org.king.monitor.util.MonitorJobUtil;
import org.king.monitor.util.MonitorUtils;
import org.king.support.domain.MonitorNotifications;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.task.MonitorTaskDelegate;
import org.king.utils.DateUtil;
import org.quartz.JobDataMap;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;
import org.quartz.StatefulJob;

public class MonitorHostJob implements StatefulJob{
	
	
	
	private static MonitorHostService monitorHostService;
	private static MonitorSupportService monitorSupportService;

	public void setMonitorHostService(MonitorHostService monitorHostService) {
		MonitorHostJob.monitorHostService = monitorHostService;
	}

	public void setMonitorSupportService(
			MonitorSupportService monitorSupportService) {
		MonitorHostJob.monitorSupportService = monitorSupportService;
	}
	private String STATUS_OK ="OK";
	
	private String STATUS_WARNING="WARNING";
	
	private String STATUS_CRITICAL="CRITICAL";
	
	private String STATUS_UNKNOW = "UNKNOW";
	
	private String[] STATUS_ARR = {"Host Recovery","Host Down","Host Unreachable","Host Pending"};
	
	private int notification =0;  //0=no 1=recovery 2=first down 3=still down 4=first unreachable  5=still unreachable
	
	private int downtime = 0; //1=down time
	
//	private int hislog = 0;//0=no 1=log history

	public void execute(JobExecutionContext context)
			throws JobExecutionException {
		String jobName = context.getJobDetail().getFullName();
		JobDataMap data = context.getJobDetail().getJobDataMap();
		
		MonitorTimedeventqueue mqueue =  (MonitorTimedeventqueue)data.get("mqueue");
		if(mqueue!=null){
			Integer objectid = mqueue.getObjectId();
			MonitorHostAll monitorhost =  monitorHostService.getMonitorHostAll(objectid);
			
			if(monitorhost==null){
				System.out.println("主机信息，id="+objectid+"似乎被删除，无法找到");
				return;
			}
			//判断是否监控
			if((monitorhost.getActiveChecksEnabled()==null)||(monitorhost.getActiveChecksEnabled()==0)){
				System.out.println("主机信息，id="+objectid+"ActiveCheck is set to false");
				//set host checkflag = 0
				if(monitorhost.getCheckFlag()==null||monitorhost.getCheckFlag()==1){
					monitorhost.setCheckFlag(0);
					monitorHostService.updateMonitorHostAll(monitorhost);			
				}
				
				return;
			}
			//判断是否在监控工作时间以内
			if(monitorhost.getCheckTimeperiod()!=null){
				if(!MonitorJobUtil.checkinWorktime(DateUtil.getNow(), monitorhost.getCheckTimeperiod().getTimerangers())){
					//set host checkflag = 0
					if(monitorhost.getCheckFlag()==null||monitorhost.getCheckFlag()==1){
						monitorhost.setCheckFlag(0);
						monitorHostService.updateMonitorHostAll(monitorhost);
					}
					return;
				}
			}
			downtime = 0;
			//判断是否在downtime时间内
			if(monitorSupportService.checkHostDowntime(objectid, DateUtil.getNow())){
				downtime=1;
			}
			notification = 0;
			
			MonitorHostStatus hoststatus = monitorHostService.getMonitorHostStatus(objectid);
			String hostAddress = monitorhost.getHostAddress();
			String commandLine = monitorhost.getCheckCommand().getCommandLine();
			String commandName = monitorhost.getCheckCommand().getCommandName();
			String commandArgs = monitorhost.getCheckCommandArgs();
			try {
				String checkedbeftime = DateUtil.getNow();
				String message ="";
				//String message = "PING OK - Packet loss = 0%, RTA = 2.25 ms|rta=2.253000ms;3000.000000;5000.000000;0.000000 pl=0%;80;100;0";

				message = MonitorUtils.commandExec(hostAddress, commandLine, commandArgs);		
				System.out.println(message);
				String checkedafttime = DateUtil.getNow();
				//check whether first check
				if(monitorhost.getCheckFlag()!=null&&monitorhost.getCheckFlag()==0){
					//continue to check from uncheck as first check
					//1、update last history record's endtime to last check time
					MonitorHostchecks monitorcheck =  monitorHostService.getLattestMonitorHostchecks(monitorhost.getHostId());
					if(monitorcheck!=null){
						if(hoststatus!=null){
							monitorcheck.setEndTime(hoststatus.getStatusUpdateTime());
						}else{
							monitorcheck.setEndTime(checkedafttime);
						}
						monitorHostService.updateMonitorHostchecks(monitorcheck);
					}
				}
				
				if((message.indexOf(STATUS_OK)!=-1)||(message.indexOf(STATUS_WARNING)!=-1)){
					//up-ok or warning
					if(hoststatus!=null){
						//update 0:up  1:down
						if(hoststatus.getCurrentState()==0){	
							//no change
							hoststatus.setLastCheck(checkedbeftime);
							hoststatus.setStatusUpdateTime(checkedafttime);
							hoststatus.setLastTimeUp(checkedbeftime);
							if(message.indexOf("|")!=-1){
								hoststatus.setOutput(message.substring(0, message.indexOf("|")));
								hoststatus.setPerfdata(message.substring(message.indexOf("|")+1));
							}else{
								hoststatus.setOutput(message);
							}
							hoststatus.setCurrentCheckAttempt(1);
							hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
							hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
							hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());
							hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getCheckInterval()*60)));
							monitorHostService.updateMonitorHostStatus(hoststatus);	
							
							if(monitorhost.getCheckFlag()!=null&&monitorhost.getCheckFlag()==0){
								//add new check to history record
								MonitorHostchecks MHcheck =  new MonitorHostchecks();
								MHcheck.setCheckType(0);
								MHcheck.setCommandArgs(commandArgs);
								MHcheck.setCommandId(monitorhost.getCheckCommand().getCommandId());
								MHcheck.setCommandLine(commandLine);
								MHcheck.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt());
								MHcheck.setExecutionTime(Double.valueOf(0));
								MHcheck.setHostId(monitorhost.getHostId());
								MHcheck.setLatency(Double.valueOf(0));
								MHcheck.setMaxCheckAttempts(hoststatus.getMaxCheckAttempts());
								MHcheck.setOutput(hoststatus.getOutput());
								MHcheck.setPerfdata(hoststatus.getPerfdata());
								MHcheck.setReturnCode(0);
								MHcheck.setStartTime(hoststatus.getStatusUpdateTime());
								MHcheck.setStateType(0);
								MHcheck.setState(hoststatus.getCurrentState());
								MHcheck.setTimeout(0);
								monitorHostService.saveMonitorHostchecks(MHcheck);								
							}
							
						}else{
							//changed status host recovery!
							//first  log history
							//1、update last history record's endtime to last check time
							MonitorHostchecks monitorcheck =  monitorHostService.getLattestMonitorHostchecks(monitorhost.getHostId());
							if(monitorcheck!=null){
								if(monitorcheck.getState()!=0){
									//truely recovery from down not from retry!!!
								monitorcheck.setEndTime(checkedafttime);
								monitorHostService.updateMonitorHostchecks(monitorcheck);
								}
							}
							hoststatus.setCurrentState(0);
							hoststatus.setLastTimeDown(hoststatus.getStatusUpdateTime());
							hoststatus.setLastTimeUp(checkedafttime);
							hoststatus.setCurrentCheckAttempt(1);
							hoststatus.setLastCheck(checkedbeftime);
							if(message.indexOf("|")!=-1){
								hoststatus.setOutput(message.substring(0, message.indexOf("|")));
								hoststatus.setPerfdata(message.substring(message.indexOf("|")+1));
							}else{
								hoststatus.setOutput(message);
							}
							hoststatus.setStatusUpdateTime(checkedafttime);
							hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
							hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
							hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());
							hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(hoststatus.getNormalCheckInterval()*60)));
							hoststatus.setLastHardState(0);
							hoststatus.setLastStateChange(checkedafttime);
							hoststatus.setLastHardStateChange(checkedafttime);
							if(hoststatus.getStateType()==0){
								//原来是retrey 现在变成check
								MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(hoststatus.getNextCheck(), "yyyyMMddHHmmss"), 0);
							}
							hoststatus.setStateType(1);
							monitorHostService.updateMonitorHostStatus(hoststatus);
							if(monitorcheck!=null){
								if(monitorcheck.getState()!=0){
									//add new check to history record
									MonitorHostchecks MHcheck =  new MonitorHostchecks();
									MHcheck.setCheckType(0);
									MHcheck.setCommandArgs(commandArgs);
									MHcheck.setCommandId(monitorhost.getCheckCommand().getCommandId());
									MHcheck.setCommandLine(commandLine);
									MHcheck.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt());
									MHcheck.setExecutionTime(Double.valueOf(0));
									MHcheck.setHostId(monitorhost.getHostId());
									MHcheck.setLatency(Double.valueOf(0));
									MHcheck.setMaxCheckAttempts(hoststatus.getMaxCheckAttempts());
									MHcheck.setOutput(hoststatus.getOutput());
									MHcheck.setPerfdata(hoststatus.getPerfdata());
									MHcheck.setReturnCode(0);
									MHcheck.setStartTime(hoststatus.getStatusUpdateTime());
									MHcheck.setStateType(0);
									MHcheck.setState(hoststatus.getCurrentState());
									MHcheck.setTimeout(0);
									monitorHostService.saveMonitorHostchecks(MHcheck);
									//NotifyOnRecovery
									if(monitorhost.getNotifyOnRecovery()!=null&&monitorhost.getNotifyOnRecovery()>0){
										notification=1;
									}
								}								
							}							
						}
					}else{
						//save first time
						hoststatus = new MonitorHostStatus();
						hoststatus.setHostId(monitorhost.getHostId());
						hoststatus.setStatusUpdateTime(checkedafttime);
						if(message.indexOf("|")!=-1){
							hoststatus.setOutput(message.substring(0, message.indexOf("|")));
							hoststatus.setPerfdata(message.substring(message.indexOf("|")+1));
						}else{
							hoststatus.setOutput(message);
						}
						hoststatus.setLastCheck(checkedbeftime);
						hoststatus.setLastTimeUp(checkedafttime);
						hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getCheckInterval()*60)));
						hoststatus.setCurrentState(0);
						hoststatus.setHasBeenChecked(1);
						hoststatus.setShouldBeScheduled(1);
						hoststatus.setCurrentCheckAttempt(1);
						hoststatus.setLastTimeDown("");
						hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());						
						hoststatus.setCheckType(0);
						hoststatus.setLastStateChange(checkedbeftime);
						hoststatus.setLastHardStateChange(checkedbeftime);
						hoststatus.setLastHardState(0);
						hoststatus.setLastTimeUnreachable("");
						hoststatus.setStateType(1);
						hoststatus.setLastNotification("");
						hoststatus.setNextNotification("");
						hoststatus.setNotificationsEnabled(monitorhost.getNotificationsEnabled());
						hoststatus.setProblemHasBeenAcknowledged(0);
						hoststatus.setAcknowledgementType(0);
						hoststatus.setCurrentNotificationNumber(0);
						hoststatus.setPassiveChecksEnabled(monitorhost.getPassiveChecksEnabled());
						hoststatus.setActiveChecksEnabled(monitorhost.getActiveChecksEnabled());
						hoststatus.setEventHandlerEnabled(monitorhost.getEventHandlerEnabled());
						hoststatus.setFlapDetectionEnabled(monitorhost.getFlapDetectionEnabled());
						hoststatus.setIsFlapping(0);
						hoststatus.setPercentStateChange(Double.valueOf(0));
						hoststatus.setLatency(Double.valueOf(0));
						hoststatus.setExecutionTime(Double.valueOf(0));
						hoststatus.setEventHandler("");
						hoststatus.setCheckCommand(commandName);
						hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
						hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
						hoststatus.setCheckTimeperiodId(monitorhost.getCheckTimeperiod().getTimeperiodId());
						monitorHostService.saveMonitorHostStatus(hoststatus);	
						
						//add new check to history record
						MonitorHostchecks MHcheck =  new MonitorHostchecks();
						MHcheck.setCheckType(0);
						MHcheck.setCommandArgs(commandArgs);
						MHcheck.setCommandId(monitorhost.getCheckCommand().getCommandId());
						MHcheck.setCommandLine(commandLine);
						MHcheck.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt());
						MHcheck.setExecutionTime(Double.valueOf(0));
						MHcheck.setHostId(monitorhost.getHostId());
						MHcheck.setLatency(Double.valueOf(0));
						MHcheck.setMaxCheckAttempts(hoststatus.getMaxCheckAttempts());
						MHcheck.setOutput(hoststatus.getOutput());
						MHcheck.setPerfdata(hoststatus.getPerfdata());
						MHcheck.setReturnCode(0);
						MHcheck.setStartTime(hoststatus.getStatusUpdateTime());
						MHcheck.setStateType(0);
						MHcheck.setState(hoststatus.getCurrentState());
						MHcheck.setTimeout(0);
						monitorHostService.saveMonitorHostchecks(MHcheck);
					}
				}else{
					// critical or unknow status
					if(hoststatus!=null){
						//update 0:up  1:down
						if(hoststatus.getCurrentState()==0){
							//changed status														
							hoststatus.setCurrentState(1);
							hoststatus.setLastTimeUp(hoststatus.getStatusUpdateTime());
							hoststatus.setLastTimeDown(checkedafttime);
							hoststatus.setCurrentCheckAttempt(1);
							hoststatus.setLastCheck(checkedbeftime);
							hoststatus.setStatusUpdateTime(checkedafttime);
							hoststatus.setOutput(message);
							hoststatus.setPerfdata("");
							hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
							hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
							hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());
							hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getRetryInterval()*60)));
							hoststatus.setLastStateChange(checkedafttime);
							hoststatus.setStateType(0);//retry attempt
							monitorHostService.updateMonitorHostStatus(hoststatus);
							//retry trriger
							MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(hoststatus.getNextCheck(), "yyyyMMddHHmmss"), 1);
							
						}else{						
							//no change
							if(hoststatus.getStateType()==0){
								hoststatus.setLastTimeDown(hoststatus.getStatusUpdateTime());
								hoststatus.setLastCheck(checkedbeftime);
								hoststatus.setOutput(message);							
								hoststatus.setPerfdata("");
								hoststatus.setStatusUpdateTime(checkedafttime);
								hoststatus.setLastStateChange(checkedafttime);
								hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
								hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
								hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());
								if(hoststatus.getCurrentCheckAttempt()>=hoststatus.getMaxCheckAttempts()){
									//max attempt
									hoststatus.setCurrentCheckAttempt(1);
									hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getCheckInterval()*60)));
									hoststatus.setLastHardState(1);
									hoststatus.setLastHardStateChange(checkedafttime);
									hoststatus.setStateType(1);
									MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(hoststatus.getNextCheck(), "yyyyMMddHHmmss"), 0);
									//NotifyOnDown
									if((downtime==0)||(monitorhost.getNotifyOnDowntime()!=null&&monitorhost.getNotifyOnDowntime()==1)){
										if(monitorhost.getNotifyOnDown()!=null&&monitorhost.getNotifyOnDown()==1){
											notification = 2;//server down definitely after serval retry check.
										}
									}
									
								}else{
									//retry attempt
									hoststatus.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt()+1);
									hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getRetryInterval()*60)));									
								}								
								monitorHostService.updateMonitorHostStatus(hoststatus);
								
								if(hoststatus.getStateType()==1){
									//first  log history
									//1、update last history record's endtime to last check time
									MonitorHostchecks monitorcheck =  monitorHostService.getLattestMonitorHostchecks(monitorhost.getHostId());
									if(monitorcheck!=null){
										monitorcheck.setEndTime(checkedafttime);
									}
									monitorHostService.updateMonitorHostchecks(monitorcheck);
									//add new check to history record
									MonitorHostchecks MHcheck =  new MonitorHostchecks();
									MHcheck.setCheckType(0);
									MHcheck.setCommandArgs(commandArgs);
									MHcheck.setCommandId(monitorhost.getCheckCommand().getCommandId());
									MHcheck.setCommandLine(commandLine);
									MHcheck.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt());
									MHcheck.setExecutionTime(Double.valueOf(0));
									MHcheck.setHostId(monitorhost.getHostId());
									MHcheck.setLatency(Double.valueOf(0));
									MHcheck.setMaxCheckAttempts(hoststatus.getMaxCheckAttempts());
									MHcheck.setOutput(hoststatus.getOutput());
									MHcheck.setPerfdata(hoststatus.getPerfdata());
									MHcheck.setReturnCode(0);
									MHcheck.setStartTime(hoststatus.getStatusUpdateTime());
									MHcheck.setStateType(0);
									MHcheck.setState(hoststatus.getCurrentState());
									MHcheck.setTimeout(0);
									monitorHostService.saveMonitorHostchecks(MHcheck);									
								}
								
							}else{
								
								//nomal check
								hoststatus.setLastTimeDown(hoststatus.getStatusUpdateTime());
								hoststatus.setLastCheck(checkedbeftime);
								hoststatus.setOutput(message);							
								hoststatus.setPerfdata("");
								hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
								hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
								hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());
								hoststatus.setStatusUpdateTime(checkedafttime);
								hoststatus.setCurrentCheckAttempt(1);
								hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getCheckInterval()*60)));
								monitorHostService.updateMonitorHostStatus(hoststatus);
								
								if(monitorhost.getCheckFlag()!=null&&monitorhost.getCheckFlag()==0){
									//add new check to history record
									MonitorHostchecks MHcheck =  new MonitorHostchecks();
									MHcheck.setCheckType(0);
									MHcheck.setCommandArgs(commandArgs);
									MHcheck.setCommandId(monitorhost.getCheckCommand().getCommandId());
									MHcheck.setCommandLine(commandLine);
									MHcheck.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt());
									MHcheck.setExecutionTime(Double.valueOf(0));
									MHcheck.setHostId(monitorhost.getHostId());
									MHcheck.setLatency(Double.valueOf(0));
									MHcheck.setMaxCheckAttempts(hoststatus.getMaxCheckAttempts());
									MHcheck.setOutput(hoststatus.getOutput());
									MHcheck.setPerfdata(hoststatus.getPerfdata());
									MHcheck.setReturnCode(0);
									MHcheck.setStartTime(hoststatus.getStatusUpdateTime());
									MHcheck.setStateType(0);
									MHcheck.setState(hoststatus.getCurrentState());
									MHcheck.setTimeout(0);
									monitorHostService.saveMonitorHostchecks(MHcheck);								
								}
								
								if((downtime==0)||(monitorhost.getNotifyOnDowntime()!=null&&monitorhost.getNotifyOnDowntime()==1)){
									if(monitorhost.getNotifyOnDown()!=null&&monitorhost.getNotifyOnDown()==1){
										notification = 3;//server still down.
									}
								}
							}							
						}
					}else{
						//save
						hoststatus = new MonitorHostStatus();
						hoststatus.setHostId(monitorhost.getHostId());
						hoststatus.setStatusUpdateTime(checkedafttime);
						hoststatus.setOutput(message);
						hoststatus.setPerfdata("");
						hoststatus.setLastCheck(checkedbeftime);
						hoststatus.setLastTimeUp("");
						hoststatus.setNextCheck(DateUtil.getNewTime(checkedafttime, (int)(monitorhost.getRetryInterval()*60)));
						hoststatus.setCurrentState(1);
						hoststatus.setHasBeenChecked(1);
						hoststatus.setShouldBeScheduled(1);
						hoststatus.setCurrentCheckAttempt(1);
						hoststatus.setLastTimeDown(checkedafttime);
						hoststatus.setMaxCheckAttempts(monitorhost.getMaxCheckAttempts());						
						hoststatus.setCheckType(0);
						hoststatus.setLastStateChange(checkedbeftime);
						hoststatus.setLastHardStateChange(checkedbeftime);
						hoststatus.setLastHardState(0);
						hoststatus.setLastTimeUnreachable("");
						hoststatus.setStateType(0);
						hoststatus.setLastNotification("");
						hoststatus.setNextNotification("");
						hoststatus.setNotificationsEnabled(monitorhost.getNotificationsEnabled());
						hoststatus.setProblemHasBeenAcknowledged(0);
						hoststatus.setAcknowledgementType(0);
						hoststatus.setCurrentNotificationNumber(0);
						hoststatus.setPassiveChecksEnabled(monitorhost.getPassiveChecksEnabled());
						hoststatus.setActiveChecksEnabled(monitorhost.getActiveChecksEnabled());
						hoststatus.setEventHandlerEnabled(monitorhost.getEventHandlerEnabled());
						hoststatus.setFlapDetectionEnabled(monitorhost.getFlapDetectionEnabled());
						hoststatus.setIsFlapping(0);
						hoststatus.setPercentStateChange(Double.valueOf(0));
						hoststatus.setLatency(Double.valueOf(0));
						hoststatus.setExecutionTime(Double.valueOf(0));
						hoststatus.setEventHandler("");
						hoststatus.setCheckCommand(commandName);
						hoststatus.setNormalCheckInterval(monitorhost.getCheckInterval());
						hoststatus.setRetryCheckInterval(monitorhost.getRetryInterval());
						hoststatus.setCheckTimeperiodId(monitorhost.getCheckTimeperiod().getTimeperiodId());
						monitorHostService.saveMonitorHostStatus(hoststatus);	
						
						//add new check to history record
						MonitorHostchecks MHcheck =  new MonitorHostchecks();
						MHcheck.setCheckType(0);
						MHcheck.setCommandArgs(commandArgs);
						MHcheck.setCommandId(monitorhost.getCheckCommand().getCommandId());
						MHcheck.setCommandLine(commandLine);
						MHcheck.setCurrentCheckAttempt(hoststatus.getCurrentCheckAttempt());
						MHcheck.setExecutionTime(Double.valueOf(0));
						MHcheck.setHostId(monitorhost.getHostId());
						MHcheck.setLatency(Double.valueOf(0));
						MHcheck.setMaxCheckAttempts(hoststatus.getMaxCheckAttempts());
						MHcheck.setOutput(hoststatus.getOutput());
						MHcheck.setPerfdata(hoststatus.getPerfdata());
						MHcheck.setReturnCode(0);
						MHcheck.setStartTime(hoststatus.getStatusUpdateTime());
						MHcheck.setStateType(0);
						MHcheck.setState(hoststatus.getCurrentState());
						MHcheck.setTimeout(0);
						monitorHostService.saveMonitorHostchecks(MHcheck);
						
						MonitorTaskDelegate.getinstance().changeTrigger(mqueue, DateUtil.getDate(hoststatus.getNextCheck(), "yyyyMMddHHmmss"), 1);
					}
				}
				
				if(monitorhost.getCheckFlag()!=null&&monitorhost.getCheckFlag()==0){
					monitorhost.setCheckFlag(1);
					monitorHostService.updateMonitorHostAll(monitorhost);						
				}
				
				//修改timed event
				mqueue.setScheduledTime(hoststatus.getNextCheck());
				monitorSupportService.updateMonitorTimedeventqueue(mqueue);
				//notification about
				if(notification>0){
					//need notification
					if(notification==1){
						//server recovery
						if(monitorhost.getContactGroups()!=null){
							MonitorNotifications mn = new MonitorNotifications();
							mn.setContactGroup(monitorhost.getContactGroups());
							mn.setNotificationTime(DateUtil.getNow());
							mn.setNotificationType(1);//host
							mn.setObjectId(monitorhost.getHostId());
							mn.setOutput("<pre>时间:"+hoststatus.getStatusUpdateTime()+"		主机:"+monitorhost.getDisplayName()+"	状态:"+STATUS_ARR[hoststatus.getCurrentState()]+"	返回信息：["+hoststatus.getOutput()+"|"+hoststatus.getPerfdata()+"]</pre>");
							mn.setSendOrNot(0);
							mn.setState(hoststatus.getCurrentState());			
							monitorSupportService.saveMonitorNotifications(mn);
						}
					}else if(notification==2){
						//server first down
						if(monitorhost.getContactGroups()!=null){
							MonitorNotifications mn = new MonitorNotifications();
							mn.setContactGroup(monitorhost.getContactGroups());
							mn.setNotificationTime(DateUtil.getNow());
							mn.setNotificationType(1);
							mn.setObjectId(monitorhost.getHostId());
							mn.setOutput("<pre>时间:"+hoststatus.getStatusUpdateTime()+"		主机:"+monitorhost.getDisplayName()+"	状态:"+STATUS_ARR[hoststatus.getCurrentState()]+"	返回信息：["+hoststatus.getOutput()+"]</pre>");
							mn.setSendOrNot(0);
							mn.setState(hoststatus.getCurrentState());			
							monitorSupportService.saveMonitorNotifications(mn);	
						}
					}
				}
				
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
			
			
		}
	}
	

}
