package org.king.check.common;

import org.hibernate.Hibernate;
import org.hibernate.dialect.OracleDialect;
import org.hibernate.dialect.function.StandardSQLFunction;

/**
 * .
 * User: Yiming.You
 * Date: 2010-10-12
 */
public class Oracle10Dialect extends OracleDialect {
    public Oracle10Dialect() {
        super();
        registerFunction("wmsys.wm_concat", new StandardSQLFunction("wmsys.wm_concat", Hibernate.STRING));
    }
}
