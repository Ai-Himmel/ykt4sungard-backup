package com.sungard.smartcard.modules.system.service.impl;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.CollectionUtils;

import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Purse;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.PurseDao;
import com.sungard.smartcard.modules.system.service.PurseService;

/**
 * [TODO 钱包信息维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
@Service
@Transactional
public class PurseServiceImpl implements PurseService {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory.getLogger(PurseServiceImpl.class);
	
	@Autowired
	@Qualifier("purseDaoImpl")
	private PurseDao purseDao;
	

	public void setPurseDao(PurseDao purseDao) {
		this.purseDao = purseDao;
	}

	

	private boolean checkPramary(Purse purse) throws FunctionException{
		if (purse == null || purse.getPurseno()==null || purse.getPurseno() == 0) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "钱包表");
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
	public List<Purse> queryAll() {
		return purseDao.findDomains();
	}

	@Override
	public List<Purse> queryByParam(Purse purse) {
		Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
		if(purse!=null){
			if (purse.getPurseno()>0) {
				wheres.put("purseno", purse.getPurseno());
			}
			if(StringUtils.isNotBlank(purse.getPursename())){
				wheres.put("pursename like ?", "%" + purse.getPursename() + "%");
			}
		}
		return purseDao.findDomains(wheres);
	}

	@Override
	public int addPurse(Purse purse) throws FunctionException {
		checkPramary(purse);
		if(StringUtils.isBlank(purse.getPursename())){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "钱包名");
		}
		if(purse.getCardmaxbal()==0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "最大存款金额");
		}
		Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
		wheres.put("(purseno", purse.getPurseno());
		wheres.put(purseDao.OR+"pursename)", purse.getPursename());
		if(!CollectionUtils.isEmpty(purseDao.findDomains(wheres))){
			throw new FunctionException(RetCode.IS_EXISTS, "钱包号或钱包名");
		}
		Map<Object, Object> domain = new LinkedHashMap<Object, Object>();
		domain.put("purseno", purse.getPurseno());
		domain.put("pursename", purse.getPursename());
		domain.put("cardmaxbal", purse.getCardmaxbal());
		if(StringUtils.isBlank(purse.getUseflag())){
			domain.put("useflag", 1);
		}else{
			domain.put("useflag", purse.getUseflag());
		}
		return successRows(purseDao.addDomain(domain));
	}

	@Override
	public int updatePurse(Purse purse) throws FunctionException {
		if(checkPramary(purse)){
			if(purse.getCardmaxbal()<=0){
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "最大存款金额","参数必须为正整数");
			}
			Map<Object, Object> wheres = new LinkedHashMap<Object, Object>();
			wheres.put("pursename", purse.getPursename());
			if(!CollectionUtils.isEmpty(purseDao.findDomains(wheres))){
				throw new FunctionException(RetCode.IS_EXISTS, "钱包名");
			}
			
			Map<Object, Object> domain = new LinkedHashMap<Object, Object>();
			domain.put("purseno", purse.getPurseno());
			domain.put("pursename", purse.getPursename());
			domain.put("cardmaxbal", purse.getCardmaxbal());
			if(StringUtils.isBlank(purse.getUseflag())){
				domain.put("useflag", 1);
			}else{
				domain.put("useflag", purse.getUseflag());
			}
			return purseDao.updateDomain(domain, purse.getPurseno());
		}else{
			return -1;
		}
		
	
	}

	@Override
	public int removePurse(Purse purse) throws FunctionException {
		if(checkPramary(purse)){
			return purseDao.removeDomain(purse.getPurseno());
		}else{
			return -1;
		}
	}

}
