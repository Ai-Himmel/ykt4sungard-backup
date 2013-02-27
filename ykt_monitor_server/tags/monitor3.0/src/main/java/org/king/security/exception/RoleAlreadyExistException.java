/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.exception.RoleAlreadyExistException.java
 * 创建日期： 2006-4-19 22:10:13
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 22:10:13      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> RoleAlreadyExistException.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="RoleAlreadyExistException.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 *
 */
public class RoleAlreadyExistException extends BaseException {

	public RoleAlreadyExistException() {
		super();
	}

	public RoleAlreadyExistException(String s, Throwable e) {
		super(s, e);
	}

	public RoleAlreadyExistException(String s) {
		super(s);
	}

	public RoleAlreadyExistException(Throwable e) {
		super(e);
	}

}
