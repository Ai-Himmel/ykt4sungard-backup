package com.kingstargroup.ecard.portlet.infotype.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.kernel.util.StringUtil;

public interface InfoTypeService {
	
	public ResultPage getChildList(String id) throws PortalException;
	
	public  ResultPage getChildList(String id, int page, int size)
	throws PortalException;
	
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
	public  void add(String parentId, String typeName)
			throws PortalException;
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
	public  void updateType(String typeId, String typeName)
			throws PortalException ;

	/**
	 * Description:根据类型ID得到类型对象
	 * 
	 * @param typeId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public  InfoType getTypeById(String typeId) throws PortalException ;
	
	
	/**
	 * Description:删除指定的信息类型
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public void deleteTypes(String[] ids) throws PortalException;
}
