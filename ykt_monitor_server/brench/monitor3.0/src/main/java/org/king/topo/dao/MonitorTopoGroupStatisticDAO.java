package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.monitor.domain.TDevice;
import org.king.topo.domain.MonitorTopoGroupInfo;
import org.king.topo.domain.MonitorTopoGroupStatistic;

public interface MonitorTopoGroupStatisticDAO extends DAO {

	public  List find(MyQuery myQuery);

	public  List find(String query);

	public  MonitorTopoGroupStatistic get(Serializable id);

	public  List getAll();

	public  void save(MonitorTopoGroupStatistic transientInstance);

	public  void update(MonitorTopoGroupStatistic transientInstance);

	public  void delete(MonitorTopoGroupStatistic persistentInstance);
	
	public TDevice getDevice(Serializable deviceid);

}
