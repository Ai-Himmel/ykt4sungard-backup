/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.util.MenuComparator.java
 * �������ڣ� 2006-5-8 14:35:51
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-5-8 14:35:51      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.util;

import java.util.Comparator;

import org.king.security.domain.Menu;

/**
 * <p> MenuComparator.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="MenuComparator.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-5-8
 * 
 *
 */
public class MenuComparator implements Comparator {

	/* (non-Javadoc)
	 * @see java.util.Comparator#compare(T, T)
	 */
	public int compare(Object o1, Object o2) {
		Menu m1 = (Menu)o1;
		Menu m2 = (Menu)o2;
		
		if(m1.getSortFlag().intValue() > m2.getSortFlag().intValue())
			return 1;
		else  
		    return 0;
	}

}
