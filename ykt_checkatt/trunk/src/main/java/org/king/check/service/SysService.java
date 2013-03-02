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
	
	//根据部门编号取得部门相关信息
	public List getDeptInfo(String deptId)throws Exception;
	
	//取得用户有操作权限的部门列表
	public List getDeptList(String accountId)throws Exception;
	//取得用户自己设置的部门列表
	public List getDeptList()throws Exception;
	//根据客户号取得该客户的有效卡号
	public Integer getCardNo(Integer custId)throws Exception;
	//取得请假类别列表
	public List getLeaveList()throws Exception;
	//根据操作员编号取得操作员名称
	public String getOperName(String operId)throws Exception;
	//根据请假类别编号取得类别名称
	public String getLeaveTypeName(String leaveTypeId)throws Exception;
	//根据学工号取得客户号
	public int getCustIdByStuempNo(String stuempNo)throws Exception;
	//根据客户号取得客户学工号，姓名等
	public Map getCustInfoByCustId(int custId)throws Exception;
	//根据学工号取得账户号
	public String getAccountIdByStuempNo(String stuempNo)throws Exception;
	//是否审核
	public String ifCheck(String checkId);
	//是否同意
	public String ifAgree(String agreeId);
	//根据部门编码取得部门名称
	public String getDeptName(String deptId) throws Exception;
	//根据客户号取得该考勤人员是否坐班
	public String getIfOffice(int custId)throws Exception;
	//取得考勤人员信息
	public List getCustInfo(Map filter)throws Exception;
	
}
