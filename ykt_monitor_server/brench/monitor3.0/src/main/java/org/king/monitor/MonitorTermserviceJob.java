package org.king.monitor;

import java.util.Iterator;
import java.util.List;

import org.hibernate.Query;
import org.king.host.domain.MonitorHostAll;
import org.king.host.domain.MonitorHostStatus;
import org.king.host.domain.MonitorHostchecks;
import org.king.host.service.MonitorHostService;
import org.king.monitor.util.MonitorJobUtil;
import org.king.monitor.util.MonitorUtils;
import org.king.support.domain.MonitorNotifications;
import org.king.support.domain.MonitorRuntimevariables;
import org.king.support.domain.MonitorTimedeventqueue;
import org.king.support.service.MonitorSupportService;
import org.king.task.MonitorTaskDelegate;
import org.king.termdev.service.TermdevService;
import org.king.utils.DateUtil;
import org.quartz.JobDataMap;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;
import org.quartz.StatefulJob;

public class MonitorTermserviceJob implements StatefulJob {
	
	
	
	private static TermdevService termdevService;
	private static MonitorSupportService monitorSupportService;


	public static void setTermdevService(TermdevService termdevService) {
		MonitorTermserviceJob.termdevService = termdevService;
	}

	public static void setMonitorSupportService(
			MonitorSupportService monitorSupportService) {
		MonitorTermserviceJob.monitorSupportService = monitorSupportService;
	}

	private String STATUS_OK ="OK";
	
	private String STATUS_WARNING="WARNING";
	
	private String STATUS_CRITICAL="CRITICAL";
	
	private String STATUS_UNKNOW = "UNKNOW";
	
	private String[] STATUS_ARR = {"Device Service","Host Down","Host Unreachable","Host Pending"};
	
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
			if(objectid==-1){
				//未上传流水
				
			}else if(objectid==-2){
				//流水缺失
				
			}else if(objectid==-3){
				//黑名单版本
				/*
				 * select {a.*} from YKT_CUR.T_DEVICE a where (not
					a.CARDVERNO>:blackSheet) and a.status=1 and
					(a.devtypecode='0226' or a.devtypecode='0201' or a.devtypecode='0232')
					and a.CARDVERNO is not null and not a.CARDVERNO='000000000000'
					order by a.CARDVERNO
				 * 
				 */
				
//				String black_sheet_warning_str ="120";
//				String black_sheet_critical_str ="240";
//				MonitorRuntimevariables black_sheet_warning = monitorSupportService.findMonitorRuntimevariablesByName("black_sheet_warning");
//				if(black_sheet_warning!=null){
//					black_sheet_warning_str = black_sheet_warning.getVarvalue();
//				}
//				MonitorRuntimevariables black_sheet_critical = monitorSupportService.findMonitorRuntimevariablesByName("black_sheet_critical");
//				if(black_sheet_critical!=null){
//					black_sheet_critical_str = black_sheet_critical.getVarvalue();
//				}
//				int warning_int = Integer.parseInt(black_sheet_warning_str.substring(0, black_sheet_warning_str.indexOf(".")));
//				int critical_int = Integer.parseInt(black_sheet_critical_str.substring(0, black_sheet_critical_str.indexOf(".")));
//				String blackSheet = termdevService.getmaxVolumeTimeFromTcardVer();
//				if(blackSheet==null){
//					System.out.println("Tcardver blacksheet is null now,it seems no card get lost");
//					return;
//				}
//				String blackSheet_warning_sherold = DateUtil.getSpecialCardver(blackSheet, warning_int);
//				String blackSheet_critical_sherold = DateUtil.getSpecialCardver(blackSheet, critical_int);
//				String max_blackSheet_warning_sherold = DateUtil.getSpecialCardver(blackSheet, warning_int+3*12*60);
//				String max_blackSheet_critical_sherold = DateUtil.getSpecialCardver(blackSheet, critical_int+3*12*60);
//				String blackSheet_warning_ver = termdevService.getVolumeFromTcardVer(blackSheet_warning_sherold,max_blackSheet_warning_sherold);
//				String blackSheet_critical_ver = termdevService.getVolumeFromTcardVer(blackSheet_critical_sherold,max_blackSheet_critical_sherold);
//				List warning_list =  termdevService.findBsverErrorWarningList(blackSheet_warning_ver,blackSheet_critical_ver);
//				List critical_list =  termdevService.findBsverErrorCriticalList(blackSheet_warning_ver,blackSheet_critical_ver);
				
				
			}else if(objectid==-4){
				//数据流量
				
			}
			
			
		}
	}
	

}
