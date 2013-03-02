/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    DeptServiceImpl.java
 * 创建日期： 2007-6-5 下午02:32:32
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-5 下午02:32:32     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service.impl;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.king.classmanage.service.ManagerService;
import org.king.common.dao.AllDAO;
import org.king.quarters.domain.TabSsManager;
import org.king.quarters.service.IManagerService;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.domain.Role;
import org.king.security.service.AccountService;
import org.king.security.service.SecurityService;

public class ManagerServiceImpl   implements IManagerService{

	private AllDAO allDAO;
	private SecurityService securityService;
	private AccountService accountService; 
	private ManagerService managerService;
	public void setManagerService(ManagerService managerService) {
		this.managerService = managerService;
	}
	public void setSecurityService(SecurityService securityService) {
		this.securityService = securityService;
	}
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}
	public boolean addOrUpdateDept(TabSsManager manager) {
		boolean res = false;
		if(manager == null) return false;
		
		if (manager.getId() == null){
			
			List l = allDAO.getHibernateTemplate().findByNamedParam("from TabSsManager m where  m.stuNo=:stuNo","stuNo",manager.getStuNo());
			if (l != null && l.size() >0) return false;
			//创建用户并赋予"宿舍资源管理"权限
			allDAO.getHibernateTemplate().save(manager);
			try{
			//保存用户
			Account account = accountService.findAccountByName(manager.getStuNo());
			String roleId = managerService.getRoleidByName("宿舍资源管理");
			List roleList = new ArrayList();
			roleList.add(roleId);
			if (account != null) {
				Iterator it = account.getRoles().iterator();
				while (it.hasNext()){
					Role r = (Role)it.next();
					roleList.add(r.getId());
				}
				
			}
			else {
				account = new Account();
				Person person = new Person();
				person.setPersonCode(manager.getStuNo());
				person.setPersonName(manager.getName());
				person.setPersonType("2");
				person.setSex(manager.getSex().trim());
				
				account.setName(manager.getStuNo());
				account.setEnabled("0");
				account.setPerson(person);
			}
			
			if (account != null && account.getId() != null){
				accountService.updateAccount(account);
			}
			else{
				accountService.saveAccount(account);
			}
			
			
			
			String[] roleArr =  new String[roleList.size()];
			roleList.toArray(roleArr);
			securityService.grantAccountRoles(account.getId(),roleArr);
			res = true;
			}catch(Throwable e){
				
				throw new RuntimeException(e.getMessage());
				
			}
		}
		else {
			//更新信息
			TabSsManager temp  = getManager(manager.getId());
			temp.setContact(manager.getContact());
			temp.setInOffice(manager.getInOffice());
			temp.setRemark(manager.getRemark());
			temp.setTabSsDept(manager.getTabSsDept());
			allDAO.getHibernateTemplate().saveOrUpdate(temp);
			res = true;
		}
		
		return res;
	}
	public TabSsManager getManager(String managerId) {
		if(managerId == null) return null;
		TabSsManager m = (TabSsManager)allDAO.getHibernateTemplate().get(TabSsManager.class, managerId);
		return m;
	}
	public List getManagers() {
		return allDAO.getHibernateTemplate().find("select new Map(m.id as id,m.name as name," +
				" m.stuNo as stuNo,m.sex as sex,m.contact as contact," +
				" m.tabSsDept.name as deptName,m.remark as remark,m.inOffice as inOffice ) " +
				" from TabSsManager m");
	}
	public void setAccountService(AccountService accountService) {
		this.accountService = accountService;
	}

	

}
