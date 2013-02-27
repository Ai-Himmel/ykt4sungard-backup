package org.king.topo.service;

import org.king.framework.service.Service;
import org.king.topo.domain.MonitorTopoGroup;
import org.king.topo.domain.MonitorTopoLocation;

import java.util.List;
import java.util.Set;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-21
 */
public interface MonitorTopoService extends Service {

    public List findAllMonitorTopoLocation();

    public void saveMonitorTopoLocation(MonitorTopoLocation monitorTopoLocation);

    public void updateMonitorTopoLocation(MonitorTopoLocation monitorTopoLocation);

    public void deleteMonitorTopoLocation(Integer locationId);

    public MonitorTopoLocation getMonitorTopoLocation(Integer locationId);

    public List findAllMonitorTopoGroup();

    public List findMonitorTopoGroup(MonitorTopoGroup monitorTopoGroup);

    public void saveMonitorTopoGroup(MonitorTopoGroup monitorTopoGroup);

    public void updateMonitorTopoGroup(MonitorTopoGroup monitorTopoGroup);

    public void deleteMonitorTopoGroup(Integer deviceGroupId);

    public MonitorTopoGroup getMonitorTopoGroup(Integer deviceGroupId);

    public List findBindingDevice(Integer deviceGroupId);

    public String getDeviceXmlTree(Integer deviceGroupId);

    public void updateBindingDevice(Integer deviceGroupId, Set devices);

    public List findDeviceGroup(String[] conditions);
}
