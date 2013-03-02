package org.king.check.service;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tworkconfinfo;

public interface WorkConfService {

  public void saveWorkConf(Tworkconfinfo workConf);

  public void updateWorkConf(Tworkconfinfo workConf);

  public void deleteWorkConf(String confId);

  public Tworkconfinfo getWorkConf(String workConfId);

  public List getAll();
  
  public List search(Map filter)throws Exception;
  
  public String getWorkConfInfo(String workConfId);
}