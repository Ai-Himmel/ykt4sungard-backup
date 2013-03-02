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
	public String getDeptName(String deptId) throws Exception;
	//���ݿͻ���ȡ�øÿ�����Ա�Ƿ�����
	public String getIfOffice(int custId)throws Exception;
	//ȡ�ÿ�����Ա��Ϣ
	public List getCustInfo(Map filter)throws Exception;
	
}
