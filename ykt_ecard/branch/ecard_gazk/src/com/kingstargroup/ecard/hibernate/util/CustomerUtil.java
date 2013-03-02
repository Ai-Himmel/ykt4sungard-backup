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
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CustomerUtil extends BasicUtil {

	/**
	 * Description: ͨ������Ŀͻ��ŵõ���Ӧ�ͻ�����
	 * @param customerId ����ͻ���
	 * @return �ͻ�����
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
	 * Description:�������֤�õ���Ӧ�ͻ�
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
			customer = persistence.getCustomerByStuempNo(manId);//stuempNo��manIdֵ����
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
		} finally {
			closeSession();
		}
		return customer;
	}
	
	/**
	 * Description:����ѧ���ŵõ���Ӧ�ͻ�����
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
			customer = persistence.getCustomerByManId(stuempNo);//��stuempNo��manIdֵ����,���Դ�ʵ����Ҳ
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
		} finally {
			closeSession();
		}
		return customer;

	}
	
	/**
	 * Description:������ѧ/���ŵõ��Ϳͻ���ص�һЩ��Ϣ������Ϣ�ȣ�
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 * 2005-10-18 �����ͻ���Ϊѧ����
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
		
		infoMap.put("customerId", customer.getStuempNo());//ѧ����
		infoMap.put("customerName", customer.getCutName());//�ͻ�����
		infoMap.put("customerDep", deptName);//�ͻ����ڲ�������
		infoMap.put("cardType", 
					DictionaryUtil.getDictionary(EcardConstants.CARD_TYPE_DIC_NO, card.getTypeId().toString()).getDictCaption());//�����
		infoMap.put("cardStatus", 
				DictionaryUtil.getDictionary(EcardConstants.CARD_STATUS_DIC_NO, card.getStateId().toString()).getDictCaption());//��״̬
		infoMap.put("beginTime", DateFormatUtil.format(card.getBeginTime()));//����������
		infoMap.put("endTime", DateFormatUtil.format(card.getEndTime()));//����������
		infoMap.put("accountNo", account.getAccountId());//�ͻ��˺�
		infoMap.put("cardbalance", account.getCardBalance().toString());//��ǰ�����
		infoMap.put("balance", account.getCurBala().toString());//�ͻ���ǰ�˺����
		infoMap.put("cardState", card.getStateId());
		return infoMap;
	}
	
	/**
	 * Description:���ؿͻ������
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
