/*
 * OperatorBeanListService.java  v1.00  2012-1-4
 * Peoject	smartcard-operator
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	OperatorBeanListService.java  v1.00 2012-1-4
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import java.math.BigInteger;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Set;

import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.sungard.common.page.Paginator;
import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.modules.utils.db.jdbc.dialect.Dialect;
import com.sungard.modules.utils.db.jdbc.dialect.OracleDialect;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Operator;
import com.sungard.smartcard.bccsvr.modules.operator.domain.OperatorQuery;
import com.sungard.smartcard.utils.drtp.TransfersNodeInfo;
import com.sungard.smartcard.utils.drtp.TransfersUtils;

/**
 * dbutils beanList .
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-1-4
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 90000103, name = "OperatorBeanListService")
public class OperatorBeanListService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(OperatorBeanListService.class);

    private static String sql_query = " select opercode, opertype, branchno, cardno, opername, tel, mobile, email, addr, zipcode, operpwd, status, lasttransdate, menuset, funcset, rightflag, sitelimit, loginflag, loginsiteno, logintime, logouttime, failnumber, opendate, closedate from t_operator";

    @Override
    public boolean doService(Function func, BccServerThread session) {

        // 获取传过来的查询参数
        List<OperatorQuery> listA = TransfersUtils.getTransfersInObjects(OperatorQuery.class, session);
        for (OperatorQuery queryObj : listA) {
            logger.info("查询参数 nameString={}", queryObj.nameString);
        }

        boolean flag = false;

        flag = query(session);

        if (!flag) {
            session.SetStringFieldByName("vsmess", "process unsuccessful!");
            session.PutRow(0);
        }
        session.DataDone(0);

        return flag;
    }

    /**
     * 查询，返回beanList.
     * 
     * @param session
     * @return boolean
     * @since v1.00
     * @see T
     */
    public boolean query(BccServerThread session) {

        long has = 0;
        long time = System.currentTimeMillis();

        try {
            boolean flag = true;

            // 获取传过来的查询参数
            List<OperatorQuery> listA = TransfersUtils.getTransfersInObjects(OperatorQuery.class, session);
            OperatorQuery operatorQuery = null;
            if (listA != null && listA.size() > 0) {
                operatorQuery = listA.get(0);
            }

            // int offset = operatorQuery.getOffset();// 起始行号
            // int pageno = operatorQuery.getPageno();// 起始页
            // int limit = operatorQuery.getPagesize();// 每页行数

            QueryRunner runner = new QueryRunner();

            // 查询总数
            String sql_count = "select count(*) from ";
            sql_count += StringUtils.substringAfter(sql_query.toLowerCase(), "from");
            sql_count = StringUtils.substringBeforeLast(sql_count.toLowerCase(), "order by");
            // ResultSetHandler<Object> rshc = new ScalarHandler();// count
            ScalarHandler sh = new ScalarHandler() {
                @Override
                public Object handle(ResultSet rs) throws SQLException {
                    Object obj = super.handle(rs);
                    if (obj instanceof BigInteger)
                        return ((BigInteger) obj).longValue();
                    return obj;
                }
            };
            Number num = (Number) runner.query(getConnection(), sql_count, sh);
            int count = num.intValue();

            Paginator paginator = new Paginator(operatorQuery.getPageno(), operatorQuery.getPagesize(), count);

            Dialect dialect = new OracleDialect();
            String sql_page = dialect.getLimitString(sql_query, paginator.getOffset(), paginator.getPageSize());

            ResultSetHandler<List<Operator>> rsh = new BeanListHandler<Operator>(Operator.class);
            List<Operator> list = runner.query(getConnection(), sql_page, rsh);
            Set<TransfersNodeInfo> transOuts = TransfersUtils.getTransfersNodeInfosOut(Operator.class);
            for (Operator operator : list) {
                if (!TransfersUtils.TransfersOneRow(session, operator, transOuts)) {
                    logger.info("传输错误", operator);
                    flag = false;
                }
            }

            // flag = TransfersUtils.TransfersAllRow(session, list,
            // Operator.class);

            has = System.currentTimeMillis() - time;
            System.out.println("---------------------hasbeanlist execute time :" + has);

            return flag;
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return true;

    }

}
