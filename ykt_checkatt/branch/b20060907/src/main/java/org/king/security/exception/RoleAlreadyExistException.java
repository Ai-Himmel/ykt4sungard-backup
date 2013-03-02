/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.exception.RoleAlreadyExistException.java
 * �������ڣ� 2006-4-19 22:10:13
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-19 22:10:13      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> RoleAlreadyExistException.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="RoleAlreadyExistException.java.html"><i>�鿴Դ����</i></a></p>  
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
