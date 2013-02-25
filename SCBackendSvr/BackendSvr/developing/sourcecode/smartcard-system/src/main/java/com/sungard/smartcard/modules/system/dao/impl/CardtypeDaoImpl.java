/*
 * CardtypeDaoImpl.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtypeDaoImpl.java  v1.00 2012-2-22
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
import com.sungard.smartcard.modules.system.dao.CardtypeDao;

/**
 * [TODO 卡类别.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@Repository
public class CardtypeDaoImpl implements CardtypeDao{
	private static final Logger logger = LoggerFactory.getLogger(CardtypeDaoImpl.class);
	private static String CARDTYPE_QUERY_ALL = "select cardtype, cardtypename, cardphytype, anonymflag, feetype, cardcostfee, reuseable, renewable, recycleable, multipurse, fixdayflag, fixdaycnt, useflag, purpose from t_cardtype where 1=1";
	private static String CARDTYPE_ADD = "insert into t_cardtype(cardtype, cardtypename, cardphytype, anonymflag, feetype, cardcostfee, reuseable, renewable, recycleable, multipurse, fixdayflag, fixdaycnt, useflag, purpose)values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
	private static String CARDTYPE_UPDATE = "update t_cardtype set cardtypename=?, cardphytype=?, anonymflag=?, feetype=?, cardcostfee=?, reuseable=?, renewable=?, recycleable=?, multipurse=?, fixdayflag=?, fixdaycnt=?, useflag=?, purpose=? where cardtype=?";
	private static String CARDTYPE_DELETE = "delete t_cardtype where cardtype = ?";
	@Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
	@Override
	public int add(Cardtype cardtype) {
		// TODO Auto-generated method stub
		return jdbcTemplate.update(CARDTYPE_ADD, 
				new Object[]{
				cardtype.getCardtype(), 
				cardtype.getCardtypename(), 
				cardtype.getCardphytype(), 
				cardtype.getAnonymflag(), 
				cardtype.getFeetype(), 
				cardtype.getCardcostfee(), 
				cardtype.getReuseable(), 
				cardtype.getRenewable(), 
				cardtype.getRecycleable(), 
				cardtype.getMultipurse(), 
				cardtype.getFixdayflag(), 
				cardtype.getFixdaycnt(), 
				cardtype.getUseflag(), 
				cardtype.getPurpose()});
	}
	@Override
	public int delete(String cardtype) {
		return jdbcTemplate.update(CARDTYPE_DELETE, cardtype);
	}

	@Override
	public List<Cardtype> findAll() {
		return jdbcTemplate.query(this.CARDTYPE_QUERY_ALL+" order by cardtype",new BeanPropertyRowMapper(Cardtype.class));
	}

	@Override
	public List<Cardtype> findbyparam(String sql, Object[] arg) {
		return jdbcTemplate.query(sql,arg,new BeanPropertyRowMapper(Cardtype.class));
	}

	@Override
	public Cardtype getCardtype(String cardtype) {
		return jdbcTemplate.queryForObject(this.CARDTYPE_QUERY_ALL+" and cardtype=?",new BeanPropertyRowMapper(Cardtype.class), cardtype);
	}

	@Override
	public int update(Cardtype cardtype) {
		return jdbcTemplate.update(CARDTYPE_UPDATE, 
				new Object[]{
				cardtype.getCardtypename(), 
				cardtype.getCardphytype(), 
				cardtype.getAnonymflag(), 
				cardtype.getFeetype(), 
				cardtype.getCardcostfee(), 
				cardtype.getReuseable(), 
				cardtype.getRenewable(), 
				cardtype.getRecycleable(), 
				cardtype.getMultipurse(), 
				cardtype.getFixdayflag(), 
				cardtype.getFixdaycnt(), 
				cardtype.getUseflag(), 
				cardtype.getPurpose(),
				cardtype.getCardtype()});
	}
	@Override
	public int getNetCardtype() {
		// TODO Auto-generated method stub
		return jdbcTemplate.queryForInt("select seq_cardtype.nextval from dual");
	}
	@Override
	public List<Cardtype> findCardtype(Cardtype cardtype) {
		StringBuffer sb = new StringBuffer("");
		List<String> param = new ArrayList<String>();
		if(cardtype!=null){
			if(StringUtils.isNotBlank(cardtype.getCardtypename())){
				sb.append(" and cardtypename like ?");
				param.add("%"+cardtype.getCardtypename()+"%");
			}
			if(StringUtils.isNotBlank(cardtype.getAnonymflag())){
				sb.append(" and anonymflag = ?");
				param.add(cardtype.getAnonymflag());
			}
		}
		sb.append(" order by cardtype");
		return this.findbyparam(CARDTYPE_QUERY_ALL+sb.toString(), param.size()>0?param.toArray():null);
	}

}
