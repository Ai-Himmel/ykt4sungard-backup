package org.king.check.service;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Leaveinfo;

public interface LeaveInfoService {

  public void saveLeaveInfo(Leaveinfo leaveInfo);

  public Leaveinfo getLeaveInfoById(String leaveInfoId);

  public List getLeaveInfosByUserId(String userId);

  public List getLeaveInfosByTime(Date startDate, Date endDate);
  
  public boolean checkIsLeaveByClerkId(Integer clerkId)throws Exception;
  
  public List searchLeaveInfo(Map filter)throws Exception;
  
  public List staticLeaveInfoByFilter(Map filter)throws Exception;
  
  public Integer getLeaveDays(Map filter)throws Exception;
  
  public List getLeaveInfoDetail(Map filter)throws Exception;
  
  public List searchClerkForRegister(Map filter)throws Exception;
  
  public List addLeaveInfo(Map filter)throws Exception;
  
  public void deleteLeaveInfo(String [] leaveInfoIds)throws Exception;
  
  public void updateLeaveInfo(Map filter)throws Exception;
  
  public List isInLeave(Map filter)throws Exception;
  
}