package com.kingstargroup.ecard.portlet.advquery.service;

import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

public class AdvqueryServiceUtil {
	
	
	
	public static List getCardUseByDept(String deptcode)throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		
		return advqueryService.getCardUseByDept(deptcode);
		
	}
	
	/**
	 * 
	 * ��ѯ���˽�����ˮ
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 * @throws PortalException
	 */
	public static List getOneAccountDetail(String custId,String beginDate,String endDate)throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		return  advqueryService.getOneAccountDetail(custId,beginDate,endDate); 
		
	}
	
	/**
	 * ��ѯ�ͻ���
	 * @param stuempno
	 * @return
	 * @throws PortalException
	 */
	public static String getCustIdBystuempNo(String stuempno) throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		return  advqueryService.getCustIdBystuempNo(stuempno); 
	}
	
	/**
	 * �������ͳ��
	 * @param enddate
	 * @return
	 * @throws PortalException
	 */
	public static List getCardUse(String enddate)throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		return  advqueryService.getCardUse(enddate);
	}
	
	/**
	 * ��Ƭ����,��ʧ,����,�������
	 * @param begindate
	 * @param enddate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	
	public static List  getCardOpenLoseBack(String begindate,String enddate,String  statType)throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		return advqueryService.getCardOpenLoseBack(begindate,enddate,statType);
		
	}
	
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
	public static List getTotleSavingMoneyStat(String beginDate,String endDate,String statType)throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getTotleSavingMoneyStat(beginDate, endDate, statType);
	} 
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
	public static List getTotleSavingNumStat(String beginDate,String endDate,String statType) throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getTotleSavingNumStat(beginDate, endDate, statType);
		
	}
	
	
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
	public static List getSavingSortStat(String seriType,String beginDate,String endDate,String statType) throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getSavingSortStat(seriType, beginDate, endDate, statType);
	}
	/**
	 * Method name:getPosDeviceList
	 * Description: �����շѻ�������
	 * Return: List
	 * @param posId
	 * @return
	 * @throws PortalException
	 */
	public static List getPosDeviceList(String posId){
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getPosDeviceList(posId);
	}
	
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
	public static List getConsumeStatByPos(String posId,String beginDate,String endDate,String statType) throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getConsumeStatByPos(posId, beginDate, endDate, statType);
	}
	
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
	public static List getShopAccountChangeStat(String beginDate,String endDate,String statType) throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getShopAccountChangeStat(beginDate, endDate, statType);		
	}
	
	/**
	 * Method name:getShopName
	 * Description:���ظ����̻���ŷ����̻�����
	 * Return: List
	 * @param shopId
	 * @return
	 */
	public static List getShopName(int shopId){
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getShopName(shopId);	
	}
	
	/**
	 * Method name:getOneAccountStat
	 * Description:  ���̻�Ӫҵ���ͳ�� 
	 * Return: List
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getOneAccountStat(int shopId,String beginDate,String endDate,String statType)throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getOneAccountStat(shopId, beginDate, endDate, statType);	
	}
	
	/**
	 * Method name:getShopAccountCompare
	 * Description: ���̻�Ӫҵ����Ա�
	 * Return: List
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getShopAccountCompare(String shopId,String beginDate,String endDate,String statType)throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getShopAccountCompare(shopId, beginDate, endDate, statType);	
	}
	
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
	public static List getAllAccountChangeStat(String beginDate,String endDate,String statType)throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getAllAccountChangeStat(beginDate, endDate, statType);	
	}
	
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
	public static List getAllConsumeStat(String beginDate,String endDate,String statType) throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getAllConsumeStat(beginDate, endDate, statType);	
	}
	
	/**
	 * Method name:getDepAccountStat
	 * Description: 3.4.2	��λ����䶯���  
	 * Return: List
	 * @param deptCode
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getDepAccountStat(String deptCode,String beginDate,String endDate,String statType) throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getDepAccountStat(deptCode, beginDate, endDate, statType);	
	}
	
	/**
	 * Method name:getDeptName
	 * Description:���ݲ��ű�ŵõ���������   
	 * Return: List
	 * @param deptCode
	 * @return
	 */
	public static List getDeptName(String deptCode){
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getDeptName(deptCode);	
	}
	
	
	/**
	 * Method name:getDeptConsumeStat
	 * Description:3.4.3	������λ�������   
	 * Return: List
	 * @param deptCode
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getDeptConsumeStat(String deptCode,String beginDate,String endDate,String statType) throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getDeptConsumeStat(deptCode, beginDate, endDate, statType);	
	}
	
	/**
	 * Method name:getphotoNumAll
	 * Description: �������ͳ�ƣ������ˣ�   
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getphotoNumAll(String beginDate,String endDate,String statType)throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getphotoNumAll(beginDate, endDate, statType);	
	}
	/**
	 * Method name:getphotoNumByType
	 * Description: �������ͳ�ư���Ա���ͳ��   
	 * Return: List
	 * @param cutType
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getphotoNumByType(String cutType,String beginDate,String endDate,String statType)throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getphotoNumByType(cutType, beginDate, endDate, statType);	
	}
	
	
	
	/**
	 * Method name:getTransferSuccessRate
	 * Description: Ȧ��ɹ���ͳ��  
	 * Return: List
	 * @param beginDate
	 * @param endDate
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List isHasTransfer(String beginDate, String endDate ) throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.isHasTransfer(beginDate, endDate);
	}
	
	public static List getTransferSuccessRate(String beginDate, String endDate,
			String statType) throws PortalException {
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getTransferSuccessRate(beginDate, endDate, statType);	
	}
	
	/**
	 * Method name:getDeviceRate
	 * Description:   �ն��豸ʹ����  
	 * Return: List
	 * @param serialtype
	 * @param beginDate
	 * @param endDate
	 * @param devType
	 * @param statType
	 * @return
	 * @throws PortalException
	 */
	public static List getDeviceRate(int serialtype,String beginDate,String endDate,String devType,String statType) throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getDeviceRate(serialtype, beginDate, endDate, devType, statType);	
	}
	
	/**
	 * Method name:getEmpType
	 * Description: �õ���Ƭ��Ϣ��Ա����б�  
	 * Return: List
	 * @return
	 * @throws PortalException
	 */
	public static List getEmpType()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getEmpType();	
	}
	
	/**
	 * �õ��շ������Ϣ
	 * @return
	 */
	public static List getFeeTypeList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getFeeTypeList();	
	}
	/**
	 * �õ��ͻ������Ϣ
	 * @return
	 */
	public static List getCusttypeList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getCusttypeList();	
	};
	/**
	 * �õ�רҵ��Ϣ
	 * @return
	 */
	public static List getSpecialityList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getSpecialityList();	
	}
	/**
	 * �õ�������Ϣ
	 */
	public static List getDeptList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getDeptList();	
	}
	
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
	 * @throws PortalException
	 */
	public static List getSpecialList(String bDate,String eDate,
			String deptNo,String specNo,
			String classNo,int custType,
			int feeType,String bStuempNo,
			String eStuempNo,int per,String meal,
			float bavgRange,float eavgRange,
			String selPer,int perRange)throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getSpecialList(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);	
	}
	
	/**
	 * Method name:getSpecStat
	 * Description:����ȡ������ƽ�����ѽ�����ƽ����Ůʿƽ��
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
	 * @throws PortalException
	 */
	public static List getSpecStat(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange)throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getSpecStat(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);	
	}
	
	// ƽ�����ѽ������ֲ�ͼ
	public static List getConsemeAvg(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange)throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getConsemeAvg(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);
	}
	
}
