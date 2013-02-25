/*
 * CardtyperightDaoImpl.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtyperightDaoImpl.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.dao.impl;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.domain.Cardtype;
import com.sungard.smartcard.domain.Cardtyperight;
import com.sungard.smartcard.modules.system.dao.CardtyperightDao;

/**
 * [TODO 发卡权限.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@Repository
public class CardtyperightDaoImpl implements CardtyperightDao{
	private static final Logger logger = LoggerFactory.getLogger(CardtyperightDaoImpl.class);
	private static String CARDTYPERIGHT_QUERY_ALL = "select cardtype, feetype, opercode, lastsaved from t_cardtyperight where 1=1 ";
	private static String CARDTYPERIGHT_UPDATE = "update t_cardtyperight set opercode=?, lastsaved=? where cardtype=? and feetype =?";
	private static String CARDTYPERIGHT_DELETE = "delete t_cardtyperight where cardtype = ? and feetype = ?";
	private static String CARDTYPERIGHT_ADD = "insert into t_cardtyperight(cardtype, feetype, opercode, lastsaved)values(?,?,?,?)";
	@Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
	@Override
	public int add(Cardtyperight cardtyperight) {
		// TODO Auto-generated method stub
		return this.jdbcTemplate.update(this.CARDTYPERIGHT_ADD, new Object[]{cardtyperight.getCardtype(),cardtyperight.getFeetype(),cardtyperight.getOpercode(),cardtyperight.getLastsaved()});
	}

	@Override
	public int delete(Integer cardtype, Integer feetype) {
		return this.jdbcTemplate.update(this.CARDTYPERIGHT_DELETE, new Object[]{cardtype,feetype});
	}

	@Override
	public List<Cardtyperight> findByparam(String sql, Object[] arg) {
		// TODO Auto-generated method stub
		return this.jdbcTemplate.query(sql, arg, new BeanPropertyRowMapper(Cardtyperight.class));
	}

	@Override
	public List<Cardtyperight> findall() {
		// TODO Auto-generated method stub
		return this.jdbcTemplate.query(this.CARDTYPERIGHT_QUERY_ALL+" order by cardtype",new BeanPropertyRowMapper(Cardtyperight.class));
	}

	@Override
	public Cardtyperight getCardtyperight(Integer cardtype, Integer feetype) {
		// TODO Auto-generated method stub
		return this.jdbcTemplate.queryForObject(this.CARDTYPERIGHT_QUERY_ALL+" and cardtype=? and feetype=?", new BeanPropertyRowMapper(Cardtyperight.class), new Object[]{cardtype,feetype});
	}

	@Override
	public int update(Cardtyperight cardtyperight) {
		return this.jdbcTemplate.update(this.CARDTYPERIGHT_UPDATE, 
				new Object[]{
				cardtyperight.getOpercode(),
				cardtyperight.getLastsaved(),
				cardtyperight.getCardtype(),
				cardtyperight.getFeetype()});
	}
	@Override
	public List<Cardtyperight> findCardtyperight(Cardtyperight cardtyperight) {
		StringBuffer sb = new StringBuffer("select cardtype, feetype, opercode, lastsaved from t_cardtyperight where 1=1");
		List<String> param = new ArrayList<String>();
		if(cardtyperight.getCardtype()>0){
			sb.append(" and cardtype = ?");
			param.add(""+cardtyperight.getCardtype());
		}
		if(cardtyperight.getFeetype()>0){
			sb.append(" and feetype = ?");
			param.add(""+cardtyperight.getFeetype());
		}
		if(StringUtils.isNotBlank(cardtyperight.getOpercode())){
			sb.append(" and opercode = ?");
			param.add(""+cardtyperight.getOpercode());	
		}
		if(StringUtils.isNotBlank(cardtyperight.getLastsaved())){
			sb.append(" and lastsaved = ?");
			param.add(""+cardtyperight.getLastsaved());	
		}
		sb.append(" order by cardtype");
		return findByparam(sb.toString(), param.size()>0?param.toArray():null);
	}

}
