package org.king.check.service;

import java.util.List;
import java.util.Map;


public interface SysService {
	
	public List getCardStatus()throws Exception;
	
	public List getPersonType()throws Exception;
	
	public List getCardType()throws Exception;
	
	public List getDepartList()throws Exception;
	
	public List search(Map filter)throws Exception;
	
	public String getCustomerNameByCustomerId(Integer customerId)throws Exception;
	
	public List isExistDate(Map filter)throws Exception;
	
	//ȡ���û��Լ����õĲ����б�
	public List getDeptList()throws Exception;
	//���ݿͻ���ȡ�øÿͻ�����Ч����
	public Integer getCardNo(Integer custId)throws Exception;
	
}
