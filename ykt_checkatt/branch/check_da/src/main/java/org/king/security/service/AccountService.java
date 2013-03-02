/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.framework.service.AccountService.java
 * �������ڣ� 2006-4-18 14:06:10
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-18 14:06:10      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.io.Serializable;
import java.util.List;

import org.king.security.domain.Account;
import org.king.security.exception.AccountAlreadyExistException;
import org.king.check.domain.Toperlimit;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;

/**
 * <p> AccountService.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="AccountService.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-18
 * 
 *
 */
public interface AccountService extends Service{

	/**
	 * ͨ��id�����ʻ�
	 * @param id
	 * @return
	 */
	public Account findAccountById(Serializable id);
	
	/**
	 * ͨ���ʻ����õ��ʻ�
	 * @param name
	 * @return
	 * @throws BusinessException
	 */
	public Account findAccountByName(String name) throws BusinessException;
	
	/**
	 * �õ������ʻ�
	 * @return
	 * @throws BusinessException
	 */
	public List findAllAccount() throws BusinessException;
	
	/**
	 * ��ͬ��ѯ������ѯ�ʻ�
	 * @param args
	 * @return
	 * @throws BusinessException
	 */
	public List findAccount(String[] args) throws BusinessException;
	
	/**
	 * �����ʻ�
	 * @param account
	 * @throws BusinessException
	 * @throws AccountAlreadyExistException
	 */
	public void saveAccount(Account account) throws BusinessException,AccountAlreadyExistException;
	
	/**
	 * �����ʻ�
	 * @param account
	 * @throws BusinessException
	 */
	public void updateAccount(Account account) throws BusinessException;

	/**
	 * ɾ���ʻ�
	 * @param id
	 * @throws BusinessException
	 */
	public void deleteAccount(Serializable id) throws BusinessException;
	
	/**
	 * ����ɾ���ʻ�
	 * @param ids
	 * @throws BusinessException
	 */
	public void deleteAccount(Serializable[] ids) throws BusinessException;
	
    /**
     * �õ��ʻ���
     * @param args
     * @return
     */
	public Integer getAccountCount(final String[] args);
	
	/**
	 * �����û�Ȩ����Ϣ
	 * @param operlimit
	 * @throws BusinessException
	 */
	public void saveAccountLimit(Toperlimit operlimit)throws BusinessException;
	
	
	/**
	 * �����û�Ȩ����Ϣ
	 * @param operlimit
	 * @throws BusinessException
	 */
	public void updateAccountLimit(Toperlimit operlimit)throws BusinessException;
	
	
	/**
	 * ���ݲ��ű�źͲ���Ա���ȡ��Ȩ����Ϣ
	 * @param deptId
	 * @param operId
	 * @return
	 */
	public List getAccountLimit(String deptId,String operId); 
	
	
	/**
	 * ɾ��Ȩ����Ϣ
	 * @param accountId
	 */
	public void deleteAccountLimit(String accountId);
	
	/**
	 * ����ɾ��Ȩ����Ϣ
	 * @param ids
	 */
	public void deleteAccountLimitIds(String[] ids);
	
	/**
	 * ɾ���û���ɫ
	 * @param ids
	 */
	public void deleteAccountRole(String[] ids);
	
	/**
	 * �����û���ɫ��Ϣ
	 * @param accrole
	 */
	//public void saveAccountRole(AccRole accrole);
	
	/**
	 * �����û���ɫ��Ϣ
	 */
	//public void updateAccountRole(AccRole accrole);
	
	/**
	 * �����û���ɫ��Ϣ
	 * @param accId
	 * @param roleId
	 * @return
	 */
	public List findAccountRole(String accId,String roleId);

    public boolean isTeacher(Account account);
}
