package com.kingstargroup.ecard.portlet.infotype.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class InfoTypeServiceUtil {
	
	public static  ResultPage getChildList(String id) throws PortalException{
		
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		return infoTypeService.getChildList(id);
	}
	
	public static  ResultPage getChildList(String id, int page, int size)
	throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		return infoTypeService.getChildList(id, page, size);	
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
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		infoTypeService.add(parentId, typeName);
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
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		infoTypeService.updateType(typeId, typeName);
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
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		return infoTypeService.getTypeById(typeId);
	}
	
	
	
	/**
	 * Description:删除指定的信息类型
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteTypes(String[] ids) throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		infoTypeService.deleteTypes(ids);
		
	}
}
