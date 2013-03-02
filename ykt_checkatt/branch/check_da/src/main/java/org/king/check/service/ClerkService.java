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
  
  public Map getCheckReportByStuempNo(int custId,String beginDate,String endDate)throws Exception;
  
  public void makeReportRecord(TMakereportrecord reportRecord); 
  public List queryClerkCheckDetail(Integer custId,String beginDate,String endDate);
}