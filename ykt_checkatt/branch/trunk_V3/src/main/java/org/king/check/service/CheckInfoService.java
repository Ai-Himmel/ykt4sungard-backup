package org.king.check.service;

import java.util.List;

import org.king.check.domain.TCheckDeviceLocation;
import org.king.check.domain.TCheckLocation;

public interface CheckInfoService {
	public void createCheckInfo(String startDate,String endDate) throws Exception;
	
	public void refreshCheckInfo(String startDate,String endDate) throws Exception;
	
	public List viewCheckInfoDetail(String startDate,String endDate,String stuempNo,String className,String locationId,String custName) throws Exception;
	
	public List viewClockCheckInfoDetail(String startDate,String endDate,String stuempNo,String className,String locationId,String custName) throws Exception;
	
	public List viewCheckInfoTotal(String startDate,String endDate,String stuempNo,String className,String locationId,String custName) throws Exception;
	
	public List viewClockCheckInfoTotal(String startDate,String endDate,String stuempNo,String className,String locationId,String custName) throws Exception;
	
	public List findAllLocation() throws Exception;
	
	public TCheckLocation getCheckLocation(String id) throws Exception;

	public void deleteCheckLocations(String[] locationIds);

	public void updateCheckLocation(TCheckLocation checkLocation);

	public void saveCheckLocation(TCheckLocation checkLocation);

	public void deleteCheckDeviceLocation(String deviceId);

	public void saveCheckDeviceLocation(TCheckDeviceLocation checkDeviceLocation);

	public List findDevice();
	
	public List findCheckDeviceLocation(String locationId);
	
	public List findNoneClockLocation();
	
	public List findClockLocation();
	
	public List findNormalLocation();

	public List viewCheckDetail(String startDate, String endDate,String stuempNo, String className, String locationId,String custName) throws Exception;

	public List viewCheckTotal(String startDate, String endDate,String stuempNo, String className, String locationId,String custName) throws Exception;
}
