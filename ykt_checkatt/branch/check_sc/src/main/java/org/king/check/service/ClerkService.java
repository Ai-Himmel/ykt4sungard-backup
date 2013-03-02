package org.king.check.service;
import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.TMakereportrecord;
import org.king.check.domain.Tclerkinfo;

public interface ClerkService {

  public Tclerkinfo  get(Serializable id);
  public void deleteClerk(String clerkId);
  
  /*
   * 通过用户id得到用户工作制度，等详细信息
   */
  public Map getClerkDetailByClerkId(String clerkId)throws Exception;
  /**
   * 根据查询条件得到考勤人员信息
   * @param filterMap
   * @return
   */
  public List queryClerk(Map filterMap);
  
  /**
   * 根据查询条件得到可设置为考勤人员的用户
   * @param filterMap
   * @return
   */
  public List queryAvailableClerk(Map filterMap);
  
  /**
   * 设置考勤人员信息
   * @param clerkList
   * @return
   */
  public int setupClerk(List clerkList);
  
  public List getCheckReportStat(String stuempNo,String beginDate,String endDate,String deptId)throws Exception;
  
  public void makeReportRecord(TMakereportrecord reportRecord); 
  
  public List getCheckDetail(String stuempNo,String beginDate,String endDate,String deptId) throws Exception;
  
  public List getCheckSerial(String stuempNo,String beginDate,String endDate,String deptId) throws Exception;
}