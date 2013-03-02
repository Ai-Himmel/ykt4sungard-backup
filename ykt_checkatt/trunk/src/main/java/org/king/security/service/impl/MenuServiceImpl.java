/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.impl.MenuServiceImpl.java
 * �������ڣ� 2006-4-26 15:31:01
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-26 15:31:01      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service.impl;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;


import org.king.framework.service.impl.BaseService;
import org.king.security.dao.MenuDAO;
import org.king.security.domain.Menu;
import org.king.security.service.MenuService;
import org.king.security.util.ConvertXmlUtil;

/**
 * <p> MenuServiceImpl.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="MenuServiceImpl.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-26
 * 
 *
 */
public class MenuServiceImpl extends BaseService implements MenuService {

	private MenuDAO menuDAO;
	
	
	public void setMenuDAO(MenuDAO menuDAO) {
		this.menuDAO = menuDAO;
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.MenuService#getMenus()
	 */
	public List getMenus() {
		return menuDAO.getAll();
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.MenuService#saveMenu(org.king.security.domain.Menu)
	 */
	public void saveMenu(Menu menu) {
		menuDAO.save(menu);

	}

	/* (non-Javadoc)
	 * @see org.king.security.service.MenuService#updateMenu(org.king.security.domain.Menu)
	 */
	public void updateMenu(Menu menu) {
		menuDAO.update(menu);

	}

	/* (non-Javadoc)
	 * @see org.king.security.service.MenuService#removeMenu(java.lang.String)
	 */
	public void removeMenu(String menuCode) {
		menuDAO.delete(menuDAO.get(menuCode));
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.MenuService#getXmlMenuTree()
	 */
	public String getXmlMenuTree() {
		if (log.isDebugEnabled()) {
			log.debug("MenuServiceImpl->getXmlMenuTree");
		}	
		
		List menus = menuDAO.getAll();
		
		Map menuMap = new HashMap();
		List menuList = null;
		
		String rootId = "-1";
		
		String menuByParentHql = "from Menu m where m.pid='";
	
		//��ӵ�һ���Ӳ˵�
		menuList = menuDAO.find(menuByParentHql+rootId+"'");
		menuMap.put(rootId,menuList);
		
		//Ϊÿ���˵���������Ӳ˵�
		for(Iterator i=menus.iterator();i.hasNext();){
			Menu menu = (Menu)i.next();
			menuList = menuDAO.find(menuByParentHql+menu.getId()+"'");
			
			menuMap.put(menu.getId(),menuList);	
		}
		
		String xmlStr = ConvertXmlUtil.convertMenuListToXml(menuMap);
		
		return xmlStr;
	}

	public Menu findMenuById(Serializable id) {
		return menuDAO.get(id);
	}


}
