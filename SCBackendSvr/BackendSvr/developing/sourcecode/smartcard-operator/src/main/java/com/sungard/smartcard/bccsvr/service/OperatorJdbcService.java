/*
 * OperatorJdbcService.java  v1.00  2011-12-21
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	OperatorJdbcService.java  v1.00 2011-12-21
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.smartcard.annotation.CrudType;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;

/**
 * 纯jdbc实现.此种方法处理效率是最高的.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-21
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 90000101, name = "OperatorJdbcService")
public class OperatorJdbcService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(OperatorJdbcService.class);

    private static final String querySql = "select opercode, opertype, branchno, cardno, opername, tel, mobile, email, addr, zipcode, operpwd, status, lasttransdate, menuset, funcset, rightflag, sitelimit, loginflag, loginsiteno, logintime, logouttime, failnumber, opendate, closedate from t_operator";

    @Override
    public boolean doService(Function func, BccServerThread session) {

        logger.debug("OperatorJdbcService - start");

        String sstatus0 = (String) session.GetFieldByName(0, "sstatus0");
        if (StringUtils.isBlank(sstatus0)) {
            sstatus0 = "Q";
        }
        switch (Enum.valueOf(CrudType.class, sstatus0)) {
        case A:
            break;
        case U:
            break;
        case D:
            break;
        case Q:
            query(session);
            break;
        case Other:
            break;
        default:
            logger.debug("OperatorJdbcService - 无处理应答");
            break;
        }

        return true;
    }

    public void query(BccServerThread session) {

        if (logger.isDebugEnabled()) {
            logger.debug("OperatorJdbcService.query() - 查询 start");
        }

        Connection conn = null;
        PreparedStatement stm = null;
        ResultSet result = null;
        long has = 0;
        try {

            long time = System.currentTimeMillis();
            conn = getConnection();
            try {
                stm = conn.prepareStatement(querySql);
                result = stm.executeQuery();
                session.ClearRow();
                // session.SetAPackMaxRows(10);//满多少个包后马上发送
                while (result.next()) {
                    session.SetStringFieldByName("scust_no", result.getString("opercode"));
                    session.SetStringFieldByName("sname", result.getString("opername"));
                    session.PutRow(0);
                }
                session.KLGMsg("结果12");
                session.DataDone(0);

            } finally {
                if (stm != null) {
                    stm.close();
                    has = System.currentTimeMillis() - time;
                    System.out.println("---------------------hasjdbc:" + has);
                }
            }

        } catch (SQLException e1) {
            logger.error("OperatorJdbcService.query()", e1);
        } catch (Exception e) {
            logger.error("OperatorJdbcService.query()", e);
        }

    }

}
