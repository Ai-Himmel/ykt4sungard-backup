/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.exception.ResourceAlreadyExistException.java
 * �������ڣ� 2006-4-19 22:15:03
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-19 22:15:03      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.exception;

import org.king.framework.exception.BaseException;

/**
 * <p> ResourceAlreadyExistException.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="ResourceAlreadyExistException.java.html"><i>�鿴Դ����</i></a></p>  
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
