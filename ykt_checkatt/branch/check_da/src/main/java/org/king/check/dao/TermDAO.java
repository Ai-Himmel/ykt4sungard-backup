package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TTerm;
import org.king.framework.dao.DAO;

public interface TermDAO extends DAO{
	
	public void  save(TTerm  term);
	
	public List  find(String query);
	
	public TTerm get(Serializable id);
	
	public void update(TTerm term);
	
}
