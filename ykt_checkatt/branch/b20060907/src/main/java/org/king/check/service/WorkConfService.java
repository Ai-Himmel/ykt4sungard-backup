package org.king.check.service;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Workconf;

public interface WorkConfService {

  public void saveWorkConf(Workconf workConf);

  public void updateWorkConf(Workconf workConf);

  public void deleteWorkConf(String confId);

  public Workconf getWorkConf(String workConfId);

  public List getAll();
  
  public List search(Map filter)throws Exception;
}