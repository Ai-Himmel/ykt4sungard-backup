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

import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.smartcard.annotation.CrudType;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Transdtl;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * 纯jdbc实现.此种方法处理效率是最高的.
 *
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-21
 */
@SmartCardFunction(infotype = 3, funcnum = 90000107, name = "TransdtlJdbcService")
public class TransdtlJdbcService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(TransdtlJdbcService.class);

    private static final String querySql = "select accdate, acctime, termid, termseqno, transdate, transtime, refno, transcode, custid, custname, stuempno, showcardno, cardno, purseno, transflag, cardcnt, cardbefbal, cardaftbal, amount, addamt, managefee, paytype, voucherno, opercode, sysid, devphyid, devseqno, exttype, extdata, coldate, coltime, offlineflag, revflag, status, errcode, remark from t_transdtl where accdate>'20101123'";

    @Override
    public boolean doService(Function func, BccServerThread session) {

        logger.debug("OperatorJdbcService - start");

        String sstatus0 = (String) session.GetFieldByName(0, "sstatus0");
        if (StringUtils.isBlank(sstatus0)) {
            sstatus0 = "Q";
        }
        switch (Enum.valueOf(CrudType.class, sstatus0)) {
            case A:
                queryAsByte(session);
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
        long count = 0;
        try {

            long time = System.currentTimeMillis();
            conn = getConnection();
            try {
                stm = conn.prepareStatement(querySql);
                stm.setFetchSize(40761);
                result = stm.executeQuery();
                session.ClearRow();
                // session.SetAPackMaxRows(10);//满多少个包后马上发送
                System.out.println("---------------------hasjdbc execute time:" + (System.currentTimeMillis() - time));
                while (result.next()) {
                    count++;
                    session.SetStringFieldByName("sname", result.getString("acctime") == null ? "" : result.getString("acctime"));
                    session.SetStringFieldByName("saddr", result.getString("transdate") == null ? "" : result.getString("transdate"));
                    session.SetStringFieldByName("saddr2", result.getString("transtime") == null ? "" : result.getString("transtime"));
//                    session.SetIntFieldByName("lvol0", result.getInt("refno"));
//                    session.SetDoubleFieldByName("damt0", result.getDouble("transcode"));
//                    session.SetDoubleFieldByName("damt1", result.getDouble("custid"));
                    session.SetStringFieldByName("sbank_code2", result.getString("custname") == null ? "" : result.getString("custname"));
                    session.SetStringFieldByName("sbank_pwd", result.getString("stuempno") == null ? "" : result.getString("stuempno"));

                    session.PutRow(0);
                }
                session.KLGMsg("结果12");
                session.DataDone(0);

            } finally {
                if (stm != null) {
                    stm.close();
                    has = System.currentTimeMillis() - time;
                    System.out.println("---------------------hasjdbc:" + has);
                    System.out.println("---------------------result size:" + count);
                }
            }

        } catch (SQLException e1) {
            logger.error("OperatorJdbcService.query()", e1);
        } catch (Exception e) {
            logger.error("OperatorJdbcService.query()", e);
        }

    }

    public void queryAsByte(BccServerThread session) {
        if (logger.isDebugEnabled()) {
            logger.debug("OperatorJdbcService.queryAsByte() - 查询 start");
        }

        Connection conn;
        PreparedStatement stm = null;
        ResultSet result;
        long has;
        long count = 0;
        ObjectOutputStream oos = null;
        ByteArrayOutputStream baos = null;
        try {
            long time = System.currentTimeMillis();
            conn = getConnection();
            try {
                stm = conn.prepareStatement(querySql);
                stm.setFetchSize(40761);
                result = stm.executeQuery();
                session.ClearRow();
                // session.SetAPackMaxRows(10);//满多少个包后马上发送
                System.out.println("---------------------hasjdbc execute time:" + (System.currentTimeMillis() - time));
                baos = new ByteArrayOutputStream();
                oos = new ObjectOutputStream(baos);
                while (result.next()) {
                    count++;
                    Transdtl entity = new Transdtl();
                    entity.setAcctime(result.getString("acctime"));
                    entity.setTransdate(result.getString("transdate"));
                    entity.setTranstime(result.getString("transtime"));
                    entity.setCustname(result.getString("custname"));
                    entity.setStuempno(result.getString("stuempno"));
                    oos.writeObject(entity);
                    byte[] bytes = baos.toByteArray();
                    baos.reset();
                    oos.reset();
                    session.SetRawRecord(bytes, bytes.length);
                    session.PutRow(0);
                }
                session.KLGMsg("结果12");
                session.DataDone(0);
                Thread.sleep(20000);
            } finally {
                if (stm != null) {
                    stm.close();
                    has = System.currentTimeMillis() - time;
                    System.out.println("---------------------hasjdbc:" + has);
                    System.out.println("---------------------result size:" + count);
                }
                if (baos != null) {
                    baos.close();
                }
                if (oos != null) {
                    oos.close();
                }
            }

        } catch (SQLException e1) {
            logger.error("OperatorJdbcService.query()", e1);
        } catch (Exception e) {
            logger.error("OperatorJdbcService.query()", e);
        }

    }

}
