/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.service.CheckTotalService.java
 * 创建日期： 2006-6-15 10:08:59
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-15 10:08:59      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="CheckTotalService.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 * 
 *
 */
public interface CheckTotalService {

	 /**
	   * 根据过滤条件查询考勤信息
	   * @param filter
	   * @return
	   */
	  public Page findBy(Map filterMap, Map sortMap, int pageNo, int pageSize);
}
