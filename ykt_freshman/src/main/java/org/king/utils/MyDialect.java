/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    MyDialect.java
 * �������ڣ� 2007-7-10 17:18:08
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-7-10 17:18:08     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.utils;

import org.hibernate.Hibernate;
import org.hibernate.dialect.DB2Dialect;
import org.hibernate.dialect.function.StandardSQLFunction;
import org.hibernate.engine.Mapping;
import org.hibernate.type.Type;

public class MyDialect extends DB2Dialect {

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
