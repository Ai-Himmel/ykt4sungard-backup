/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.exception.CatalogAlreadyExistException.java
 * �������ڣ� 2006-6-16 11:00:26
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-16 11:00:26      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.check.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> CatalogAlreadyExistException.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="CatalogAlreadyExistException.java.html"><i>�鿴Դ����</i></a></p>  
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
