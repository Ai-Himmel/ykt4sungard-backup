/*
 * DefaultService.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	DefaultService.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;

/**
 * 缺省3类消息处理方法类.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 999, name = "Default")
public class DefaultService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(DefaultService.class);

    public DefaultService() {
        super();
    }

    // @Transactional
    public boolean doService(Function func, BccServerThread session) {

        for (int i = 0; i < session.GetRecordCount(); i++) {
            System.out.println("DefaultService Recv : scust_no = " + session.GetFieldByName(0, "scust_no").toString());
        }
        switch (func.GetInfoType()) {
        case Function.NOTIFY_0_INFO:
        case Function.NOTIFY_1_INFO:
            break;
        case Function.Q_A_INFO:

             session.ClearRow();
             session.SetStringFieldByName("scust_no", "结果12");
             session.KLGMsg("结果12");
             session.PutRow(0);
             session.DataDone(0);
            
//            retriveUser(session);

            System.out.println("应答");
            break;
        }

        // DataSource dataSource = SpringContextHolder.getBean("dataSource",
        // DataSource.class);
        // logger.info("dataSource={}", dataSource);
        // Connection connection = null;
        // try {
        // connection = dataSource.getConnection();
        // ResultSet rs =
        // connection.createStatement().executeQuery("SELECT * FROM CLUB_MEMBER ");
        // while (rs.next()) {
        // logger.info(rs.getString(1));
        // }
        // rs.close();
        //
        // System.out.println(connection + "-------------");
        // } catch (SQLException e) {
        // e.printStackTrace();
        // } finally {
        // try {
        // if (connection != null)
        // connection.close();
        // dataSource = null;
        // } catch (SQLException e) {
        // e.printStackTrace();
        // }
        // }

        return true;
    }

    public HashMap retriveUser(BccServerThread session) {

        if (logger.isDebugEnabled()) {
            logger.debug("retriveUser() - start");
        }

        String sql = "";
        Connection conn = null;
        PreparedStatement stm = null;
        ResultSet result = null;

        try {
            conn = getConnection();
            sql = "SELECT ID,EMAIL ,LOGIN_NAME ,NAME ,PASSWORD  FROM ACCT_USER ";
            try {
                stm = conn.prepareStatement(sql);
                result = stm.executeQuery();
                HashMap users = new HashMap();

                session.ClearRow();
                session.SetAPackMaxRows(2);
                while (result.next()) {
                    logger.info("id{}, name{}", result.getString("id"), result.getString("NAME"));
                    users.put(result.getString("id"), result.getString("NAME"));
                    session.SetStringFieldByName("sname", result.getString("NAME"));
                    session.SetStringFieldByName("scust_no", result.getString("id"));
                    session.PutRow(0);
                }
                session.KLGMsg("结果12");
                session.DataDone(0);
                return users;
            } finally {
                if (stm != null) {
                    stm.close();
                }
            }

        } catch (SQLException e1) {
            logger.error("RetriveDevice()", e1); //$NON-NLS-1$
            return null;
        } catch (Exception e) {
            logger.error("RetriveDevice()", e); //$NON-NLS-1$
            return null;
        }

    }
}
