package org.king.check.service;

import java.util.List;
import java.util.Map;

import org.king.check.domain.TTime;

public interface TimeService {

    public List findAllTimes();
	
	public  List findClassTimes()throws Exception ;
	
	public  void saveClassTimes(TTime time)throws Exception ;
	
	public  void deleClassTime(TTime time)throws Exception ;
	
	public  void updateClassTime(TTime time)throws Exception ;
	
	public  TTime  getTime(Integer classNum)throws Exception;
	
	public  Map  getTimeByClass(String ClassNum)throws Exception;

}
