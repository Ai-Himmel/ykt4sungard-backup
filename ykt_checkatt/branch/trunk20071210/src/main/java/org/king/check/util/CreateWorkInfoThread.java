package org.king.check.util;

import java.util.HashMap;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.service.WorkInfoService;
import org.king.framework.service.ServiceLocator;

/**
 * @author liufei
 * 20061213 modify it by hanjiwei 
 */
public class CreateWorkInfoThread extends Thread {
	private static final Log log = LogFactory.getLog(CreateWorkInfoThread.class);

	long sleepTime = 60000;

	public boolean runThread = true;

	private WorkInfoService workInfoService;

	private Map paraMap = new HashMap();

	private String createTime = "0230";

	public CreateWorkInfoThread() {
		start();
	}

	public void run() {
		//log.debug("start thread");

		while (runThread) {
			log.debug("run in thread");
			String curTime = DateUtilExtend.getNowTime2();

			try{
				if (curTime.equals(createTime)) {
					log.debug("开始运行生成报表进程...");
					startCreateWorkInfo();
					sleepTime = 720000;
				}
				Thread.sleep(sleepTime);

			}catch(Exception ie){
				ie.printStackTrace();
			}
		}
	}
	
	private void startCreateWorkInfo(){
		String statDate = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		paraMap.put("startDate",statDate);
		paraMap.put("endDate",statDate);
		paraMap.put("deptId","");
		paraMap.put("stuEmpNo","");
		//sleepTime = 720000;//休眠两个小时
		//Thread.sleep(sleepTime);
		log.debug("开始生成考勤报表，当前日期： "+statDate);
		workInfoService = (WorkInfoService) ServiceLocator.getInstance().getService("workInfoService");
		try{
			workInfoService.createAllWorkInfoByDptConf(paraMap);
			workInfoService.createAllWorkReportByDptConf(paraMap);
			log.debug("生成考勤报表成功，报表日期："+statDate);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}
