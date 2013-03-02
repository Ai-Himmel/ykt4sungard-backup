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
	 * Description: 通过传入的客户号得到对应客户对象
	 * 
	 * @param customerId
	 *            传入客户号
	 * @return 客户对象 Modify History:
	 */
	public TCustomer getCustomerById(String custid) throws PortalException {
		return customerPersistence.getCustomerById(Long.parseLong(custid));

	}

	/**
	 * Description:根据学工号得到对应客户对象
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
	 * Description:根据用学/工号得到和客户相关的一些信息（卡信息等）
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History: 2005-10-18 更换客户号为学工号
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
		
		infoMap.put("customerId", customer.getStuempno());// 学工号
		infoMap.put("customerName", customer.getCustname());// 客户名称
		infoMap.put("customerDep", deptName);// 客户所在部门名称
		TCardtype tcardtype = DictionaryUtil.getCardType(card.getCardtype());
		String cardType = tcardtype==null?"":tcardtype.getCardtypename();
		infoMap.put("cardType", cardType);// 卡类别
		TDictionary tdictionary =  DictionaryUtil.getDictionary(EcardConstants.CARD_STATUS_DIC_NO, card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag());
		String cardStatus = tdictionary==null?"":tdictionary.getDictcaption();
		infoMap.put("cardStatus", cardStatus);// 卡状态
		infoMap.put("beginTime", DateFormatUtil.format(card.getOpendate()));// 卡开户日期
		infoMap.put("endTime", DateFormatUtil.format(card.getExpiredate()));// 卡截至日期
		infoMap.put("accountNo", account.getAccno());// 客户账号
		infoMap.put("cardbalance", account.getLastcardbal());// 当前卡余额
		infoMap.put("balance", account.getBalance());// 客户当前账号余额
		infoMap.put("cardState", card.getStatus()+card.getLossflag()+card.getFrozeflag()+card.getBadflag());
		return infoMap;
	}

	public HashMap getRelatedCustomerInfo(String customerId, Integer cardId)
			throws PortalException {
		// TODO Auto-generated method stub
		return null;
	}

}
