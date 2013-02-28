/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.impl.AclImpl.java
 * 创建日期： 2006-4-19 23:02:06
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 23:02:06      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 *
 */
package org.king.security.service.impl;

import org.apache.log4j.Logger;
import org.king.framework.util.MyUtils;
import org.king.security.service.Acl;
import org.king.security.util.MenuParser;

/**
 * <p>
 * AclImpl.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * <p/>
 * <p>
 * <a href="AclImpl.java.html"><i>查看源代码</i></a>
 * </p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 */
public class AclImpl implements Acl {

    private static Logger logger = Logger.getLogger(AclImpl.class);

    /**
     * 判断指定url是否为受保护资源
     *
     * @param url .
     * @return .
     */
    public boolean isProtectedResource(String url) {
        if (MyUtils.isBlank(url)) {
            return false;
        }
        return MenuParser.getUrls().contains(url);
    }

	public boolean hasRight(String url, String acctype) {
		if (MyUtils.isBlank(url)&&MyUtils.isBlank(acctype)) {
            return false;
        }
		return MenuParser.getAcctypeurls().contains(acctype+url);
	}
}
