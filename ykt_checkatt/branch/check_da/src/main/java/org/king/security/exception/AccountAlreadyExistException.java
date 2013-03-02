/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.framework.exception.AccountAlreadyExistException.java
 * 创建日期： 2006-4-18 15:01:20
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-18 15:01:20      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> AccountAlreadyExistException.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="AccountAlreadyExistException.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-18
 * 
 *
 */
public class AccountAlreadyExistException extends BaseException {

	/**
	 *  
	 */
	public AccountAlreadyExistException() {
		super();
	}

	/**
	 * @param s
	 */
	public AccountAlreadyExistException(String s) {
		super(s);
	}

	/**
	 * @param s
	 * @param e
	 */
	public AccountAlreadyExistException(String s, Throwable e) {
		super(s, e);
	}

	/**
	 * @param e
	 */
	public AccountAlreadyExistException(Throwable e) {
		super(e);
	}
}
