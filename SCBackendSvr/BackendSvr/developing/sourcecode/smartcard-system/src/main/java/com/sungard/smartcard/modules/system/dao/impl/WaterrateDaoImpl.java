package com.sungard.smartcard.modules.system.dao.impl;


import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import com.sungard.smartcard.dao.impl.BaseDomainDaoImpl;
import com.sungard.smartcard.domain.Waterrate;
import com.sungard.smartcard.modules.system.dao.WaterrateDao;

/**
 * [TODO 脱机水价维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-23
 */
@Repository
public class WaterrateDaoImpl extends BaseDomainDaoImpl<Waterrate> implements WaterrateDao {
	

	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory.getLogger(WaterrateDaoImpl.class);
	

    @Autowired
    private JdbcTemplate jdbcTemplate;


	public WaterrateDaoImpl() {
		super();
		super.setTableName("t_waterrate");
		super.setParamas(new String[]{"feetype", "rate1", "rate2", "rate3","lastsaved"});
		super.setKey("feetype");
	}
    
    

}
