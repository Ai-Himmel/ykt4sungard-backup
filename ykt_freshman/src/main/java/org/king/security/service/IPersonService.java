/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    IPersonService.java
 * 创建日期： 2007-6-8 上午11:13:31
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-8 上午11:13:31     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.security.service;

import org.king.security.domain.Person;

public interface IPersonService {

	public Person getPersonByPersonNo(String no);
}
