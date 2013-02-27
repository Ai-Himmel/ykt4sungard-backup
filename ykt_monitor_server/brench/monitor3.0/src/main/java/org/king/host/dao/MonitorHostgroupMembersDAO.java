package org.king.host.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHostgroupMembers;

public interface MonitorHostgroupMembersDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorHostgroupMembers get(Serializable id);

	public List getAll();

	public void save(MonitorHostgroupMembers transientInstance);

	public void update(MonitorHostgroupMembers transientInstance);

	public void delete(MonitorHostgroupMembers persistentInstance);

}