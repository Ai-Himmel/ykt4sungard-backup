package org.king.check.service;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tleaveinfo;
import org.king.check.domain.Treportleave;
import org.king.check.domain.WebDictionary;

public interface LeaveInfoService {

  public void saveLeaveInfo(Tleaveinfo leaveInfo);

  public Tleaveinfo getLeaveInfoById(String leaveInfoId);

  public List getLeaveInfosByUserId(String userId);

  public List getLeaveInfosByTime(Date startDate, Date endDate);
  
  public String checkIsLeaveByClerkId(Integer clerkId,String inStart,String inEnd)throws Exception;
  
  public List searchLeaveInfo(Map filter)throws Exception;
  
  public List staticLeaveInfoByFilter(Map filter)throws Exception;
  
  public Integer getLeaveDays(Map filter)throws Exception;
  
  public List getLeaveInfoDetail(Map filter)throws Exception;
  
  public List searchClerkForRegister(Map filter)throws Exception;
  
  public void addLeaveInfo(Map filter)throws Exception;
  
  public List getLeaveInfo(String[] custIds)throws Exception;
  
  public void deleteLeaveInfo(String [] leaveInfoIds)throws Exception;
  
  public void updateLeaveInfo(Map filter)throws Exception;
  
  public List isInLeave(Map filter)throws Exception;
  
  public List getLeaveQuery(Map filter)throws Exception;
  
  /**
   * Çë¼ÙÉêÇë±£´æ£¬É¾³ý£¬¸üÐÂ£¬²éÕÒ
   * @param leaveInfoIds
   * @throws Exception
   */
  public void deleteLeaveReport(String leaveInfoIds)throws Exception;
  
  public void saveLeaveReport(Map filter)throws Exception;
  
  public Treportleave getReportLeaveInfo(String reportLeaveId)throws Exception;
  
  public Map getReportLeaveDetailInfo(String reportLeaveId)throws Exception;
  
  public Map getManualDetailInfo(String custId,String clerkDate,String maxTime,String minTime) throws Exception;
  
  public void reportLeaveCheck(String reportLeaveIds,Map filter)throws Exception;
  
  public void reportLeaveCheckCancel(String reportLeaveIds,Map filter)throws Exception;
  
  public List getLeaveCheckQuery(Map filter) throws Exception ;
  
  public List getMailList(String deptId) throws Exception;
  
  public void sendMailToManager(String deptId,String custId)throws Exception;
  
  public boolean   updateEmail(WebDictionary dic)throws Exception;
  
  public void deleteDic(WebDictionary dic)throws Exception;
  
  public List QueryEmail(String dicNo) throws Exception ;
 
  public void saveEmail(WebDictionary dic) throws Exception;
}