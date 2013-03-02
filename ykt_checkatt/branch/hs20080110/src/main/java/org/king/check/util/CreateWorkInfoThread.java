package org.king.check.util;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
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
 
	private static SimpleDateFormat formatter_yyyymm = new SimpleDateFormat(
	"yyyy-MM");
	
	
	public CreateWorkInfoThread() {
		start();
	}

	public void run() {
		log.debug("start thread");

		while (runThread) {
			log.debug("run in thread");
			String curTime = DateUtilExtend.getNowTime2();

			try{
				if (curTime.equals(createTime)) {
					startCreateWorkInfo();
					sleepTime = 3*60*60*1000;
				}
				
				//Thread.sleep(sleepTime);
				Thread.sleep(3*60*60*1000);

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
		log.debug("start create workinfo report,the time is "+statDate);
		workInfoService = (WorkInfoService) ServiceLocator.getInstance().getService("workInfoService");
		try{
			workInfoService.createAllWorkInfoByDptConf(paraMap);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
	private void runSumKQ(String sumMonth) {
		//String sumMonth = formatter_yyyymm.format(Calendar.getInstance().getTime());
		workInfoService = (WorkInfoService) ServiceLocator.getInstance().getService("workInfoService");

		try {
			workInfoService.deleteRecords(sumMonth);
			
			List deptList = workInfoService.getDeptListForKQService();

			StringBuffer deptStr = new StringBuffer();
			for (int i = 0; i < deptList.size(); i++) {
				Map deptMap = (Map) deptList.get(i);
				String dep = deptMap.get("deptId").toString();
				if (deptList.size() == 1) {
					deptStr.append(dep);
				} else {
					if (i == 0) {
						deptStr.append(dep).append("',");
					} else if (i == deptList.size() - 1) {
						deptStr.append("'").append(dep);
					} else {
						deptStr.append("'").append(dep).append("',");
					}
				}

			}
			List kqList = workInfoService.makeCheckReport(sumMonth, deptStr.toString());
			
			int deleterow =0;
			Iterator reportIter = kqList.iterator();
			while (reportIter.hasNext()){
		    	Map reportMap = (Map)reportIter.next();
		    	
		    	//如果没有考勤记录，则把这行跳过去，不再显示
		    	if ("0".equals(reportMap.get("totMoney").toString())&& 
		    			"0".equals(reportMap.get("totNum").toString())){
		    		deleterow++;
		    		continue;
		    	}
				String deptName = reportMap.get("deptName").toString();
				String stuempNo = reportMap.get("stuempNo").toString();
				String custName = reportMap.get("custName").toString();
				String custType = reportMap.get("custType").toString();
				log.debug(deptName +","
						+ stuempNo +","
						+custName + ","
						+custType );
				
				workInfoService.insertRecords(sumMonth,reportMap);
		    }
			
			
			
		} catch (Exception e1) {
			e1.printStackTrace();
		}
	}
}
