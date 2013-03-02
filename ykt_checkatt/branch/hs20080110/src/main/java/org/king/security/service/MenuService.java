/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.MenuService.java
 * 创建日期： 2006-4-20 11:15:20
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-20 11:15:20      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="MenuService.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */
public interface MenuService extends Service {

	/**
	 * 通过id查找菜单
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
     * 级联删除同该菜单项关联的菜单角色和用户扩展权限
     * @param menu the menu's menuCode
     * @
     */
      
    public void removeMenu(String menuCode) ;
    
    /**
     * 得到xml格式的当前系统的菜单树
     *
     */
	public String getXmlMenuTree() ;
}
