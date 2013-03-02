/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.MenuService.java
 * �������ڣ� 2006-4-20 11:15:20
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-20 11:15:20      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.io.Serializable;
import java.util.List;

import org.king.framework.service.Service;
import org.king.security.domain.Menu;

/**
 * <p> MenuService.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="MenuService.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */
public interface MenuService extends Service {

	/**
	 * ͨ��id���Ҳ˵�
	 * @param id
	 * @return
	 */
	public Menu findMenuById(Serializable id);
	
    /**
     * Retrieves all menu
     * @return List
     * 
     */
    public List getMenus() ;
    
    /**
     * 
     * @param menu
     */
    public void saveMenu(Menu menu) ;

    /**
     * 
     * @param menu
     */
    public void updateMenu(Menu menu);
    
    /**
     * Removes menu from the database by their menu code
     * ����ɾ��ͬ�ò˵�������Ĳ˵���ɫ���û���չȨ��
     * @param menu the menu's menuCode
     * @
     */
      
    public void removeMenu(String menuCode) ;
    
    /**
     * �õ�xml��ʽ�ĵ�ǰϵͳ�Ĳ˵���
     *
     */
	public String getXmlMenuTree() ;
}
