/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.account.AccountPersistence;
import com.kingstargroup.ecard.hibernate.account.TAifAccount;
import com.kingstargroup.ecard.hibernate.card.TPifCard;
import com.kingstargroup.ecard.hibernate.customer.CustomerPersistence;
import com.kingstargroup.ecard.hibernate.subsyslog.TSubsysLog;
import com.kingstargroup.ecard.hibernate.sysdate.SysDatePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AccountUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-26  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AccountUtil extends BasicUtil {

	/**
	 * Description:���ݿ��ŵõ��˿ͻ���Ӧ���ʺ�
	 * @param cardId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static TAifAccount getAccountByCardId(String cardId) throws PortalException {
		AccountPersistence persistence = (AccountPersistence) getPersistence(AccountPersistence.class.getName());		
		TAifAccount account = null;
		Transaction t = beginTransaction();
		try {
			account = persistence.getAccountByCardId(cardId);
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
		return account;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AccountUtil��¼��¼��־<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-5-19  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static void loginInfo(String stuempno)throws PortalException{
		AccountPersistence persistence = (AccountPersistence) getPersistence(AccountPersistence.class.getName());
		CustomerPersistence custper = (CustomerPersistence)getPersistence(CustomerPersistence.class.getName());
		SysDatePersistence sysPst = (SysDatePersistence) getPersistence(SysDatePersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			String dateTime = sysPst.getSysDate(0);
			String operateDate = dateTime.substring(0, 8);
			String operateTime = dateTime.substring(8);
			TSubsysLog log = new TSubsysLog();
			log.setCustId(custper.getCustomerByStuempNo(stuempno).getCutId());
			log.setLoginName("");
			log.setLogDate(operateDate);
			log.setLogTime(operateTime);
			log.setSussysId(new Integer(2000));
			log.setComments(stuempno+"["+operateDate+operateTime+"]:�ɹ���¼�ۺϲ�ѯϵͳ");
			persistence.save(log);
			t.commit();
		} catch (HibernateException dbse) {
			dbse.printStackTrace();
			t.rollback();
			throw dbse;
		}finally{
			closeSession();
		}
	}
	
	public static String cardNoString(int custId)throws PortalException{
		AccountPersistence persistence = (AccountPersistence) getPersistence(AccountPersistence.class.getName());
		try {
			List card = persistence.getCardNoByCustNo(custId);
			StringBuffer cardNoS = new StringBuffer();
			Iterator iter = card.iterator();
			while (iter.hasNext()){
				TPifCard pcard = (TPifCard)iter.next();
				if (iter.hasNext()){
					cardNoS.append(pcard.getCardId()+",");
				}else{
					cardNoS.append(pcard.getCardId());
				}
			}
			return cardNoS.toString();
		} catch (HibernateException he) {
			he.printStackTrace();
			throw he;
		}finally{
			closeSession();
		}
	}
	
}
