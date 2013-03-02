/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.HashMap;
import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.account.TAccount;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.customer.CustomerPersistence;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: CustomerUtil.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CustomerUtil {

	/**
	 * Description: 通过传入的客户号得到对应客户对象
	 * @param customerId 传入客户号
	 * @return 客户对象
	 * Modify History:
	 */
	public static TCustomer getCustomerById(String custid) throws PortalException {
		return getPersistence().getCustomerById(Integer.parseInt(custid));

	}
	
	/**
	 * Description:根据学工号得到对应客户对象
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TCustomer getCustomerByStuempno(String stuempno) throws PortalException {
			return getPersistence().getCustomerByStuempno(stuempno);
	}
	
	/**
	 * Description:根据用学/工号得到和客户相关的一些信息（卡信息等）
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 * 2005-10-18 更换客户号为学工号
	 */
	public static HashMap getRelatedCustomerInfo(String stuempno) throws PortalException {
		String custid = getCustomerByStuempno(stuempno).getCustid().toString();
		List cards = CardUtil.getAvailableCards(custid);
		return getRelatedCustomerInfo(custid, ((TCard) cards.get(0)).getCardno()); 
	}
	
	public static HashMap getRelatedCustomerInfo(String custid, Long cardno) throws PortalException {
		HashMap infoMap = new HashMap();
		TCustomer customer = getCustomerById(custid);
		TCard card = CardUtil.getCardByNo(cardno);
		String deptName ="";
		if(customer.getDeptcode()!=null&&!"".equals(customer.getDeptcode())){
			TDept dept = CardUtil.getDept(customer.getDeptcode());
			if(dept!=null){
				deptName = dept.getDeptname();
			}
		}
		
		TAccount account = AccountUtil.getAccountByCardno(card.getCardno().toString());		
		
		infoMap.put("customerId", customer.getStuempno());//学工号
		infoMap.put("customerName", customer.getCustname());//客户名称
		infoMap.put("customerDep", deptName);//客户所在部门名称
		infoMap.put("cardType", 
					DictionaryUtil.getDictionary(EcardConstants.CARD_TYPE_DIC_NO, card.getCardtype().toString()).getDictcaption());//卡类别
		infoMap.put("cardStatus", 
				DictionaryUtil.getDictionary(EcardConstants.CARD_STATUS_DIC_NO, card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag()).getDictcaption());//卡状态
		infoMap.put("beginTime", DateFormatUtil.format(card.getOpendate()));//卡开户日期
		infoMap.put("endTime", DateFormatUtil.format(card.getExpiredate()));//卡截至日期
		infoMap.put("accountNo", account.getAccno());//客户账号
		infoMap.put("cardbalance", account.getLastcardbal());//当前卡余额
		infoMap.put("balance", account.getBalance());//客户当前账号余额
		infoMap.put("cardState", card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag());
		return infoMap;
	}
	
	
	
	public static CustomerPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CustomerPersistence persistence) {
		_persistence = persistence;
	}

	private static CustomerUtil _getUtil() {
		if (_util == null) {
			_util = (CustomerUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CustomerUtil.class.getName();
	private static CustomerUtil _util;
	private CustomerPersistence _persistence;
}
