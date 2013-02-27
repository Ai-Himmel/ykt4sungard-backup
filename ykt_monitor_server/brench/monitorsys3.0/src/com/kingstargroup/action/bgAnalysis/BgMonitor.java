package com.kingstargroup.action.bgAnalysis;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.log4j.Logger;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapParamTable;
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

	public static Map analyzesThreadMap = new HashMap();

	private static BgMonitor intance = null;

	private static Object mutex = new Object();

	private static boolean stopRequest = false;

	private static Map analyzeTime = new HashMap();

	private static Map cycleTime = new HashMap();

	private static Map threadNames = new HashMap();

	private static Map threadStatus = new HashMap();

	public String accelateParam = "60";

	public String SerialLostAnalysisThreadaccelateParam = "60";

	
	/**
			* Method name: getThreadInstance<br>
			* Description: 获得实际的实例类<br>
			* Return: AnalyzeThreadInterface<br>
			* Args: @param clazz
			* Args: @return
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
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

	
	/**
			* Method name: newAnalyzeIntance<br>
			* Description: 线程启动控制<br>
			* Return: void<br>
			* Args: 
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	public void newAnalyzeIntance() {
		if (logger.isInfoEnabled()) {
			logger.info("newAnalyzeIntance() - start");
		}

		try {
			PropertiesConfiguration config = GetPropertiesUtil.getInstance();
			Session session = HibernateSessionFactory.currentSession();
			Query queryCycle = session
					.createQuery("from MapParamTable param where param.parameter=:paramRefer or param.parameter=:paramRefer1");
			queryCycle.setString("paramRefer", "AccelateParam");
			queryCycle.setString("paramRefer1", "SerialLostAccelateParam");
			List list = queryCycle.list();
			Iterator iterParam = list.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("AccelateParam".equals(mapParamTable.getParameter())) {
					String myParam = String.valueOf(mapParamTable.getValue());
					this.accelateParam = myParam.substring(0, myParam
							.indexOf("."));
				}
				if ("SerialLostAccelateParam".equals(mapParamTable
						.getParameter())) {
					String myParam = String.valueOf(mapParamTable.getValue());
					this.SerialLostAnalysisThreadaccelateParam = myParam
							.substring(0, myParam.indexOf("."));
				}
			}
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
		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger.debug("newAnalyzeIntance() - end");
		}
	}

	
	/**
			* Method name: reStart<br>
			* Description: 重启某个线程<br>
			* Return: void<br>
			* Args: @param clazz
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	public static void reStart(String clazz) {
		if (logger.isInfoEnabled()) {
			logger.info("线程重启服务起动：" + clazz + "重新启动，重启时间：" + DateUtil.getNow());
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

		Thread newThread = (Thread) analyzeInterface;
		newThread.start();

		if (logger.isDebugEnabled()) {
			logger.debug("reStart(String) - end");
		}
	}

	
	/**
			* Method name: startThread<br>
			* Description: 启动线程<br>
			* Return: void<br>
			* Args: 
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
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
	
	
	/**
			* Method name: stopAllThreads<br>
			* Description: 停止所有受控的线程<br>
			* Return: void<br>
			* Args: 
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	public void stopAllThreads(){
		if (logger.isInfoEnabled()) {
			logger.info("所有线程停止，停止时间：" + DateUtil.getNow());
		}
		Iterator iter = analyzesThreadMap.keySet().iterator();
		while(iter.hasNext()){
			Object clazz = iter.next();
			if (null != analyzesThreadMap.get(clazz)) {
				analyzeInterface = (AnalyzeThreadInterface) analyzesThreadMap
						.get(clazz);
				if (analyzeInterface.isTerminate()) {
					analyzeInterface.terminate();
				}
				analyzeInterface = null;
				analyzesThreadMap.remove(clazz);
				
				threadNames.remove(clazz);
				analyzeTime.remove(clazz);
				cycleTime.remove(clazz);
				threadStatus.remove(clazz);
			}
			
			if (logger.isInfoEnabled()) {
				logger.debug("stop:"+clazz);
			}
		}
		
	}

	
	/**
			* Method name: monitorThreadStatusReport<br>
			* Description: 个线程报告运行情况<br>
			* Return: void<br>
			* Args: @param clazz
			* Args: @param threadname
			* Args: @param nowTime
			* Args: @param cycle
			* Args: @param status
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	synchronized public static void monitorThreadStatusReport(String clazz,
			String threadname, String nowTime, String cycle, String status) {
		if (logger.isInfoEnabled()) {
			logger.info("线程状态跟踪报告*********名称：" + threadname + " |分析开始时间："
					+ nowTime + " |分析周期：" + cycle + " 秒 |线程状态：" + status);
		}

		threadNames.put(clazz, threadname);
		analyzeTime.put(clazz, nowTime);
		cycleTime.put(clazz, cycle);
		threadStatus.put(clazz, status);
	}

	
	/**
			* Method name: monitorThreadTime<br>
			* Description: <br>
			* Return: void<br>
			* Args: @param clazz
			* Args: @param nowTime
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	synchronized public static void monitorThreadTime(String clazz,
			String nowTime) {
		System.out.println("*****************************" + clazz
				+ " foot print time at: " + nowTime + "****************");
		analyzeTime.put(clazz, nowTime);

	}

	
	/**
			* Method name: monitorCycleTime<br>
			* Description: <br>
			* Return: void<br>
			* Args: @param clazz
			* Args: @param cycle
			* Modify History: <br>
			* 操作类型    操作人     操作时间       操作内容<br>
			* ======================================<br>
			*  创建      何林青    Aug 15, 2007  <br>
			* @author   何林青
			* @version 
			* @since 1.0
			*/
	synchronized public static void monitorCycleTime(String clazz, String cycle) {
		System.out.println("****************************" + clazz
				+ " foot cycle time at: " + cycle + "********************");
		cycleTime.put(clazz, cycle);
	}

	public static Map getMonitorThreadName() {
		return threadNames;
	}

	public static Map getMonitorThreadTime() {
		return analyzeTime;
	}

	public static Map getMonitorCycleTime() {
		return cycleTime;
	}

	public static Map getMonitorStatus() {
		return threadStatus;
	}

}
