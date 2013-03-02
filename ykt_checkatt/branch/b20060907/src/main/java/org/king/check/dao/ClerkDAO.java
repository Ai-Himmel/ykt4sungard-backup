package org.king.check.dao;


import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Clerk;
import org.king.check.domain.Clerkinfo;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface ClerkDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Clerk get(Serializable id);
	
	public List getAll();
	
	public void save(Clerkinfo transientInstance);
	
    public void update(Clerkinfo transientInstance);
    
    public void delete(Clerk persistentInstance);
    
    public boolean isExist(Integer clerkId);

 /* public Clerk getClerkByClerkName(String clerkName);

  public List getClerksByDepartId(String departId);

  public Clerk getClerkByStuNumber(String stuNumber);

  public Clerk getClerkByCardNumber(String cardNumber);*/
}