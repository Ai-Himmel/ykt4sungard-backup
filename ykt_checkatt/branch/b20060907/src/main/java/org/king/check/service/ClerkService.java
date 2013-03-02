package org.king.check.service;
import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Clerk;

public interface ClerkService {

  public void saveClerk(Clerk clerk);

  public Clerk getClerkByStuNumber(String stuNumber);

  public Clerk getClerkBycardNumber(String cardNumber);

  public Clerk getClerkByClerkName(String clerkName);

  public Clerk  get(Serializable id);
  
  public List getClerksByDepartId(String departId);

  public void updateClerk(Clerk clerk);
  
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
  
}