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

import java.util.ArrayList;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;
import org.king.security.domain.TCardphytype;

/**
 * <p>
 * SecurityService.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * <p/>
 * <p>
 * <a href="SecurityService.java.html"><i>查看源代码</i></a>
 * </p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 */
public interface AccManageService extends Service {

	/*
     * 修改密码
     * @param account
     * @param accpwd
     * @param pwdtype
     * return 
     */
    public boolean changepwd(String account,String pwd,String pwdtype,String acctype) throws BusinessException;
    
    public boolean checkoldpwd(String account, String oldpwd, String pwdtype,String acctype);
    /*
     * 止付，解付
     * @param flag--设置止付--0，设置解付--1
     * @param accno--账号
     * return true--设置成功，false--设置失败
     */
    public boolean setStopPay(String flag,String accno);
    
    public void getPayRecordList(DBPaginatedList page,Object[] conditions);

    /**
     * 根据查询条件获取电子账户列表
     * @param page
     * @param conditions
     */
	public void getNetaccList(DBPaginatedList page, Object[] conditions);
	
	public List getAvailCardPhytype();
    
    
}
