/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    MyDialect.java
 * 创建日期： 2007-7-10 17:18:08
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-7-10 17:18:08     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.utils;

import org.hibernate.Hibernate;
import org.hibernate.dialect.Oracle9iDialect;
import org.hibernate.dialect.function.StandardSQLFunction;
import org.hibernate.engine.Mapping;
import org.hibernate.type.Type;

public class MyDialect extends Oracle9iDialect {

	public MyDialect() {
		super();
		registerFunction("count",new StandardSQLFunction("count") {
			public Type getReturnType(Type columnType, Mapping mapping) {
				return Hibernate.INTEGER;
			}
		});
		registerFunction("sum",new StandardSQLFunction("sum") {
			public Type getReturnType(Type columnType, Mapping mapping) {
				return Hibernate.INTEGER;		
			}
		
		});
	}
}
