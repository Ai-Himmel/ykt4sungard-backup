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
public class CreateWorkInfoThread {
	private static final Log log = LogFactory.getLog(CreateWorkInfoThread.class);

	public boolean runThread = true;

	private static WorkInfoService workInfoService;

	public static void startCreateWorkInfo(){
		String statDate = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		Map paraMap = new HashMap();
		paraMap.put("startDate",statDate);
		paraMap.put("endDate",statDate);
		paraMap.put("deptId","");
		paraMap.put("stuEmpNo","");
		//sleepTime = 720000;//��������Сʱ
		//Thread.sleep(sleepTime);
		log.debug("Workinfo-��ʼ���ɿ��ڱ�����ǰ���ڣ� "+statDate);
		workInfoService = (WorkInfoService) ServiceLocator.getInstance().getService("workInfoService");
		try{
			workInfoService.createAllWorkInfoByDptConf(paraMap);
			workInfoService.createAllWorkReportByDptConf(paraMap);
			log.debug("Workinfo-���ɿ��ڱ���ɹ����������ڣ�"+statDate);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
}
