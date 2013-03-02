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
	 * 查询个人交易流水
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
	 * 查询客户号
	 * @param stuempno
	 * @return
	 * @throws PortalException
	 */
	public static String getCustIdBystuempNo(String stuempno) throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		return  advqueryService.getCustIdBystuempNo(stuempno); 
	}
	
	/**
	 * 发卡情况统计
	 * @param enddate
	 * @return
	 * @throws PortalException
	 */
	public static List getCardUse(String enddate)throws PortalException{
		AdvqueryService advqueryService =AdvqueryServiceFactory.getService();
		return  advqueryService.getCardUse(enddate);
	}
	
	/**
	 * 卡片发行,丢失,销户,冻结情况
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
	* Description:  存款总体情况统计（存款金额统计）<br>
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
	* Description: 存款总体情况笔数统计<br>
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
	* Description: 存款情况分类统计<br>
	* Return: List<br>
	* Args: @param seriType 存款类型
	* Args: @param beginDate 统计开始日期
	* Args: @param endDate 统计结束日期
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
	 * Description: 返回收费机的名称
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
	 * Description:  得到某一台Pos机在一段时间内的消费情况 
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
	 * Description: 商户整体账户变动情况，营业额，管理费金额  
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
	 * Description:返回根据商户编号返回商户名称
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
	 * Description:  各商户营业情况统计 
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
	 * Description: 各商户营业情况对比
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
	 * Description:整体帐务情况变化：存款，消费，押金(按日期范围统计) 
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
	 * Description:总体消费情况统计   
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
	 * Description: 3.4.2	单位帐务变动情况  
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
	 * Description:根据部门编号得到部门名称   
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
	 * Description:3.4.3	整个单位消费情况   
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
	 * Description: 拍照情况统计（所有人）   
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
	 * Description: 拍照情况统计按人员类别统计   
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
	 * Description: 圈存成功率统计  
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
	 * Description:   终端设备使用率  
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
	 * Description: 得到照片信息人员类别列表  
	 * Return: List
	 * @return
	 * @throws PortalException
	 */
	public static List getEmpType()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getEmpType();	
	}
	
	/**
	 * 得到收费类别信息
	 * @return
	 */
	public static List getFeeTypeList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getFeeTypeList();	
	}
	/**
	 * 得到客户类别信息
	 * @return
	 */
	public static List getCusttypeList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getCusttypeList();	
	};
	/**
	 * 得到专业信息
	 * @return
	 */
	public static List getSpecialityList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getSpecialityList();	
	}
	/**
	 * 得到部门信息
	 */
	public static List getDeptList()throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getDeptList();	
	}
	
	/**
	 * Method name:getSpecialList
	 * Description: 查询贫困生名单 
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
	 * Description:按年取得总体平均消费金额，男生平均和女士平均
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
	
	// 平均消费金额，人数分布图
	public static List getConsemeAvg(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange)throws PortalException{
		AdvqueryService advqueryService = AdvqueryServiceFactory.getService();
		return advqueryService.getConsemeAvg(bDate, eDate, deptNo, specNo, classNo, custType, feeType, bStuempNo, eStuempNo, per, meal, bavgRange, eavgRange, selPer, perRange);
	}
	
}
