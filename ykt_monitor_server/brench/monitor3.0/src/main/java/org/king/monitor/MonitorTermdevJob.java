package org.king.monitor;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.king.monitor.domain.MapStateDic;
import org.king.monitor.domain.TDevice;
import org.king.monitor.util.MonitorJobUtil;
import org.king.monitor.util.MonitorUtils;
import org.king.support.domain.MonitorNotifications;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.template.domain.MonitorTermdevTemplateAll;
import org.king.template.service.TemplateService;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.termdev.service.TermdevService;
import org.king.topo.service.TopoCalculatorService;
import org.king.utils.DateUtil;
import org.quartz.JobDataMap;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;
import org.quartz.StatefulJob;

public class MonitorTermdevJob implements StatefulJob {

	private static TermdevService termdevService;
	private static TemplateService templateService;
	private static MonitorSupportService monitorSupportService;
	private static TopoCalculatorService topoCalculatorService;

	public void setTermdevService(TermdevService termdevService) {
		MonitorTermdevJob.termdevService = termdevService;
	}

	public void setTemplateService(TemplateService templateService) {
		MonitorTermdevJob.templateService = templateService;
	}

	public void setMonitorSupportService(
			MonitorSupportService monitorSupportService) {
		MonitorTermdevJob.monitorSupportService = monitorSupportService;
	}

	public void setTopoCalculatorService(
			TopoCalculatorService topoCalculatorService) {
		MonitorTermdevJob.topoCalculatorService = topoCalculatorService;
	}

	private String STATUS_OK = "OK";

	private String STATUS_DOWN = "DOWN";

	private String[] STATUS_ARR={"Device Recovery","Device Down"};
	
	private int notification =0;  //0=no 1=recovery 2=first down 3=still down 4=first unreachable  5=still unreachable
	
	private int downtime = 0; //1=down time

	private HashMap errinfoHashmap = new HashMap();

	private HashMap preErrHashmap = new HashMap();

	private StringBuffer errcodeStr = new StringBuffer();

	public void execute(JobExecutionContext context)
			throws JobExecutionException {
		String jobName = context.getJobDetail().getFullName();
		JobDataMap data = context.getJobDetail().getJobDataMap();

		MonitorTimedeventqueue mqueue = (MonitorTimedeventqueue) data
				.get("mqueue");
		if (mqueue != null) {

			try {
				Integer objectid = mqueue.getObjectId();

				MonitorTermdevTemplateAll monitorTermdevTemplate = templateService
						.findMonitorTermdevTemplateAllById(objectid);
				if (monitorTermdevTemplate == null) {
					System.out.println("设备模板，id=" + objectid + "似乎被删除，无法找到");
					return;
				}
				
				if(monitorTermdevTemplate.getActiveChecksEnabled()==null||monitorTermdevTemplate.getActiveChecksEnabled()==0){
					System.out.println("设备模板，id="+objectid+"ActiveCheck is set to false");
					//set dev checkflag = 0
					if(monitorTermdevTemplate.getCheckFlag()==null||monitorTermdevTemplate.getCheckFlag()==1){
						monitorTermdevTemplate.setCheckFlag(0);
						templateService.updateMonitorTermdevTemplateAll(monitorTermdevTemplate);			
					}					
					return;
					
				}

				// 判断是否在监控工作时间以内
				if (monitorTermdevTemplate.getCheckPeriod() != null) {
					if (!MonitorJobUtil.checkinWorktime(DateUtil.getNow(),
							monitorTermdevTemplate.getCheckPeriod()
									.getTimerangers())) {
						//set dev checkflag = 0
						if(monitorTermdevTemplate.getCheckFlag()==null||monitorTermdevTemplate.getCheckFlag()==1){
							monitorTermdevTemplate.setCheckFlag(0);
							templateService.updateMonitorTermdevTemplateAll(monitorTermdevTemplate);			
						}	
						return;
					}
				}

				String checkedbeftime = DateUtil.getNow();
				String deverrStr = "";
				errcodeStr.append("select dev from TDevice dev,TDevmonitor a,MonitorDevtem b where a.deviceid=dev.deviceid "
								+ "and dev.deviceid=b.deviceid and b.templateid= "
								+ monitorTermdevTemplate.getTemplateId()
								 + " and (dev.ip is null or dev.ip='') "
								+ " and dev.status=1 ");
				List errCodeList = termdevService.getSqlList("from MapStateDic where errornot=1");
				if (errCodeList == null || errCodeList.size() == 0) {
					errcodeStr.append(" and a.beatstatus='1' ");
				} else {
					Iterator errCodeIter = errCodeList.iterator();
					MapStateDic mapStateDic = (MapStateDic) errCodeIter.next();
					errcodeStr.append(" and (").append(" a.beatstatus='")
							.append(mapStateDic.getStateid()).append("'");
					errinfoHashmap.put(mapStateDic.getStateid(), mapStateDic.getErrorcode());
					preErrHashmap.put(mapStateDic.getErrorcode(), "");

					while (errCodeIter.hasNext()) {
						mapStateDic = (MapStateDic) errCodeIter.next();
						errcodeStr.append(" or a.beatstatus='").append(mapStateDic.getStateid()).append("'");
						errinfoHashmap.put(mapStateDic.getStateid(),mapStateDic.getErrorcode());
						preErrHashmap.put(mapStateDic.getErrorcode(), "");
					}

					errcodeStr.append(")");

				}

				List termerrstatus = termdevService.getSqlList(errcodeStr
						.toString());

				for (int i = 0; i < termerrstatus.size(); i++) {
					
					TDevice tdevice = (TDevice) termerrstatus.get(i);
					deverrStr += tdevice.getDeviceid() + ",";
					Integer deviceid = Integer.valueOf(String.valueOf(tdevice.getDeviceid()));
					downtime = 0;
					//判断是否在downtime时间内
					if(monitorSupportService.checkDevDowntime(deviceid, DateUtil.getNow())){
						downtime=1;
					}
					notification = 0;
					
					MonitorTermdeviceStatus monitorTermdeviceStatus = termdevService.getMonitorTermdeviceStatus(deviceid);
					//check whether first check
					if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
						//continue to check from uncheck as first check
						//1、update last history record's endtime to last check time
						MonitorTermdevchecks termdevcheck =  termdevService.getLattestMonitorTermdevchecks(deviceid);
						if(termdevcheck!=null){
							if (monitorTermdeviceStatus != null) {
								termdevcheck.setEndTime(monitorTermdeviceStatus.getStatusUpdateTime());
								long dtime = DateUtil.getDuration(monitorTermdeviceStatus.getLastHardStateChange(),monitorTermdeviceStatus.getStatusUpdateTime());
								termdevcheck.setTimeLast(Double.valueOf(dtime));
							}else{
								termdevcheck.setEndTime(checkedbeftime);
								long dtime = DateUtil.getDuration(termdevcheck.getStartTime(),checkedbeftime);
								termdevcheck.setTimeLast(Double.valueOf(dtime));
							}
							termdevService.updateMonitorTermdevchecks(termdevcheck);
						}
																		
					}		
					
					if (monitorTermdeviceStatus != null) {
						if (monitorTermdeviceStatus.getCurrentState() == 1) {
							// no change still down
							monitorTermdeviceStatus.setLastTimeDown(checkedbeftime);
							monitorTermdeviceStatus.setLastCheck(checkedbeftime);
							monitorTermdeviceStatus.setOutput("Status Down");
							monitorTermdeviceStatus.setPerfdata("");
							monitorTermdeviceStatus
									.setNormalCheckInterval(monitorTermdevTemplate
											.getCheckInterval());
							monitorTermdeviceStatus
									.setRetryCheckInterval(monitorTermdevTemplate
											.getRetryInterval());
							monitorTermdeviceStatus
									.setStatusUpdateTime(checkedbeftime);
							monitorTermdeviceStatus.setCurrentCheckAttempt(1);
							monitorTermdeviceStatus.setNextCheck(DateUtil
									.getNewTime(checkedbeftime,
											(int) (monitorTermdevTemplate
													.getCheckInterval() * 60)));
							termdevService
									.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
							if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
								//add new check to history record
								MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
								MTdevchecks.setCheckCount(0);
								MTdevchecks.setCheckType(0);
								MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
								MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
								MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
								MTdevchecks.setExecutionTime(Double.valueOf(0));
								MTdevchecks.setLatency(Double.valueOf(0));
								MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
								MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
								MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
								MTdevchecks.setReturnCode(0);
								MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
								MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
								MTdevchecks.setStateType(0);
								MTdevchecks.setTimeLast(Double.valueOf(0));
								MTdevchecks.setTimeout(0);
								termdevService.saveMonitorTermdevchecks(MTdevchecks);						
							}
						} else {
							// status changed
							//1、update last history record's endtime to last check time
							MonitorTermdevchecks termdevcheck =  termdevService.getLattestMonitorTermdevchecks(deviceid);
							if(termdevcheck!=null){
								termdevcheck.setEndTime(checkedbeftime);
								long dtime = DateUtil.getDuration(monitorTermdeviceStatus.getLastHardStateChange(),checkedbeftime);
								termdevcheck.setTimeLast(Double.valueOf(dtime));
								termdevService.updateMonitorTermdevchecks(termdevcheck);
							}
							switch (monitorTermdeviceStatus.getCurrentState()) {
							case 0:
								monitorTermdeviceStatus
										.setLastTimeUp(monitorTermdeviceStatus
												.getStatusUpdateTime());
								break;
							case 1:
								monitorTermdeviceStatus
										.setLastTimeDown(monitorTermdeviceStatus
												.getStatusUpdateTime());
								break;
							case 2:
								monitorTermdeviceStatus
										.setLastTimeUnreachable(monitorTermdeviceStatus
												.getStatusUpdateTime());
								break;
							default:
								break;
							}
							monitorTermdeviceStatus.setCurrentCheckAttempt(1);
							monitorTermdeviceStatus
									.setLastCheck(checkedbeftime);
							monitorTermdeviceStatus
									.setStatusUpdateTime(checkedbeftime);
							monitorTermdeviceStatus.setOutput("Status Down");
							monitorTermdeviceStatus.setPerfdata("");
							monitorTermdeviceStatus
									.setNormalCheckInterval(monitorTermdevTemplate
											.getCheckInterval());
							monitorTermdeviceStatus
									.setRetryCheckInterval(monitorTermdevTemplate
											.getRetryInterval());
							// termdev do not retry
							monitorTermdeviceStatus.setNextCheck(DateUtil
									.getNewTime(checkedbeftime,
											(int) (monitorTermdevTemplate
													.getCheckInterval() * 60)));
							monitorTermdeviceStatus
									.setLastStateChange(checkedbeftime);
							monitorTermdeviceStatus.setStateType(1);
							// attempt
							monitorTermdeviceStatus.setCurrentState(1);
							termdevService
									.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
							
							// log history first
							MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
							MTdevchecks.setCheckCount(0);
							MTdevchecks.setCheckType(0);
							MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
							MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
							MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
							MTdevchecks.setExecutionTime(Double.valueOf(0));
							MTdevchecks.setLatency(Double.valueOf(0));
							MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
							MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
							MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
							MTdevchecks.setReturnCode(0);
							MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
							MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
							MTdevchecks.setStateType(0);
							MTdevchecks.setTimeLast(Double.valueOf(0));
							MTdevchecks.setTimeout(0);
							termdevService.saveMonitorTermdevchecks(MTdevchecks);
							//NotifyOnDown
							if((downtime==0)&&(monitorTermdevTemplate.getNotificationsEnabled()!=null)&&(monitorTermdevTemplate.getNotificationsEnabled()==1)){
									notification = 2;//server down .
							}
						}
					} else {
						// new one should be added
						// save first time
						monitorTermdeviceStatus = new MonitorTermdeviceStatus();
						monitorTermdeviceStatus.setDeviceId(deviceid);
						monitorTermdeviceStatus
								.setStatusUpdateTime(checkedbeftime);
						monitorTermdeviceStatus.setOutput("Status Down");
						monitorTermdeviceStatus.setLastCheck(checkedbeftime);
						monitorTermdeviceStatus.setLastTimeUp("");
						monitorTermdeviceStatus.setNextCheck(DateUtil
								.getNewTime(checkedbeftime,
										(int) (monitorTermdevTemplate
												.getCheckInterval() * 60)));
						monitorTermdeviceStatus.setCurrentState(1);
						monitorTermdeviceStatus.setHasBeenChecked(1);
						monitorTermdeviceStatus.setShouldBeScheduled(1);
						monitorTermdeviceStatus.setCurrentCheckAttempt(1);
						monitorTermdeviceStatus.setLastTimeDown(checkedbeftime);
						monitorTermdeviceStatus.setLastTimeUnreachable("");
						monitorTermdeviceStatus
								.setMaxCheckAttempts(monitorTermdevTemplate
										.getMaxCheckAttempts());
						monitorTermdeviceStatus.setCheckType(0);
						monitorTermdeviceStatus
								.setLastStateChange(checkedbeftime);
						monitorTermdeviceStatus
								.setLastHardStateChange(checkedbeftime);
						monitorTermdeviceStatus.setLastHardState(0);
						monitorTermdeviceStatus.setStateType(1);
						monitorTermdeviceStatus.setLastNotification("");
						monitorTermdeviceStatus.setNextNotification("");
						monitorTermdeviceStatus
								.setNotificationsEnabled(monitorTermdevTemplate
										.getNotificationsEnabled());
						monitorTermdeviceStatus
								.setProblemHasBeenAcknowledged(0);
						monitorTermdeviceStatus.setAcknowledgementType(0);
						monitorTermdeviceStatus.setCurrentNotificationNumber(0);
						monitorTermdeviceStatus.setPassiveChecksEnabled(1);
						monitorTermdeviceStatus.setActiveChecksEnabled(1);
						monitorTermdeviceStatus.setEventHandlerEnabled(0);
						monitorTermdeviceStatus.setFlapDetectionEnabled(0);
						monitorTermdeviceStatus.setIsFlapping(0);
						monitorTermdeviceStatus.setPercentStateChange(Double
								.valueOf(0));
						monitorTermdeviceStatus.setLatency(Double.valueOf(0));
						monitorTermdeviceStatus.setExecutionTime(Double
								.valueOf(0));
						monitorTermdeviceStatus.setEventHandler("");
						monitorTermdeviceStatus.setCheckCommand("");
						monitorTermdeviceStatus
								.setNormalCheckInterval(monitorTermdevTemplate
										.getCheckInterval());
						monitorTermdeviceStatus
								.setRetryCheckInterval(monitorTermdevTemplate
										.getRetryInterval());
						monitorTermdeviceStatus
								.setCheckTimeperiodId(monitorTermdevTemplate
										.getCheckPeriod().getTimeperiodId());
						termdevService
								.saveMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
						
						// log history first
						MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
						MTdevchecks.setCheckCount(0);
						MTdevchecks.setCheckType(0);
						MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
						MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
						MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
						MTdevchecks.setExecutionTime(Double.valueOf(0));
						MTdevchecks.setLatency(Double.valueOf(0));
						MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
						MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
						MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
						MTdevchecks.setReturnCode(0);
						MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
						MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
						MTdevchecks.setStateType(0);
						MTdevchecks.setTimeLast(Double.valueOf(0));
						MTdevchecks.setTimeout(0);
						termdevService.saveMonitorTermdevchecks(MTdevchecks);
						//NotifyOnDown
						if((downtime==0)&&(monitorTermdevTemplate.getNotificationsEnabled()!=null)&&(monitorTermdevTemplate.getNotificationsEnabled()==1)){
								notification = 2;//server down .
						}
					}					
					//notification about
					if(notification>0){
						//need notification
						if(notification==2){
							//server first down
							MonitorNotifications mn = new MonitorNotifications();
							mn.setContactGroup(monitorTermdevTemplate.getContactGroups());
							mn.setNotificationTime(DateUtil.getNow());
							mn.setNotificationType(3);
							mn.setObjectId(deviceid);
							mn.setOutput(monitorTermdeviceStatus.getOutput());
							mn.setOutput("<pre>时间:"+monitorTermdeviceStatus.getStatusUpdateTime()+"		设备:"+tdevice.getDevicename()+"		状态:"+STATUS_ARR[monitorTermdeviceStatus.getCurrentState()]+"		返回信息：["+monitorTermdeviceStatus.getOutput()+"]</pre>");
							mn.setSendOrNot(0);
							mn.setState(monitorTermdeviceStatus.getCurrentState());			
							monitorSupportService.saveMonitorNotifications(mn);
							
						}
					}					
				}
				
				// 正常设备
				List list = termdevService
						.getSqlList("select dev from TDevice dev,MonitorDevtem b where dev.deviceid=b.deviceid and b.templateid= "
								+ monitorTermdevTemplate.getTemplateId()
								 + " and (dev.ip is null or dev.ip='') "
								+ " and dev.status=1 and dev.deviceid not in("
								+ deverrStr + "-1)");

				for (int i = 0; i < list.size(); i++) {

					TDevice tdevice = (TDevice) list.get(i);
					Integer deviceid = Integer.valueOf(String.valueOf(tdevice
							.getDeviceid()));
					
					downtime = 0;
					//判断是否在downtime时间内
					if(monitorSupportService.checkDevDowntime(deviceid, DateUtil.getNow())){
						downtime=1;
					}
					notification = 0;
					MonitorTermdeviceStatus monitorTermdeviceStatus = termdevService
							.getMonitorTermdeviceStatus(deviceid);
					if (monitorTermdeviceStatus != null) {
						if (monitorTermdeviceStatus.getCurrentState() == 0) {
							// nochange
							monitorTermdeviceStatus
									.setLastCheck(checkedbeftime);
							monitorTermdeviceStatus
									.setStatusUpdateTime(checkedbeftime);
							monitorTermdeviceStatus
									.setLastTimeUp(checkedbeftime);
							monitorTermdeviceStatus.setOutput("Status OK");
							monitorTermdeviceStatus.setCurrentCheckAttempt(1);
							monitorTermdeviceStatus
									.setNormalCheckInterval(monitorTermdevTemplate
											.getCheckInterval());
							monitorTermdeviceStatus
									.setRetryCheckInterval(monitorTermdevTemplate
											.getRetryInterval());
							monitorTermdeviceStatus.setNextCheck(DateUtil
									.getNewTime(checkedbeftime,
											(int) (monitorTermdevTemplate
													.getCheckInterval() * 60)));
							termdevService
									.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
							
							if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
								//add new check to history record
								MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
								MTdevchecks.setCheckCount(0);
								MTdevchecks.setCheckType(0);
								MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
								MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
								MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
								MTdevchecks.setExecutionTime(Double.valueOf(0));
								MTdevchecks.setLatency(Double.valueOf(0));
								MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
								MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
								MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
								MTdevchecks.setReturnCode(0);
								MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
								MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
								MTdevchecks.setStateType(0);
								MTdevchecks.setTimeLast(Double.valueOf(0));
								MTdevchecks.setTimeout(0);
								termdevService.saveMonitorTermdevchecks(MTdevchecks);						
							}
						} else {
							// changed to up
							//1、update last history record's endtime to last check time
							MonitorTermdevchecks termdevcheck =  termdevService.getLattestMonitorTermdevchecks(deviceid);
							if(termdevcheck!=null){
								termdevcheck.setEndTime(checkedbeftime);
								long dtime = DateUtil.getDuration(monitorTermdeviceStatus.getLastHardStateChange(),checkedbeftime);
								termdevcheck.setTimeLast(Double.valueOf(dtime));
							}
							termdevService.updateMonitorTermdevchecks(termdevcheck);

							monitorTermdeviceStatus.setCurrentState(0);
							monitorTermdeviceStatus
									.setLastTimeDown(monitorTermdeviceStatus
											.getStatusUpdateTime());
							monitorTermdeviceStatus
									.setLastTimeUp(checkedbeftime);
							monitorTermdeviceStatus.setCurrentCheckAttempt(1);
							monitorTermdeviceStatus
									.setLastCheck(checkedbeftime);
							monitorTermdeviceStatus.setOutput("Status OK");
							monitorTermdeviceStatus
									.setStatusUpdateTime(checkedbeftime);
							monitorTermdeviceStatus
									.setNormalCheckInterval(monitorTermdevTemplate
											.getCheckInterval());
							monitorTermdeviceStatus
									.setRetryCheckInterval(monitorTermdevTemplate
											.getRetryInterval());
							monitorTermdeviceStatus
									.setNextCheck(DateUtil
											.getNewTime(
													checkedbeftime,
													(int) (monitorTermdeviceStatus
															.getNormalCheckInterval() * 60)));
							monitorTermdeviceStatus.setLastHardState(0);
							monitorTermdeviceStatus
									.setLastStateChange(checkedbeftime);
							monitorTermdeviceStatus
									.setLastHardStateChange(checkedbeftime);
							monitorTermdeviceStatus.setStateType(1);
							termdevService
									.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
							// log history first
							MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
							MTdevchecks.setCheckCount(0);
							MTdevchecks.setCheckType(0);
							MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
							MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
							MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
							MTdevchecks.setExecutionTime(Double.valueOf(0));
							MTdevchecks.setLatency(Double.valueOf(0));
							MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
							MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
							MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
							MTdevchecks.setReturnCode(0);
							MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
							MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
							MTdevchecks.setStateType(0);
							MTdevchecks.setTimeLast(Double.valueOf(0));
							MTdevchecks.setTimeout(0);
							termdevService.saveMonitorTermdevchecks(MTdevchecks);
							//dev status recovery
							//NotifyOnRecovery
							if(monitorTermdevTemplate.getNotificationsEnabled()!=null&&monitorTermdevTemplate.getNotificationsEnabled()>0){
								notification=1;
							}
						}
					} else {
						// new one should be added
						// save first time
						monitorTermdeviceStatus = new MonitorTermdeviceStatus();
						monitorTermdeviceStatus.setDeviceId(deviceid);
						monitorTermdeviceStatus
								.setStatusUpdateTime(checkedbeftime);
						monitorTermdeviceStatus.setOutput("Status Ok");
						monitorTermdeviceStatus.setLastCheck(checkedbeftime);
						monitorTermdeviceStatus.setLastTimeUp("");
						monitorTermdeviceStatus.setNextCheck(DateUtil
								.getNewTime(checkedbeftime,
										(int) (monitorTermdevTemplate
												.getCheckInterval() * 60)));
						monitorTermdeviceStatus.setCurrentState(0);
						monitorTermdeviceStatus.setHasBeenChecked(1);
						monitorTermdeviceStatus.setShouldBeScheduled(1);
						monitorTermdeviceStatus.setCurrentCheckAttempt(1);
						monitorTermdeviceStatus.setLastTimeDown(checkedbeftime);
						monitorTermdeviceStatus.setLastTimeUnreachable("");
						monitorTermdeviceStatus
								.setMaxCheckAttempts(monitorTermdevTemplate
										.getMaxCheckAttempts());
						monitorTermdeviceStatus.setCheckType(0);
						monitorTermdeviceStatus
								.setLastStateChange(checkedbeftime);
						monitorTermdeviceStatus
								.setLastHardStateChange(checkedbeftime);
						monitorTermdeviceStatus.setLastHardState(0);
						monitorTermdeviceStatus.setStateType(1);
						monitorTermdeviceStatus.setLastNotification("");
						monitorTermdeviceStatus.setNextNotification("");
						monitorTermdeviceStatus
								.setNotificationsEnabled(monitorTermdevTemplate
										.getNotificationsEnabled());
						monitorTermdeviceStatus
								.setProblemHasBeenAcknowledged(0);
						monitorTermdeviceStatus.setAcknowledgementType(0);
						monitorTermdeviceStatus.setCurrentNotificationNumber(0);
						monitorTermdeviceStatus.setPassiveChecksEnabled(1);
						monitorTermdeviceStatus.setActiveChecksEnabled(1);
						monitorTermdeviceStatus.setEventHandlerEnabled(0);
						monitorTermdeviceStatus.setFlapDetectionEnabled(0);
						monitorTermdeviceStatus.setIsFlapping(0);
						monitorTermdeviceStatus.setPercentStateChange(Double
								.valueOf(0));
						monitorTermdeviceStatus.setLatency(Double.valueOf(0));
						monitorTermdeviceStatus.setExecutionTime(Double
								.valueOf(0));
						monitorTermdeviceStatus.setEventHandler("");
						monitorTermdeviceStatus.setCheckCommand("");
						monitorTermdeviceStatus
								.setNormalCheckInterval(monitorTermdevTemplate
										.getCheckInterval());
						monitorTermdeviceStatus
								.setRetryCheckInterval(monitorTermdevTemplate
										.getRetryInterval());
						monitorTermdeviceStatus
								.setCheckTimeperiodId(monitorTermdevTemplate
										.getCheckPeriod().getTimeperiodId());
						termdevService
								.saveMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
						// log history first
						MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
						MTdevchecks.setCheckCount(0);
						MTdevchecks.setCheckType(0);
						MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
						MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
						MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
						MTdevchecks.setExecutionTime(Double.valueOf(0));
						MTdevchecks.setLatency(Double.valueOf(0));
						MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
						MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
						MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
						MTdevchecks.setReturnCode(0);
						MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
						MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
						MTdevchecks.setStateType(0);
						MTdevchecks.setTimeLast(Double.valueOf(0));
						MTdevchecks.setTimeout(0);
						termdevService.saveMonitorTermdevchecks(MTdevchecks);
					}
					//notification about
					if(notification>0){
						//need notification
						if(notification==1){
							//device recovery fron down
							MonitorNotifications mn = new MonitorNotifications();
							mn.setContactGroup(monitorTermdevTemplate.getContactGroups());
							mn.setNotificationTime(DateUtil.getNow());
							mn.setNotificationType(3);
							mn.setObjectId(deviceid);		
							mn.setOutput("<pre>时间:"+monitorTermdeviceStatus.getStatusUpdateTime()+"		设备:"+tdevice.getDevicename()+"		状态:"+STATUS_ARR[monitorTermdeviceStatus.getCurrentState()]+"		返回信息：["+monitorTermdeviceStatus.getOutput()+"]</pre>");
							mn.setSendOrNot(0);
							mn.setState(monitorTermdeviceStatus.getCurrentState());			
							monitorSupportService.saveMonitorNotifications(mn);
							
						}
					}
					
				}
				
				//tcp/ip设备 通过ping直接了解状态
				List tcplist = termdevService
				.getSqlList("select dev from TDevice dev,MonitorDevtem b where dev.deviceid=b.deviceid and b.templateid= "
						+ monitorTermdevTemplate.getTemplateId()
						 + " and dev.ip is not null  "
						+ " and dev.status=1 and (dev.devtypecode='0121' or dev.devtypecode='0248' or dev.devtypecode='0201' or dev.devtypecode='0226')");
				for (int i = 0; i < tcplist.size(); i++) {

					TDevice tdevice = (TDevice) tcplist.get(i);
					Integer deviceid = Integer.valueOf(String.valueOf(tdevice.getDeviceid()));
					
					downtime = 0;
					//判断是否在downtime时间内
					if(monitorSupportService.checkDevDowntime(deviceid, DateUtil.getNow())){
						downtime=1;
					}
					notification = 0;
					MonitorTermdeviceStatus monitorTermdeviceStatus = termdevService.getMonitorTermdeviceStatus(deviceid);
					String ipaddr = tdevice.getIp();
					if (!"".equals(ipaddr)) {
						String ret = MonitorUtils.pingCheck(ipaddr);
						//System.out.println("ip:"+ipaddr+" status:"+ret);
						if ("down".equals(ret)) {
							//check whether first check
							if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
								//continue to check from uncheck as first check
								//1、update last history record's endtime to last check time
								MonitorTermdevchecks termdevcheck =  termdevService.getLattestMonitorTermdevchecks(deviceid);
								if(termdevcheck!=null){
									if (monitorTermdeviceStatus != null) {
										termdevcheck.setEndTime(monitorTermdeviceStatus.getStatusUpdateTime());
										long dtime = DateUtil.getDuration(monitorTermdeviceStatus.getLastHardStateChange(),monitorTermdeviceStatus.getStatusUpdateTime());
										termdevcheck.setTimeLast(Double.valueOf(dtime));
									}else{
										termdevcheck.setEndTime(checkedbeftime);
										long dtime = DateUtil.getDuration(termdevcheck.getStartTime(),checkedbeftime);
										termdevcheck.setTimeLast(Double.valueOf(dtime));
									}
									termdevService.updateMonitorTermdevchecks(termdevcheck);
								}
																				
							}		
							
							if (monitorTermdeviceStatus != null) {
								if (monitorTermdeviceStatus.getCurrentState() == 1) {							
									// no change still down
									monitorTermdeviceStatus.setLastTimeDown(checkedbeftime);
									monitorTermdeviceStatus.setLastCheck(checkedbeftime);
									monitorTermdeviceStatus.setOutput("Status Down");
									monitorTermdeviceStatus.setPerfdata("");
									monitorTermdeviceStatus
											.setNormalCheckInterval(monitorTermdevTemplate
													.getCheckInterval());
									monitorTermdeviceStatus
											.setRetryCheckInterval(monitorTermdevTemplate
													.getRetryInterval());
									monitorTermdeviceStatus
											.setStatusUpdateTime(checkedbeftime);
									monitorTermdeviceStatus.setCurrentCheckAttempt(1);
									monitorTermdeviceStatus.setNextCheck(DateUtil
											.getNewTime(checkedbeftime,
													(int) (monitorTermdevTemplate
															.getCheckInterval() * 60)));
									termdevService
											.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
									if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
										//add new check to history record
										MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
										MTdevchecks.setCheckCount(0);
										MTdevchecks.setCheckType(0);
										MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
										MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
										MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
										MTdevchecks.setExecutionTime(Double.valueOf(0));
										MTdevchecks.setLatency(Double.valueOf(0));
										MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
										MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
										MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
										MTdevchecks.setReturnCode(0);
										MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
										MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
										MTdevchecks.setStateType(0);
										MTdevchecks.setTimeLast(Double.valueOf(0));
										MTdevchecks.setTimeout(0);
										termdevService.saveMonitorTermdevchecks(MTdevchecks);						
									}
								} else {
									// status changed
									//1、update last history record's endtime to last check time
									MonitorTermdevchecks termdevcheck =  termdevService.getLattestMonitorTermdevchecks(deviceid);
									if(termdevcheck!=null){
										termdevcheck.setEndTime(checkedbeftime);
										long dtime = DateUtil.getDuration(monitorTermdeviceStatus.getLastHardStateChange(),checkedbeftime);
										termdevcheck.setTimeLast(Double.valueOf(dtime));
										termdevService.updateMonitorTermdevchecks(termdevcheck);
									}				
									switch (monitorTermdeviceStatus.getCurrentState()) {
									case 0:
										monitorTermdeviceStatus
												.setLastTimeUp(monitorTermdeviceStatus
														.getStatusUpdateTime());
										break;
									case 1:
										monitorTermdeviceStatus
												.setLastTimeDown(monitorTermdeviceStatus
														.getStatusUpdateTime());
										break;
									case 2:
										monitorTermdeviceStatus
												.setLastTimeUnreachable(monitorTermdeviceStatus
														.getStatusUpdateTime());
										break;
									default:
										break;
									}
									monitorTermdeviceStatus.setCurrentCheckAttempt(1);
									monitorTermdeviceStatus
											.setLastCheck(checkedbeftime);
									monitorTermdeviceStatus
											.setStatusUpdateTime(checkedbeftime);
									monitorTermdeviceStatus.setOutput("Status Down");
									monitorTermdeviceStatus.setPerfdata("");
									monitorTermdeviceStatus
											.setNormalCheckInterval(monitorTermdevTemplate
													.getCheckInterval());
									monitorTermdeviceStatus
											.setRetryCheckInterval(monitorTermdevTemplate
													.getRetryInterval());
									// termdev do not retry
									monitorTermdeviceStatus.setNextCheck(DateUtil
											.getNewTime(checkedbeftime,
													(int) (monitorTermdevTemplate
															.getCheckInterval() * 60)));
									monitorTermdeviceStatus
											.setLastStateChange(checkedbeftime);
									monitorTermdeviceStatus.setStateType(1);
									// attempt
									monitorTermdeviceStatus.setCurrentState(1);
									termdevService
											.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
									
									// log history first
									MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
									MTdevchecks.setCheckCount(0);
									MTdevchecks.setCheckType(0);
									MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
									MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
									MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
									MTdevchecks.setExecutionTime(Double.valueOf(0));
									MTdevchecks.setLatency(Double.valueOf(0));
									MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
									MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
									MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
									MTdevchecks.setReturnCode(0);
									MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
									MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
									MTdevchecks.setStateType(0);
									MTdevchecks.setTimeLast(Double.valueOf(0));
									MTdevchecks.setTimeout(0);
									termdevService.saveMonitorTermdevchecks(MTdevchecks);
									//NotifyOnDown
									if((downtime==0)&&(monitorTermdevTemplate.getNotificationsEnabled()!=null)&&(monitorTermdevTemplate.getNotificationsEnabled()==1)){
											notification = 2;//server down .
									}
								}
							} else {
								// new one should be added
								// save first time
								monitorTermdeviceStatus = new MonitorTermdeviceStatus();
								monitorTermdeviceStatus.setDeviceId(deviceid);
								monitorTermdeviceStatus
										.setStatusUpdateTime(checkedbeftime);
								monitorTermdeviceStatus.setOutput("Status Down");
								monitorTermdeviceStatus.setLastCheck(checkedbeftime);
								monitorTermdeviceStatus.setLastTimeUp("");
								monitorTermdeviceStatus.setNextCheck(DateUtil
										.getNewTime(checkedbeftime,
												(int) (monitorTermdevTemplate
														.getCheckInterval() * 60)));
								monitorTermdeviceStatus.setCurrentState(1);
								monitorTermdeviceStatus.setHasBeenChecked(1);
								monitorTermdeviceStatus.setShouldBeScheduled(1);
								monitorTermdeviceStatus.setCurrentCheckAttempt(1);
								monitorTermdeviceStatus.setLastTimeDown(checkedbeftime);
								monitorTermdeviceStatus.setLastTimeUnreachable("");
								monitorTermdeviceStatus
										.setMaxCheckAttempts(monitorTermdevTemplate
												.getMaxCheckAttempts());
								monitorTermdeviceStatus.setCheckType(0);
								monitorTermdeviceStatus
										.setLastStateChange(checkedbeftime);
								monitorTermdeviceStatus
										.setLastHardStateChange(checkedbeftime);
								monitorTermdeviceStatus.setLastHardState(0);
								monitorTermdeviceStatus.setStateType(1);
								monitorTermdeviceStatus.setLastNotification("");
								monitorTermdeviceStatus.setNextNotification("");
								monitorTermdeviceStatus
										.setNotificationsEnabled(monitorTermdevTemplate
												.getNotificationsEnabled());
								monitorTermdeviceStatus
										.setProblemHasBeenAcknowledged(0);
								monitorTermdeviceStatus.setAcknowledgementType(0);
								monitorTermdeviceStatus.setCurrentNotificationNumber(0);
								monitorTermdeviceStatus.setPassiveChecksEnabled(1);
								monitorTermdeviceStatus.setActiveChecksEnabled(1);
								monitorTermdeviceStatus.setEventHandlerEnabled(0);
								monitorTermdeviceStatus.setFlapDetectionEnabled(0);
								monitorTermdeviceStatus.setIsFlapping(0);
								monitorTermdeviceStatus.setPercentStateChange(Double
										.valueOf(0));
								monitorTermdeviceStatus.setLatency(Double.valueOf(0));
								monitorTermdeviceStatus.setExecutionTime(Double
										.valueOf(0));
								monitorTermdeviceStatus.setEventHandler("");
								monitorTermdeviceStatus.setCheckCommand("");
								monitorTermdeviceStatus
										.setNormalCheckInterval(monitorTermdevTemplate
												.getCheckInterval());
								monitorTermdeviceStatus
										.setRetryCheckInterval(monitorTermdevTemplate
												.getRetryInterval());
								monitorTermdeviceStatus
										.setCheckTimeperiodId(monitorTermdevTemplate
												.getCheckPeriod().getTimeperiodId());
								termdevService
										.saveMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
								
								// log history first
								MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
								MTdevchecks.setCheckCount(0);
								MTdevchecks.setCheckType(0);
								MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
								MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
								MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
								MTdevchecks.setExecutionTime(Double.valueOf(0));
								MTdevchecks.setLatency(Double.valueOf(0));
								MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
								MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
								MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
								MTdevchecks.setReturnCode(0);
								MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
								MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
								MTdevchecks.setStateType(0);
								MTdevchecks.setTimeLast(Double.valueOf(0));
								MTdevchecks.setTimeout(0);
								termdevService.saveMonitorTermdevchecks(MTdevchecks);
								//NotifyOnDown
								if((downtime==0)&&(monitorTermdevTemplate.getNotificationsEnabled()!=null)&&(monitorTermdevTemplate.getNotificationsEnabled()==1)){
										notification = 2;//server down .
								}
							}					
							//notification about
							if(notification>0){
								//need notification
								if(notification==2){
									//server first down
									MonitorNotifications mn = new MonitorNotifications();
									mn.setContactGroup(monitorTermdevTemplate.getContactGroups());
									mn.setNotificationTime(DateUtil.getNow());
									mn.setNotificationType(3);
									mn.setObjectId(deviceid);
									mn.setOutput("<pre>时间:"+monitorTermdeviceStatus.getStatusUpdateTime()+"		设备:"+tdevice.getDevicename()+"		状态:"+STATUS_ARR[monitorTermdeviceStatus.getCurrentState()]+"		返回信息：["+monitorTermdeviceStatus.getOutput()+"]</pre>");
									mn.setSendOrNot(0);
									mn.setState(monitorTermdeviceStatus.getCurrentState());			
									monitorSupportService.saveMonitorNotifications(mn);
									
								}
							}	
						}else{
							if (monitorTermdeviceStatus != null) {
								if (monitorTermdeviceStatus.getCurrentState() == 0) {
									// nochange
									monitorTermdeviceStatus
											.setLastCheck(checkedbeftime);
									monitorTermdeviceStatus
											.setStatusUpdateTime(checkedbeftime);
									monitorTermdeviceStatus
											.setLastTimeUp(checkedbeftime);
									monitorTermdeviceStatus.setOutput("Status OK");
									monitorTermdeviceStatus.setCurrentCheckAttempt(1);
									monitorTermdeviceStatus
											.setNormalCheckInterval(monitorTermdevTemplate
													.getCheckInterval());
									monitorTermdeviceStatus
											.setRetryCheckInterval(monitorTermdevTemplate
													.getRetryInterval());
									monitorTermdeviceStatus.setNextCheck(DateUtil
											.getNewTime(checkedbeftime,
													(int) (monitorTermdevTemplate
															.getCheckInterval() * 60)));
									termdevService
											.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
									
									if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
										//add new check to history record
										MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
										MTdevchecks.setCheckCount(0);
										MTdevchecks.setCheckType(0);
										MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
										MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
										MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
										MTdevchecks.setExecutionTime(Double.valueOf(0));
										MTdevchecks.setLatency(Double.valueOf(0));
										MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
										MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
										MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
										MTdevchecks.setReturnCode(0);
										MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
										MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
										MTdevchecks.setStateType(0);
										MTdevchecks.setTimeLast(Double.valueOf(0));
										MTdevchecks.setTimeout(0);
										termdevService.saveMonitorTermdevchecks(MTdevchecks);						
									}
								} else {
									// changed to up
									//1、update last history record's endtime to last check time
									MonitorTermdevchecks termdevcheck =  termdevService.getLattestMonitorTermdevchecks(deviceid);
									if(termdevcheck!=null){
										termdevcheck.setEndTime(checkedbeftime);
										long dtime = DateUtil.getDuration(monitorTermdeviceStatus.getLastHardStateChange(),checkedbeftime);
										termdevcheck.setTimeLast(Double.valueOf(dtime));
									}
									termdevService.updateMonitorTermdevchecks(termdevcheck);

									monitorTermdeviceStatus.setCurrentState(0);
									monitorTermdeviceStatus
											.setLastTimeDown(monitorTermdeviceStatus
													.getStatusUpdateTime());
									monitorTermdeviceStatus
											.setLastTimeUp(checkedbeftime);
									monitorTermdeviceStatus.setCurrentCheckAttempt(1);
									monitorTermdeviceStatus
											.setLastCheck(checkedbeftime);
									monitorTermdeviceStatus.setOutput("Status OK");
									monitorTermdeviceStatus
											.setStatusUpdateTime(checkedbeftime);
									monitorTermdeviceStatus
											.setNormalCheckInterval(monitorTermdevTemplate
													.getCheckInterval());
									monitorTermdeviceStatus
											.setRetryCheckInterval(monitorTermdevTemplate
													.getRetryInterval());
									monitorTermdeviceStatus
											.setNextCheck(DateUtil
													.getNewTime(
															checkedbeftime,
															(int) (monitorTermdeviceStatus
																	.getNormalCheckInterval() * 60)));
									monitorTermdeviceStatus.setLastHardState(0);
									monitorTermdeviceStatus
											.setLastStateChange(checkedbeftime);
									monitorTermdeviceStatus
											.setLastHardStateChange(checkedbeftime);
									monitorTermdeviceStatus.setStateType(1);
									termdevService
											.updateMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
									// log history first
									MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
									MTdevchecks.setCheckCount(0);
									MTdevchecks.setCheckType(0);
									MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
									MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
									MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
									MTdevchecks.setExecutionTime(Double.valueOf(0));
									MTdevchecks.setLatency(Double.valueOf(0));
									MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
									MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
									MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
									MTdevchecks.setReturnCode(0);
									MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
									MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
									MTdevchecks.setStateType(0);
									MTdevchecks.setTimeLast(Double.valueOf(0));
									MTdevchecks.setTimeout(0);
									termdevService.saveMonitorTermdevchecks(MTdevchecks);
									//dev status recovery
									//NotifyOnRecovery
									if(monitorTermdevTemplate.getNotificationsEnabled()!=null&&monitorTermdevTemplate.getNotificationsEnabled()>0){
										notification=1;
									}
								}
							} else {
								// new one should be added
								// save first time
								monitorTermdeviceStatus = new MonitorTermdeviceStatus();
								monitorTermdeviceStatus.setDeviceId(deviceid);
								monitorTermdeviceStatus
										.setStatusUpdateTime(checkedbeftime);
								monitorTermdeviceStatus.setOutput("Status Ok");
								monitorTermdeviceStatus.setLastCheck(checkedbeftime);
								monitorTermdeviceStatus.setLastTimeUp("");
								monitorTermdeviceStatus.setNextCheck(DateUtil
										.getNewTime(checkedbeftime,
												(int) (monitorTermdevTemplate
														.getCheckInterval() * 60)));
								monitorTermdeviceStatus.setCurrentState(0);
								monitorTermdeviceStatus.setHasBeenChecked(1);
								monitorTermdeviceStatus.setShouldBeScheduled(1);
								monitorTermdeviceStatus.setCurrentCheckAttempt(1);
								monitorTermdeviceStatus.setLastTimeDown(checkedbeftime);
								monitorTermdeviceStatus.setLastTimeUnreachable("");
								monitorTermdeviceStatus
										.setMaxCheckAttempts(monitorTermdevTemplate
												.getMaxCheckAttempts());
								monitorTermdeviceStatus.setCheckType(0);
								monitorTermdeviceStatus
										.setLastStateChange(checkedbeftime);
								monitorTermdeviceStatus
										.setLastHardStateChange(checkedbeftime);
								monitorTermdeviceStatus.setLastHardState(0);
								monitorTermdeviceStatus.setStateType(1);
								monitorTermdeviceStatus.setLastNotification("");
								monitorTermdeviceStatus.setNextNotification("");
								monitorTermdeviceStatus
										.setNotificationsEnabled(monitorTermdevTemplate
												.getNotificationsEnabled());
								monitorTermdeviceStatus
										.setProblemHasBeenAcknowledged(0);
								monitorTermdeviceStatus.setAcknowledgementType(0);
								monitorTermdeviceStatus.setCurrentNotificationNumber(0);
								monitorTermdeviceStatus.setPassiveChecksEnabled(1);
								monitorTermdeviceStatus.setActiveChecksEnabled(1);
								monitorTermdeviceStatus.setEventHandlerEnabled(0);
								monitorTermdeviceStatus.setFlapDetectionEnabled(0);
								monitorTermdeviceStatus.setIsFlapping(0);
								monitorTermdeviceStatus.setPercentStateChange(Double
										.valueOf(0));
								monitorTermdeviceStatus.setLatency(Double.valueOf(0));
								monitorTermdeviceStatus.setExecutionTime(Double
										.valueOf(0));
								monitorTermdeviceStatus.setEventHandler("");
								monitorTermdeviceStatus.setCheckCommand("");
								monitorTermdeviceStatus
										.setNormalCheckInterval(monitorTermdevTemplate
												.getCheckInterval());
								monitorTermdeviceStatus
										.setRetryCheckInterval(monitorTermdevTemplate
												.getRetryInterval());
								monitorTermdeviceStatus
										.setCheckTimeperiodId(monitorTermdevTemplate
												.getCheckPeriod().getTimeperiodId());
								termdevService
										.saveMonitormonitorTermdeviceStatus(monitorTermdeviceStatus);
								// log history first
								MonitorTermdevchecks MTdevchecks = new MonitorTermdevchecks();
								MTdevchecks.setCheckCount(0);
								MTdevchecks.setCheckType(0);
								MTdevchecks.setCommandLine(monitorTermdevTemplate.getCheckCommand());
								MTdevchecks.setCurrentCheckAttempt(monitorTermdeviceStatus.getCurrentCheckAttempt());
								MTdevchecks.setDeviceId(monitorTermdeviceStatus.getDeviceId());
								MTdevchecks.setExecutionTime(Double.valueOf(0));
								MTdevchecks.setLatency(Double.valueOf(0));
								MTdevchecks.setMaxCheckAttempts(monitorTermdeviceStatus.getMaxCheckAttempts());
								MTdevchecks.setOutput(monitorTermdeviceStatus.getOutput());
								MTdevchecks.setPerfdata(monitorTermdeviceStatus.getPerfdata());
								MTdevchecks.setReturnCode(0);
								MTdevchecks.setStartTime(monitorTermdeviceStatus.getStatusUpdateTime());
								MTdevchecks.setState(monitorTermdeviceStatus.getCurrentState());
								MTdevchecks.setStateType(0);
								MTdevchecks.setTimeLast(Double.valueOf(0));
								MTdevchecks.setTimeout(0);
								termdevService.saveMonitorTermdevchecks(MTdevchecks);
							}
							//notification about
							if(notification>0){
								//need notification
								if(notification==1){
									//server first down
									MonitorNotifications mn = new MonitorNotifications();
									mn.setContactGroup(monitorTermdevTemplate.getContactGroups());
									mn.setNotificationTime(DateUtil.getNow());
									mn.setNotificationType(3);
									mn.setObjectId(deviceid);
									mn.setOutput("<pre>时间:"+monitorTermdeviceStatus.getStatusUpdateTime()+"		设备:"+tdevice.getDevicename()+"		状态:"+STATUS_ARR[monitorTermdeviceStatus.getCurrentState()]+"		返回信息：["+monitorTermdeviceStatus.getOutput()+"]</pre>");
									mn.setSendOrNot(0);
									mn.setState(monitorTermdeviceStatus.getCurrentState());			
									monitorSupportService.saveMonitorNotifications(mn);
									
								}
							}
						}
					}
					
				}
				
				if(monitorTermdevTemplate.getCheckFlag()!=null&&monitorTermdevTemplate.getCheckFlag()==0){
					monitorTermdevTemplate.setCheckFlag(1);
					templateService.updateMonitorTermdevTemplateAll(monitorTermdevTemplate);			
				}
				//统计异常信息
				topoCalculatorService.calculateTopoGroupStatistic(1);

			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}

		}

	}

}
