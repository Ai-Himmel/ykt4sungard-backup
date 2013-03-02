package org.king.check.service;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Worktimeconf;

public interface WorkTimeConfService {

  public void saveWorkTimeConf(Worktimeconf workTimeConf);

  public void updateWorkTimeConf(Worktimeconf workTimeConf);

  public void deleteWorkTimeConf(String workTimeConfId);

  public Worktimeconf getWorkTimeConf(String workTimeConfId);

  public List getAll();

  public List getWorkTimeConfParasByWorkTimeConfName(String workTimeConfName);
  
  public List getWorkTimeConfParasByWorkTimeConfId(String workTimeConfId);
  
  public List search(Map filter)throws Exception;
  
  public List reForMatWorkTimeList(List workTimeList)throws Exception;
  
}