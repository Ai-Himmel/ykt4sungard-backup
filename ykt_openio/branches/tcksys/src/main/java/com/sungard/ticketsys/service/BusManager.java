package com.sungard.ticketsys.service;

import java.util.List;

import com.sungard.ticketsys.dao.BusDao;
import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.common.Page;

public class BusManager {
private BusDao busDao = BusDao.getInstance();
	
	private static BusManager busManager ;
    
    public static BusManager getInstance(){
        if(busManager == null){
        	busManager = new BusManager();
        }
        return busManager;
    }
    
    @SuppressWarnings("unchecked")
	public List<Bus> getBusByConditions(int pageNo, int pageSize, Bus bus, String orderBy) {
		Page page = busDao.getBusByCondition(pageNo,pageSize,bus,orderBy);
		if (page != null) {
			return (List<Bus>) page.getResult();
		}
		else {
			return null;
		}
	}
	
	public Page getBusByConditions(int pageNo, int pageSize,
			Bus searchBus) {
		Page page=busDao.getBusByCondition(pageNo, pageSize, searchBus, null);
			return page;
	}

	public Bus getBus(String busNo) {
		return busDao.getBus(busNo);
	}

	public void removeBus(Bus newBus) {
		busDao.remove(newBus);
	}

	public boolean checkBusIsUsed(String busNo) {
		return busDao.checkBus(busNo);
	}

	public void saveBus(Bus Bus) {
		busDao.saveBus(Bus);
	}

	public void updateBus(Bus infoBus) {
		busDao.updateBus(infoBus);
		
	}

	public List<Bus> getAllBus() {
		return busDao.getAllBus();
	}

	public boolean busIsUsed(String busNo) {
		// TODO Auto-generated method stub
		return busDao.busIsUsed(busNo);
	}
    
}

