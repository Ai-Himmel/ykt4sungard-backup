package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TCheckattReport;
import org.king.check.domain.Tattserialrecord;
import org.king.framework.dao.MyQuery;

public interface WorkInfoDao {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Tattserialrecord get(Serializable id);

	public List getAll();

	public void save(Tattserialrecord workInfo);

	public void update(Tattserialrecord workInfo);

	public void delete(Tattserialrecord workInfo);

	public void save(TCheckattReport workInfo);
	
	public void update(TCheckattReport workInfo);

	public void delete(TCheckattReport workInfo);
	
}