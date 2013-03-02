/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.SecurityService.java
 * �������ڣ� 2006-4-19 17:14:45
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-19 17:14:45      ljf        �����ļ���ʵ�ֻ�������
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
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="SecurityService.java.html"><i>�鿴Դ����</i></a>
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
	 * ��ʼ����ȫ
	 * 
	 * @throws BusinessException
	 */
	public void initSecurity() throws BusinessException;

	/**
	 * ��¼
	 * 
	 * @param name
	 * @param password
	 * @return
	 * @throws BusinessException
	 */
	public Account login(String name, String password) throws BusinessException;

	/**
	 * �ı��ʻ���ɫ
	 * 
	 * @param accountId
	 * @param groupId
	 * @throws BusinessException
	 */
	public void changeAccountRole(Serializable accountId, Serializable roleId)
			throws BusinessException;

	// --------------------------------��ɫ�ӿ�-------------
	/**
	 * �������н�ɫ
	 * 
	 * @return
	 * @throws BusinessException
	 */
	public List findAllRole() throws BusinessException;

	/**
	 * ͨ��id���ҽ�ɫ
	 * 
	 * @param id
	 * @return
	 * @throws BusinessException
	 */
	public Role findRoleById(Serializable id) throws BusinessException;

	/**
	 * �����ɫ
	 * 
	 * @param role
	 * @param resources
	 * @throws BusinessException
	 * @throws RoleExistException
	 */
	public void saveRole(Role role, String[] resources)
			throws BusinessException, RoleAlreadyExistException;

	/**
	 * ���½�ɫ�����ӻ�ɾ���˽�ɫ����Դ
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
	 * ����ɾ����ɫ
	 * 
	 * @param ids
	 * @throws BusinessException
	 */
	public void removeRole(Serializable[] ids) throws BusinessException;

	// --------------------------------��Դ�ӿ�------------------------
	/**
	 * ����������Դ
	 * 
	 * @return
	 * @throws BusinessException
	 */
	public List findAllResource() throws BusinessException;

	/**
	 * ������Դ
	 * 
	 * @param resource
	 * @throws BusinessException
	 * @throws ResourceExistException
	 */
	public void saveResource(Resource resource) throws BusinessException,
			ResourceAlreadyExistException;

	/**
	 * ������Դ
	 * 
	 * @param resource
	 * @throws BusinessException
	 */
	public void updateResource(Resource resource) throws BusinessException;

	/**
	 * ����������Դ
	 * 
	 * @param rights
	 * @throws BusinessException
	 */
	public void updateResource(Resource[] resources) throws BusinessException;

	/**
	 * ����ɾ����Դ
	 * 
	 * @param ids
	 * @throws BusinessException
	 */
	public void deleteResource(Serializable[] ids) throws BusinessException;

	// -------------------------------------�˵��ӿ�----------------------------------
	
	
	/**
	 * �õ��û��˵�
	 * 
	 * @param accountId
	 * @return
	 */
	public List getAccountMenus(String accountId) throws BusinessException;
	
	/**
	 * �õ���ɫ�˵�
	 * 
	 * @param roleId
	 * @return
	 */
	public List getRoleMenus(String roleId) throws BusinessException;

	/**
	 * ɾ����ɫ�����в˵�
	 * 
	 * @param roleId
	 */
	public void deleteRoleMenu(String roleId) throws BusinessException;

	/**
	 * ��Ȩ��ɫ�˵�
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
