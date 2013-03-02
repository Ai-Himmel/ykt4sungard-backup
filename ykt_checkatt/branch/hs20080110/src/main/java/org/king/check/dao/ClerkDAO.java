package org.king.check.dao;


import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TMakereportrecord;
import org.king.check.domain.Tclerkinfo;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface ClerkDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Tclerkinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Tclerkinfo transientInstance);
	
    public void update(Tclerkinfo transientInstance);
    
    public void delete(Tclerkinfo persistentInstance);
    
    public boolean isExist(Integer clerkId);
    
	public void save(TMakereportrecord transientInstance);
	
    public void update(TMakereportrecord transientInstance);
    public void delete(TMakereportrecord persistentInstance);

 /* public Clerk getClerkByClerkName(String clerkName);

  public List getClerksByDepartId(String departId);

  public Clerk getClerkByStuNumber(String stuNumber);

  public Clerk getClerkByCardNumber(String cardNumber);*/
}