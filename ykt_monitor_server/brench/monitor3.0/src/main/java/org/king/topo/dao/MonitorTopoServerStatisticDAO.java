package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.monitor.domain.TDevice;
import org.king.topo.domain.MonitorTopoGroupStatistic;
import org.king.topo.domain.MonitorTopoServerStatistic;

public interface MonitorTopoServerStatisticDAO extends DAO {

	public  List find(MyQuery myQuery);

	public  List find(String query);

	public  MonitorTopoServerStatistic get(Serializable id);

	public  List getAll();

	public  void save(MonitorTopoServerStatistic transientInstance);

	public  void update(MonitorTopoServerStatistic transientInstance);

	public  void delete(MonitorTopoServerStatistic persistentInstance);
	

}
