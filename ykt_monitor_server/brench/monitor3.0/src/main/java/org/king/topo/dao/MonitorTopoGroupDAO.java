package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorTopoGroup;

public interface MonitorTopoGroupDAO extends DAO {

	public  void setBaseDAO(BaseDAO baseDAO);

	public  List find(MyQuery myQuery);

	public  List find(String query);

	public  MonitorTopoGroup get(Serializable id);

	public  List getAll();
	
	public List getAllTopoGroupWithLocationOrder();
	
	public int getXWidthbyLocationAndYindex(Integer location,Integer yindex);
	
	public int getYHeightbyLocation(Integer location);

	public  void save(MonitorTopoGroup transientInstance);

	public  void update(MonitorTopoGroup transientInstance);

	public  void delete(MonitorTopoGroup persistentInstance);

}