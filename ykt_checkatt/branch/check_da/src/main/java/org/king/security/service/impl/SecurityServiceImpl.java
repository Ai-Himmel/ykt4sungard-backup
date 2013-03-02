/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.impl.SecurityServiceImpl.java
 * 创建日期： 2006-4-19 22:46:46
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 22:46:46      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service.impl;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Iterator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.framework.util.MyUtils;

import org.king.security.dao.AccountDAO;
import org.king.security.dao.MenuDAO;
import org.king.security.dao.ResourceDAO;
import org.king.security.dao.RoleDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Menu;
import org.king.security.domain.ProtectedResource;
import org.king.security.domain.Resource;
import org.king.security.domain.Role;
import org.king.security.exception.ResourceAlreadyExistException;
import org.king.security.exception.RoleAlreadyExistException;
import org.king.security.service.Acl;
import org.king.security.service.SecurityService;
import org.king.security.util.MenuComparator;
import org.king.utils.PasswordUtil;
import org.springframework.orm.hibernate3.LocalSessionFactoryBean;

/**
 * <p>
 * SecurityServiceImpl.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * 
 * <p>
 * <a href="SecurityServiceImpl.java.html"><i>查看源代码</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 * 
 */
public class SecurityServiceImpl extends BaseService implements SecurityService {

	private static Log log = LogFactory.getLog(SecurityServiceImpl.class);
	
	private AccountDAO accountDAO;
	
	
	private Acl acl;
	
	
	private RoleDAO roleDAO;
	
	private MenuDAO menuDAO;
	
	private ResourceDAO resourceDAO;

	private LocalSessionFactoryBean lsfb;
	
	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}

	public void setResourceDAO(ResourceDAO resourceDAO) {
		this.resourceDAO = resourceDAO;
	}

	public void setRoleDAO(RoleDAO roleDAO) {
		this.roleDAO = roleDAO;
	}
	
	
	public void setMenuDAO(MenuDAO menuDAO) {
		this.menuDAO = menuDAO;
	}

	public void setAcl(Acl acl) {
		this.acl = acl;
	}

	public void setLsfb(LocalSessionFactoryBean lsfb) {
		this.lsfb = lsfb;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#initSecurity()
	 */
	public void initSecurity() throws BusinessException {
		 log.info("*****************init security begin!****************");
		 acl.setProtectedResourcesMap(loadRights());
		 log.info("*****************init security success!***************");
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#login(java.lang.String,
	 *      java.lang.String)
	 */
    public Account login(String name, String password) throws BusinessException {
        Account account = findAccountByName(name);
        String encodedPassword;
        try {
            encodedPassword = PasswordUtil.DESEnc(password);
        } catch (Exception e) {
            throw new BusinessException("can't encode password");
        }
        if ((account == null) || !account.getPassword().equals(encodedPassword)) {
            //todo 暂时注释掉验证密码
            throw new BusinessException("password not match");
        }
        return account;
    }

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#changeAccountRole(java.io.Serializable,
	 *      java.io.Serializable)
	 */
	public void changeAccountRole(Serializable accountId, Serializable roleId)
			throws BusinessException {
		// TODO Auto-generated method stub

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#findAllRole()
	 */
	public List findAllRole() throws BusinessException {
		return roleDAO.getAll();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#findRoleById(java.io.Serializable)
	 */
	public Role findRoleById(Serializable id) throws BusinessException {
		return roleDAO.get(id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#saveRole(org.king.security.domain.Role,
	 *      java.lang.String[])
	 */
	public void saveRole(Role role, String[] resources)
			throws BusinessException, RoleAlreadyExistException {
        Set resourceset = new HashSet();
        Resource resource;

        for (int i = 0, n = resources.length; i < n; i++) {
        	resource = (Resource)resourceDAO.get(resources[i]);

            if (resource != null) {
            	//resource.get().add(role);
            	resourceset.add(resource);
                //rightDAO.updateRight(right);
            }
        }

        role.setResources(resourceset);
        roleDAO.save(role);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#updateRole(org.king.security.domain.Role,
	 *      java.lang.String[], java.lang.String[])
	 */
	public void updateRole(Role role, String[] removeResource,
			String[] addResource) throws BusinessException {
		
		Role entity = roleDAO.get(role.getId());
		Resource resource = null;
        entity.setName(role.getName());
        entity.setRemark(role.getRemark());
        entity.setType(role.getType());
		
        //remove right
		if (!MyUtils.isBlank(removeResource)) {
            for (int i = 0, n = removeResource.length; i < n; i++) {
                resource = resourceDAO.get(removeResource[i]);
                entity.getResources().remove(resource);
            }
        }
		
		//add right
		if (!MyUtils.isBlank(addResource)) {
            for (int i = 0, n = addResource.length; i < n; i++) {
                resource = resourceDAO.get(addResource[i]);
                entity.getResources().add(resource);
            }
        }
		
		roleDAO.update(entity);
		

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#removeRole(java.io.Serializable[])
	 */
	public void removeRole(Serializable[] ids) throws BusinessException {
		if (MyUtils.isBlank(ids)) {
            throw new BusinessException("roles can't be null");
        }
		
		for(int i=0;i<ids.length;i++){
		    roleDAO.delete((Role)roleDAO.get(ids[i]));
		}

	}

	
	public void removeRole(Serializable id) throws BusinessException {
		roleDAO.delete((Role)roleDAO.get(id));
		
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#findAllResource()
	 */
	public List findAllResource() throws BusinessException {
		return resourceDAO.getAll();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#saveResource(org.king.security.domain.Resource)
	 */
	public void saveResource(Resource resource) throws BusinessException,
			ResourceAlreadyExistException {
		resourceDAO.save(resource);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#updateResource(org.king.security.domain.Resource)
	 */
	public void updateResource(Resource resource) throws BusinessException {
		resourceDAO.update(resource);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#updateResource(org.king.security.domain.Resource[])
	 */
	public void updateResource(Resource[] resources) throws BusinessException {
		if (MyUtils.isBlank(resources)) {
            return;
        }
		
		  for (int i = 0, n = resources.length; i < n; i++) {
			  updateResource(resources[i]);
	        }

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#deleteResource(java.io.Serializable[])
	 */
	public void deleteResource(Serializable[] ids) throws BusinessException {
		if (MyUtils.isBlank(ids)) {
            return;
        }
		
		for(int i=0;i<ids.length;i++){
			resourceDAO.delete(resourceDAO.get(ids[i]));
		}
		
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#getRoleMenus(java.lang.String)
	 */
	public List getRoleMenus(String roleId) throws BusinessException{
		Role role = roleDAO.get(roleId);
		ArrayList roleMenus = new ArrayList();
		Set menus = role.getMenus();
		
		if(menus!=null){
		   for(Iterator iterator =menus.iterator();iterator.hasNext(); ){
			   Menu menu = (Menu)iterator.next();
			   roleMenus.add(menu);
		   }
			
		}
		return roleMenus;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#deleteRoleMenu(java.lang.String)
	 */
	public void deleteRoleMenu(String roleId) throws BusinessException{
		// TODO Auto-generated method stub

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.security.service.SecurityService#grantRoleMenus(java.lang.String,
	 *      java.util.List)
	 */
	public void grantRoleMenus(String roleId, List menuList) throws BusinessException{
		Role role = roleDAO.get(roleId);
		Set menus = new HashSet();
		
		if(role != null){
			
			if(menuList != null){
				for(int i=0;i<menuList.size();i++){
					Menu menu = (Menu)menuList.get(i);
					menu = menuDAO.get(menu.getId());
					menus.add(menu);
				}
			}
			role.setMenus(menus);
			roleDAO.update(role);
		}

	}
	
    public Account findAccountByName(String name) throws BusinessException {
	    if (MyUtils.isBlank(name)) {
	        return null;
	    }
	
	    Account account = null;
	    account = accountDAO.findAccountByName(name);
	    return account;
}

	public List getAccountMenus(String accountId) throws BusinessException {
		List menus = new ArrayList();
		Set roleMenus = null;
		Account account = accountDAO.get(accountId);
		Set accountRoles  = account.getRoles();
		if(accountRoles != null){
			for(Iterator iterator = accountRoles.iterator();iterator.hasNext();){
				Role role = (Role)iterator.next();
				roleMenus = role.getMenus();
				if(roleMenus!=null){
					for(Iterator ite = roleMenus.iterator();ite.hasNext();){
						Menu menu = (Menu)ite.next();
						if(!menus.contains(menu)){
							menus.add(menu);
						}
					}
				}
			 }
		}
		
		if(menus!=null){
			Collections.sort(menus,new MenuComparator());
		}
		return menus;
	}

	
	public void grantAccountRoles(String accountId, String[] currentRole) throws BusinessException {
		Account account = accountDAO.get(accountId);
		Set currentAccountRole = new HashSet();
		if(currentRole!=null) {
			for(int i=0;i<currentRole.length;i++){
				currentAccountRole.add((Role)roleDAO.get(currentRole[i]));
			}
		}
		account.setRoles(currentAccountRole);
		accountDAO.update(account);
	}


    private Map loadRights() {
        Map rightMap = new HashMap();
        List resources = null;
        
        resources = resourceDAO.getAll();


        Resource resource;
        Set roles;
        Role role;
        Collection protectedResources = new ArrayList();

        for (int i = 0, n = resources.size(); i < n; i++) {
            resource = (Resource)resources.get(i);
            roles = resource.getRoles();

            Map roleMap = new HashMap();

            if (!MyUtils.isBlank(roles)) {
                for (Iterator it = roles.iterator(); it.hasNext();) {
                    String roleId = ((Role) it.next()).getId().trim();
                    roleMap.put(roleId, roleId);
                }
            }

            protectedResources.add(new ProtectedResource(resource.getCode(),
                    resource.getName(), resource.getUrl()));
            rightMap.put(resource.getUrl(), roleMap);
        }

        rightMap.put("protectedResources", protectedResources);

        return rightMap;
    }


}
