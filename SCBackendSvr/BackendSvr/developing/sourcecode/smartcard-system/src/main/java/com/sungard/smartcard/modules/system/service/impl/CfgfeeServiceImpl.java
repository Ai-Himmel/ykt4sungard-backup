/*
 * cfgfeeDaoImpl.java  v1.00  2012-2-21
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	cfgfeeDaoImpl.java  v1.00 2012-2-21
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service.impl;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.Constant;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.dao.CfgDao;
import com.sungard.smartcard.domain.Cfgfee;
import com.sungard.smartcard.domain.Transtype;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.CfgfeeDao;
import com.sungard.smartcard.modules.system.dao.impl.CfgfeeDaoImpl;
import com.sungard.smartcard.modules.system.service.CfgfeeService;

/**
 * [TODO 交易收费信息维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-21
 * 
 */
@Service
public class CfgfeeServiceImpl implements CfgfeeService{
	
	@Autowired
	@Qualifier("cfgfeeDaoImpl")
	private CfgfeeDao cfgfeeDao;
	
	@Autowired
	@Qualifier("cfgDaoImpl")
	private CfgDao CfgDao;
	
	public void setCfgfeeDao(CfgfeeDao cfgfeeDao) {
		this.cfgfeeDao = cfgfeeDao;
	}

	@Override
	@Transactional
	public boolean add(Cfgfee cfgfee,String opercode) throws FunctionException {
		if(cfgfee.getCardtype() ==null||cfgfee.getCardtype()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"卡类型");
		if(cfgfee.getFeetype() ==null||cfgfee.getFeetype()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"消费类型");
		if(cfgfee.getTranstype() ==null||cfgfee.getTranstype()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"交易类型");
		if(cfgfee.getTranscode() ==null||cfgfee.getTranscode()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"交易码");
		if(cfgfeeDao.getCfgfee(cfgfee.getFeetype(), cfgfee.getTranscode(), cfgfee.getCardtype(), Constant.TRANSTYPE_FREE)!=null){
			throw new FunctionException(RetCode.E_CFGFEE_EXIST_FREEFEE,"");
		}
		if(cfgfeeDao.getCfgfee(cfgfee.getFeetype(), cfgfee.getTranscode(), cfgfee.getCardtype(), cfgfee.getTranstype())!=null){
			throw new FunctionException(RetCode.E_CFGFEE_EXIST_FEEITEM,"");
		}
		if(cfgfee.getTranstype()==Constant.TRANSTYPE_FREE){
			cfgfee.setRateamt(Double.valueOf(0.00));
			cfgfee.setRemark("0");
			cfgfee.setRatetype(0);
		}else{
			Transtype transtype = cfgfeeDao.getTranstype(cfgfee.getTranstype());
			if(transtype==null){
				throw new FunctionException(RetCode.SYSTEM_EXCEPTION,"");
			}
			if(cfgfee.getRatetype()==2){
				cfgfee.setRemark(transtype.getTransname()+":"+cfgfee.getRateamt()+"%");
			}else if(cfgfee.getRatetype()==1){
				cfgfee.setRemark(transtype.getTransname()+":"+cfgfee.getRateamt()+"元");
			}else{
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"收费方式");
			}
		}
		if(cfgfeeDao.add(cfgfee)>0){
			//修改版本
			CfgDao.updateCfgver(opercode);
			return true;
		}
		return false;
	}

	@Override
	@Transactional
	public boolean delete(Cfgfee cfgfee,String opercode) throws FunctionException {
		if(cfgfee.getCardtype() ==null||cfgfee.getCardtype()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"卡类型");
		if(cfgfee.getFeetype() ==null||cfgfee.getFeetype()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"消费类型");
		if(cfgfee.getTranstype() ==null||cfgfee.getTranstype()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"交易类型");
		if(cfgfee.getTranscode() ==null||cfgfee.getTranscode()<=0)
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"交易码");
		if(cfgfeeDao.delete(cfgfee.getFeetype(), cfgfee.getTranscode(), cfgfee.getCardtype(), cfgfee.getTranstype())>0){
			//修改交易码配置的标志
			cfgfeeDao.update("update t_transcode set feeflag=? where feeflag=? and transcode not in (select distinct transcode from t_cfgfee)", new Object[]{0,1});
			//修改版本号
			CfgDao.updateCfgver(opercode);
			return true;
		}else{
			return false;
		}
	}

	@Override
	@Transactional
	public List<Cfgfee> findCfgfee(Cfgfee cfgfee) {
		return this.cfgfeeDao.findCfgfee(cfgfee);
	}

	@Override
	@Transactional
	public Cfgfee getCfgfee(Integer feetype, Integer transcode,
			Integer cardtype, Integer transtype) throws FunctionException {
		return this.cfgfeeDao.getCfgfee(feetype, transcode, cardtype, transtype);
	}
	
	@Override
	@Transactional
	public boolean update(Cfgfee cfgfee,String opercode) throws FunctionException {
		if(Constant.TRANSTYPE_FREE == cfgfee.getTranstype()){
			throw new FunctionException(RetCode.E_CFGFEE_FREEITEM_UPD,"");
		}
		Cfgfee o = this.getCfgfee(cfgfee.getFeetype(), cfgfee.getTranscode(), cfgfee.getCardtype(), cfgfee.getTranstype());
		if(o==null){
			throw new FunctionException(RetCode.RECORD_NOT_EXIST,"");
		}
		Transtype transtype = cfgfeeDao.getTranstype(cfgfee.getTranstype());
		if(cfgfee.getRatetype()==2){
			cfgfee.setRemark(transtype.getTransname()+":"+cfgfee.getRateamt()+"%");
		}else if(cfgfee.getRatetype()==1){
			cfgfee.setRemark(transtype.getTransname()+":"+cfgfee.getRateamt()+"元");
		}else{
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"收费方式");
		}
		if(this.cfgfeeDao.update(cfgfee)>0){
			//修改版本
			CfgDao.updateCfgver(opercode);
			return true;
		}
		return false;
	}

}
