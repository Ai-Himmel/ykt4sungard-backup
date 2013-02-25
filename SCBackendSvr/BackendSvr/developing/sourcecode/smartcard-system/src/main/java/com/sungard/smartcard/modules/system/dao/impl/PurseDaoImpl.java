package com.sungard.smartcard.modules.system.dao.impl;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.dao.impl.BaseDomainDaoImpl;
import com.sungard.smartcard.domain.Purse;
import com.sungard.smartcard.modules.system.dao.PurseDao;

/**
 * [TODO 钱包信息维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-23
 */
@Repository
public class PurseDaoImpl extends BaseDomainDaoImpl<Purse> implements PurseDao {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory.getLogger(PurseDaoImpl.class);
	

    @Autowired
    private JdbcTemplate jdbcTemplate;


	public PurseDaoImpl() {
		super();
		super.setTableName("t_purse");
		super.setParamas(new String[]{"purseno", "pursename", "cardmaxbal", "useflag"});
		super.setKey("purseno");
	}

	

}
