package com.kingstargroup.ecard.portlet.advquery.service;

import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:AdvqueryService.java
 * Description: 
 * Modify History����Change Log��: 
 * �������ͣ��������޸ĵȣ� ��������     ������    �������ݼ���
 * ����               2009-10-21  ������    
 * <p>
 * 
 * @author ������
 * @version 1.0
 * @since 1.0
 */
public interface AdvqueryService {
	
	
	public List getCardUseByDept(String deptcode)throws PortalException;
	
	
	/**
	 *   ��ѯ�ͻ�������ˮ
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 * @throws PortalException
	 */
	
	public List  getOneAccountDetail(String custId,String beginDate,String endDate)throws PortalException;
	
	
	/**
	 * ��ͻ���
	 * @param stuempno
	 * @return
	 * @throws PortalException
	 */
	public  String getCustIdBystuempNo(String stuempno)throws PortalException;
	
	/**
	 * ������� 
	 * @param enddate
	 * @return
	 * @throws PortalException
	 */
	public List getCardUse(String enddate)throws  PortalException;
	
	
	
	/**
	 * 
	 * @param begindate
	 * @param enddate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getCardOpenLoseBack(String begindate,String enddate,String  statType)throws PortalException;
	
	
	/**
		* Method name: getTotleSavingMoneyStat<br>
		* Description:  ����������ͳ�ƣ������ͳ�ƣ�<br>
		* Return: List<br>
		* Args: @param beginDate
		* Args: @param endDate
		* Args: @param statType
		* Args: @return
		* Args: @throws PortalException
		*/
	public List getTotleSavingMoneyStat(String beginDate,String endDate,String statType)throws PortalException;
	
	/**
		* Method name: getTotleSavingNumStat<br>
		* Description: ��������������ͳ��<br>
		* Return: List<br>
		* Args: @param beginDate
		* Args: @param endDate
		* Args: @param statType
		* Args: @return
		* Args: @throws PortalException
		*/
	public List getTotleSavingNumStat(String beginDate,String endDate,String statType) throws PortalException;
	
	/**
		* Method name: getSavingSortStat<br>
		* Description: ����������ͳ��<br>
		* Return: List<br>
		* Args: @param seriType �������
		* Args: @param beginDate ͳ�ƿ�ʼ����
		* Args: @param endDate ͳ�ƽ�������
		* Args: @param statType
		* Args: @return
		* Args: @throws PortalException
		*/
	public List getSavingSortStat(String seriType,String beginDate,String endDate,String statType) throws PortalException;
	
	/**
	 * Method name:getPosDeviceList
	 * Description: �����շѻ�������
	 * Return: List
	 * @param posId
	 * @return
	 * @throws PortalException
	 */
	public List getPosDeviceList(String posId);
	
	/**
	 * Method name:getConsumeStatByPos
	 * Description:  �õ�ĳһ̨Pos����һ��ʱ���ڵ�������� 
	 * Return: List
	 * @param posId
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws HibernateException
	 */
	public List getConsumeStatByPos(String posId,String beginDate,String endDate,String statType) throws PortalException;
	
	/**
	 * Method name:getShopAccountChangeStat
	 * Description: �̻������˻��䶯�����Ӫҵ�����ѽ��
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getShopAccountChangeStat(String beginDate,String endDate,String statType) throws PortalException;
	
	/**
	 * Method name:getShopName
	 * Description:   ���ظ����̻���ŷ����̻�����
	 * Return: List
	 * @param shopId
	 * @return
	 */
	public List getShopName(int shopId);
	
	/**
	 * Method name:getOneAccountStat
	 * Description:���̻�Ӫҵ���ͳ��   
	 * Return: List
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getOneAccountStat(int shopId,String beginDate,String endDate,String statType)throws PortalException;
	
	/**
	 * Method name:getShopAccountCompare
	 * Description:   ���̻�Ӫҵ����Ա�
	 * Return: List
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getShopAccountCompare(String shopId,String beginDate,String endDate,String statType)throws PortalException;
	
	/**
	 * Method name:getAllAccountChangeStat
	 * Description:������������仯�������ѣ�Ѻ��(�����ڷ�Χͳ��)
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getAllAccountChangeStat(String beginDate,String endDate,String statType)throws PortalException;
	
	/**
	 * Method name:getAllConsumeStat
	 * Description:�����������ͳ��   
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getAllConsumeStat(String beginDate,String endDate,String statType) throws PortalException;
	
	/**
	 * Method name:getDepAccountStat
	 * Description:��λ����䶯��� 
	 * Return: List
	 * @param deptCode
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getDepAccountStat(String deptCode,String beginDate,String endDate,String statType)throws PortalException;
	
	
	/**
	 * Method name:getDeptName
	 * Description:  ���ݲ��ű�ŵõ���������
	 * Return: List
	 * @param deptCode
	 * @return
	 */
	public List getDeptName(String deptCode);
	
	/**
	 * Method name:getDeptConsumeStat
	 * Description: 3.4.3	������λ�������  
	 * Return: List
	 * @param deptCode
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getDeptConsumeStat(String deptCode,String beginDate,String endDate,String statType)throws PortalException;
	
	/**
	 * Method name:getphotoNumAll
	 * Description:  �������ͳ�ƣ������ˣ� 
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getphotoNumAll(String beginDate,String endDate,String statType)throws PortalException;
	
	/**
	 * Method name:getphotoNumByType
	 * Description:�������ͳ�ư���Ա���ͳ�� 
	 * Return: List
	 * @param cutType
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getphotoNumByType(String cutType,String beginDate,String endDate,String statType)throws PortalException;
	
	/**
	 * Method name:getTransferSuccessRate
	 * Description:Ȧ��ɹ���ͳ��
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 *
	 */
	public List isHasTransfer(String beginDate, String endDate ) throws PortalException;
	
	public List getTransferSuccessRate(String beginDate,String endDate, String statType)throws PortalException;
	
	/**
	 * Method name:getDeviceRate
	 * Description: �ն��豸ʹ����  
	 * Return: List
	 * @param serialtype
	 * @param beginDate
	 * @param endDate
	 * @param devType
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public List getDeviceRate(int serialtype,String beginDate,String endDate,String devType,String statType) throws PortalException;
	
	/**
	 * Method name:getEmpType
	 * Description:�õ���Ƭ��Ϣ��Ա����б�
	 * Return: List
	 * @return
	 */
	public List getEmpType();
	/**
	 * �õ��շ������Ϣ
	 * @return
	 */
	public List getFeeTypeList();
	/**
	 * �õ��ͻ������Ϣ
	 * @return
	 */
	public List getCusttypeList();
	/**
	 * �õ�רҵ��Ϣ
	 * @return
	 */
	public List getSpecialityList();
	/**
	 * �õ�������Ϣ
	 */
	public List getDeptList();
	
	/**
	 * Method name:getSpecialList
	 * Description: ��ѯƶ�������� 
	 * Return: List
	 * @param bDate
	 * @param eDate
	 * @param deptNo
	 * @param specNo
	 * @param classNo
	 * @param custType
	 * @param feeType
	 * @param bStuempNo
	 * @param eStuempNo
	 * @param per
	 * @param meal
	 * @param bavgRange
	 * @param eavgRange
	 * @param selPer
	 * @param perRange
	 * @return
	 */
	public List getSpecialList(String bDate,String eDate,
			String deptNo,String specNo,
			String classNo,int custType,
			int feeType,String bStuempNo,
			String eStuempNo,int per,String meal,
			float bavgRange,float eavgRange,
			String selPer,int perRange);
	
	/**
	 * ����ȡ������ƽ�����ѽ�����ƽ����Ůʿƽ�� gejinfeng ��������ѯ 2009-01-04
	 * 
	 * @return
	 */
	public List getSpecStat(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange);
	
	// ƽ�����ѽ������ֲ�ͼ
	public List getConsemeAvg(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange);
}

