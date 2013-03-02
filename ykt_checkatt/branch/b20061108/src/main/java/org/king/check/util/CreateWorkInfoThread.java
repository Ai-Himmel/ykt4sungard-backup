package org.king.check.util;

import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.service.WorkInfoService;
import org.king.framework.service.ServiceLocator;

/**
 * @author liufei
 * 
 */
public class CreateWorkInfoThread extends Thread {
	private static final Log log = LogFactory
			.getLog(CreateWorkInfoThread.class);

	long sleepTime = 6000;

	public boolean runThread = true;

	private WorkInfoService workInfoService;

	private Map paraMap = new HashMap();

	private String createTime = "2359";

	public CreateWorkInfoThread() {
		start();

	}

	public void run() {
		log.debug("start thread");

		while (runThread) {
			log.debug("run in thread");
			Calendar cal = Calendar.getInstance();
			Date nowDate = new Date();
			cal.setTime(nowDate);

			String curTime = Integer.toString(cal.get(Calendar.HOUR_OF_DAY))
					+ Integer.toString(cal.get(Calendar.MINUTE));
			log.debug("createTime:" + createTime + " curTime:" + curTime);

			try {
				sleepTime = 6000;
				// 一到时间启动生成考勤数据的功能
				if (curTime.equals(createTime)) {

					workInfoService = (WorkInfoService) ServiceLocator
							.getInstance().getService("workInfoService");
					workInfoService.createAllWorkInfoByDptConf(paraMap);
					sleepTime = 60000;
				}
				Thread.sleep(sleepTime);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
