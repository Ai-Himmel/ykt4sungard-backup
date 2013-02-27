package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorTopoGroupInfo;

public interface MonitorTopoGroupInfoDAO extends DAO {

	public  List find(MyQuery myQuery);

	public  List find(String query);

	public  MonitorTopoGroupInfo get(Serializable id);

	public  List getAll();

	public  void save(MonitorTopoGroupInfo transientInstance);

	public  void update(MonitorTopoGroupInfo transientInstance);

	public  void delete(MonitorTopoGroupInfo persistentInstance);

}
