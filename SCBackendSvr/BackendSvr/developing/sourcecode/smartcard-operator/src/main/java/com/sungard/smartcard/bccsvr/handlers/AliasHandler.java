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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

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
public class AliasHandler implements ResultSetHandler<List<Map<String, Object>>> {

    private BccServerThread thread;

    public AliasHandler() {
        super();
    }

    public AliasHandler(BccServerThread session) {
        thread = session;
    }

    @Override
    public List<Map<String, Object>> handle(ResultSet rs) throws SQLException {
        if (!rs.next()) {
            return null;
        }
        ResultSetMetaData rsmd = rs.getMetaData();
        String[] methodNames = mapColumnsToProperties(rsmd);
        for (int i = 1; i <= methodNames.length; i++) {

        }

        List<Map<String, Object>> rows = new ArrayList<Map<String, Object>>();
        if (thread != null) {
            thread.ClearRow();
        }
        while (rs.next()) {
            rows.add(this.handleRow(rs, rsmd, methodNames, thread));
        }
        if (thread != null) {
            thread.DataDone(0);
        }
        return rows;
    }

    protected String[] mapColumnsToProperties(ResultSetMetaData rsmd) throws SQLException {

        int cols = rsmd.getColumnCount();
        String[] columnType = new String[cols + 1];

        for (int col = 1; col <= cols; col++) {
            // System.out.println(rsmd.getColumnLabel(col) + "  " +
            // rsmd.getColumnType(col));
            System.out.println("sqltype="
                    + rsmd.getColumnType(col)
                    + "  getPrecision="
                    + rsmd.getPrecision(col)
                    + " getScale="
                    + rsmd.getScale(col)
                    + "  "
                    + DatabaseDataTypesUtils.getPreferredJavaType(rsmd.getColumnType(col), rsmd.getPrecision(col),
                            rsmd.getScale(col)));
            columnType[col] = DatabaseDataTypesUtils.getPreferredJavaType(rsmd.getColumnType(col),
                    rsmd.getPrecision(col), rsmd.getScale(col));
            // columnType[col] = rsmd.getColumnTypeName(col);
        }

        return columnType;
    }

    protected Map<String, Object> handleRow(ResultSet rs, ResultSetMetaData rsmd, String[] methodNames,
            BccServerThread session) throws SQLException {
        Map<String, Object> result = new HashMap<String, Object>();

        int cols = rsmd.getColumnCount();
        try {
            if (thread != null) {
                Method setter = session.getClass().getDeclaredMethod("SetFieldByName", String.class, Object.class);
                for (int i = 1; i <= cols; i++) {
                    setter.invoke(session, rsmd.getColumnName(i).toLowerCase(), rs.getObject(i));
                    result.put(rsmd.getColumnName(i), rs.getObject(i));
                }
                session.PutRow(0);
            } else {
                for (int i = 1; i <= cols; i++) {
                    result.put(rsmd.getColumnName(i), rs.getObject(i));
                }
            }
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

        return result;
    }
}
