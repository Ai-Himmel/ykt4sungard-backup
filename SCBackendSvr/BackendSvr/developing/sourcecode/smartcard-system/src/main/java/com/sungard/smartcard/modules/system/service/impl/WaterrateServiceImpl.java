package com.sungard.smartcard.modules.system.service.impl;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Waterrate;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.WaterrateDao;
import com.sungard.smartcard.modules.system.service.WaterrateService;
import com.sungard.smartcard.util.DateUtil;

/**
 * 
 * [TODO 卡物理类型维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-24
 */
@Service
@Transactional
public class WaterrateServiceImpl implements WaterrateService {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory.getLogger(WaterrateServiceImpl.class);
	
	@Autowired
	@Qualifier("waterrateDaoImpl")
	private WaterrateDao waterrateDao;
	

	public void setWaterrateDao(WaterrateDao waterrateDao) {
		this.waterrateDao = waterrateDao;
	}

	

	private boolean checkPramary(Waterrate waterrate) throws FunctionException{
		if (waterrate == null || waterrate.getFeetype()==null || waterrate.getFeetype() == 0) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "收费类别");
		}
		return true;
	}
	
	private int successRows(int rows) throws FunctionException{
		if(rows==0){
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "脱机水价");
		}
		return rows;
	}
	
	@Override
	public List<Waterrate> queryAll() {
		return waterrateDao.findDomains();
	}

	@Override
	public List<Waterrate> queryByParam(Waterrate waterrate) {
		Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
		if(waterrate!=null){
			if (waterrate.getFeetype()>0) {
				wheres.put("feetype", waterrate.getFeetype());
			}
		}
		return waterrateDao.findDomains(wheres);
	}

	@Override
	public int addWaterrate(Waterrate waterrate) throws FunctionException {
		checkPramary(waterrate);
		if(waterrateDao.getDomain(waterrate.getFeetype())!=null){
			throw new FunctionException(RetCode.IS_EXISTS, "脱机水价");
		}
		Map<Object, Object> domain = new LinkedHashMap<Object, Object>();
		domain.put("feetype", waterrate.getFeetype());
		domain.put("rate1", waterrate.getRate1());
		domain.put("rate2", waterrate.getRate2());
		domain.put("rate3", waterrate.getRate3());
		domain.put("lastsaved",DateUtil.getCurrentTime());
		return waterrateDao.addDomain(domain);
	}

	@Override
	public int updateWaterrate(Waterrate waterrate) throws FunctionException {
		if(checkPramary(waterrate)){
			Map<Object, Object> domain = new LinkedHashMap<Object, Object>();
			domain.put("rate1", waterrate.getRate1());
			domain.put("rate2", waterrate.getRate2());
			domain.put("rate3", waterrate.getRate3());
			domain.put("lastsaved",DateUtil.getCurrentTime());
			return successRows(waterrateDao.updateDomain(domain, waterrate.getFeetype()));
		}else{
			return -1;
		}
		
	
	}

	@Override
	public int removeWaterrate(Waterrate waterrate) throws FunctionException {
		if(checkPramary(waterrate)){
			return successRows(waterrateDao.removeDomain(waterrate.getFeetype()));
			
		}else{
			return -1;
		}
	}

}
