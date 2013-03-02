package com.kingstargroup.ecard.portlet.distribution.service;

import java.util.HashMap;
import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.account.TAccount;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.card.TCardtype;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.hibernate.dictionary.TDictionary;
import com.kingstargroup.ecard.hibernate.util.AccountUtil;
import com.kingstargroup.ecard.hibernate.util.CardUtil;
import com.kingstargroup.ecard.hibernate.util.DictionaryUtil;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.util.DateFormatUtil;
import com.kingstargroup.ecard.util.EcardConstants;

public class CustomerLocalServiceImpl extends CustomerLocalServiceBase {

	/**
	 * Description: ͨ������Ŀͻ��ŵõ���Ӧ�ͻ�����
	 * 
	 * @param customerId
	 *            ����ͻ���
	 * @return �ͻ����� Modify History:
	 */
	public TCustomer getCustomerById(String custid) throws PortalException {
		return customerPersistence.getCustomerById(Long.parseLong(custid));

	}

	/**
	 * Description:����ѧ���ŵõ���Ӧ�ͻ�����
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TCustomer getCustomerByStuempNo(String stuempno)
			throws PortalException {
		return customerPersistence.getCustomerByStuempno(stuempno);
	}

	/**
	 * Description:������ѧ/���ŵõ��Ϳͻ���ص�һЩ��Ϣ������Ϣ�ȣ�
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History: 2005-10-18 �����ͻ���Ϊѧ����
	 */
	public HashMap getRelatedCustomerInfo(String stuempNo)
			throws PortalException {
		String custid = getCustomerByStuempNo(stuempNo).getCustid().toString();
		List cards = CardUtil.getAvailableCards(custid);
		return getRelatedCustomerInfo(custid, ((TCard) cards.get(0))
				.getCardno());
	}

	public HashMap getRelatedCustomerInfo(String custid, Long cardno) throws PortalException {
		HashMap infoMap = new HashMap();
		TCustomer customer = getCustomerById(custid);
		TCard card = CardServiceUtil.getCardById(cardno);
		String deptName ="";
		if(customer.getDeptcode()!=null&&!"".equals(customer.getDeptcode())){
			TDept dept = CardUtil.getDept(customer.getDeptcode());
			if(dept!=null){
				deptName = dept.getDeptname();
			}
		}
		
		TAccount account = AccountUtil.getAccountByCardno(card.getCardno().toString());		
		
		infoMap.put("customerId", customer.getStuempno());// ѧ����
		infoMap.put("customerName", customer.getCustname());// �ͻ�����
		infoMap.put("customerDep", deptName);// �ͻ����ڲ�������
		TCardtype tcardtype = DictionaryUtil.getCardType(card.getCardtype());
		String cardType = tcardtype==null?"":tcardtype.getCardtypename();
		infoMap.put("cardType", cardType);// �����
		TDictionary tdictionary =  DictionaryUtil.getDictionary(EcardConstants.CARD_STATUS_DIC_NO, card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag());
		String cardStatus = tdictionary==null?"":tdictionary.getDictcaption();
		infoMap.put("cardStatus", cardStatus);// ��״̬
		infoMap.put("beginTime", DateFormatUtil.format(card.getOpendate()));// ����������
		infoMap.put("endTime", DateFormatUtil.format(card.getExpiredate()));// ����������
		infoMap.put("accountNo", account.getAccno());// �ͻ��˺�
		infoMap.put("cardbalance", account.getLastcardbal());// ��ǰ�����
		infoMap.put("balance", account.getBalance());// �ͻ���ǰ�˺����
		infoMap.put("cardState", card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag());
		return infoMap;
	}

	public HashMap getRelatedCustomerInfo(String customerId, Integer cardId)
			throws PortalException {
		// TODO Auto-generated method stub
		return null;
	}

}
