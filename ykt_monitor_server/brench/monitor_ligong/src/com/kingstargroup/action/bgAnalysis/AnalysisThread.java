package com.kingstargroup.action.bgAnalysis;

import org.apache.log4j.Logger;

import java.util.HashMap;
import java.util.Map;

import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetPropertiesUtil;

public class AnalysisThread extends Thread {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(AnalysisThread.class);

	// // 1、设备异常（不通、超过警戒线）
	// private double DEVICE_EXCEPTION = 10;
	//
	// // 2、突变流水
	// private double SERI_EXCEPTION = 1.0;
	//
	// // 3、大额不正常流水
	// private double LARGE_EXCEPTION = 1.0;
	//
	// // 4、中途拔卡流水
	// private double MID_EXCEPTION = 1.0;
	//
	// // 5、黑卡消费
	// private double BSHEETVER_EXCEPTION = 1.0;
	//
	// // 6、其他异常流水
	// private double OTHER_EXCEPTION = 1.0;
	//
	// // 7、流水缺号
	// private double SERI_LOSS = 1.0;
	//
	// // 8、压数监控
	// private double SUPRESS_EXCEPTION = 24.0;
	//
	// // 9、未入帐流水
	// private double UNCHECK_SERI = 1.0;
	//
	// // 10、充正流水
	// private double REVERSE_SERI = 1.0;
	//
	// // 11、黑名单版本不正确
	// private double BSHEETVER_ERROR = 1.0;
	//
	// // 12、设备时钟错误
	// private double SETTIME_ERROR = 1.0;
	//
	// // 13、卡库不平
	// private double UNBALANCE_ERROR = 1.0;
	//
	// // 14、短期多次消费
	// private double SHORTTIME_MUTI_COMSUMPTION = 1.0;

	private Map startThreads = null;

	private static Map threadNames = null;

	private static Map threadTimes = null;

	private static Map cycleTimes = null;

	private static Map threadStatus = null;

	// flag of stop this thread
	private boolean requestStop = false;

	/**
	 * @param name
	 */
	public AnalysisThread(HashMap analyzes) {
		this.startThreads = analyzes;
	}

	public void run() {
		if (logger.isInfoEnabled()) {
			logger.info("总控线程开始启动各子线程...");
		}

		try {
			String[] poolThreads = new String[startThreads.keySet().size()];
			startThreads.keySet().toArray(poolThreads);
			String key = "";
			Thread analyze = null;
			for (int i = 0; i < poolThreads.length; i++) {
				key = poolThreads[i];
				analyze = (Thread) startThreads.get(key);
				analyze.start();
				if (logger.isInfoEnabled()) {
					logger.info("第" + (i + 1)+ "个子线程将在5分钟后启动");
				}
				sleep(59000);
			}
		} catch (InterruptedException e) {
			logger.error("子线程启动出现以下错误", e);

		}
		while (!requestStop) {
			try {
				//
				if (GetPropertiesUtil.fileChanged()) {
					BgMonitor.getIntance().accelateParam = GetPropertiesUtil
							.getInstance().getString(
									"THREADS.ACCELATE.PARAMETER");
					BgMonitor.getIntance().newAnalyzeIntance();
				}
				threadNames = BgMonitor.getMonitorThreadName();
				threadTimes = BgMonitor.getMonitorThreadTime();
				cycleTimes = BgMonitor.getMonitorCycleTime();
				threadStatus = BgMonitor.getMonitorStatus();
				String[] timeThreads = new String[threadTimes.keySet().size()];
				threadTimes.keySet().toArray(timeThreads);
				for (int i = 0; i < timeThreads.length; i++) {
					logger.info("线程名："
							+ threadNames.get(timeThreads[i]).toString()
							+ "| 分析时间："
							+ threadTimes.get(timeThreads[i]).toString()
							+ "|分析周期:"
							+ cycleTimes.get(timeThreads[i]).toString()
							+ "|线程状态："
							+ threadStatus.get(timeThreads[i]).toString());

					String tempTime = DateUtil.getNewTime(threadTimes.get(
							timeThreads[i]).toString(),
							(Integer.parseInt(cycleTimes.get(timeThreads[i])
									.toString()) + 300));
					if ((DateUtil
							.checkTimeSequence(DateUtil.getNow(), tempTime)) > 0) {
						// thread has question should be deal with it
						logger.info("总控线程开始重新启动子线程"+threadNames.get(timeThreads[i]).toString());
						BgMonitor.reStart(timeThreads[i]);
					}

				}
				if (logger.isInfoEnabled()) {
					logger.info("总控线进入休眠状态...");
				}

				sleep(1767612);

			} catch (InterruptedException e) {
				logger.error("总线程出现以下异常：", e);

			} catch (Exception e) {
				logger.error("总线程出现以下异常：", e);

			}
		}

		if (logger.isDebugEnabled()) {
			logger.debug("run() - end");
		}
	}

}
