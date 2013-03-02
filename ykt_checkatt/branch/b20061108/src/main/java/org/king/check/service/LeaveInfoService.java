package org.king.check.service;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tleaveinfo;

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
  
}