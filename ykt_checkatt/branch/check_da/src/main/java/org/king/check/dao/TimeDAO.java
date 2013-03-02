package org.king.check.dao;
import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TTime;

public interface TimeDAO {
	
	public  List findClassTimes(String query);
	
	public  void saveClassTimes(TTime time);
	
	public  void deleClassTime(TTime time);
	
	public  void updateClassTime(TTime time);
	
	public  TTime getTime(Serializable   id);

}
