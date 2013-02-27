package org.king.host.service;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;
import org.king.host.domain.MonitorHost;
import org.king.host.domain.MonitorHostAll;
import org.king.host.domain.MonitorHostStatus;
import org.king.host.domain.MonitorHostchecks;
import org.king.host.domain.MonitorHostgroups;
import org.king.host.exception.HostAlreadyExistException;
import org.king.host.exception.HostgroupsAlreadyExistException;

import java.util.Date;
import java.util.List;

public interface MonitorHostService extends Service {

    public MonitorHost getMonitorHost(Integer Objectid);
    
    public MonitorHostAll getMonitorHostAll(Integer Objectid);

    public void saveMonitorHost(MonitorHost monitorHost) throws HostAlreadyExistException;

    public List findAllMonitorHost();

    public List findMonitorHost(Integer hostgroupId);

    public void findMonitorHostByPage(DBPaginatedList page, MonitorHost monitorHost);

    public void updateMonitorHost(MonitorHost monitorHost);
    public void updateMonitorHostAll(MonitorHostAll monitorHostAll);

    public void deleteMonitorHost(Integer id) throws BusinessException;

    public MonitorHostgroups getMonitorHostgroups(Integer id);

    public void saveMonitorHostgroups(MonitorHostgroups monitorHostgroups) throws HostgroupsAlreadyExistException;

    public List findAllMonitorHostgroups();

    public void findMonitorHostgroupsByPage(DBPaginatedList page, MonitorHostgroups monitorHostgroups);

    public void updateMonitorHostgroups(MonitorHostgroups monitorHostgroups) throws HostgroupsAlreadyExistException;

    public void deleteMonitorHostgroups(Integer id) throws BusinessException;

    public void findMonitorHostStatusByPage(DBPaginatedList page, String[] conditions);

    public String[][] calculateHostStatus();

    public MonitorHostStatus getMonitorHostStatus(Integer Objectid);

    public void updateMonitorHostStatus(MonitorHostStatus monitorHostStatus) throws BusinessException;

    public void saveMonitorHostStatus(MonitorHostStatus monitorHostStatus) throws BusinessException;

    public List findMonitorHostchecks(Integer hostId, Date startTime, Date endTime);

    public void findHostHistoryStatusByPage(DBPaginatedList page, Object[] conditions);

    public void findMonitorHostchecksByPage(DBPaginatedList page, Object[] conditions);
    
    public MonitorHostchecks getLattestMonitorHostchecks(Integer Objectid);
	
	public void saveMonitorHostchecks(MonitorHostchecks MHc) throws BusinessException;
	
	public void updateMonitorHostchecks(MonitorHostchecks MHc) throws BusinessException;
}
