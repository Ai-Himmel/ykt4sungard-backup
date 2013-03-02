/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.SecurityService.java
 * 创建日期： 2006-4-19 17:14:45
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 17:14:45      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.io.Serializable;
import java.util.List;

import org.king.security.domain.Account;
import org.king.security.domain.Resource;
import org.king.security.domain.Role;
import org.king.security.exception.ResourceAlreadyExistException;
import org.king.framework.exception.BusinessException;
import org.king.security.exception.RoleAlreadyExistException;
import org.king.framework.service.Service;

/**
 * <p>
 * SecurityService.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * 
 * <p>
 * <a href="SecurityService.java.html"><i>查看源代码</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 * 
 */
public interface SecurityService extends Service {

	/**
	 * 初始化安全
	 * 
	 * @throws BusinessException
	 */
	public void initSecurity() throws BusinessException;

	/**
	 * 登录
	 * 
	 * @param name
	 * @param password
	 * @return
	 * @throws BusinessException
	 */
	public Account login(String name, String password) throws BusinessException;

	/**
	 * 改变帐户角色
	 * 
	 * @param accountId
	 * @param groupId
	 * @throws BusinessException
	 */
	public void changeAccountRole(Serializable accountId, Serializable roleId)
			throws BusinessException;

	// --------------------------------角色接口-------------
	/**
	 * 查找所有角色
	 * 
	 * @return
	 * @throws BusinessException
	 */
	public List findAllRole() throws BusinessException;

	/**
	 * 通过id查找角色
	 * 
	 * @param id
	 * @return
	 * @throws BusinessException
	 */
	public Role findRoleById(Serializable id) throws BusinessException;

	/**
	 * 保存角色
	 * 
	 * @param role
	 * @param resources
	 * @throws BusinessException
	 * @throws RoleExistException
	 */
	public void saveRole(Role role, String[] resources)
			throws BusinessException, RoleAlreadyExistException;

	/**
	 * 更新角色，增加或删除此角色的资源
	 * 
	 * @param group
	 * @param removeRight
	 * @param addRight
	 * @throws BusinessException
	 * @throws GroupExistException
	 */
	public void updateRole(Role role, String[] removeResource,
			String[] addResource) throws BusinessException;

	/**
	 * 批量删除角色
	 * 
	 * @param ids
	 * @throws BusinessException
	 */
	public void removeRole(Serializable[] ids) throws BusinessException;

	// --------------------------------资源接口------------------------
	/**
	 * 查找所有资源
	 * 
	 * @return
	 * @throws BusinessException
	 */
	public List findAllResource() throws BusinessException;

	/**
	 * 保存资源
	 * 
	 * @param resource
	 * @throws BusinessException
	 * @throws ResourceExistException
	 */
	public void saveResource(Resource resource) throws BusinessException,
			ResourceAlreadyExistException;

	/**
	 * 更新资源
	 * 
	 * @param resource
	 * @throws BusinessException
	 */
	public void updateResource(Resource resource) throws BusinessException;

	/**
	 * 批量更新资源
	 * 
	 * @param rights
	 * @throws BusinessException
	 */
	public void updateResource(Resource[] resources) throws BusinessException;

	/**
	 * 批量删除资源
	 * 
	 * @param ids
	 * @throws BusinessException
	 */
	public void deleteResource(Serializable[] ids) throws BusinessException;

	// -------------------------------------菜单接口----------------------------------
	
	
	/**
	 * 得到用户菜单
	 * 
	 * @param accountId
	 * @return
	 */
	public List getAccountMenus(String accountId) throws BusinessException;
	
	/**
	 * 得到角色菜单
	 * 
	 * @param roleId
	 * @return
	 */
	public List getRoleMenus(String roleId) throws BusinessException;

	/**
	 * 删除角色的所有菜单
	 * 
	 * @param roleId
	 */
	public void deleteRoleMenu(String roleId) throws BusinessException;

	/**
	 * 授权角色菜单
	 * 
	 * @param roleId
	 * @param menuList
	 */
	public void grantRoleMenus(String roleId, List menuList) throws BusinessException;
	
	/**
	 * 
	 * @param accountId
	 * @param currentRole
	 */
	public void grantAccountRoles(String accountId,String [] currentRole) throws BusinessException;
	
}
