/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.hitinfo.EcardHitInfo;
import com.kingstargroup.ecard.hibernate.hitinfo.HitInfoPersistence;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: HitInfoUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-17  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class HitInfoUtil extends BasicUtil {
	
	/**
	 * Description:添加一条滚动新闻
	 * @param title
	 * @param mapInfoId
	 * @throws PortalException
	 * Modify History:
	 */
	public static void add(String title, int mapInfoId) throws PortalException {
		HitInfoPersistence persistence = (HitInfoPersistence) getPersistence(HitInfoPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardHitInfo info = new EcardHitInfo();
			info.setInfoId(new Integer(mapInfoId));
			info.setTitle(title);
			persistence.save(info);
			t.commit();
		} catch(DBSystemException ex) {
			t.rollback();
			throw ex;
		} finally {
			closeSession();
		}
	}
	
	public static void update(int id, String title, int mapInfoId) throws PortalException {
		HitInfoPersistence persistence = (HitInfoPersistence) getPersistence(HitInfoPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardHitInfo info = (EcardHitInfo) persistence.findByPrimaryKey(EcardHitInfo.class, new Integer(id));
			if (info == null)
				return;			
			info.setInfoId(new Integer(mapInfoId));
			info.setTitle(title);
			persistence.saveOrUpdate(info);
			t.commit();
		} catch(DBSystemException ex) {
			t.rollback();
			throw ex;
		} finally {
			closeSession();
		}
	}
	
	public static void delete(String[] ids) throws PortalException {
		HitInfoPersistence persistence = (HitInfoPersistence) getPersistence(HitInfoPersistence.class.getName());
		Transaction t = beginTransaction();
		try {			
			persistence.delete(ids);
			t.commit();
		} catch(DBSystemException ex) {
			t.rollback();
			throw ex;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:返回需要显示的滚动新闻列表
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static List getHitInfos() throws PortalException {
		HitInfoPersistence persistence = (HitInfoPersistence) getPersistence(HitInfoPersistence.class.getName());
		try {
			return persistence.search("", 0, EcardConstants.HIT_INFO_SIZE).getList();			
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}

	public static ResultPage search(String title, int page, int size) throws PortalException {
		HitInfoPersistence persistence = (HitInfoPersistence) getPersistence(HitInfoPersistence.class.getName());
		try {
			return persistence.search(title, page, size);
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
	
	public static EcardHitInfo getHitInfo(String id) throws PortalException {
		HitInfoPersistence persistence = (HitInfoPersistence) getPersistence(HitInfoPersistence.class.getName());
		try {
			return (EcardHitInfo) persistence.findByPrimaryKey(EcardHitInfo.class, Integer.valueOf(id));
		} catch (DBSystemException e) {			
			throw e;
		} finally {
			closeSession();
		}
	}
}
