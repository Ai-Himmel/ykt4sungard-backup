package org.king.checkinmanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.checkinmanage.domain.CheckinSubmin;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface CheckinSubminDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public CheckinSubmin get(Serializable id);

	public List getAll();

	public void save(CheckinSubmin transientInstance);

	public void update(CheckinSubmin transientInstance);

	public void delete(CheckinSubmin persistentInstance);

}
