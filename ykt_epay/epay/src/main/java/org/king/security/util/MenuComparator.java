/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.util.MenuComparator.java
 * 创建日期： 2006-5-8 14:35:51
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-5-8 14:35:51      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 *
 */
package org.king.security.util;

import org.king.security.domain.Menu;

import java.util.Comparator;

/**
 * <p> MenuComparator.java </p>
 * <p> {功能说明} </p>
 * <p/>
 * <p><a href="MenuComparator.java.html"><i>查看源代码</i></a></p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-5-8
 */
public class MenuComparator implements Comparator {

    /* (non-Javadoc)
      * @see java.utils.Comparator#compare(T, T)
      */

    public int compare(Object o1, Object o2) {
        Menu m1 = (Menu) o1;
        Menu m2 = (Menu) o2;

        if (m1.getSortFlag().intValue() > m2.getSortFlag().intValue())
            return 1;
        else
            return 0;
    }

}
