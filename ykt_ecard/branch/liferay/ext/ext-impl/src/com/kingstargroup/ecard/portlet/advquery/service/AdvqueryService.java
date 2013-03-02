package com.kingstargroup.ecard.portlet.advquery.service;

import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:AdvqueryService.java
 * Description: 
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建               2009-10-21  何林青    
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public interface AdvqueryService {
	
	
	public List getCardUseByDept(String deptcode)throws PortalException;
	
	
	/**
	 *   查询客户交易流水
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 * @throws PortalException
	 */
	
	public List  getOneAccountDetail(String custId,String beginDate,String endDate)throws PortalException;
	
	
	/**
	 * 查客户号
	 * @param stuempno
	 * @return
	 * @throws PortalException
	 */
	public  String getCustIdBystuempNo(String stuempno)throws PortalException;
	
	/**
	 * 发卡情况 
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
		* Description:  存款总体情况统计（存款金额统计）<br>
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
		* Description: 存款总体情况笔数统计<br>
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
		* Description: 存款情况分类统计<br>
		* Return: List<br>
		* Args: @param seriType 存款类型
		* Args: @param beginDate 统计开始日期
		* Args: @param endDate 统计结束日期
		* Args: @param statType
		* Args: @return
		* Args: @throws PortalException
		*/
	public List getSavingSortStat(String seriType,String beginDate,String endDate,String statType) throws PortalException;
	
	/**
	 * Method name:getPosDeviceList
	 * Description: 返回收费机的名称
	 * Return: List
	 * @param posId
	 * @return
	 * @throws PortalException
	 */
	public List getPosDeviceList(String posId);
	
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
	public List getConsumeStatByPos(String posId,String beginDate,String endDate,String statType) throws PortalException;
	
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
	public List getShopAccountChangeStat(String beginDate,String endDate,String statType) throws PortalException;
	
	/**
	 * Method name:getShopName
	 * Description:   返回根据商户编号返回商户名称
	 * Return: List
	 * @param shopId
	 * @return
	 */
	public List getShopName(int shopId);
	
	/**
	 * Method name:getOneAccountStat
	 * Description:各商户营业情况统计   
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
	 * Description:   各商户营业情况对比
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
	 * Description:整体帐务情况变化：存款，消费，押金(按日期范围统计)
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
	 * Description:总体消费情况统计   
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
	 * Description:单位帐务变动情况 
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
	 * Description:  根据部门编号得到部门名称
	 * Return: List
	 * @param deptCode
	 * @return
	 */
	public List getDeptName(String deptCode);
	
	/**
	 * Method name:getDeptConsumeStat
	 * Description: 3.4.3	整个单位消费情况  
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
	 * Description:  拍照情况统计（所有人） 
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
	 * Description:拍照情况统计按人员类别统计 
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
	 * Description:圈存成功率统计
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
	 * Description: 终端设备使用率  
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
	 * Description:得到照片信息人员类别列表
	 * Return: List
	 * @return
	 */
	public List getEmpType();
	/**
	 * 得到收费类别信息
	 * @return
	 */
	public List getFeeTypeList();
	/**
	 * 得到客户类别信息
	 * @return
	 */
	public List getCusttypeList();
	/**
	 * 得到专业信息
	 * @return
	 */
	public List getSpecialityList();
	/**
	 * 得到部门信息
	 */
	public List getDeptList();
	
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
	 */
	public List getSpecialList(String bDate,String eDate,
			String deptNo,String specNo,
			String classNo,int custType,
			int feeType,String bStuempNo,
			String eStuempNo,int per,String meal,
			float bavgRange,float eavgRange,
			String selPer,int perRange);
	
	/**
	 * 按年取得总体平均消费金额，男生平均和女士平均 gejinfeng 按条件查询 2009-01-04
	 * 
	 * @return
	 */
	public List getSpecStat(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange);
	
	// 平均消费金额，人数分布图
	public List getConsemeAvg(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange);
}

