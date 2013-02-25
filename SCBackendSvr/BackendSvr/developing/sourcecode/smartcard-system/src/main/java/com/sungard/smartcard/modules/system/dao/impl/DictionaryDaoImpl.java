package com.sungard.smartcard.modules.system.dao.impl;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.dao.impl.BaseDomainDaoImpl;
import com.sungard.smartcard.domain.Dictionary;
import com.sungard.smartcard.modules.system.dao.DictionaryDao;

/**
 * [TODO 数据字典维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
@Repository
public class DictionaryDaoImpl extends BaseDomainDaoImpl<Dictionary> implements DictionaryDao {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory.getLogger(DictionaryDaoImpl.class);
	

	@Autowired
	private JdbcTemplate jdbcTemplate;
	
	
	

	public DictionaryDaoImpl() {
		super();
		super.setTableName("t_dictionary");
		super.setParamas(new String[]{"dicttype", "dicttypename", "dictval", "dictcaption"});
	}

	
}
