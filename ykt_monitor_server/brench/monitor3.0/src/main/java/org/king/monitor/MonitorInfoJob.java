package org.king.monitor;

import java.util.ArrayList;
import java.util.List;

import org.king.support.domain.MonitorContact;
import org.king.support.domain.MonitorNotifications;
import org.king.support.service.MonitorSupportService;
import org.king.support.util.CommonSendMailUtil;
import org.quartz.JobDataMap;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;
import org.quartz.StatefulJob;

public class MonitorInfoJob implements StatefulJob{
	
	
	
	private static MonitorSupportService monitorSupportService;

	public void setMonitorSupportService(
			MonitorSupportService monitorSupportService) {
		MonitorInfoJob.monitorSupportService = monitorSupportService;
	}
	private String STATUS_OK ="OK";
	
	private String STATUS_WARNING="WARNING";
	
	private String STATUS_CRITICAL="CRITICAL";
	
	private String STATUS_UNKNOW = "UNKNOW";
	
	private String[] subject_arr={"一卡通监控系统主机信息通知","一卡通监控系统主机服务通知","一卡通监控系统终端设备通知","一卡通监控系统终端监控项通知"}; 
	
	private int notification =0;  //0=no 1=recovery 2=first down 3=still down 4=first unreachable  5=still unreachable
	
	private int downtime = 0; //1=down time
	
//	private int hislog = 0;//0=no 1=log history

	public void execute(JobExecutionContext context)
			throws JobExecutionException {
		String jobName = context.getJobDetail().getFullName();
		JobDataMap data = context.getJobDetail().getJobDataMap();
		List list = monitorSupportService.getMonitorNotificationsByFlag(0);
		String infoContent="";
		boolean flag =false;
		Integer pre_groupid = -1;
		List tempList = new ArrayList();
		for(int i=0;i<list.size();i++){
			MonitorNotifications MNotify = (MonitorNotifications)list.get(i);
			Integer groupid = MNotify.getContactGroup().getContactgroupId();
			List notifyList = monitorSupportService.findMonitorContactBygroup(groupid);
			if(notifyList!=null&&notifyList.size()>0){
				if(pre_groupid==-1){
					pre_groupid=groupid;
					infoContent=MNotify.getOutput()+"<br/>";
					tempList.add(MNotify);
				}else if(pre_groupid==groupid){
					infoContent+=MNotify.getOutput()+"<br/>";
					tempList.add(MNotify);
				}else{
					for(int j=0;j<notifyList.size();j++){
						MonitorContact mc = (MonitorContact) notifyList.get(j);
						if(mc.getNotifyCommand()!=null&&mc.getNotifyCommand().indexOf("EMAIL")>=0){
							if(CommonSendMailUtil.sendMail(subject_arr[MNotify.getNotificationType()],mc.getContactName(), mc.getEmailAddress(), infoContent)){
								for(int k=0;k<tempList.size();k++){
									MonitorNotifications MNotifyOK = (MonitorNotifications)tempList.get(k);
									if(MNotifyOK.getSendOrNot()==null||MNotifyOK.getSendOrNot()==0){
										MNotifyOK.setSendOrNot(1);
										monitorSupportService.updateMonitorNotifications(MNotifyOK);
									}
								}
								tempList.clear();								
							}
						}
					}
				
					infoContent=MNotify.getOutput()+"<br/>";
					pre_groupid = groupid;
					tempList.add(MNotify);
				}
				
				if(i==list.size()-1){
					for(int j=0;j<notifyList.size();j++){
						MonitorContact mc = (MonitorContact) notifyList.get(j);
						if(mc.getNotifyCommand()!=null&&mc.getNotifyCommand().indexOf("EMAIL")>=0){
							if(CommonSendMailUtil.sendMail(subject_arr[MNotify.getNotificationType()],mc.getContactName(), mc.getEmailAddress(), infoContent)){
								for(int k=0;k<tempList.size();k++){
									MonitorNotifications MNotifyOK = (MonitorNotifications)tempList.get(k);
									if(MNotifyOK.getSendOrNot()==null||MNotifyOK.getSendOrNot()==0){
										MNotifyOK.setSendOrNot(1);
										monitorSupportService.updateMonitorNotifications(MNotifyOK);
									}
								}
							}
						}
					}
				}
			}
			
		}
			
	}
}
