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
	
	//ȡ�ð����Ϣ
	public List getCheckTypeInfo() throws Exception;
	
	//ȡ�ð����Ϣ����
	public String getCheckTypeName(String typeId);
	
	//���ݲ��ű��ȡ�ò��������Ϣ
	public List getDeptInfo(String deptId)throws Exception;
	
	//ȡ���û��в���Ȩ�޵Ĳ����б�
	public List getDeptList(String accountId)throws Exception;
	//ȡ���û��Լ����õĲ����б�
	public List getDeptList()throws Exception;
	//���ݿͻ���ȡ�øÿͻ�����Ч����
	public Integer getCardNo(Integer custId)throws Exception;
	//ȡ���������б�
	public List getLeaveList()throws Exception;
	//���ݲ���Ա���ȡ�ò���Ա����
	public String getOperName(String operId)throws Exception;
	//������������ȡ���������
	public String getLeaveTypeName(String leaveTypeId)throws Exception;
	//����ѧ����ȡ�ÿͻ���
	public int getCustIdByStuempNo(String stuempNo)throws Exception;
	//���ݿͻ���ȡ�ÿͻ�ѧ���ţ�������
	public Map getCustInfoByCustId(int custId)throws Exception;
	//����ѧ����ȡ���˻���
	public String getAccountIdByStuempNo(String stuempNo)throws Exception;
	//�Ƿ����
	public String ifCheck(String checkId);
	//�Ƿ�ͬ��
	public String ifAgree(String agreeId);
	//���ݲ��ű���ȡ�ò�������
	public String getDeptName(String deptId);
	//���ݿͻ���ȡ�øÿ�����Ա�Ƿ�����
	public String getIfOffice(int custId)throws Exception;
	//ȡ�ÿ�����Ա��Ϣ
	public List getCustInfo(Map filter)throws Exception;
	//���ݲ��ű��ȥ��������Ա����ϸ��Ϣ
	public List getClerkInfo(String deptId) throws Exception;
	//�����·�ȡ��ǰ�·�ÿ�������ܼ�
	public List getWeekByDate(String statMonth);
	public List getWeekByDate(String startDate,String endDate);
	//ȡ���ֹ����ڼ�¼
	public int getManCheck(String custId,String checkDate) throws Exception;
	//ȡ�ô򿨿��ڼ�¼
	public int getCardCheck(String custId,String checkDate) throws Exception;
	//�ѿ��ڼ�¼���뵽Excel
	public void importReportToExcel(String realPath,String deptId,String statMonth,List reportList,String operId) throws Exception;
	public void importReportToExcelStu(String realPath,String deptId,String beginDate,String endDate,List reportList,String operId) throws Exception;
	//������Ա���ȥ��������Ϣ
	public Map getDeptInfo(int custId);
	public int getReportRecord(String deptId,String statMonth);
	//�����ֹ�ǩ����ˮ��ȡ�ø���Ա���ڲ���
	public Map getDeptInfoBySeriId(int seriId);
	
	public void downLoadFile(HttpServletRequest request, HttpServletResponse response)throws IOException, ServletException;
	
	public List getCheckReportList(String custId,String checkDate);
	public List getCheckClerkInfo(String deptId,String ifoffice) throws Exception;
}
