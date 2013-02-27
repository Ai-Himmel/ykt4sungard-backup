package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorTopoDeviceDic;

public interface MonitorTopoDeviceDicDAO extends DAO {
	
	public  List find(MyQuery myQuery);

	public  List find(String query);

	public  MonitorTopoDeviceDic get(Serializable id);

	public  List getAll();

	public  void save(MonitorTopoDeviceDic transientInstance);

	public  void update(MonitorTopoDeviceDic transientInstance);

	public  void delete(MonitorTopoDeviceDic persistentInstance);
	
	public MonitorTopoDeviceDic findDictByTypecode(Integer devphytype,String devtypecode);

}