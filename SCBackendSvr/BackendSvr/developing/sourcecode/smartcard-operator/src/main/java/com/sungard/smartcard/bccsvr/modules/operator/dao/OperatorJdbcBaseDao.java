/*
 * OperatorJdbcBaseDao.java  v1.00  2012-1-6
 * Peoject	smartcard-operator
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	OperatorJdbcBaseDao.java  v1.00 2012-1-6
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.modules.operator.dao;

import com.sungard.smartcard.bccsvr.dao.AbstractJdbcBaseDao;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Operator;

/**
 * dao 实现.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-1-6
 * 
 */
public class OperatorJdbcBaseDao extends AbstractJdbcBaseDao<Operator, String> {

    public OperatorJdbcBaseDao() {
        super(Operator.class);
    }

    private static String sql_query = " select opercode, opertype, branchno, cardno, opername, tel, mobile, email, addr, zipcode, operpwd, status, lasttransdate, menuset, funcset, rightflag, sitelimit, loginflag, loginsiteno, logintime, logouttime, failnumber, opendate, closedate from t_operator";

    @Override
    public String getSelectAllSql() {
        return sql_query;
    }

}
