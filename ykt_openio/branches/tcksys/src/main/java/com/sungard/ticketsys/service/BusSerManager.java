package com.sungard.ticketsys.service;

import java.util.List;

import com.sungard.ticketsys.dao.BusSerDao;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.common.Page;

public class BusSerManager {
	private BusSerDao busSerDao = BusSerDao.getInstance();

	private static BusSerManager busSerManager;

	public static BusSerManager getInstance() {
		if (busSerManager == null) {
			busSerManager = new BusSerManager();
		}
		return busSerManager;
	}

	public boolean checkBusSerIsUsed(String serilNo) {
		return busSerDao.checkBusSer(serilNo);
	}

	public void saveBusSer(BusSer busSer) {
       busSerDao.saveBusSer(busSer);
	}

	public BusSer getBusSer(String serilNo) {
		return busSerDao.getBusSer(serilNo);
	}

	public void removeBusSer(BusSer newBusSer) {
		busSerDao.remove(newBusSer);
	}

	@SuppressWarnings("unchecked")
	public List<BusSer> getBusSerByConditions(int pageNo, int pageSize,
			BusSer searchBusSer, String orderBy) {
		Page page = busSerDao.getBusByCondition(pageNo,pageSize,searchBusSer,orderBy);
		if (page != null) {
			return (List<BusSer>) page.getResult();
		}
		else {
			return null;
		}
	}

	public Page getBusSerPageByConditions(int pageNo, int pageSize,
			BusSer searchBusSer, String orderBy) {
		Page page=busSerDao.getBusByCondition(pageNo, pageSize, searchBusSer, orderBy);
		return page;
	}

	public void updateBusSer(BusSer infoBusSer) {
		busSerDao.updateBusSer(infoBusSer);
	}

	public List<BusSer> getAllBusSer() {
		return busSerDao.getAllBusSer();
	}

	public boolean busSerIsUsed(String serilNo) {
		return busSerDao.busSerIsUsed(serilNo);
	}
    
}
