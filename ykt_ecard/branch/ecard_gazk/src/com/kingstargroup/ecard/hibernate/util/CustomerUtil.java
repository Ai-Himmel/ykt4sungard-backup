/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.HashMap;
import java.util.List;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.account.TAifAccount;
import com.kingstargroup.ecard.hibernate.card.TCifDept;
import com.kingstargroup.ecard.hibernate.card.TPifCard;
import com.kingstargroup.ecard.hibernate.customer.CustomerPersistence;
import com.kingstargroup.ecard.hibernate.customer.TCifCustomer;
import com.kingstargroup.ecard.hibernate.custype.CustomerTypePersistence;
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
public class CustomerUtil extends BasicUtil {

	/**
	 * Description: 通过传入的客户号得到对应客户对象
	 * @param customerId 传入客户号
	 * @return 客户对象
	 * Modify History:
	 */
	public static TCifCustomer getCustomerById(String customerId) throws PortalException {
		CustomerPersistence persistence = (CustomerPersistence) getPersistence(CustomerPersistence.class.getName());
		Transaction t = beginTransaction();
		TCifCustomer customer = null;
		try {
			customer = persistence.getCustomerById(Integer.parseInt(customerId));
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
		} finally {
			closeSession();
		}
		return customer;
	}
	
	/**
	 * Description:根据身份证得到对应客户
	 * @param manId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static TCifCustomer getCustomerByManId(String manId) throws PortalException {
		CustomerPersistence persistence = (CustomerPersistence) getPersistence(CustomerPersistence.class.getName());
		Transaction t = beginTransaction();
		TCifCustomer customer = null;
		try {
			customer = persistence.getCustomerByStuempNo(manId);//stuempNo和manId值互换
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
		} finally {
			closeSession();
		}
		return customer;
	}
	
	/**
	 * Description:根据学工号得到对应客户对象
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 * 
	 */
	public static TCifCustomer getCustomerByStuempNo(String stuempNo) throws PortalException {
		CustomerPersistence persistence = (CustomerPersistence) getPersistence(CustomerPersistence.class.getName());
		Transaction t = beginTransaction();
		TCifCustomer customer = null;
		try {
			//customer = persistence.getCustomerByStuempNo(stuempNo);
			customer = persistence.getCustomerByManId(stuempNo);//因stuempNo和manId值互换,所以此实现类也
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
		} finally {
			closeSession();
		}
		return customer;

	}
	
	/**
	 * Description:根据用学/工号得到和客户相关的一些信息（卡信息等）
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 * 2005-10-18 更换客户号为学工号
	 */
	public static HashMap getRelatedCustomerInfo(String stuempNo) throws PortalException {
		String customerId = getCustomerByStuempNo(stuempNo).getCutId().toString();
		List cards = CardUtil.getAvailableCards(customerId);
		return getRelatedCustomerInfo(customerId, ((TPifCard) cards.get(0)).getCardId()); 
	}
	
	public static HashMap getRelatedCustomerInfo(String customerId, Integer cardId) throws PortalException {
		HashMap infoMap = new HashMap();
		TCifCustomer customer = getCustomerById(customerId);
		TPifCard card = CardUtil.getCardById(cardId);
		String deptName ="";
		if(customer.getClassdeptNo()!=null&&!"".equals(customer.getClassdeptNo())){
			TCifDept dept = CardUtil.getDept(customer.getClassdeptNo());
			if(dept!=null){
				deptName = dept.getDeptName();
			}
		}
		
		TAifAccount account = AccountUtil.getAccountByCardId(card.getCardId().toString());		
		
		infoMap.put("customerId", customer.getStuempNo());//学工号
		infoMap.put("customerName", customer.getCutName());//客户名称
		infoMap.put("customerDep", deptName);//客户所在部门名称
		infoMap.put("cardType", 
					DictionaryUtil.getDictionary(EcardConstants.CARD_TYPE_DIC_NO, card.getTypeId().toString()).getDictCaption());//卡类别
		infoMap.put("cardStatus", 
				DictionaryUtil.getDictionary(EcardConstants.CARD_STATUS_DIC_NO, card.getStateId().toString()).getDictCaption());//卡状态
		infoMap.put("beginTime", DateFormatUtil.format(card.getBeginTime()));//卡开户日期
		infoMap.put("endTime", DateFormatUtil.format(card.getEndTime()));//卡截至日期
		infoMap.put("accountNo", account.getAccountId());//客户账号
		infoMap.put("cardbalance", account.getCardBalance().toString());//当前卡余额
		infoMap.put("balance", account.getCurBala().toString());//客户当前账号余额
		infoMap.put("cardState", card.getStateId());
		return infoMap;
	}
	
	/**
	 * Description:返回客户类别名
	 * @param id
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static String getCustomerTypeName(Integer id) throws PortalException {
		CustomerTypePersistence persistence = (CustomerTypePersistence) getPersistence(CustomerTypePersistence.class.getName());		
		String typeName = null;
		Transaction t = beginTransaction();
		try {
			typeName = persistence.getCustomerType(id).getTypeName();
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return typeName;
	}
}
