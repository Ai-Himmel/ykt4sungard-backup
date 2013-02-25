/*
 * OperatorAliasService.java  v1.00  2012-1-5
 * Peoject	smartcard-operator
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	OperatorAliasService.java  v1.00 2012-1-5
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import java.sql.Connection;
import java.sql.SQLException;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.smartcard.annotation.CrudType;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.bccsvr.handlers.AliasTransHandler;

/**
 * AliasTransHandler实现. 处理效率较jdbc次之.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-1-5
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 90000102, name = "OperatorAliasService")
public class OperatorAliasService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(OperatorAliasService.class);
    private static final String querySql = "select opercode  as scust_no,opertype  as sstatus2,opername  as sname,tel     as sphone,mobile  as sphone2,email   as semail,addr    as scusttypes,zipcode as spost_code,sitelimit as sstatus1,status  as sstatus3,loginflag as sstatus4,opendate  as sdate0 from t_operator";

    @Override
    public boolean doService(Function func, BccServerThread session) {

        logger.debug("OperatorAliasService - start");

        long has = 0;
        long time = System.currentTimeMillis();

        boolean flag = false;

        String sstatus0 = "";// (String) session.GetFieldByName(0, "sstatus0");
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
            flag = query(session);
            break;
        case Other:
            break;
        default:
            logger.debug("OperatorAliasService - 无处理应答");
            break;
        }

        if (!flag) {
            session.SetStringFieldByName("vsmess", "process unsuccessful!");
            session.PutRow(0);
        }
        session.DataDone(0);

        has = System.currentTimeMillis() - time;
        System.out.println("---------------------has Alias execute time :" + has);

        return flag;
    }

    private boolean query(BccServerThread session) {

        if (logger.isDebugEnabled()) {
            logger.debug("OperatorAliasService.query() - 查询 start");
        }

        Connection conn = null;
        try {

            conn = getConnection();

            QueryRunner runner = new QueryRunner();
            ResultSetHandler<Boolean> rsh = new AliasTransHandler(session);
            return runner.query(conn, querySql, rsh);

        } catch (SQLException e1) {
            logger.error("OperatorAliasService.query()", e1);
        } catch (Exception e) {
            logger.error("OperatorAliasService.query()", e);
        }

        return false;
    }

}
