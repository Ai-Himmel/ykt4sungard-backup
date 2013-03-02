package org.king.check.service;
import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tclerkinfo;

public interface ClerkService {

  public void saveClerk(Tclerkinfo clerk);

  public Tclerkinfo getClerkByStuNumber(String stuNumber);

  public Tclerkinfo getClerkBycardNumber(String cardNumber);

  public Tclerkinfo getClerkByClerkName(String clerkName);

  public Tclerkinfo  get(Serializable id);
  
  public List getClerksByDepartId(String departId);

  public void updateClerk(Tclerkinfo clerk);
  
  public void deleteClerk(String clerkId);
  
  /*
   * ͨ���û�id�õ��û������ƶȣ�����ϸ��Ϣ
   */
  public Map getClerkDetailByClerkId(String clerkId)throws Exception;
  /**
   * ���ݲ�ѯ�����õ�������Ա��Ϣ
   * @param filterMap
   * @return
   */
  public List queryClerk(Map filterMap);
  
  /**
   * ���ݲ�ѯ�����õ�������Ϊ������Ա���û�
   * @param filterMap
   * @return
   */
  public List queryAvailableClerk(Map filterMap);
  
  /**
   * ���ÿ�����Ա��Ϣ
   * @param clerkList
   * @return
   */
  public int setupClerk(List clerkList);
  
}