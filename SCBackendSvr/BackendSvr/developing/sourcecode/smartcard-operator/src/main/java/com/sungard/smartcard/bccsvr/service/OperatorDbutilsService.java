/*
 * OperatorDbutilsService.java  v1.00  2011-12-26
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	OperatorDbutilsService.java  v1.00 2011-12-26
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import java.math.BigDecimal;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

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
import com.sungard.smartcard.bccsvr.handlers.AliasHandler;

/**
 * dbutils 实现.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-26
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 90000104, name = "OperatorJdbcService")
public class OperatorDbutilsService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(OperatorDbutilsService.class);
    private static final String querySql = "select opercode  as scust_no,opertype  as sstatus2,opername  as sname,tel     as sphone,mobile  as sphone2,email   as semail,addr    as scusttypes,zipcode as spost_code,sitelimit as sstatus1,status  as sstatus3,loginflag as sstatus4,opendate  as sdate0 from t_operator";

    @Override
    public boolean doService(Function func, BccServerThread session) {

        logger.debug("OperatorJdbcService - start");

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
            query(session);
            break;
        case Other:
            break;
        default:
            logger.debug("OperatorDbutilsService - 无处理应答");
            break;
        }

        return true;
    }

    public void query(BccServerThread session) {

        if (logger.isDebugEnabled()) {
            logger.debug("OperatorDbutilsService.query() - 查询 start");
        }

        Connection conn = null;
        long has = 0;
        try {
            long time = System.currentTimeMillis();
            conn = getConnection();

            QueryRunner runner = new QueryRunner();
            ResultSetHandler<List<Map<String, Object>>> rsh = new AliasHandler(null);
            List<Map<String, Object>> results = runner.query(conn, querySql, rsh);
            for (Map<String, Object> map : results) {
                logger.info(map + "");
            }

            Map<String, Object> m = results.get(0);
            Set s = m.keySet();

            for (Iterator iterator = s.iterator(); iterator.hasNext();) {
                Object object = (Object) iterator.next();
                Object c = m.get(object);
                String type = "";
                if (c != null) {
                    if (c instanceof Integer) {
                        type = Integer.class.getName();
                    } else if (c instanceof String) {
                        type = String.class.getName();
                    } else if (c instanceof Boolean) {
                        type = Boolean.class.getName();
                    } else if (c instanceof Long) {
                        type = Long.class.getName();
                    } else if (c instanceof Double) {
                        type = Double.class.getName();
                    } else if (c instanceof Float) {
                        type = Float.class.getName();
                    } else if (c instanceof Short) {
                        type = Short.class.getName();
                    } else if (c instanceof Byte) {
                        type = Byte.class.getName();
                    } else if (c instanceof Timestamp) {
                        type = Timestamp.class.getName();
                    } else if (c instanceof BigDecimal) {
                        type = BigDecimal.class.getName();
                    }
                    logger.info(c.getClass().getName());
                }

                logger.info("name={" + object + "} type={" + type + "} value={" + c + "}");
            }

            has = System.currentTimeMillis() - time;
            System.out.println("---------------------hasjdbc:" + has);

        } catch (SQLException e1) {
            logger.error("OperatorDbutilsService.query()", e1);
        } catch (Exception e) {
            logger.error("OperatorDbutilsService.query()", e);
        }

    }

}
