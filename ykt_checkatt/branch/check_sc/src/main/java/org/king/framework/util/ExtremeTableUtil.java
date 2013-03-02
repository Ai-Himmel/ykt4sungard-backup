/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.framework.util.ExtremeTableUtil.java
 * 创建日期： 2006-6-14 11:24:45
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-14 11:24:45      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="ExtremeTableUtil.java.html"><i>查看源代码</i></a></p>  
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
     * 从request构造limit对象实例.
     */
    static public Limit getLimit(HttpServletRequest request, int defautPageSize) {
        Context context = new HttpServletRequestContext(request);
        LimitFactory limitFactory = new TableLimitFactory(context);
        TableLimit limit = new TableLimit(limitFactory);
        limit.setRowAttributes(1000000000, defautPageSize);
        return limit;
    }

    /**
     * 获取排序信息
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
