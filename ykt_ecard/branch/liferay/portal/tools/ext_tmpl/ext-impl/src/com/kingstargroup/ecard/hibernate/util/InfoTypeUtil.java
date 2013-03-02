/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.infotype.InfoTypePersistence;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.StringUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: InfoTypeUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-9-22 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class InfoTypeUtil {
	/**
	 * Description: 根据传入的信息父ID得到此类型下面所有子类型
	 * 
	 * @param id
	 *            传入的信息ID
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static ResultPage getChildList(String id) throws PortalException {
		return getChildList(id, 0, EcardConstants.MAX_RESULT_SIZE);
	}

	public static ResultPage getChildList(String id, int page, int size)
			throws PortalException {
		return getPersistence().search(id + ".", null, page, size);

	}

	/**
	 * Description: 增加一个新的子类型到指定的父类型下面
	 * 
	 * @param parentId
	 *            父类型ID
	 * @param typeName
	 *            要增加的类型名称
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void add(String parentId, String typeName)
			throws PortalException {
		/*
		 * 先取得需要插入的子类型ID
		 */
		List childList = getChildList(parentId).getList();
		StringBuffer newTypeId = new StringBuffer(parentId);
		int maxTypeId = 0;
		for (int i = 0; i < childList.size(); i++) {
			InfoType tmp = (InfoType) childList.get(i);
			int tmpTypeId = Integer.parseInt(StringUtil.split(
					tmp.getInfoType(), ".")[1]);
			if (tmpTypeId > maxTypeId) {
				maxTypeId = tmpTypeId;
			}
		}
		newTypeId.append(".").append(maxTypeId + 1);
		InfoType type = new InfoType();
		type.setInfoName(typeName);
		type.setInfoType(newTypeId.toString());
		getPersistence().saveOrUpdate(type);
	}

	/**
	 * Description:更新对应的类型对象
	 * 
	 * @param typeId
	 *            类型ID
	 * @param typeName
	 *            类型名称
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void updateType(String typeId, String typeName)
			throws PortalException {

		InfoType type = getPersistence().getTypeById(typeId);
		if (type != null) {
			type.setInfoName(typeName);
			getPersistence().saveOrUpdate(type);
		}
	}

	/**
	 * Description:根据类型ID得到类型对象
	 * 
	 * @param typeId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static InfoType getTypeById(String typeId) throws PortalException {

		return getPersistence().getTypeById(typeId);
	}

	/**
	 * Description:删除指定的信息类型
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteTypes(String[] ids) throws PortalException {
			getPersistence().deleteTypesByIds(ids);
	}

	public static InfoTypePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(InfoTypePersistence persistence) {
		_persistence = persistence;
	}

	private static InfoTypeUtil _getUtil() {
		if (_util == null) {
			_util = (InfoTypeUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = InfoTypeUtil.class.getName();
	private static InfoTypeUtil _util;
	private InfoTypePersistence _persistence;
}
