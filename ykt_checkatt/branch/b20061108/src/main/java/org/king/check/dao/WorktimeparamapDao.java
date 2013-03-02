package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Worktimeparamap;
import org.king.framework.dao.MyQuery;


public interface WorktimeparamapDao {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Worktimeparamap get(Serializable id);
	
	public List getAll();
	
	public void save(Worktimeparamap transientInstance);
	
    public void update(Worktimeparamap transientInstance);
    
    public void delete(Worktimeparamap persistentInstance);
}
