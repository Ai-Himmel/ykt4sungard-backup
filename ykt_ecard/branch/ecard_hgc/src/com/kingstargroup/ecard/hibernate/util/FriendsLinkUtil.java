package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.friendslink.FriendsLink;
import com.kingstargroup.ecard.hibernate.friendslink.FriendsLinkPersistence;
import com.kingstargroup.ecard.util.EcardConstants;

public class FriendsLinkUtil extends BasicUtil {
	
	
	public static void add(String linkName, String  linkUrl,String creater) throws PortalException {
		FriendsLinkPersistence persistence = (FriendsLinkPersistence) getPersistence(FriendsLinkPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			FriendsLink link = new FriendsLink();
			link.setLinkName(linkName);
			link.setLinkUrl(linkUrl);
			link.setCreateDate(new Date());
			link.setCreater(creater);
			persistence.save(link);
			t.commit();
		} catch(DBSystemException ex) {
			t.rollback();
			throw ex;
		} finally {
			closeSession();
		}
	}
	
	public static ResultPage list(int page, int size) throws PortalException {
		return search(null, null,  page, size);
	}

	public static void deleteLink(String[] ids) throws PortalException {
		FriendsLinkPersistence persistence = (FriendsLinkPersistence) getPersistence(FriendsLinkPersistence.class.getName());
		Transaction t = beginTransaction();
		try {			
			
			for	(int i=0;i<ids.length;i++){
				FriendsLink link = persistence.getLinkById(ids[i]);
				persistence.delete(link);
			}
			
			t.commit();
		} catch(DBSystemException ex) {
			t.rollback();
			throw ex;
		} finally {
			closeSession();
		}
	}
	
	public static void update(String id, String linkName, String linkUrl) throws PortalException {
		FriendsLinkPersistence persistence = (FriendsLinkPersistence) getPersistence(FriendsLinkPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			FriendsLink link = (FriendsLink) persistence.findByPrimaryKey(FriendsLink.class, Integer.valueOf(id));
			if (link == null)
				return;			
			link.setLinkName(linkName);
			link.setLinkUrl(linkUrl);
			persistence.saveOrUpdate(link);
			t.commit();
		} catch(DBSystemException ex) {
			t.rollback();
			throw ex;
		} finally {
			closeSession();
		}
	}
	public static FriendsLink getLink(String id) throws PortalException {
		FriendsLinkPersistence persistence = (FriendsLinkPersistence) getPersistence(FriendsLinkPersistence.class.getName());
		try {
			return (FriendsLink) persistence.findByPrimaryKey(FriendsLink.class, Integer.valueOf(id));
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	
	public static ResultPage search(String title, String content,  int page) throws PortalException {
		return search(title, content, page, EcardConstants.LIST_MORE_SIZE);
	}
	
	public static ResultPage search(String title,String url, int page, int size) throws PortalException {
		FriendsLinkPersistence persistence = (FriendsLinkPersistence) getPersistence(FriendsLinkPersistence.class.getName());
		try {
			return persistence.search(title,"",page, size);
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	
}
