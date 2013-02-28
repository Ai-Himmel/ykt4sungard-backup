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

import org.king.framework.exception.BusinessException;
import org.king.framework.service.Service;
import org.king.security.domain.TNetacc;
import org.king.security.domain.TOperator;
import org.king.security.domain.TShopacc;

import java.util.List;
import java.util.Map;

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
public interface SecurityService extends Service {

    /**
     * 初始化安全
     *
     * @throws BusinessException
     */
    public void initSecurity() throws BusinessException;


    // -------------------------------------菜单接口----------------------------------


    /**
     * 得到用户菜单
     *
     * @param accountId
     * @return
     */
    public List getAccountMenus(String accountId) throws BusinessException;

    /*
     * 检测激活码
     * @param account
     * @param accpwd
     * @param paypwd
     * @param activatecode
     * return 
     */
    public boolean actiCheckActivate(String account,String activatecode) throws BusinessException;
    /*
     * 激活账号
     * @param account
     * @param accpwd
     * @param paypwd
     * return 
     */
    public boolean activate(String account,String accpwd,String paypwd,String activatecode,String ip) throws BusinessException;


	/**
	 * 更新网络账户信息
	 * @param netacc
	 */
	public void updateTnetacc(TNetacc netacc);

	/**
	 * 获取网络账户信息
	 * @param accno
	 * @return
	 */
	public TNetacc getNetaccByAccno(String accno);

	/**
	 * 获取商户信息
	 * @param accno
	 * @return
	 */
	public TShopacc getShopaccByAccno(String accno);
	
	
	public List getacc(String xh,String pwd);


	/**
	 * 获取操作员信息
	 * @param operCode
	 * @return
	 */
	public TOperator getOperBycode(String operCode);
	
}
