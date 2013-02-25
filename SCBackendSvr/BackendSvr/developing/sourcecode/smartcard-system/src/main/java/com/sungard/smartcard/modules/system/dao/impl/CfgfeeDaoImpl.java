/*
 * CfgfeeDaoImpl.java  v1.00  2012-2-21
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CfgfeeDaoImpl.java  v1.00 2012-2-21
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.dao.impl;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.domain.Cfgfee;
import com.sungard.smartcard.domain.Transtype;
import com.sungard.smartcard.modules.system.dao.CfgfeeDao;

/**
 * [TODO 交易收费信息维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-21
 * 
 */
@Repository
public class CfgfeeDaoImpl implements CfgfeeDao{
	
	private static final Logger logger = LoggerFactory.getLogger(CfgfeeDaoImpl.class);
	
	private static String CFGFEE_QUERY_ALL = "SELECT feetype,transcode,cardtype,transtype,ratetype,rateamt,remark FROM t_cfgfee where 1=1 ";
	private static String CFGFEE_UPDATE = "update t_cfgfee set ratetype =?,rateamt=?,remark=? where feetype=? and transcode=? and cardtype=? and transtype=?";
	private static String CFGFEE_ADD = "insert into t_cfgfee(feetype,transcode,cardtype,transtype,ratetype,rateamt,remark) values(?,?,?,?,?,?,?)";
	private static String CFGFEE_DELETE = "delete t_cfgfee where feetype=? and transcode=? and cardtype=? and transtype=?";
	@Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
	@Override
	public int delete(String sql, Object[] args) {
		return jdbcTemplate.update(sql, args);
	}
	@Override
	public List<Cfgfee> findCfgfee() {
		return jdbcTemplate.query(this.CFGFEE_QUERY_ALL+" order by feetype,cardtype,transcode,ratetype", new BeanPropertyRowMapper(Cfgfee.class));
	}

	@Override
	public List<Cfgfee> findCfgfee(String sql, Object[] args) {
		return jdbcTemplate.query(sql,args,new BeanPropertyRowMapper(Cfgfee.class));
	}

	@Override
	public Cfgfee getCfgfee(Integer feetype, Integer transcode,
			Integer cardtype, Integer transtype) {
		try{
			return jdbcTemplate.queryForObject(CFGFEE_QUERY_ALL+" and feetype = ? and transcode = ? and cardtype = ? and transtype = ?", 
				new Object[]{feetype,transcode,cardtype,transtype}, new BeanPropertyRowMapper(Cfgfee.class));
		}catch(Exception e){
			return null;
		}
		
	}
	@Override
	public int update(String sql, Object[] args) {
		return jdbcTemplate.update(sql, args);
	}
	@Override
	public Transtype getTranstype(int transtype) {
		return jdbcTemplate.queryForObject("select transtype, transname, displayflag, useflag from t_transtype where transtype = ? ",  new BeanPropertyRowMapper(Transtype.class),transtype);
	}
	@Override
	public int add(Cfgfee cfgfee) {
		
		return this.update(this.CFGFEE_ADD, 
				new Object[]{cfgfee.getFeetype(),
							 cfgfee.getTranscode(),
							 cfgfee.getCardtype(),
							 cfgfee.getTranstype(),
							 cfgfee.getRatetype(),
							 cfgfee.getRateamt(),
							 cfgfee.getRemark()});
	}
	@Override
	public int update(Cfgfee cfgfee) {
		return this.update(this.CFGFEE_UPDATE, 
				new Object[]{cfgfee.getRatetype(),
							 cfgfee.getRateamt(),
							 cfgfee.getRemark(),
							 cfgfee.getFeetype(),
							 cfgfee.getTranscode(),
							 cfgfee.getCardtype(),
							 cfgfee.getTranstype(),
							 });
	}
	@Override
	public int delete(Integer feetype, Integer transcode, Integer cardtype,
			Integer transtype) {
		return this.delete(this.CFGFEE_DELETE, new Object[]{feetype,transcode,cardtype,transtype});
	}
	@Override
	public List<Cfgfee> findCfgfee(Cfgfee cfgfee) {
		StringBuffer sb = new StringBuffer();
		List<String> param = new ArrayList<String>();
		if(cfgfee!=null){
			if(cfgfee.getCardtype()>0){
				sb.append(" and cardtype = ?");
				param.add(""+cfgfee.getCardtype());
			}
			if(cfgfee.getFeetype()>0){
				sb.append(" and Feetype = ?");
				param.add(""+cfgfee.getFeetype());
			}
			if(cfgfee.getTranscode()>0){
				sb.append(" and Transcode = ?");
				param.add(""+cfgfee.getTranscode());	
			}
			if(cfgfee.getTranstype()>0){
				sb.append(" and Transtype = ?");
				param.add(""+cfgfee.getTranstype());
			}
		}
		sb.append(" order by feetype,cardtype,transcode,ratetype");
		return findCfgfee(sb.toString(),param.size()>0?param.toArray():null);
	}

}
