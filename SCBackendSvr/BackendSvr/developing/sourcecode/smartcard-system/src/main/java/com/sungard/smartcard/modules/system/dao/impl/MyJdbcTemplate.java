package com.sungard.smartcard.modules.system.dao.impl;

import java.util.List;

import org.springframework.dao.DataAccessException;
import org.springframework.dao.support.DataAccessUtils;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.RowMapperResultSetExtractor;
import org.springframework.util.CollectionUtils;

/**
 * [TODO ]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
public class MyJdbcTemplate extends JdbcTemplate {

	public <T> T queryForObject(String sql, RowMapper<T> rowMapper,
			Object... args) throws DataAccessException {
		List<T> results = query(sql, args, new RowMapperResultSetExtractor<T>(rowMapper, 1));
		if(CollectionUtils.isEmpty(results)){
			return null;
		}
		return DataAccessUtils.requiredSingleResult(results);
	}
	
	
}
