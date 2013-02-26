package com.sungard.ticketsys.service;

import java.util.List;

import com.sungard.ticketsys.dao.SerSetDao;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.common.Page;

public class RunbusManager {

	private SerSetDao serSetDao = SerSetDao.getInstance();

	private static RunbusManager runbusManager;

	public static RunbusManager getInstance() {
		if (runbusManager == null) {
			runbusManager = new RunbusManager();
		}
		return runbusManager;
	}

	/**
	 * 查询出”停止售票“的车次
	 * @param pageNo
	 * @param pageSize
	 * @param searchSerSet
	 * @param departDate
	 * @param startAddr
	 * @param endAddr
	 * @param orderBy
	 * @return
	 */
	@SuppressWarnings("unchecked")
	public List<BusserDay> getSerSetByConditions(int pageNo,
			int pageSize, BusserDay searchSerSet, String departDate, String orderBy) {
		Page page = serSetDao.getSerSetByConditions(pageNo, pageSize,
				searchSerSet, departDate, null,null, orderBy,BusserDay.STATE_STOP_SALE);
		if (page != null) {
			return (List<BusserDay>) page.getResult();
		} else {
			return null;
		}
	}
	
	/**
	 *  查询出”停止售票“的车次分页对象
	 * @param pageNo
	 * @param pageSize
	 * @param searchSerSet
	 * @param departDate
	 * @param startAddr
	 * @param endAddr
	 * @param orderBy
	 * @return
	 */
	public Page getPageByConditions(int pageNo,
			int pageSize, BusserDay searchSerSet, String departDate,String orderBy){
		return serSetDao.getSerSetByConditions(pageNo, pageSize,
				searchSerSet, departDate, null,null, orderBy,BusserDay.STATE_STOP_SALE);
	}

	public void checkDepartBus(BusserDay sleBusserDay)throws Exception {
		serSetDao.updateBusserDay(sleBusserDay);
		
	}

	/**
	 *  查询出”已发车“的车次分页对象
	 * @param pageNo
	 * @param defaultPageSize
	 * @param searchSerSet
	 * @param startDate
	 * @param endDate
	 * @param lineName
	 * @param string
	 * @return
	 */
	public Page getPageByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String startDate, String endDate,
			String lineName, String orderBy) {
		return serSetDao.geBusserDayByConditions(pageNo, pageSize,
				searchSerSet, startDate, endDate,lineName, orderBy,BusserDay.STATE_IS_RUN);
	}
	
}
