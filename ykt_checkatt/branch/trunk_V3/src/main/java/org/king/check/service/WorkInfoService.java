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

	public void updateWorkInfo(Tattserialrecord workInfo)
			throws BusinessException;

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
	//生成没有符号明细的报表
	public List makeCheckReport(String statDate,String deptId,boolean noToken)throws Exception;
	public List makeStuCheckReport(String beginDate,String endDate,String deptId)throws Exception;

}