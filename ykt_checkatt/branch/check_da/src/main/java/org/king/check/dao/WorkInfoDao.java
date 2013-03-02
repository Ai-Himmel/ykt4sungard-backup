package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Tattserial;
import org.king.check.domain.Tattserialrecord;
import org.king.check.domain.Tcheckattreport;
import org.king.framework.dao.MyQuery;

public interface WorkInfoDao {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Tattserialrecord get(Serializable id);

	public List getAll();

	public void save(Tattserialrecord workInfo);

	public void update(Tattserialrecord workInfo);

	public void delete(Tattserialrecord workInfo);

	public void save(Tcheckattreport workInfo);
	
	public void update(Tcheckattreport workInfo);

	public void delete(Tcheckattreport workInfo);
	
	public Tattserial getAttSeri(Serializable id);
	
	public void update(Tattserial transientInstance);
	
}