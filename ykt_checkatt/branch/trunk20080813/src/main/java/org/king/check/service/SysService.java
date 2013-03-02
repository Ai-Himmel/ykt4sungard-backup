package org.king.check.service;

import java.io.IOException;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


public interface SysService {
	public List getEmailList();
	public int getDeptCount();
	public int getDeptByLogin(String loginCode);
	public List getCardStatus()throws Exception;
	
	public List getCheckattType()throws Exception;
	
	public List getPersonType()throws Exception;
	
	public List getCardType()throws Exception;
	
	public List getDepartList()throws Exception;
	
	public List getSpecList()throws Exception;
	
	public List search(Map filter)throws Exception;
	
	public String getCustomerNameByCustomerId(Integer customerId)throws Exception;
	
	public List isExistDate(Map filter)throws Exception;
	
	//取得班次信息
	public List getCheckTypeInfo() throws Exception;
	
	//取得班次信息名称
	public String getCheckTypeName(String typeId);
	
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
	public String getDeptName(String deptId);
	//根据客户号取得该考勤人员是否坐班
	public String getIfOffice(int custId)throws Exception;
	//取得考勤人员信息
	public List getCustInfo(Map filter)throws Exception;
	//根据部门编号去掉考勤人员的详细信息
	public List getClerkInfo(String deptId) throws Exception;
	//根据月份取当前月份每天属于周几
	public List getWeekByDate(String statMonth);
	public List getWeekByDate(String startDate,String endDate);
	//取得手工考勤记录
	public int getManCheck(String custId,String checkDate) throws Exception;
	//取得打卡考勤记录
	public int getCardCheck(String custId,String checkDate) throws Exception;
	//把考勤记录导入到Excel
	public void importReportToExcel(String realPath,String deptId,String statMonth,List reportList,String operId) throws Exception;
	public void importReportToExcelStu(String realPath,String deptId,String beginDate,String endDate,List reportList,String operId) throws Exception;
	//根据人员编号去掉部门信息
	public Map getDeptInfo(int custId);
	public int getReportRecord(String deptId,String statMonth);
	//根据手工签到流水号取得该人员所在部门
	public Map getDeptInfoBySeriId(int seriId);
	
	public void downLoadFile(HttpServletRequest request, HttpServletResponse response)throws IOException, ServletException;
	
	public List getCheckReportList(String custId,String checkDate);
	public List getCheckClerkInfo(String deptId,String ifoffice) throws Exception;
}
