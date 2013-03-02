/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.framework.util.ExtremeTableUtil.java
 * �������ڣ� 2006-6-14 11:24:45
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-14 11:24:45      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.framework.util;

import javax.servlet.http.HttpServletRequest;

import org.extremecomponents.table.context.Context;
import org.extremecomponents.table.context.HttpServletRequestContext;
import org.extremecomponents.table.limit.*;
import org.king.framework.Constants;

import javax.servlet.http.HttpServletRequest;
import java.util.HashMap;
import java.util.Map;


/**
 * <p> ExtremeTableUtil.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="ExtremeTableUtil.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-14
 * 
 *
 */
public class ExtremeTableUtil {

    static public Limit getLimit(HttpServletRequest request) {
        return getLimit(request, Constants.DEFAULT_PAGE_SIZE);
    }

    /**
     * ��request����limit����ʵ��.
     */
    static public Limit getLimit(HttpServletRequest request, int defautPageSize) {
        Context context = new HttpServletRequestContext(request);
        LimitFactory limitFactory = new TableLimitFactory(context);
        TableLimit limit = new TableLimit(limitFactory);
        limit.setRowAttributes(1000000000, defautPageSize);
        return limit;
    }

    /**
     * ��ȡ������Ϣ
     */
    static public Map getSort(Limit limit) {
        Map sortMap = new HashMap();
        if (limit != null) {
            Sort sort = limit.getSort();
            if (sort != null && sort.isSorted()) {
                sortMap.put(sort.getProperty(), sort.getSortOrder());
            }
        }
        return sortMap;
    }

}
