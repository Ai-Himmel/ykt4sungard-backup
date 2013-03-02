package org.king.check.service;
import java.util.Date;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Workinfo;
import org.king.framework.exception.BusinessException;


/**
 * @author a
 *
 */
public interface WorkInfoService {

  public void saveWorkInfo(Workinfo workInfo)throws BusinessException;

  public void updateWorkInfo(Workinfo workInfo)throws BusinessException;

  public void getWorkInfoByWorkInfoId(String workInfoId)throws BusinessException;

  public void getWorkInfoBySerialId(String serialId)throws BusinessException;
 
  public List getWorkInfosByCardNumber(String cardNumber)throws BusinessException;
  
  /*通过流水信息生成考勤信息*/
  public void createAllClerkWorkInfo(Map filter) throws Exception;
  
  public List getClerkWorkInfosDetailByDate(Date startDate, Date endDate, String userId)throws BusinessException;

  public List getDepartWorkInfosByDate(Date startDate, Date endDate, String departId)throws BusinessException;
  
//处理非坐班信息
  public void dealWithNoSeatClerk(Map filter)throws Exception;
  
  public List searchClerkForReg(Map filter)throws Exception;
  
  public void manualRegister(Map filter)throws Exception;
  
  public String[] judgeIsOwnValidCardByClerkId(String [] clerkIds)throws Exception;

  public String createWorkInfoByClerkId(Map filter)throws Exception;
  
  public Map getRecentTime(List dutyList,String ondutyTimeConf,boolean requireOnduty)throws Exception;
  
  public Integer getInterval(String confTime,String dutyTime)throws Exception;
  
  public void createWorkInfoByDptConf(Map paraMap)throws Exception;
  
  public void createAllWorkInfoByDptConf(Map paraMap)throws Exception;
  
  
}