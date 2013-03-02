/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.impl.AccountServiceImpl.java
 * 创建日期： 2006-4-20 10:45:37
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-20 10:45:37      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service.impl;

import java.io.Serializable;
import java.sql.Types;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.king.check.domain.Toperlimit;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.security.dao.AccountDAO;
import org.king.security.domain.Account;
import org.king.security.exception.AccountAlreadyExistException;
import org.king.security.service.AccountService;

/**
 * <p> AccountServiceImpl.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="AccountServiceImpl.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */
public class AccountServiceImpl extends BaseService implements AccountService {

	private AccountDAO accountDAO;
	
	
	
	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#findAccountById(java.io.Serializable)
	 */
	public Account findAccountById(Serializable id) {
		return accountDAO.get(id);
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#findAccountByName(java.lang.String)
	 */
	public Account findAccountByName(String name) throws BusinessException {
		return accountDAO.findAccountByName(name);
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#findAllAccount()
	 */
	public List findAllAccount() throws BusinessException {
		return accountDAO.getAll();
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#findAccount(java.lang.String[])
	 */
	public List findAccount(String[] args) throws BusinessException {
    	String number = args[0];
    	String personName = args[1];
    	String page = args[2];
    	//String sex = args[3];
    	List entitys = null;
        
    	String hqlStr = "from Account a where 1=1 ";
    	hqlStr += (StringUtils.isNotEmpty(number)?" and a.name like ?" : "");
    	
    	hqlStr += (StringUtils.isNotEmpty(personName)?" and a.person.personName like ?" : "");
    	
    	//hqlStr += (StringUtils.isNotEmpty(sex)?" and a.person.sex =?" : "");
    	
    	MyQuery myQuery = new MyQuery();

        if (StringUtils.isNotEmpty(number)) {
        	myQuery.addPara("%" + number + "%", Types.VARCHAR);
        }

        if (StringUtils.isNotEmpty(personName)) {
        	myQuery.addPara("%" + personName + "%", Types.VARCHAR);
        }
        
        if (StringUtils.isNumeric(page)) {
        	myQuery.setPageStartNo(Integer.parseInt(page));
        }else {
        	myQuery.setPageStartNo(0);
        }
        /*
        if ("1".equals(sex)){
        	hqlStr += (" and a.person.sex =1");
        }else{
        	hqlStr += (" and a.person.sex =0 or a.person.sex is null");
        }
        */
        myQuery.setOrderby(" order by a.name");
        myQuery.setQueryString(hqlStr);

        myQuery.setOffset(true);
        entitys = accountDAO.find(myQuery);
        return entitys;
	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#saveAccount(org.king.security.domain.Account)
	 */
	public void saveAccount(Account account) throws BusinessException,
			AccountAlreadyExistException {
		
		accountDAO.save(account);

	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#updateAccount(org.king.security.domain.Account)
	 */
	public void updateAccount(Account account) throws BusinessException {
		
		accountDAO.update(account);

	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#deleteAccount(java.io.Serializable)
	 */
	public void deleteAccount(Serializable id) throws BusinessException {
		if (id == null) {
            throw new BusinessException("account can't be null");
        }
		accountDAO.delete(findAccountById(id));

	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#deleteAccount(java.io.Serializable[])
	 */
	public void deleteAccount(Serializable[] ids) throws BusinessException {
		if (ids == null) {
            throw new BusinessException("accounts can't be null");
        }

        for (int i = 0, n = ids.length; i < n; i++) {
        	deleteAccount(ids[i]);
        }


	}

	/* (non-Javadoc)
	 * @see org.king.security.service.AccountService#getAccountCount(java.lang.String[])
	 */
	public Integer getAccountCount(String[] args) {
	   	String number = args[0];
    	String personName = args[1];
    	//String sex = args[3];
    	List countList = null;
        Integer accountCount = new Integer("0");
    	String hqlStr = "select count(*) from Account a where 1=1 ";
    	hqlStr += (StringUtils.isNotEmpty(number)?" and a.name like ?" : "");
    	
    	hqlStr += (StringUtils.isNotEmpty(personName)?" and a.person.personName like ?" : "");
    	
        //myQuery.addPara(sex,Types.VARCHAR);
    	/*
        if ("1".equals(sex)){
        	hqlStr += (" and a.person.sex =1");
        }else{
        	hqlStr += (" and a.person.sex =0 or a.person.sex is null");
        }
    	*/
    	
    	MyQuery myQuery = new MyQuery();

        if (StringUtils.isNotEmpty(number)) {
        	myQuery.addPara("%" + number + "%", Types.VARCHAR);
        }

        if (StringUtils.isNotEmpty(personName)) {
        	myQuery.addPara("%" + personName + "%", Types.VARCHAR);
        }
        
        myQuery.setQueryString(hqlStr);
        
        countList = accountDAO.find(myQuery);
        if(countList!=null){
        	accountCount = (Integer)countList.get(0);
        }
        return accountCount;
	}

	public void saveAccountLimit(Toperlimit operlimit) throws BusinessException {
		accountDAO.saveAccountLimit(operlimit);
		
	}

	public void updateAccountLimit(Toperlimit operlimit) throws BusinessException {
		accountDAO.updateAccountLimit(operlimit);
		
	}

	public List getAccountLimit(String deptId, String operId) {
		return accountDAO.getAccountLimit(deptId,operId);
	}

	public void deleteAccountLimit(String accountId) {
		List accIds = accountDAO.getAccountLimit(accountId);
		if (accIds.size()>0){
			Iterator iter = accIds.iterator();
			while (iter.hasNext()){
				Toperlimit operLimit = (Toperlimit)iter.next();
				//String operId = operLimit.getId().getOperId();
				//String deptId = operLimit.getId().getDeptId();
				//Toperlimit operLimitD = new Toperlimit();
				//ToperlimitId operLimitIdD = new ToperlimitId();
				//operLimitIdD.setDeptId(deptId);
				//operLimitIdD.setOperId(operId);
				//operLimitD.setId(operLimitIdD);
				accountDAO.deleteAccountLimit(operLimit);
			}
		}
		
	}
	
	public void deleteAccountLimitIds(String[] ids){
		for (int i=0;i<ids.length;i++){
			deleteAccountLimit(ids[i]);			
		}
	}

	public void deleteAccountRole(String[] ids) {
		// TODO Auto-generated method stub
		
	}

	public List findAccountRole(String accId, String roleId) {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	public void saveAccountRole(AccRole accrole) {
		
		
	}

	public void updateAccountRole(AccRole accrole) {
		
		
	}
**/
	
}
