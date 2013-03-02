package org.king.check.service;
import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.TMakereportrecord;
import org.king.check.domain.Tclerkinfo;

public interface ClerkService {

  public Tclerkinfo  get(Serializable id);
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
  
  public List getCheckReportStat(String stuempNo,String beginDate,String endDate,String deptId)throws Exception;
  
  public void makeReportRecord(TMakereportrecord reportRecord); 
  
  public List getCheckDetail(String stuempNo,String beginDate,String endDate,String deptId) throws Exception;
  
  public List getCheckSerial(String stuempNo,String beginDate,String endDate,String deptId) throws Exception;
}