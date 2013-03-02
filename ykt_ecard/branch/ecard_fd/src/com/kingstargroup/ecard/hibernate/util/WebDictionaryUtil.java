package com.kingstargroup.ecard.hibernate.util;

import java.util.ArrayList;
import java.util.List;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.web.DictionaryPersistence;
import com.kingstargroup.ecard.hibernate.web.WebDictionary;
import com.kingstargroup.ecard.hibernate.web.WebDictionaryKey;
import com.kingstargroup.ecard.util.EcardConstants;

public class WebDictionaryUtil extends BasicUtil {

	public static WebDictionary getDictionary(String dicNo, String dicValue)
			throws PortalException {
		DictionaryPersistence persistence = (DictionaryPersistence) getPersistence(DictionaryPersistence.class
				.getName());
		Transaction t = beginTransaction();
		WebDictionary dic = null;
		try {
			dic = persistence.getDictionaryByPK(persistence.createPK(dicNo,
					dicValue));
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
		return dic;
	}
	
	public static List getDictionaryByDicNo(String dicNo)throws PortalException {
		List list = new ArrayList();
		try{
		DictionaryPersistence persistence = (DictionaryPersistence) getPersistence(DictionaryPersistence.class
				.getName());
		WebDictionary dic = null;
		list = persistence.getDictionaryByDicNo(dicNo);
		
		}catch (DBSystemException dbse) {
			throw dbse;
		} finally {
			closeSession();
		}
		return list;
	}
	
	private static void  deleDictionary(WebDictionary  dic)throws PortalException {
		try{
			DictionaryPersistence persistence = (DictionaryPersistence) getPersistence(DictionaryPersistence.class
					.getName());
	    		persistence.delete(dic);
	    }catch (DBSystemException dbse) {
			throw dbse;
		} finally {
			closeSession();
		}
	}

	public static boolean saveorupdate(String title, String service,
			String[] receiveemail, String sendemail, String username,
			String password,String emailReport,String beginDate,String secondtimes) throws PortalException {

		DictionaryPersistence persistence = (DictionaryPersistence) getPersistence(DictionaryPersistence.class
				.getName());
		Transaction t = beginTransaction();

		try {
			WebDictionary dic = new WebDictionary();
			WebDictionaryKey key = new WebDictionaryKey("003", "01");
			dic.setId(key);
			dic.setDicName(EcardConstants.MAINTAIN_EMAIL_SERVICE);
			dic.setDicCaption(service);
			persistence.saveOrUpdate(dic);

			WebDictionary dic2 = new WebDictionary();
			WebDictionaryKey key2 = new WebDictionaryKey("004", "01");
			dic2.setId(key2);
			dic2.setDicName(EcardConstants.MAINTAIN_EMAIL_SENDADDRESS);
			dic2.setDicCaption(sendemail);
			persistence.saveOrUpdate(dic2);

			WebDictionary dic3 = new WebDictionary();
			WebDictionaryKey key3 = new WebDictionaryKey("005", "01");
			dic3.setId(key3);
			dic3.setDicName(EcardConstants.MAINTAIN_SMTP_USER);
			dic3.setDicCaption(username);
			persistence.saveOrUpdate(dic3);

			WebDictionary dic4 = new WebDictionary();
			WebDictionaryKey key4 = new WebDictionaryKey("006", "01");
			dic4.setId(key4);
			dic4.setDicName(EcardConstants.MAINTAIN_SMTP_PWD);
			dic4.setDicCaption(password);
			persistence.saveOrUpdate(dic4);

			WebDictionary dic5 = new WebDictionary();
			WebDictionaryKey key5 = new WebDictionaryKey("007", "01");
			dic5.setId(key5);
			dic5.setDicName(EcardConstants.MAINTAIN_SMTP_TITLE);
			dic5.setDicCaption(title);
			persistence.saveOrUpdate(dic5);
			
			//删除多个邮箱
			List list = persistence.getDictionaryByDicNo("008");
			if(list != null){
				for(int i=0;i<list.size();i++){
					persistence.delete((WebDictionary)list.get(i));
			      
				}
			}

			//插入多个邮箱
			if (receiveemail != null && receiveemail.length > 0) {
				for (int i = 0; i < receiveemail.length; i++) {
					String dicValue = String.valueOf(i + 1);

					WebDictionary dic6 = new WebDictionary();
					WebDictionaryKey key6 = new WebDictionaryKey("008",
							dicValue);
					dic6.setId(key6);
					dic6
							.setDicName(EcardConstants.MAINTAIN_EMAIL_RECEIVEADDRESS);
					dic6.setDicCaption(receiveemail[i]);
					persistence.save(dic6);
				}
			}
			WebDictionary dic7 = new WebDictionary();
			WebDictionaryKey key7 = new WebDictionaryKey("010", "0");
			dic7.setId(key7);
			dic7.setDicName(EcardConstants.ISSENDREPORT);
			dic7.setDicCaption(emailReport);
			persistence.saveOrUpdate(dic7);
			
			WebDictionary dic8 = new WebDictionary();
			WebDictionaryKey key8 = new WebDictionaryKey("011", "0");
			dic8.setId(key8);
			dic8.setDicName(EcardConstants.SENDBEGINDATE);
			dic8.setDicCaption(beginDate);
			persistence.saveOrUpdate(dic8);
			
			WebDictionary dic9 = new WebDictionary();
			WebDictionaryKey key9 = new WebDictionaryKey("012", "0");
			dic9.setId(key9);
			dic9.setDicName(EcardConstants.DAYS);
			dic9.setDicCaption(secondtimes);
			persistence.saveOrUpdate(dic9);
			
			t.commit();
			return true;
		} catch (DBSystemException dbse) {
			t.rollback();
			return false;
		} finally {
			closeSession();
		}

	}
	
	
}
