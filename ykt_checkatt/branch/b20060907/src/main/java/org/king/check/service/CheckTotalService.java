/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.service.CheckTotalService.java
 * �������ڣ� 2006-6-15 10:08:59
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-15 10:08:59      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.check.service;

import java.text.ParseException;
import java.util.List;
import java.util.Map;

import org.king.framework.common.support.Page;

/**
 * <p> CheckTotalService.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="CheckTotalService.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 * 
 *
 */
public interface CheckTotalService {

	 /**
	   * ���ݹ���������ѯ������Ϣ
	   * @param filter
	   * @return
	   */
	  public Page findBy(Map filterMap, Map sortMap, int pageNo, int pageSize);
}
