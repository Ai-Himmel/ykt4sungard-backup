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

import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.modules.system.dao.FeetypeDao;



/**
 * [TODO 收费类型基本的数据库实现.]
 * 
 * @author <a href="mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-20
 * 
 */
@Repository
public class FeetypeDaoImpl implements FeetypeDao{
	
	private static final Logger logger = LoggerFactory.getLogger(FeetypeDaoImpl.class);
	
	private static String FEETYPE_QUERY_ALL = "select feetype, feename, boardfeeflag, useflag, remark, boardfeerate from t_feetype";
	private static String FEETYPE_UPDATE_BYFEETYPE = "update t_feetype set feename=?,boardfeeflag=?,useflag=?,remark=?,boardfeerate=? where feetype = ?";
	private static String FEETYPE_DELETE_BYFEETYPE = "delete t_feetype where feetype = ?";
	private static String FEETYPE_ADD = "INSERT INTO t_feetype(feetype, feename, boardfeeflag, useflag, remark, boardfeerate) values(?,?,?,?,?,?)";
	@Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
	@Override
	public List<Feetype> findFeetype() {
		// TODO Auto-generated method stub
		return jdbcTemplate.query(FEETYPE_QUERY_ALL, new BeanPropertyRowMapper(Feetype.class));
	}
	@Override
	public int addFeetype(Feetype feetype) {
		// TODO Auto-generated method stub
		return jdbcTemplate.update(FEETYPE_ADD, 
				new Object[]{
				feetype.getFeetype(),
				feetype.getFeename(),
				feetype.getBoardfeeflag(),
				feetype.getUseflag(),
				feetype.getRemark(),
				feetype.getBoardfeerate()
				});
	}
	@Override
	public Feetype getFeetype(String feetype) {
		return jdbcTemplate.queryForObject(FEETYPE_QUERY_ALL+" where 1=1 and feetype = ?",new BeanPropertyRowMapper(Feetype.class), feetype);
	}
	@Override
	public int removeFeetype(String feetype) {
		return jdbcTemplate.update(FEETYPE_DELETE_BYFEETYPE, new Object[]{feetype});
	}
	@Override
	public int updateFeetype(Feetype feetype) {
		return jdbcTemplate.update(FEETYPE_UPDATE_BYFEETYPE, feetype.getFeename(),
				feetype.getBoardfeeflag(),feetype.getUseflag(),feetype.getRemark(),feetype.getBoardfeerate(),feetype.getFeetype());
	}
	@Override
	public List<Feetype> findFeetype(String sql,Object[] args) {
		return jdbcTemplate.query(sql, args, new BeanPropertyRowMapper(Feetype.class));
	}
	@Override
	public List<Feetype> findFeetype(Feetype feetype) {
		StringBuffer sql = new StringBuffer(
		"select feetype, feename, boardfeeflag, useflag, remark, boardfeerate from t_feetype where 1=1");
		List<String> param = new ArrayList<String>();
		if (feetype.getFeetype()>0) {
			sql.append(" and feetype = ?");
			param.add(""+feetype.getFeetype());
		}
		if (StringUtils.isNotBlank(feetype.getFeename())) {
			sql.append(" and feename like ?");
			param.add("%" + feetype.getFeename() + "%");
		}
		if (StringUtils.isNotBlank(feetype.getBoardfeeflag())) {
			sql.append(" and boardfeeflag = ?");
			param.add(feetype.getBoardfeeflag());
		}
		return this.findFeetype(sql.toString(), param.size()>0?param.toArray():null);
	}

}
