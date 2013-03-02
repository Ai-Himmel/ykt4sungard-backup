package org.king.check.service;
import java.util.List;
import java.util.Map;


/**
 * @author a
 *
 */
public interface WorkStaticService {
	
  public List checklogByFilter(Map filter)throws Exception;

  public List clerkstaticByFilter(Map filter)throws Exception;
  
  public List clerkstaticDetail(String checkdate,String clerkid,String flag)throws Exception;
  
  public List getclerkInfo(String clerkid)throws Exception;
  
  public String getclerkId(String stuNo)throws Exception;
  
  public Map sumstaticByFilter(Map filter)throws Exception;
  
  public List deptstaticByFilter(Map filter)throws Exception;
  
  public List getdeptInfo(String deptid)throws Exception;
  
  public String getDepartment()throws Exception;
   
}
