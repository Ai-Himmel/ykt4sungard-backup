/*
 * OperatorMapperTest.java  v1.00  2011-12-30
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	OperatorMapperTest.java  v1.00 2011-12-30
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.modules.operator.dao;

import java.io.IOException;
import java.io.Reader;
import java.sql.SQLException;
import java.util.List;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Operator;
import com.sungard.smartcard.bccsvr.modules.operator.domain.OperatorExample;

/**
 * test Class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-30
 * 
 */
public class OperatorMapperTest {

    public static void main(String[] args) {
        Reader reader;
        try {
            reader = Resources.getResourceAsReader("mapper/Configuration.xml");
            SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(reader);
            DBSessionDao dbSessionDao = new DBSessionDao();
            System.out.println(" -------- " + dbSessionDao);

            SqlSession sqlSession = sqlSessionFactory.openSession(dbSessionDao.getConnection());
            // SqlSession sqlSession = sqlSessionFactory.openSession();
            System.out.println(sqlSession);

            OperatorMapper operatorMapper = sqlSession.getMapper(OperatorMapper.class);
            OperatorExample operatorExample = new OperatorExample();
            operatorExample.createCriteria().andOpernameEqualTo("tc");
            List<Operator> list = operatorMapper.selectByExample(operatorExample);
            for (Operator operator : list) {
                System.out.println("   2  " + operator);
            }

            sqlSession.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
