package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorContactgroupMembers;


public interface MonitorContactgroupMembersDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorContactgroupMembers get(Serializable id);

	public List getAll();

	public void save(MonitorContactgroupMembers transientInstance);

	public void update(MonitorContactgroupMembers transientInstance);

	public void delete(MonitorContactgroupMembers persistentInstance);

}