/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

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
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-11-17 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class HitInfoUtil {

	/**
	 * Description:添加一条滚动新闻
	 * 
	 * @param title
	 * @param mapInfoId
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void add(String title, int mapInfoId) throws PortalException {
		EcardHitInfo info = new EcardHitInfo();
		info.setInfoId(new Integer(mapInfoId));
		info.setTitle(title);
		getPersistence().save(info);
	}

	public static void update(int id, String title, int mapInfoId)
			throws PortalException {
		EcardHitInfo info = (EcardHitInfo) getPersistence().findByPrimaryKey(
				EcardHitInfo.class, new Integer(id));
		if (info != null) {
			info.setInfoId(new Integer(mapInfoId));
			info.setTitle(title);
			getPersistence().saveOrUpdate(info);
		}
	}

	public static void delete(String[] ids) throws PortalException {
		try {
			getPersistence().delete(ids);
		} catch (DBSystemException ex) {
			throw ex;
		}
	}

	/**
	 * Description:返回需要显示的滚动新闻列表
	 * 
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static List getHitInfos() throws PortalException {
		return getPersistence().search("", 0, EcardConstants.HIT_INFO_SIZE)
				.getList();
	}

	public static ResultPage search(String title, int page, int size)
			throws PortalException {
		return getPersistence().search(title, page, size);
	}

	public static EcardHitInfo getHitInfo(String id) throws PortalException {
		return (EcardHitInfo) getPersistence().findByPrimaryKey(
				EcardHitInfo.class, Integer.valueOf(id));
	}

	public static HitInfoPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(HitInfoPersistence persistence) {
		_persistence = persistence;
	}

	private static HitInfoUtil _getUtil() {
		if (_util == null) {
			_util = (HitInfoUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = HitInfoUtil.class.getName();
	private static HitInfoUtil _util;
	private HitInfoPersistence _persistence;
}
