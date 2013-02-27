package com.kingstargroup.action.bgAnalysis;

/**
 * <p>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ServiceAnalysisThread.java
 * Description: 服务检查线程
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				2006-11-10   何林青    服务检查线程
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.apache.xml.utils.FastStringBuffer;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.serverAnalysis.MonitorSystemUtils;
import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapDeviceTable;
import com.kingstargroup.form.MapDeviceTableKey;
import com.kingstargroup.form.MapFathersetsTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.Monitors;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class ServerAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ServerAnalysisThread.class);

	private boolean requestStop = false;

	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// inteval param
	private int doubleCycle = 0;

	// alarm contact
	private String contactName = "";

	// record the record of analysis result
	private int mailRecord = 0;

	// whether to record
	private boolean recordOrNot = true;

	// whether to mail
	private boolean mailOrNot = false;

	// whether to SMG
	private boolean smgOrNot = false;

	// mail content' bufferString
	private FastStringBuffer buffer = null;

	// SMG content's Sting
	private String SmgMessage = "";

	// phone number list with delimeter ";"
	private String phoneNumber = "";

	// phone contact name list with delimeter ";"

	private String phoneName = "";

	// mail address list with delimeter ";"
	private String mailList = "";

	// mail contact name list with delimeter ";"
	private String mailName = "";

	// accelate plus time
	private int accelateParam = 0;

	// cpu limit ratio
	private float cpuLimit = 80;

	// memory limit ratio
	private float memLimit = 80;

	// disk used limit ratio
	private float diskLimit = 80;

	private int timeDelay = 30;

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		while (!requestStop) {
			buffer = new FastStringBuffer(100);
			mailRecord = 0;
			anaylize();
		}
		logger.info("$$$$$$$$$$$$$$$$服务器状态分析线程停止运行$$$$$$$$$$$$$$$$$$$$$"); //$NON-NLS-1$
	}

	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************服务器状态分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SERVER_EXCEPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}

			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer1 "
							+ "or param.parameter=:paramRefer2 or param.parameter=:paramRefer3 "
							+ "or param.parameter=:paramRefer4 or param.parameter=:paramRefer5");
			queryCycle.setString("paramRefer1", "ServerExceptionCycle");
			queryCycle.setString("paramRefer2", "MeMopercentage");
			queryCycle.setString("paramRefer3", "CPUpercentage");
			queryCycle.setString("paramRefer4", "HWpercentage");
			queryCycle.setString("paramRefer5", "ServerExceptionParam");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("ServerExceptionCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue().doubleValue();
				} else if ("MeMopercentage"
						.equals(mapParamTable.getParameter())) {
					this.memLimit = mapParamTable.getValue().floatValue();
				} else if ("CPUpercentage".equals(mapParamTable.getParameter())) {
					this.cpuLimit = mapParamTable.getValue().floatValue();
				} else if ("HWpercentage".equals(mapParamTable.getParameter())) {
					this.diskLimit = mapParamTable.getValue().floatValue();
				} else if ("ServerExceptionParam".equals(mapParamTable
						.getParameter())) {
					this.timeDelay = mapParamTable.getValue().intValue();
				}

			}
			String s = String.valueOf(cycle * 60);
			this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

			if (!"20050101000000".equals(this.startTime)) {
				this.endTime = DateUtil.getNewTime(startTime, doubleCycle);
			} else {
				this.endTime = DateUtil.getNow();
				this.startTime = DateUtil
						.getNewTime(this.endTime, -doubleCycle);
			}

		} catch (HibernateException e) {
			logger.error("服务器状态分析线程初始化失败！", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************服务器状态分析线程初始化成功**************"); //$NON-NLS-1$
		}
	}

	/**
	 * @param session
	 */
	private void getParameter(Session session) {
		phoneNumber = "";
		phoneName = "";
		mailList = "";
		contactName = "";
		recordOrNot = true;
		mailOrNot = false;
		smgOrNot = false;
		// monitor param
		Query queryOrNot = session
				.createQuery("from MapAlertTable alert where alert.parameter='ServerException'");
		Iterator iterOrNot = queryOrNot.iterate();
		if (iterOrNot.hasNext()) {
			MapAlertTable alertTable = (MapAlertTable) iterOrNot.next();
			if ("0".equals(alertTable.getNote().toString())) {
				recordOrNot = false;
			}
			if ("1".equals(alertTable.getMailalert().toString())) {
				mailOrNot = true;
			}
			if ("1".equals(alertTable.getPhonealert().toString())) {
				smgOrNot = true;
			}
		}
		Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer1 "
						+ "or param.parameter=:paramRefer2 or param.parameter=:paramRefer3 "
						+ "or param.parameter=:paramRefer4 or param.parameter=:paramRefer5");
		queryCycle.setString("paramRefer1", "ServerExceptionCycle");
		queryCycle.setString("paramRefer2", "MeMopercentage");
		queryCycle.setString("paramRefer3", "CPUpercentage");
		queryCycle.setString("paramRefer4", "HWpercentage");
		queryCycle.setString("paramRefer5", "ServerExceptionParam");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("ServerExceptionCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue().doubleValue();
			} else if ("MeMopercentage".equals(mapParamTable.getParameter())) {
				this.memLimit = mapParamTable.getValue().floatValue();
			} else if ("CPUpercentage".equals(mapParamTable.getParameter())) {
				this.cpuLimit = mapParamTable.getValue().floatValue();
			} else if ("HWpercentage".equals(mapParamTable.getParameter())) {
				this.diskLimit = mapParamTable.getValue().floatValue();
			} else if ("ServerExceptionParam".equals(mapParamTable
					.getParameter())) {
				this.timeDelay = mapParamTable.getValue().intValue();
			}

		}
		String s = String.valueOf(cycle * 60);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SERVER_EXCEPTION'");
		List listContact = queryContact.list();
		Iterator iterContact = listContact.iterator();
		while (iterContact.hasNext()) {
			MapContactMonitorTable contactMonitor = (MapContactMonitorTable) iterContact
					.next();
			String nowDayTime = DateUtil.getNow("HHmmss");

			Query queryPhone = session
					.createQuery("from MapContactTable a where a.contactname=:contactName "
							+ "and a.starttime<=:starttime and a.endtime>=:endtime");
			queryPhone
					.setString("contactName", contactMonitor.getContactname());
			queryPhone.setString("starttime", nowDayTime);
			queryPhone.setString("endtime", nowDayTime);
			Iterator iterPhone = queryPhone.iterate();
			if (iterPhone.hasNext()) {
				MapContactTable contactTable = (MapContactTable) iterPhone
						.next();
				int dayofWeek = DateUtil.getDayofWeek();
				if ((1 == dayofWeek)
						&& ("1".equals(contactTable.getWeekdays().substring(6,
								7)))) {
					if (!"".equals(contactTable.getCellphone())) {
						phoneNumber += contactTable.getCellphone() + ";";
						phoneName += contactTable.getContactname() + ";";
					}
					if (!"".equals(contactTable.getEmail())) {
						mailList += contactTable.getEmail() + ";";
						mailName += contactMonitor.getContactname() + ";";
					}
					if (!"".equals(contactMonitor.getContactname())) {
						contactName += contactMonitor.getContactname() + ",";
					}
				} else if ("1".equals(contactTable.getWeekdays().substring(
						dayofWeek - 2, dayofWeek - 1))) {
					if (!"".equals(contactTable.getCellphone())) {
						phoneNumber += contactTable.getCellphone() + ";";
						phoneName += contactTable.getContactname() + ";";
					}
					if (!"".equals(contactTable.getEmail())) {
						mailList += contactTable.getEmail() + ";";
						mailName += contactMonitor.getContactname() + ";";
					}
					if (!"".equals(contactMonitor.getContactname())) {
						contactName += contactMonitor.getContactname() + ",";
					}
				}
			}
		}
		if (!"".equals(contactName)) {
			contactName = contactName
					.substring(0, contactName.lastIndexOf(","));
		}
	}

	public void anaylize() {
		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().accelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);
			if (logger.isInfoEnabled()) {
				logger
						.info("服务器状态分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 != DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("服务器状态分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}

			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("服务器状态分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			}

			getParameter(session);
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.ServerAnalysisThread",
							"服务器状态分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "运行中...");
			Query query = session
					.createSQLQuery(
							"select {server.*} from ykt_mon.map_fathersets_table server with ur")
					.addEntity("server", MapFathersetsTable.class);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				MapFathersetsTable server = (MapFathersetsTable) iter.next();
				String operationsystem = server.getOperationsystem();
				if ("windows".equals(operationsystem)) {
					String ipaddr = server.getIp();
					String cpuratio = MonitorSystemUtils.cpuCheck(ipaddr,
							"kingstar", 1);
					String memratio = MonitorSystemUtils.memCheck(ipaddr,
							"kingstar", 1);
					String diskratio = MonitorSystemUtils.diskCheck(ipaddr,
							"kingstar", 1);
					if ("down".equals(cpuratio) && "down".equals(memratio)
							&& "down".equals(diskratio)) {
						// 机器down了
						MapDeviceTable mapDeviceTable = new MapDeviceTable();
						MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
						deviceTableKey.setAnalysisTime(recordTime);
						deviceTableKey.setDeviceId(server.getId());
						mapDeviceTable.setArea(server.getArea());
						mapDeviceTable.setBsheetver("");
						Query queryContact = session
								.createQuery("select a.contactname from MapContactMonitorTable a "
										+ "where a.monitorno= :monitorNo");
						queryContact.setString("monitorNo", server.getId()
								.toString());
						List listContact = queryContact.list();
						contactName = "";
						for (int i = 0; i < listContact.size(); i++) {
							contactName += listContact.get(i).toString() + ",";
						}
						if (!"".equals(contactName)) {
							contactName = contactName.substring(0, contactName
									.lastIndexOf(","));
						}
						mapDeviceTable.setContactName(contactName);
						mapDeviceTable.setCpu(Float.valueOf("0"));
						mapDeviceTable.setDevicetime("");
						mapDeviceTable.setServertime("");
						mapDeviceTable.setDeviceName(server.getSystemname());
						mapDeviceTable.setDeviceType("0000");
						mapDeviceTable.setDevphy999Id(server.getSystemid());
						mapDeviceTable.setErrorReason(Short.valueOf("105"));
						// down机
						mapDeviceTable.setFdevphyId("FFFFFFFF");
						mapDeviceTable.setHarddisk(Float.valueOf("0"));
						mapDeviceTable.setId(deviceTableKey);
						mapDeviceTable.setMemory(Float.valueOf("0"));
						mapDeviceTable.setSubsystemId(server.getArea());
						session.save(mapDeviceTable);
					} else {
						float cpu = 0;
						float mem = 0;
						float disk =0;
						if(!"down".equals(cpuratio)){
							cpu = Float.parseFloat("".equals(cpuratio)?"0":cpuratio);
						}
						if(!"down".equals(memratio)){
							mem= Float.parseFloat("".equals(memratio)?"0":memratio);
						}
						if(!"down".equals(diskratio)){
							disk= Float.parseFloat("".equals(diskratio)?"0":diskratio);
						}						
						if (cpu > cpuLimit) {
							// cpu越界了
							MapDeviceTable mapDeviceTable = new MapDeviceTable();
							MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
							deviceTableKey.setAnalysisTime(recordTime);
							deviceTableKey.setDeviceId(server.getId());
							mapDeviceTable.setArea(server.getArea());
							mapDeviceTable.setBsheetver("");
							Query queryContact = session
									.createQuery("select a.contactname from MapContactMonitorTable a "
											+ "where a.monitorno= :monitorNo");
							queryContact.setString("monitorNo", server.getId()
									.toString());
							List listContact = queryContact.list();
							contactName = "";
							for (int i = 0; i < listContact.size(); i++) {
								contactName += listContact.get(i).toString()
										+ ",";
							}
							if (!"".equals(contactName)) {
								contactName = contactName.substring(0,
										contactName.lastIndexOf(","));
							}
							mapDeviceTable.setContactName(contactName);
							mapDeviceTable.setCpu(Float.valueOf(cpuratio));
							mapDeviceTable.setDevicetime("");
							mapDeviceTable.setServertime("");
							mapDeviceTable
									.setDeviceName(server.getSystemname());
							mapDeviceTable.setDeviceType("0000");
							mapDeviceTable.setDevphy999Id(server.getSystemid());
							mapDeviceTable.setErrorReason(Short.valueOf("102"));
							mapDeviceTable.setFdevphyId("FFFFFFFF");
							mapDeviceTable
									.setHarddisk(Float.valueOf(diskratio));
							mapDeviceTable.setId(deviceTableKey);
							mapDeviceTable.setMemory(Float.valueOf(memratio));
							mapDeviceTable.setSubsystemId(server.getArea());
							session.save(mapDeviceTable);
						}
						if (mem > memLimit) {
							// mem越界了
							MapDeviceTable mapDeviceTable = new MapDeviceTable();
							MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
							deviceTableKey.setAnalysisTime(DateUtil.getNewTime(
									recordTime, 1));
							deviceTableKey.setDeviceId(server.getId());
							mapDeviceTable.setArea(server.getArea());
							mapDeviceTable.setBsheetver("");
							Query queryContact = session
									.createQuery("select a.contactname from MapContactMonitorTable a "
											+ "where a.monitorno= :monitorNo");
							queryContact.setString("monitorNo", server.getId()
									.toString());
							List listContact = queryContact.list();
							contactName = "";
							for (int i = 0; i < listContact.size(); i++) {
								contactName += listContact.get(i).toString()
										+ ",";
							}
							if (!"".equals(contactName)) {
								contactName = contactName.substring(0,
										contactName.lastIndexOf(","));
							}
							mapDeviceTable.setContactName(contactName);
							mapDeviceTable.setCpu(Float.valueOf(cpuratio));
							mapDeviceTable.setDevicetime("");
							mapDeviceTable.setServertime("");
							mapDeviceTable
									.setDeviceName(server.getSystemname());
							mapDeviceTable.setDeviceType("0000");
							mapDeviceTable.setDevphy999Id(server.getSystemid());
							mapDeviceTable.setErrorReason(Short.valueOf("103"));
							mapDeviceTable.setFdevphyId("FFFFFFFF");
							mapDeviceTable
									.setHarddisk(Float.valueOf(diskratio));
							mapDeviceTable.setId(deviceTableKey);
							mapDeviceTable.setMemory(Float.valueOf(memratio));
							mapDeviceTable.setSubsystemId(server.getArea());
							session.save(mapDeviceTable);
						}
						if (disk > diskLimit) {
							// disk越界了
							MapDeviceTable mapDeviceTable = new MapDeviceTable();
							MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
							deviceTableKey.setAnalysisTime(DateUtil.getNewTime(
									recordTime, 2));
							deviceTableKey.setDeviceId(server.getId());
							mapDeviceTable.setArea(server.getArea());
							mapDeviceTable.setBsheetver("");
							Query queryContact = session
									.createQuery("select a.contactname from MapContactMonitorTable a "
											+ "where a.monitorno= :monitorNo");
							queryContact.setString("monitorNo", server.getId()
									.toString());
							List listContact = queryContact.list();
							contactName = "";
							for (int i = 0; i < listContact.size(); i++) {
								contactName += listContact.get(i).toString()
										+ ",";
							}
							if (!"".equals(contactName)) {
								contactName = contactName.substring(0,
										contactName.lastIndexOf(","));
							}
							mapDeviceTable.setContactName(contactName);
							mapDeviceTable.setCpu(Float.valueOf(cpuratio));
							mapDeviceTable.setDevicetime("");
							mapDeviceTable.setServertime("");
							mapDeviceTable
									.setDeviceName(server.getSystemname());
							mapDeviceTable.setDeviceType("0000");
							mapDeviceTable.setDevphy999Id(server.getSystemid());
							mapDeviceTable.setErrorReason(Short.valueOf("104"));
							mapDeviceTable.setFdevphyId("FFFFFFFF");
							mapDeviceTable
									.setHarddisk(Float.valueOf(diskratio));
							mapDeviceTable.setId(deviceTableKey);
							mapDeviceTable.setMemory(Float.valueOf(memratio));
							mapDeviceTable.setSubsystemId(server.getArea());
							session.save(mapDeviceTable);
						}
					}

				} else {// linux/unix/solrias
					String hostname = server.getIp();
					Query lateQuery = session
							.createSQLQuery(
									"select distinct current timestamp time from ykt_mon.monitors")
							.addScalar("time", Hibernate.TIMESTAMP);
					List lateList = lateQuery.list();
					Date systime = (Date) lateList.get(0);
					Date timeLimit = DateUtil.getNewDate(systime, -timeDelay);
					Query timeQuery = session
							.createQuery("from Monitors a where a.id.host=:hostname and a.id.category='APP' and a.id.entry='monitor_agent'");
					timeQuery.setString("hostname", hostname);
					List listTime = timeQuery.list();
					Iterator iterTime = listTime.iterator();
					if (iterTime.hasNext()) {
						Monitors monitor = (Monitors) iterTime.next();
						Date clientTime = monitor.getModified();
						if (DateUtil.checkDateSequence(timeLimit, clientTime) > 0) {
							// server'status hasn't update for a long time
							// may be is down
							MapDeviceTable mapDeviceTable = new MapDeviceTable();
							MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
							deviceTableKey.setAnalysisTime(recordTime);
							deviceTableKey.setDeviceId(server.getId());
							mapDeviceTable.setArea(server.getArea());
							mapDeviceTable.setBsheetver("");
							Query queryContact = session
									.createQuery("select a.contactname from MapContactMonitorTable a "
											+ "where a.monitorno= :monitorNo");
							queryContact.setString("monitorNo", server.getId()
									.toString());
							List listContact = queryContact.list();
							contactName = "";
							for (int i = 0; i < listContact.size(); i++) {
								contactName += listContact.get(i).toString()
										+ ",";
							}
							if (!"".equals(contactName)) {
								contactName = contactName.substring(0,
										contactName.lastIndexOf(","));
							}
							mapDeviceTable.setContactName(contactName);
							mapDeviceTable.setCpu(Float.valueOf("0"));
							mapDeviceTable.setDevicetime("");
							mapDeviceTable.setServertime("");
							mapDeviceTable
									.setDeviceName(server.getSystemname());
							mapDeviceTable.setDeviceType("0000");
							mapDeviceTable.setDevphy999Id(server.getSystemid());
							mapDeviceTable.setErrorReason(Short.valueOf("105"));
							// down机
							mapDeviceTable.setFdevphyId("FFFFFFFF");
							mapDeviceTable.setHarddisk(Float.valueOf("0"));
							mapDeviceTable.setId(deviceTableKey);
							mapDeviceTable.setMemory(Float.valueOf("0"));
							mapDeviceTable.setSubsystemId(server.getArea());
							session.save(mapDeviceTable);

						}
					}

					Query cpuQuery = session
							.createQuery("from Monitors a where a.id.host=:hostname and a.id.category='CPU' and a.id.entry='IDLE' and a.modified>=:timeLimit");
					cpuQuery.setString("hostname", hostname);
					cpuQuery.setTimestamp("timeLimit", timeLimit);
					List listCPU = cpuQuery.list();
					Iterator iterCPU = listCPU.iterator();
					if (iterCPU.hasNext()) {
						Monitors monitor = (Monitors) iterCPU.next();
						String cpu = monitor.getValuestr();
						cpu = cpu.substring(0, cpu.indexOf("%"));
						int idlecpu = Integer.valueOf(cpu).intValue();
						if (idlecpu < (100 - cpuLimit)) {
							// 有问题
							if (true == recordOrNot) {
								MapDeviceTable mapDeviceTable = new MapDeviceTable();
								MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
								deviceTableKey.setAnalysisTime(recordTime);
								deviceTableKey.setDeviceId(server.getId());
								mapDeviceTable.setArea(server.getArea());
								mapDeviceTable.setBsheetver("");
								Query queryContact = session
										.createQuery("select a.contactname from MapContactMonitorTable a "
												+ "where a.monitorno= :monitorNo");
								queryContact.setString("monitorNo", server
										.getId().toString());
								List listContact = queryContact.list();
								contactName = "";
								for (int i = 0; i < listContact.size(); i++) {
									contactName += listContact.get(i)
											.toString()
											+ ",";
								}
								if (!"".equals(contactName)) {
									contactName = contactName.substring(0,
											contactName.lastIndexOf(","));
								}
								mapDeviceTable.setContactName(contactName);
								mapDeviceTable.setCpu(Float.valueOf(String
										.valueOf(100 - idlecpu)));
								mapDeviceTable.setDevicetime("");
								mapDeviceTable.setServertime("");
								mapDeviceTable.setDeviceName(server
										.getSystemname());
								mapDeviceTable.setDeviceType("0000");
								mapDeviceTable.setDevphy999Id(server
										.getSystemid());
								mapDeviceTable.setErrorReason(Short
										.valueOf("102"));
								mapDeviceTable.setFdevphyId("FFFFFFFF");
								mapDeviceTable.setHarddisk(Float.valueOf("0"));
								mapDeviceTable.setId(deviceTableKey);
								mapDeviceTable.setMemory(Float.valueOf("0"));
								mapDeviceTable.setSubsystemId(server.getArea());
								session.save(mapDeviceTable);
							}
						}
					}

					Query MenQuery = session
							.createQuery("from Monitors a where a.id.host=:hostname and (a.id.category='MEM' or a.id.category='MEM1') and a.modified>=:timeLimit");
					MenQuery.setString("hostname", hostname);
					MenQuery.setTimestamp("timeLimit", timeLimit);
					List listMEM = MenQuery.list();
					Iterator iterMEM = listMEM.iterator();
					if (iterMEM.hasNext()) {
						String MemTotal = "";
						String MemFree = "";
						while (iterMEM.hasNext()) {
							Monitors monitor = (Monitors) iterMEM.next();
							if ("MemTotal:".equals(monitor.getId().getEntry()
									.trim())) {
								MemTotal = monitor.getValuestr();
							} else if ("MemFree:".equals(monitor.getId()
									.getEntry().trim())) {
								MemFree = monitor.getValuestr();
							}
						}
						int MemTotalInt = Integer.valueOf(MemTotal).intValue();
						int MemFreeInt = Integer.valueOf(MemFree).intValue();
						int ratio = MemFreeInt * 100 / MemTotalInt;
						ratio = 100 - ratio;//使用率
						if (ratio > memLimit) {
							// 有问题
							if (true == recordOrNot) {
								MapDeviceTable mapDeviceTable = new MapDeviceTable();
								MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
								deviceTableKey.setAnalysisTime(DateUtil
										.getNewTime(recordTime, 1));
								deviceTableKey.setDeviceId(server.getId());
								mapDeviceTable.setArea(server.getArea());
								mapDeviceTable.setBsheetver("");
								Query queryContact = session
										.createQuery("select a.contactname from MapContactMonitorTable a "
												+ "where a.monitorno= :monitorNo");
								queryContact.setString("monitorNo", server
										.getId().toString());
								List listContact = queryContact.list();
								contactName = "";
								for (int i = 0; i < listContact.size(); i++) {
									contactName += listContact.get(i)
											.toString()
											+ ",";
								}
								if (!"".equals(contactName)) {
									contactName = contactName.substring(0,
											contactName.lastIndexOf(","));
								}
								mapDeviceTable.setContactName(contactName);
								mapDeviceTable.setCpu(Float.valueOf("0"));
								mapDeviceTable.setDevicetime("");
								mapDeviceTable.setServertime("");
								mapDeviceTable.setDeviceName(server
										.getSystemname());
								mapDeviceTable.setDeviceType("0000");
								mapDeviceTable.setDevphy999Id(server
										.getSystemid());
								mapDeviceTable.setErrorReason(Short
										.valueOf("103"));
								mapDeviceTable.setFdevphyId("FFFFFFFF");
								mapDeviceTable.setHarddisk(Float.valueOf("0"));
								mapDeviceTable.setId(deviceTableKey);
								mapDeviceTable.setMemory(Float.valueOf(String
										.valueOf(ratio)));
								mapDeviceTable.setSubsystemId(server.getArea());
								session.save(mapDeviceTable);
							}
						}
					}

					Query DiskQuery = session
							.createQuery("from Monitors a where a.id.host=:hostname and a.id.category='DISK' and a.modified>=:timeLimit");
					DiskQuery.setString("hostname", hostname);
					DiskQuery.setTimestamp("timeLimit", timeLimit);
					List listDISK = DiskQuery.list();
					Iterator iterDISK = listDISK.iterator();
					long DISKUsed = 0;
					long DISKTOTAL = 0;
					if (iterDISK.hasNext()) {
						while (iterDISK.hasNext()) {
							Monitors monitor = (Monitors) iterDISK.next();
							String value = monitor.getValuestr();
							String tempused = value.substring(0, value
									.indexOf("_"));
							String temptotal = value.substring(value
									.indexOf("_") + 1);
							long tempusedint = Long.parseLong(tempused);
							long temptotalint = Long.parseLong(temptotal);
							DISKTOTAL += temptotalint;
							DISKUsed += tempusedint;
						}
						long ratio = DISKUsed * 100 / DISKTOTAL;
						if (ratio > diskLimit) {
							// 有问题
							if (true == recordOrNot) {
								MapDeviceTable mapDeviceTable = new MapDeviceTable();
								MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
								deviceTableKey.setAnalysisTime(DateUtil
										.getNewTime(recordTime, 2));
								deviceTableKey.setDeviceId(server.getId());
								mapDeviceTable.setArea(server.getArea());
								mapDeviceTable.setBsheetver("");
								Query queryContact = session
										.createQuery("select a.contactname from MapContactMonitorTable a "
												+ "where a.monitorno= :monitorNo");
								queryContact.setString("monitorNo", server
										.getId().toString());
								List listContact = queryContact.list();
								contactName = "";
								for (int i = 0; i < listContact.size(); i++) {
									contactName += listContact.get(i)
											.toString()
											+ ",";
								}
								if (!"".equals(contactName)) {
									contactName = contactName.substring(0,
											contactName.lastIndexOf(","));
								}
								mapDeviceTable.setContactName(contactName);
								mapDeviceTable.setCpu(Float.valueOf("0"));
								mapDeviceTable.setDevicetime("");
								mapDeviceTable.setServertime("");
								mapDeviceTable.setDeviceName(server
										.getSystemname());
								mapDeviceTable.setDeviceType("0000");
								mapDeviceTable.setDevphy999Id(server
										.getSystemid());
								mapDeviceTable.setErrorReason(Short
										.valueOf("104"));
								mapDeviceTable.setFdevphyId("FFFFFFFF");
								mapDeviceTable.setHarddisk(Float.valueOf(String
										.valueOf(ratio)));
								mapDeviceTable.setId(deviceTableKey);
								mapDeviceTable.setMemory(Float.valueOf("0"));
								mapDeviceTable.setSubsystemId(server.getArea());
								session.save(mapDeviceTable);
							}
						}
					}

				}
			}

			// mailRecord++;
			// if (!"".equals(mailList)) {
			// String device_name = "";
			// device_name = DeviceNameDictionary.getInstance().get(
			// rcvdtl.getId().getDeviceId()).trim();
			// Query queryCustomer = session
			// .createSQLQuery(
			// "select a.cut_name as cutName "
			// + "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
			// + "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId with ur")
			// .addScalar("cutName", Hibernate.STRING);
			// queryCustomer.setInteger("cutId", rcvdtl.getId()
			// .getCardNo().intValue());
			// List listCust = queryCustomer.list();
			// String cust_name = "";
			// if (listCust.size() > 0) {
			// cust_name = listCust.get(0).toString().trim();
			// }
			// buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
			// .getDeviceId(), device_name, rcvdtl.getId()
			// .getCardNo(), cust_name, rcvdtl.getId()
			// .getSerialNo().toString(), rcvdtl.getId()
			// .getTxDate(), rcvdtl.getId().getTxTime(),
			// "SERVER_EXCEPTION.BLACK_ERR"));
			// }

			session.flush();
			session.clear();

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SERVER_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SERVER_EXCEPTION");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}

			tx.commit();
			// mail
			sendMail();
			// SMG
			sendSMG();

		} catch (HibernateException e) {
			logger.error("服务器状态分析线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("服务器状态分析线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
		} finally {
			HibernateSessionFactory.closeSession();
		}

		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("服务器状态线程分析结束进入休眠状态!"
								+ " 休眠开始时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", 休眠时间:" + sleepTime + " 毫秒"); //$NON-NLS-1$
			}
			this.startTime = this.endTime;
			this.endTime = DateUtil.getNewTime(this.endTime, doubleCycle);
			if (sleepTime <= 0) {
				sleep(600000);
			} else {
				sleep(sleepTime);
			}
		} catch (InterruptedException e) {
			logger.error("服务器状态分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("服务器状态分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("服务器状态分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("服务器状态分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
			this.destroy();

		}
	}

	public boolean isTerminate() {
		// TODO Auto-generated method stub
		return this.isAlive();
	}

	public void sendMail() {
		// TODO Auto-generated method stub
		if ((true == mailOrNot) && (!"".equals(mailList))
				&& (0 != buffer.size())) {
			if (logger.isInfoEnabled()) {
				logger.info("服务器状态分析线程发送邮件给联系人:" + contactName);
			}
			String tmpStr = "";
			if (buffer.size() > 5000) {
				tmpStr = buffer.getString(0, 5000);
			}
			tmpStr = buffer.toString();

			String[] tempList = null;
			String[] nameList = null;
			tempList = mailList.split(";");
			nameList = mailName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					CommonSendMailUtil.sendMail(GetApplicationResources
							.getInstance().getString(
									"com.kingstar.MonitorSys.SUBJECT_SERIAL"),
									nameList[i], tempList[i], StringUtil
									.wholeMailGenerate(nameList[i], DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"SERVER_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("服务器状态分析线程发送短信给联系人:" + contactName);
			}

			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			// String tempPhone = phoneNumber.substring(0, phoneNumber
			// .lastIndexOf(";"));
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"SERVER_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}

		}
	}
}
