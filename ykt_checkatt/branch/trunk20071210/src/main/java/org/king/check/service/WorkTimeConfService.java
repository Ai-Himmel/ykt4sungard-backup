package org.king.check.service;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tworktimeinfo;

public interface WorkTimeConfService {

  public void saveWorkTimeConf(Tworktimeinfo workTimeConf);

  public void updateWorkTimeConf(Tworktimeinfo workTimeConf);

  public void deleteWorkTimeConf(String workTimeConfId);

  public Tworktimeinfo getWorkTimeConf(String workTimeConfId);

  public List getAll();

  public List getWorkTimeConfParasByWorkTimeConfName(String workTimeConfName);
  
  public List getWorkTimeConfParasByWorkTimeConfId(String workTimeConfId);
  
  public List search(Map filter)throws Exception;
  
  public List reForMatWorkTimeList(List workTimeList)throws Exception;
  
  public String getWorkTimeInfo(String workTimeId);
  
  public List getUsedWorkTime(String workTimes) throws Exception;
  
}