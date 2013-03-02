/**
 * 
 */
package com.kingstargroup.ecard.hibernate.bank;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import com.kingstargroup.ecard.hibernate.bank.TbankcardId;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-19 <br>
 * 
 * @author HLQ
 * @version
 * @since 1.0
 */
public class BankPersistence extends BasePersistence {

	public String getBankAccountFromDB(long custid, String bankcode) throws DBSystemException {
		String bankacc = "";
		Session s = null;
		try {
			s = openSession();
			TbankcardId tbankcardid = new TbankcardId(custid, bankcode);
			Tbankcard tbankcard = (Tbankcard) s.get(Tbankcard.class,
					tbankcardid);
			if(tbankcard!=null){
				bankacc = tbankcard.getBankcardno();
			}
			return bankacc;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException("数据库查询失败");
		}

	}

	public void updateBankAccountToDB(long custid, String bankcode,
			String bankcardno) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			TbankcardId tbankcardid = new TbankcardId(custid, bankcode);
			Tbankcard tbankcard = (Tbankcard) s.get(Tbankcard.class,
					tbankcardid);
			if (tbankcard == null) {
				tbankcard = new Tbankcard();
				tbankcard.setId(tbankcardid);
				tbankcard.setBankcardno(bankcardno);
				tbankcard.setCreateddate(DateUtil.getNow("yyyyMMdd"));
				tbankcard.setLastsaved(DateUtil.getNow());
			}
			tbankcard.setBankcardno(bankcardno);
			tbankcard.setLastsaved(DateUtil.getNow());
			s.saveOrUpdate(tbankcard);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException("数据库更新失败");
		}

	}

	public void removeBankAccountFromDB(long custid, String bankcode,
			String bankcardno) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			TbankcardId tbankcardid = new TbankcardId(custid, bankcode);
			Tbankcard tbankcard = (Tbankcard) s.get(Tbankcard.class,
					tbankcardid);
			if (tbankcard != null) {
				s.delete(tbankcard);
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException("数据库删除失败");
		}

	}

	private static final Log _log = LogFactory.getLog(BankPersistence.class);
}
