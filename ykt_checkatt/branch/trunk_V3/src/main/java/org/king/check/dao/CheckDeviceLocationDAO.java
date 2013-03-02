package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TCheckDeviceLocation;
import org.king.framework.dao.MyQuery;

public interface CheckDeviceLocationDAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public TCheckDeviceLocation get(Serializable id);

	public List getAll();

	public void save(TCheckDeviceLocation transientInstance);

	public void update(TCheckDeviceLocation transientInstance);

	public void delete(TCheckDeviceLocation persistentInstance);
	
	public TCheckDeviceLocation getCheckDeviceLocation(String deviceid);

}