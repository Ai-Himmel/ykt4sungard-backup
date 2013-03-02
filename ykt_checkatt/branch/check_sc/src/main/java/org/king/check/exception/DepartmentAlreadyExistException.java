/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.exception.CatalogAlreadyExistException.java
 * 创建日期： 2006-6-16 11:00:26
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-16 11:00:26      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.check.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> CatalogAlreadyExistException.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="CatalogAlreadyExistException.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-16
 * 
 *
 */
public class DepartmentAlreadyExistException extends BaseException {

	/**
	 *  
	 */
	public DepartmentAlreadyExistException() {
		super();
	}

	/**
	 * @param s
	 */
	public DepartmentAlreadyExistException(String s) {
		super(s);
	}

	/**
	 * @param s
	 * @param e
	 */
	public DepartmentAlreadyExistException(String s, Throwable e) {
		super(s, e);
	}

	/**
	 * @param e
	 */
	public DepartmentAlreadyExistException(Throwable e) {
		super(e);
	}
}
