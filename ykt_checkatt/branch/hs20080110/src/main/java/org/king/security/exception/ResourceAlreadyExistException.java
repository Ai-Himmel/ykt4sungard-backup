/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.exception.ResourceAlreadyExistException.java
 * 创建日期： 2006-4-19 22:15:03
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 22:15:03      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> ResourceAlreadyExistException.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ResourceAlreadyExistException.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 *
 */
public class ResourceAlreadyExistException extends BaseException {

	public ResourceAlreadyExistException() {
		super();
	}

	public ResourceAlreadyExistException(String s, Throwable e) {
		super(s, e);
	}

	public ResourceAlreadyExistException(String s) {
		super(s);
	}

	public ResourceAlreadyExistException(Throwable e) {
		super(e);
	}

}
