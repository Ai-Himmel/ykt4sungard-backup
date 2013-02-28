package org.king.security.service.impl;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TEpayRecordDAO;
import org.king.security.dao.TEpayShopinfoDAO;
import org.king.security.domain.TEpayRecord;
import org.king.security.service.PayManageService;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.orm.hibernate3.LocalSessionFactoryBean;

public class PayManageServiceImpl implements PayManageService{

	private static Log log = LogFactory.getLog(PayManageServiceImpl.class);
	
	private JdbcTemplate jdbcTemplate;

    private LocalSessionFactoryBean lsfb;
    
    private TEpayShopinfoDAO tShopinfoDAO;
    
    private TEpayRecordDAO tEpayRecordDAO;
    
	public static void setLog(Log log) {
		PayManageServiceImpl.log = log;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public void setLsfb(LocalSessionFactoryBean lsfb) {
		this.lsfb = lsfb;
	}

	public void settShopinfoDAO(TEpayShopinfoDAO tShopinfoDAO) {
		this.tShopinfoDAO = tShopinfoDAO;
	}

	public void settEpayRecordDAO(TEpayRecordDAO tEpayRecordDAO) {
		this.tEpayRecordDAO = tEpayRecordDAO;
	}
	//0:预留表头,1:v_shopid,2:v_account,3:v_oid,4:v_amount,5:v_currency,6:v_url,7:v_code,8:v_date,9:v_time
	//11:v_name,12:v_remark1,13:v_remark2
	public String epay(String[] str) {
		TEpayRecord tEpayRecord = new TEpayRecord();
		
		return "1";
	}

	public String epayerrorcode(String code) {
		Map a = jdbcTemplate.queryForMap("select errcode,errmsg from ykt_cur.t_errcode a where a.errcode='"+code+"'");
		String errmeg =	a.get("ERRMSG")==null?"":a.get("ERRMSG").toString();
		a.get(code);
		return errmeg;
	}
	
	public String epaymd5errorcode(String v_oid,String v_status,String v_amount,String v_currency,String key){
		return MyUtils.toMD5(v_oid+v_status+v_amount+v_currency+key);
	}

}
