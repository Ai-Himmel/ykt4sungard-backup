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
import java.util.Date;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.framework.util.MyUtils;
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
    	String roleId = args[3];
    	List entitys = null;
        
    	String hqlStr = "from Account a where 1=1 ";
    	hqlStr += (StringUtils.isNotEmpty(number)?" and a.name like ?" : "");
    	
    	hqlStr += (StringUtils.isNotEmpty(personName)?" and a.person.personName like ?" : "");
    	
    	MyQuery myQuery = new MyQuery();

        if (StringUtils.isNotEmpty(number)) {
        	myQuery.addPara("%" + number.trim() + "%", Types.VARCHAR);
        }

        if (StringUtils.isNotEmpty(personName)) {
        	myQuery.addPara("%" + personName.trim() + "%", Types.VARCHAR);
        }
        if (StringUtils.isNotEmpty(roleId)) {
        	 hqlStr += " and a.roles.id=?";
        	myQuery.addPara(roleId, Types.VARCHAR);
        }
        
        if (StringUtils.isNumeric(page)) {
        	myQuery.setPageStartNo(Integer.parseInt(page));
        }else {
        	myQuery.setPageStartNo(0);
        }
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
		
		if(account==null){
			throw new BusinessException("account can not be null");
		}
		
		if((Account)accountDAO.findAccountByName(account.getName())!=null){
			throw new AccountAlreadyExistException("account already exist!");
		}
		
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
    	String roleId = args[3];
    	List countList = null;
        Integer accountCount = new Integer("0");
    	String hqlStr = "select count(*) from Account a where 1=1 ";
    	hqlStr += (StringUtils.isNotEmpty(number)?" and a.name like ?" : "");
    	
    	hqlStr += (StringUtils.isNotEmpty(personName)?" and a.person.personName like ?" : "");
    	
    	MyQuery myQuery = new MyQuery();

        if (StringUtils.isNotEmpty(number)) {
        	myQuery.addPara("%" + number.trim() + "%", Types.VARCHAR);
        }

        if (StringUtils.isNotEmpty(personName)) {
        	myQuery.addPara("%" + personName.trim() + "%", Types.VARCHAR);
        }
        if (StringUtils.isNotEmpty(roleId)) {
        	hqlStr+=" and a.roles.id=?";
        	myQuery.addPara(roleId, Types.VARCHAR);
        }
        myQuery.setQueryString(hqlStr);
        
        countList = accountDAO.find(myQuery);
        if(countList!=null){
        	accountCount = (Integer)countList.get(0);
        }
        return accountCount;
	}

}
