package org.king.check.service;

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

	public void manualRegister(List filter) throws Exception;

	public String[] judgeIsOwnValidCardByClerkId(String[] clerkIds)throws Exception;

	public void createAllWorkInfoByDptConf(Map paraMap) throws Exception;
	
	public List getOneCheckDetail(int custId,String beginDate,String endDate) throws Exception;

}