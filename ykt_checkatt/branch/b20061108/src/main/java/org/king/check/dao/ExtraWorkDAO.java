package org.king.check.dao;


import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Extraworkinfo;
import org.king.framework.dao.MyQuery;

public interface ExtraWorkDAO {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Extraworkinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Extraworkinfo transientInstance);
	
    public void update(Extraworkinfo transientInstance);
    
    public void delete(Extraworkinfo persistentInstance);

  /*public void saveExtraWorkInfo(Extraworkinfo extraWorkInfo);

  public Extraworkinfo getExtraWorkInfoByExtraInfoId(String extraInfoId);

  public void updateExtraWorkInfo(Extraworkinfo extraWorkInfo);*/
}