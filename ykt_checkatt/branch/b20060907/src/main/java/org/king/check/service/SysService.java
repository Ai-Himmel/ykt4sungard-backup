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
	
	//取得用户自己设置的部门列表
	public List getDeptList()throws Exception;
	//根据客户号取得该客户的有效卡号
	public Integer getCardNo(Integer custId)throws Exception;
	
}
