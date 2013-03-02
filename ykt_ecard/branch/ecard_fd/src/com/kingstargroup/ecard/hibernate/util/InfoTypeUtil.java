/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.infotype.InfoTypePersistence;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.StringUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: InfoTypeUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-22  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class InfoTypeUtil extends BasicUtil {	
	/**
	 * Description: 根据传入的信息父ID得到此类型下面所有子类型
	 * @param id 传入的信息ID
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static ResultPage getChildList(String id) throws PortalException {		
		return getChildList(id, 0, EcardConstants.MAX_RESULT_SIZE);
	}
	
	public static ResultPage getChildList(String id, int page, int size) throws PortalException {
		InfoTypePersistence persistence = (InfoTypePersistence) getPersistence(InfoTypePersistence.class.getName());
		Transaction t = beginTransaction();
		ResultPage result = null;				
		try {
			result = persistence.search(id + ".", null, page, size);			
			t.commit();
			return result;
		} catch (DBSystemException dbse) {			
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description: 增加一个新的子类型到指定的父类型下面
	 * @param parentId 父类型ID
	 * @param typeName 要增加的类型名称
	 * @throws PortalException
	 * Modify History:
	 */
	public static void add(String parentId, String typeName) throws PortalException {
		InfoTypePersistence persistence = (InfoTypePersistence) getPersistence(InfoTypePersistence.class.getName());
		/*
		 * 先取得需要插入的子类型ID
		 */
		List childList = getChildList(parentId).getList();
		StringBuffer newTypeId = new StringBuffer(parentId);
		int maxTypeId = 0;
		for (int i = 0; i < childList.size(); i++) {
			InfoType tmp = (InfoType) childList.get(i);
			int tmpTypeId = Integer.parseInt(StringUtil.split(tmp.getInfoType(), ".")[1]);
			if (tmpTypeId > maxTypeId) {
				maxTypeId = tmpTypeId;
			}
		}
		newTypeId.append(".")
				.append(maxTypeId + 1);		
		InfoType type = new InfoType();
		type.setInfoName(typeName);
		type.setInfoType(newTypeId.toString());
		Transaction t = beginTransaction();
		try {
			persistence.saveOrUpdate(type);
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:更新对应的类型对象
	 * @param typeId 类型ID
	 * @param typeName 类型名称
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updateType(String typeId, String typeName) throws PortalException {
		InfoTypePersistence persistence = (InfoTypePersistence) getPersistence(InfoTypePersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			InfoType type = persistence.getTypeById(typeId);
			type.setInfoName(typeName);
			persistence.saveOrUpdate(type);
			t.commit();
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:根据类型ID得到类型对象
	 * @param typeId
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static InfoType getTypeById(String typeId) throws PortalException {
		InfoTypePersistence persistence = (InfoTypePersistence) getPersistence(InfoTypePersistence.class.getName());		
		InfoType type = null;
		Transaction t = beginTransaction();
		try {
			type = persistence.getTypeById(typeId);
			t.commit();
			return type;
		} catch (DBSystemException dbse) {
			t.rollback();
			throw dbse;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:删除指定的信息类型
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public static void deleteTypes(String[] ids) throws PortalException {
		InfoTypePersistence persistence = (InfoTypePersistence) getPersistence(InfoTypePersistence.class.getName());
		Transaction t = beginTransaction();		
		try {			
			persistence.deleteTypesByIds(ids);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
}
