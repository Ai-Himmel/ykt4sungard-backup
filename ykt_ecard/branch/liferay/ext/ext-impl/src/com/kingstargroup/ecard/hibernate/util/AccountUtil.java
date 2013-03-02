/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.account.AccountPersistence;
import com.kingstargroup.ecard.hibernate.account.TAccount;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AccountUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AccountUtil {

	/**
	 * Description:根据卡号得到此客户对应的帐号
	 * @param cardId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static TAccount getAccountByCardno(String cardno) throws PortalException {
			return getPersistence().getAccountByCardno(cardno);
	}
	
	
	
	public static TCustomer getCustomerByStuempno(String stuempno)throws PortalException{
		try {
			List list = getPersistence().getCustomerByStuempno(stuempno);
			TCustomer cust = null;
			if(list!=null&&list.size()>0){
				cust = (TCustomer)list.get(0);
			}
			return cust;
		} catch (HibernateException he) {
			he.printStackTrace();
			throw he;
		}
	}
	
	public static String cardNoString(int custid)throws PortalException{
		try {
			List card = getPersistence().getCardnoByCustid(custid);
			StringBuffer cardNoS = new StringBuffer();
			Iterator iter = card.iterator();
			while (iter.hasNext()){
				TCard pcard = (TCard)iter.next();
				if (iter.hasNext()){
					cardNoS.append("'"+pcard.getCardno()+"',");
				}else{
					cardNoS.append("'"+pcard.getCardno()+"'");
				}
			}
			return cardNoS.toString();
		} catch (HibernateException he) {
			he.printStackTrace();
			throw he;
		}
	}
	
	
	public static AccountPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(AccountPersistence persistence) {
		_persistence = persistence;
	}

	private static AccountUtil _getUtil() {
		if (_util == null) {
			_util = (AccountUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = AccountUtil.class.getName();
	private static AccountUtil _util;
	private AccountPersistence _persistence;
	
}
