/*
 * MyBatisTest.java  v1.00  2011-12-30
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	MyBatisTest.java  v1.00 2011-12-30
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.io.IOException;
import java.io.Reader;
import java.util.List;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import com.sungard.smartcard.bccsvr.modules.user.dao.AuthorityMapper;
import com.sungard.smartcard.bccsvr.modules.user.domain.Authority;
import com.sungard.smartcard.bccsvr.modules.user.domain.AuthorityExample;

/**
 * test class.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-30
 * 
 */
public class MyBatisTest {

    public static void main(String[] args) {
        Reader reader;
        try {
            reader = Resources.getResourceAsReader("mapper/Configuration.xml");
            SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(reader);
            SqlSession sqlSession = sqlSessionFactory.openSession();
            System.out.println(sqlSession);
            
            List<Authority>  list = sqlSession.selectList("com.sungard.smartcard.bccsvr.modules.user.dao.AuthorityMapper.selectByExample");
            for (Authority authority : list) {
                System.out.println(authority);
            }
            
            AuthorityMapper authorityMapper =sqlSession.getMapper(AuthorityMapper.class);
            AuthorityExample authorityExample = new  AuthorityExample();
            authorityExample.createCriteria().andIdEqualTo(3L);
            List<Authority>  list1 = authorityMapper.selectByExample(authorityExample);
            for (Authority authority : list1) {
                System.out.println("   2  "+authority);
            }
            
            sqlSession.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
