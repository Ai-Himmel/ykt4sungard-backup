/*
 * CardtyperightServiceImpl.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtyperightServiceImpl.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service.impl;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.dao.CfgDao;
import com.sungard.smartcard.domain.Cardtyperight;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.CardtyperightDao;
import com.sungard.smartcard.modules.system.service.CardtyperightService;
import com.sungard.smartcard.util.DateUtil;

/**
 * [TODO 发卡权限维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@Service
@Transactional
public class CardtyperightServiceImpl implements CardtyperightService{

	@Autowired
	@Qualifier("cardtyperightDaoImpl")
	private CardtyperightDao cardtyperightDao;

	public void setCardtyperightDao(CardtyperightDao cardtyperightDao) {
		this.cardtyperightDao = cardtyperightDao;
	}

	@Override
	public int addCardtyperight(Cardtyperight cardtyperight) throws FunctionException{
		if(cardtyperight.getCardtype()<=0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"卡类型");
		}
		if(cardtyperight.getFeetype()<=0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"收费类型");
		}
		if(cardtyperight.getOpercode()==null){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"操作员");
		}
		cardtyperight.setLastsaved(DateUtil.getCurrentTime());
		return this.cardtyperightDao.add(cardtyperight);
	}

	@Override
	public int deleteCardtyperight(Cardtyperight cardtyperight) throws FunctionException{
		if(cardtyperight.getCardtype()<=0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"卡类型");
		}
		if(cardtyperight.getFeetype()<=0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"收费类型");
		}
		return this.cardtyperightDao.delete(cardtyperight.getCardtype(), cardtyperight.getFeetype());
	}

	@Override
	public List<Cardtyperight> queryCardtyperight(Cardtyperight cardtyperight) throws FunctionException{
		return this.cardtyperightDao.findCardtyperight(cardtyperight);
	}

}
