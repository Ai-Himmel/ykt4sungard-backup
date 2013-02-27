package org.king.hostservice.service;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceAll;
import org.king.hostservice.domain.MonitorServiceCheck;
import org.king.hostservice.domain.MonitorServiceStatus;
import org.king.hostservice.exception.HostserviceAlreadyExistException;

import java.util.Date;
import java.util.List;

public interface MonitorHostserviceService extends Service {
	
	public MonitorService getMonitorService(Integer Objectid);
	public MonitorServiceAll getMonitorServiceAll(Integer Objectid);
	
	public MonitorServiceStatus getMonitorServiceStatus(Integer Objectid);
	public void updateMonitorServiceStatus(MonitorServiceStatus monitorServiceStatus) throws BusinessException;
	public void saveMonitorServiceStatus(MonitorServiceStatus monitorServiceStatus) throws BusinessException;

    public void saveMonitorService(MonitorService monitorService);

    public List findAllMonitorService();

    public List findMonitorService(Integer hostId);

    public void findMonitorServiceByPage(DBPaginatedList page, MonitorService monitorService);

    public void updateMonitorService(MonitorService monitorService);
    
    public void updateMonitorServiceAll(MonitorServiceAll monitorServiceAll);

    public void deleteMonitorService(Integer id);

    public List findMonitorServiceCheck(Integer serviceId, Date startTime, Date endTime);

    public void findMonitorServiceStatusByPage(DBPaginatedList page, String[] conditions);

    public String[][] calculateServiceStatus();

    public void findServiceHistoryStatusByPage(DBPaginatedList page, Object[] conditions);

    public void findMonitorServiceCheckByPage(DBPaginatedList page, Object[] conditions);
    
    public void saveMonitorServiceCheck(MonitorServiceCheck MScheck) throws BusinessException;
    
    public void updateMonitorServiceCheck(MonitorServiceCheck MScheck) throws BusinessException;
    
    public MonitorServiceCheck getLattestMonitorServiceCheck(Integer Objectid);
}
