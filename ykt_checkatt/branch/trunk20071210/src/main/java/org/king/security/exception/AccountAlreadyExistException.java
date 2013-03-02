/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.framework.exception.AccountAlreadyExistException.java
 * �������ڣ� 2006-4-18 15:01:20
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-18 15:01:20      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> AccountAlreadyExistException.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="AccountAlreadyExistException.java.html"><i>�鿴Դ����</i></a></p>  
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
