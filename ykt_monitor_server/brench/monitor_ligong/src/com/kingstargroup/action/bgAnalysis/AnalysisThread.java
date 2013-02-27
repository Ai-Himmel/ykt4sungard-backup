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

	// // 1���豸�쳣����ͨ�����������ߣ�
	// private double DEVICE_EXCEPTION = 10;
	//
	// // 2��ͻ����ˮ
	// private double SERI_EXCEPTION = 1.0;
	//
	// // 3����������ˮ
	// private double LARGE_EXCEPTION = 1.0;
	//
	// // 4����;�ο���ˮ
	// private double MID_EXCEPTION = 1.0;
	//
	// // 5���ڿ�����
	// private double BSHEETVER_EXCEPTION = 1.0;
	//
	// // 6�������쳣��ˮ
	// private double OTHER_EXCEPTION = 1.0;
	//
	// // 7����ˮȱ��
	// private double SERI_LOSS = 1.0;
	//
	// // 8��ѹ�����
	// private double SUPRESS_EXCEPTION = 24.0;
	//
	// // 9��δ������ˮ
	// private double UNCHECK_SERI = 1.0;
	//
	// // 10��������ˮ
	// private double REVERSE_SERI = 1.0;
	//
	// // 11���������汾����ȷ
	// private double BSHEETVER_ERROR = 1.0;
	//
	// // 12���豸ʱ�Ӵ���
	// private double SETTIME_ERROR = 1.0;
	//
	// // 13�����ⲻƽ
	// private double UNBALANCE_ERROR = 1.0;
	//
	// // 14�����ڶ������
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
			logger.info("�ܿ��߳̿�ʼ���������߳�...");
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
					logger.info("��" + (i + 1)+ "�����߳̽���5���Ӻ�����");
				}
				sleep(59000);
			}
		} catch (InterruptedException e) {
			logger.error("���߳������������´���", e);

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
					logger.info("�߳�����"
							+ threadNames.get(timeThreads[i]).toString()
							+ "| ����ʱ�䣺"
							+ threadTimes.get(timeThreads[i]).toString()
							+ "|��������:"
							+ cycleTimes.get(timeThreads[i]).toString()
							+ "|�߳�״̬��"
							+ threadStatus.get(timeThreads[i]).toString());

					String tempTime = DateUtil.getNewTime(threadTimes.get(
							timeThreads[i]).toString(),
							(Integer.parseInt(cycleTimes.get(timeThreads[i])
									.toString()) + 300));
					if ((DateUtil
							.checkTimeSequence(DateUtil.getNow(), tempTime)) > 0) {
						// thread has question should be deal with it
						logger.info("�ܿ��߳̿�ʼ�����������߳�"+threadNames.get(timeThreads[i]).toString());
						BgMonitor.reStart(timeThreads[i]);
					}

				}
				if (logger.isInfoEnabled()) {
					logger.info("�ܿ��߽�������״̬...");
				}

				sleep(1767612);

			} catch (InterruptedException e) {
				logger.error("���̳߳��������쳣��", e);

			} catch (Exception e) {
				logger.error("���̳߳��������쳣��", e);

			}
		}

		if (logger.isDebugEnabled()) {
			logger.debug("run() - end");
		}
	}

}
