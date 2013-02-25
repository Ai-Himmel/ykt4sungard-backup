/*
 * AliasHandler.java  v1.00  2011-12-26
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	AliasHandler.java  v1.00 2011-12-26
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.handlers;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

import org.apache.commons.dbutils.ResultSetHandler;

import com.sungard.modules.utils.db.typemapping.DatabaseDataTypesUtils;
import com.sungard.smartcard.bccsvr.BccServerThread;

/**
 * 别传传输.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-26
 * 
 */
public class AliasTransHandler implements ResultSetHandler<Boolean> {

    private BccServerThread thread;

    public AliasTransHandler() {
        super();
    }

    public AliasTransHandler(BccServerThread session) {
        thread = session;
    }

    @Override
    public Boolean handle(ResultSet rs) throws SQLException {
        if (!rs.next()) {
            return true;
        }
        ResultSetMetaData rsmd = rs.getMetaData();
        String[] methodNames = mapColumnsToProperties(rsmd);

        if (thread != null) {
            thread.ClearRow();
        }
        boolean flag = true;
        while (rs.next() && flag) {
            flag = this.handleRow(rs, rsmd, methodNames, thread);
        }
        if (thread != null) {
            thread.DataDone(0);
        }
        return flag;
    }

    /**
     * 将ResultSetMetaData转换成java类型数组.
     * 
     * @param rsmd
     * @return String[]
     * @throws SQLException
     * @since v1.00
     * @see com.sungard.modules.utils.db.typemapping.DatabaseDataTypesUtils
     */
    protected String[] mapColumnsToProperties(ResultSetMetaData rsmd) throws SQLException {
        int cols = rsmd.getColumnCount();
        String[] columnType = new String[cols + 1];

        for (int col = 1; col <= cols; col++) {
            columnType[col] = DatabaseDataTypesUtils.getPreferredJavaType(rsmd.getColumnType(col),
                    rsmd.getPrecision(col), rsmd.getScale(col));
        }
        return columnType;
    }

    /**
     * 传输信息.
     * 
     * @param rs
     *            查询结果集
     * @param rsmd
     *            metaData
     * @param methodNames
     * @param session
     * @return
     * @throws SQLException
     * @since v1.00
     * @see T
     */
    protected boolean handleRow(ResultSet rs, ResultSetMetaData rsmd, String[] methodNames, BccServerThread session)
            throws SQLException {

        int cols = rsmd.getColumnCount();
        try {
            if (thread != null) {
                Method setter = session.getClass().getDeclaredMethod("SetFieldByName", String.class, Object.class);
                for (int i = 1; i <= cols; i++) {
                    setter.invoke(session, rsmd.getColumnName(i).toLowerCase(), rs.getObject(i));
                }
                session.PutRow(0);
            }
            return true;
        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        return false;
    }
}
