package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tattserialrecord;
import org.king.framework.exception.BusinessException;

/**
 * @author a
 * 
 */
public interface WorkInfoService {

	public void saveWorkInfo(Tattserialrecord workInfo)
			throws BusinessException;
	
	public List getCheckReportByMonth(String deptId, List detpList ,String statMonth)throws Exception;

	public void updateWorkInfo(Tattserialrecord workInfo)throws BusinessException;

	public Integer getCardIdByCustId(String custId) throws Exception;

	public String getPhyCardIdByCustId(String custId) throws Exception;

	public List searchClerkForReg(Map filter) throws Exception;
	
	public List searchClerkForModify(Map filter)throws Exception;
	
	public Map searchClerkForModify(int seriId)throws Exception;
	
	public Tattserialrecord get(Serializable id);
	
	public void manualRegister(List filter) throws Exception;
	
	public void updateRegister(Tattserialrecord att)throws Exception;
	
	public void deleteRegister(Tattserialrecord att)throws Exception;

	public String[] judgeIsOwnValidCardByClerkId(String[] clerkIds)throws Exception;

	public void createAllWorkInfoByDptConf(Map paraMap) throws Exception;
	
	public void createAllWorkReportByDptConf(Map paraMap) throws Exception;
	
	public List getManualCheckList(int custId,String attDate) throws Exception;
	
	public List getCustWorkTime(String deptId,String beginDate,String endDate);
	public List makeCheckReport(String statMonth,String deptId)throws Exception;
	public List makeStuCheckReport(String beginDate,String endDate,String deptId)throws Exception;
	/**
	 * ɾ�� �������µ�ͳ������
	 * @param ny example:200810
	 */
	public void deleteRecords(String ny);
	
	/**
	 * ���뿼��ͳ�ƽ�����ݵ�t_kq_result_month
	 * @param ny example:200810
	 * @param kqMap
	 */
	public void insertRecords(String ny,Map kqMap);
	
	/**
	 * ȡ�ÿ��ں�̨ͳ�Ʒ�����Ҫ�Ĳ����б�
	 * @return
	 * @throws Exception
	 */
	public List getDeptListForKQService()throws Exception;	
	
	/**
	 * ɾ�� 4����ǰ����ʷ��ˮ������ת�뵽��ʷ����
	 */
	public void deleteHistoryRecords() ;

}