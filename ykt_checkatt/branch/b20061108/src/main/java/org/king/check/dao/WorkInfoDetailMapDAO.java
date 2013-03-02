package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Workinfodetailmap;


public interface WorkInfoDetailMapDAO {

	public List find(String query);
	 
	public Workinfodetailmap get(Serializable id);
	
	public List getAll();
  public void save(Workinfodetailmap workInfo);

  public void update(Workinfodetailmap workInfo);
  
  public void delete(Workinfodetailmap workInfo);
    
	

    

    


}