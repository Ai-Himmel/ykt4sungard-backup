package com.kingstargroup.action.bgAnalysis;

import org.apache.log4j.Logger;
import java.util.HashMap;
import java.util.Map;
import org.apache.commons.configuration.PropertiesConfiguration;
import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetPropertiesUtil;

public class BgMonitor {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(BgMonitor.class);
	/*
	 * 
	 */
	private static AnalyzeThreadInterface analyzeInterface = null;

	private static HashMap analyzesThreadMap = new HashMap();

	private static BgMonitor intance = null;

	private static Object mutex = new Object();

	private static boolean stopRequest = false;

	private static Map analyzeTime = new HashMap();
	
	private static Map cycleTime = new HashMap();
	
	private static Map threadNames = new HashMap();
	
	private static Map threadStatus = new HashMap();
	
	public String accelateParam = "0";


	private static AnalyzeThreadInterface getThreadInstance(String clazz) {
		if (logger.isInfoEnabled()) {
			logger.info("getThreadInstance(String) - start");
		}

		Class c;
		try {
			c = Class.forName(clazz);
			AnalyzeThreadInterface analyzethread = (AnalyzeThreadInterface) c
					.newInstance();

			if (logger.isDebugEnabled()) {
				logger.debug("getThreadInstance(String) - end");
			}
			return analyzethread;
		} catch (ClassNotFoundException e1) {
			logger.error("getThreadInstance(String)", e1);
			if (logger.isDebugEnabled()) {
				logger.debug("getThreadInstance(String) - end");
			}
			return null;
		} catch (InstantiationException e) {
			logger.error("getThreadInstance(String)", e);
			if (logger.isDebugEnabled()) {
				logger.debug("getThreadInstance(String) - end");
			}
			return null;
		} catch (IllegalAccessException e) {
			logger.error("getThreadInstance(String)", e);
			if (logger.isDebugEnabled()) {
				logger.debug("getThreadInstance(String) - end");
			}
			return null;
		}
	}

	public void newAnalyzeIntance() {
		if (logger.isInfoEnabled()) {
			logger.info("newAnalyzeIntance() - start");
		}

		try {
			PropertiesConfiguration config = GetPropertiesUtil.getInstance();
			this.accelateParam = config.getString("THREADS.ACCELATE.PARAMETER");
			String[] threads = config.getStringArray("THREADS.NEED.TO.START");
			String[] poolThreads = new String[analyzesThreadMap.keySet().size()];
			analyzesThreadMap.keySet().toArray(poolThreads);
			String key = "";
			for (int i = 0; i < poolThreads.length; i++) {
				key = poolThreads[i];
				for (int j = 0; j < threads.length; j++) {
					stopRequest = false;
					if (poolThreads[i].equals(threads[j])) {
						stopRequest = true;
						break;
					}
					if (false == stopRequest) {
						// stop this thread
						if (null != analyzesThreadMap.get(key)) {
							analyzeInterface = (AnalyzeThreadInterface) analyzesThreadMap
									.get(key);
							if (!analyzeInterface.isTerminate()) {
								analyzeInterface.terminate();
							}
							analyzeInterface = null;
							analyzesThreadMap.remove(key);
						}
					} else {
						// remove form threads
						threads[j] = "";
					}
				}
			}
			for (int k = 0; k < threads.length; k++) {
				if (!"".equals(threads[k])) {
					analyzeInterface = getThreadInstance(threads[k]);
					analyzesThreadMap.put(threads[k], analyzeInterface);
					analyzeInterface.initParam();
				}
			}
			startThread();
		} catch (Exception e) {
			logger.error("newAnalyzeIntance()", e);
		}

		if (logger.isDebugEnabled()) {
			logger.debug("newAnalyzeIntance() - end");
		}
	}
	
	public static void reStart(String clazz){
		if (logger.isInfoEnabled()) {
			logger.info("线程重启服务起动："+clazz+"重新启动，重启时间："+DateUtil.getNow());
		}

		if (null != analyzesThreadMap.get(clazz)) {
			analyzeInterface = (AnalyzeThreadInterface) analyzesThreadMap
					.get(clazz);
			if (analyzeInterface.isTerminate()) {
				analyzeInterface.terminate();
			}
			analyzeInterface = null;
			analyzesThreadMap.remove(clazz);
		}
		analyzeInterface = getThreadInstance(clazz);
		analyzesThreadMap.put(clazz, analyzeInterface);
		analyzeInterface.initParam();

		Thread newThread = (Thread)analyzeInterface;
		newThread.start();

		if (logger.isDebugEnabled()) {
			logger.debug("reStart(String) - end");
		}
	}

	public void startThread() {
		new AnalysisThread(analyzesThreadMap).start();
	}

	public static BgMonitor getIntance() {
		if (intance == null) {
			synchronized (mutex) {
				if (intance == null) {
					intance = new BgMonitor();
				}
			}
		}
		return intance;
	}

	synchronized public static void monitorThreadStatusReport(String clazz,String threadname,String nowTime,String cycle,String status){
		if (logger.isInfoEnabled()) {
			logger
					.info("线程状态跟踪报告*********名称："+threadname+" |分析开始时间："+nowTime+" |分析周期："+cycle+" 秒 |线程状态："+status);
		}

		threadNames.put(clazz,threadname);
		analyzeTime.put(clazz,nowTime);
		cycleTime.put(clazz,cycle);
		threadStatus.put(clazz,status);
	}
	
	synchronized public static void monitorThreadTime(String clazz,String nowTime) {
		System.out.println("*****************************"+clazz +" foot print time at: "+ nowTime+"****************");
		analyzeTime.put(clazz,nowTime);
		
	}
	synchronized public static void monitorCycleTime(String clazz,String cycle) {
		System.out.println("****************************"+clazz +" foot cycle time at: "+ cycle+"********************");
		cycleTime.put(clazz,cycle);
	}
	public static Map getMonitorThreadName(){
		return threadNames;
	}
	public static Map getMonitorThreadTime(){
		return analyzeTime;
	}
	public static Map getMonitorCycleTime(){
		return cycleTime;
	}
	public static Map getMonitorStatus(){
		return threadStatus;
	}
	
}
