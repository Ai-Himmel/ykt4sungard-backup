/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.service.impl.AccountServiceImpl.java
 * �������ڣ� 2006-4-20 10:45:37
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-20 10:45:37      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 *
 */
package org.king.security.service.impl;

import org.apache.commons.lang.StringUtils;
import org.king.check.Constants;
import org.king.check.domain.Toperlimit;
import org.king.framework.dao.MyQuery;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.impl.BaseService;
import org.king.security.dao.AccountDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Role;
import org.king.security.exception.AccountAlreadyExistException;
import org.king.security.service.AccountService;

import java.io.Serializable;
import java.sql.Types;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <p> AccountServiceImpl.java </p>
 * <p> {����˵��} </p>
 * <p/>
 * <p><a href="AccountServiceImpl.java.html"><i>�鿴Դ����</i></a></p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
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
        String stuempno = args[0];
        String custname = args[1];
        String deptcode = args[2];
        String page = args[3];
        //String sex = args[3];
        List entitys = null;

        String hqlStr = "select new Map(a.id as id,a.person.stuempno as stuempno,a.person.custname as custname,d.deptname as deptname) from Account a,TDept d where a.person.deptcode=d.deptcode and a.enabled='1' and a.person.custtype<>9 ";
        hqlStr += (StringUtils.isNotEmpty(stuempno) ? " and a.person.stuempno like ?" : "");

        hqlStr += (StringUtils.isNotEmpty(custname) ? " and a.person.custname like ?" : "");
        hqlStr += (StringUtils.isNotEmpty(deptcode) ? " and a.person.deptcode= ?" : "");
        //hqlStr += (StringUtils.isNotEmpty(sex)?" and a.person.sex =?" : "");

        MyQuery myQuery = new MyQuery();

        if (StringUtils.isNotEmpty(stuempno)) {
            myQuery.addPara("%" + stuempno.trim() + "%", Types.VARCHAR);
        }

        if (StringUtils.isNotEmpty(custname)) {
            myQuery.addPara("%" + custname.trim() + "%", Types.VARCHAR);
        }
        if (StringUtils.isNotEmpty(deptcode)) {
            myQuery.addPara(deptcode.trim(), Types.VARCHAR);
        }

        if (StringUtils.isNumeric(page)) {
            myQuery.setPageStartNo(Integer.parseInt(page));
        } else {
            myQuery.setPageStartNo(0);
        }
        /*
        if ("1".equals(sex)){
        	hqlStr += (" and a.person.sex =1");
        }else{
        	hqlStr += (" and a.person.sex =0 or a.person.sex is null");
        }
        */
        myQuery.setOrderby(" order by a.person.stuempno");
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
        String stuempno = args[0];
        String custname = args[1];
        String deptcode = args[2];
        String page = args[3];
        //String sex = args[3];
        List countList = null;
        Integer accountCount = new Integer("0");
        String hqlStr = "select count(*) from Account a,TDept d where a.person.deptcode=d.deptcode and a.enabled='1' and a.person.custtype=1 ";
        hqlStr += (StringUtils.isNotEmpty(stuempno) ? " and a.person.stuempno like ?" : "");

        hqlStr += (StringUtils.isNotEmpty(custname) ? " and a.person.custname like ?" : "");
        hqlStr += (StringUtils.isNotEmpty(deptcode) ? " and a.person.deptcode= ?" : "");

        //myQuery.addPara(sex,Types.VARCHAR);
        /*
          if ("1".equals(sex)){
              hqlStr += (" and a.person.sex =1");
          }else{
              hqlStr += (" and a.person.sex =0 or a.person.sex is null");
          }
          */

        MyQuery myQuery = new MyQuery();

        if (StringUtils.isNotEmpty(stuempno)) {
            myQuery.addPara("%" + stuempno + "%", Types.VARCHAR);
        }

        if (StringUtils.isNotEmpty(custname)) {
            myQuery.addPara("%" + custname + "%", Types.VARCHAR);
        }
        if (StringUtils.isNotEmpty(deptcode)) {
            myQuery.addPara(deptcode.trim(), Types.VARCHAR);
        }

        myQuery.setQueryString(hqlStr);

        countList = accountDAO.find(myQuery);
        if (countList != null) {
            accountCount = ((Long) countList.get(0)).intValue();
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
        return accountDAO.getAccountLimit(deptId, operId);
    }

    public void deleteAccountLimit(String accountId) {
        List accIds = accountDAO.getAccountLimit(accountId);
        if (accIds.size() > 0) {
            Iterator iter = accIds.iterator();
            while (iter.hasNext()) {
                Toperlimit operLimit = (Toperlimit) iter.next();
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

    public void deleteAccountLimitIds(String[] ids) {
        for (int i = 0; i < ids.length; i++) {
            deleteAccountLimit(ids[i]);
        }
    }

    public void deleteAccountRole(String[] ids) {
        // TODO Auto-generated method stub

    }

    public List findAccountRole(String accId, String roleId) {
        return accountDAO.findAccountRole(accId, roleId);
    }

    /**
     * �ж�accountId��Ӧ��person�Ƿ�Ϊ�ο���ʦ�����жϸ��˻��Ƿ��Ӧ�ο���ʦ��ɫ
     *
     * @param account
     * @return
     */
    public boolean isTeacher(Account account) {
        Set roles = account.getRoles();
        for (Iterator iterator = roles.iterator(); iterator.hasNext();) {
            Role role = (Role) iterator.next();
            if (Constants.ROLE_TYPE_TEACHER.equals(role.getType())) {
                return true;
            }
        }
        return false;
    }

    /**
     public void saveAccountRole(AccRole accrole) {


     }

     public void updateAccountRole(AccRole accrole) {


     }
     **/

}
