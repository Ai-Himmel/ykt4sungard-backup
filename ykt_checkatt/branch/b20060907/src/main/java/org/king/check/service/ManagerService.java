package org.king.check.service;
import java.util.List;

import org.king.check.domain.Manager;

public interface ManagerService {

  public void saveManager(Manager manager);

  public void deleteManager(String managerId);

  public void updateManager(Manager manager);

  public Manager getManagerByManagerId(String ManagerId);

  public List getManagersByDepartId(String departId);
}