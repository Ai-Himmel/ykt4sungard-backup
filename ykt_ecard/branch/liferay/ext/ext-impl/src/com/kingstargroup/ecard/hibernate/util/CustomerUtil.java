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
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CustomerUtil {

	/**
	 * Description: ͨ������Ŀͻ��ŵõ���Ӧ�ͻ�����
	 * @param customerId ����ͻ���
	 * @return �ͻ�����
	 * Modify History:
	 */
	public static TCustomer getCustomerById(String custid) throws PortalException {
		return getPersistence().getCustomerById(Integer.parseInt(custid));

	}
	
	/**
	 * Description:����ѧ���ŵõ���Ӧ�ͻ�����
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TCustomer getCustomerByStuempno(String stuempno) throws PortalException {
			return getPersistence().getCustomerByStuempno(stuempno);
	}
	
	/**
	 * Description:������ѧ/���ŵõ��Ϳͻ���ص�һЩ��Ϣ������Ϣ�ȣ�
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 * 2005-10-18 �����ͻ���Ϊѧ����
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
		
		infoMap.put("customerId", customer.getStuempno());//ѧ����
		infoMap.put("customerName", customer.getCustname());//�ͻ�����
		infoMap.put("customerDep", deptName);//�ͻ����ڲ�������
		infoMap.put("cardType", 
					DictionaryUtil.getDictionary(EcardConstants.CARD_TYPE_DIC_NO, card.getCardtype().toString()).getDictcaption());//�����
		infoMap.put("cardStatus", 
				DictionaryUtil.getDictionary(EcardConstants.CARD_STATUS_DIC_NO, card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag()).getDictcaption());//��״̬
		infoMap.put("beginTime", DateFormatUtil.format(card.getOpendate()));//����������
		infoMap.put("endTime", DateFormatUtil.format(card.getExpiredate()));//����������
		infoMap.put("accountNo", account.getAccno());//�ͻ��˺�
		infoMap.put("cardbalance", account.getLastcardbal());//��ǰ�����
		infoMap.put("balance", account.getBalance());//�ͻ���ǰ�˺����
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
