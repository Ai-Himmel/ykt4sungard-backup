/*
 * FeetypeServiceImpl.java  v1.00  2012-2-20
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	FeetypeServiceImpl.java  v1.00 2012-2-20
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service.impl;

import java.util.ArrayList;
import java.util.List;

import javax.swing.text.AbstractDocument.Content;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.Constant;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.FeetypeDao;
import com.sungard.smartcard.modules.system.dao.impl.FeetypeDaoImpl;
import com.sungard.smartcard.modules.system.service.FeetypeService;

/**
 * [TODO 收费类型维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-20
 * 
 */
@Service
public class FeetypeServiceImpl implements FeetypeService {
	private static final Logger logger = LoggerFactory
			.getLogger(FeetypeServiceImpl.class);
	@Autowired
	@Qualifier("feetypeDaoImpl")
	private FeetypeDao feetypeDao;

	public void setFeetypeDao(FeetypeDao feetypeDao) {
		this.feetypeDao = feetypeDao;
	}

	@Override
	@Transactional
	public List<Feetype> queryAll() {
		// TODO Auto-generated method stub
		return feetypeDao.findFeetype();
	}

	@Override
	@Transactional
	public int addFeetype(Feetype feetype) throws FunctionException {
		if (feetype == null || feetype.getFeetype() == null) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "类型代码");
		}
		if (feetype.getFeetype() >= Constant.FEETYPE_COMM
				|| feetype.getFeetype() < 10) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_ERROR, "类型代码");
		}
		if ("1".equals(feetype.getBoardfeeflag())) {
			if (feetype.getBoardfeerate() == null) {
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "搭伙费费率");
			}
		} else {
			feetype.setBoardfeeflag("0");
			feetype.setBoardfeerate(0.00);
		}
		return feetypeDao.addFeetype(feetype);
	}

	@Override
	@Transactional
	public Feetype queryByFeetype(String feetype) throws FunctionException {
		if (StringUtils.isBlank(feetype)) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "收费类别");
		}
		return feetypeDao.getFeetype(feetype);
	}

	@Override
	@Transactional
	public List<Feetype> queryByParam(Feetype feetype) {
		return feetypeDao.findFeetype(feetype);
	}

	@Override
	@Transactional
	public int removeFeetype(String feetype) throws FunctionException {
		if (StringUtils.isBlank(feetype)) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "收费类别");
		}
		return feetypeDao.removeFeetype(feetype);
	}

	@Override
	@Transactional
	public int updateFeetype(Feetype feetype) throws FunctionException {
		if (feetype == null || feetype.getFeetype() == null) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "类型代码");
		}
		if (feetype.getFeetype() >= Constant.FEETYPE_COMM
				|| feetype.getFeetype() < 10) {
			throw new FunctionException(RetCode.SYSTEM_PARAM_ERROR, "类型代码");
		}
		Feetype sfeetype = this.queryByFeetype("" + feetype.getFeetype());
		if ("1".equals(feetype.getBoardfeeflag())) {
			if (feetype.getBoardfeerate() == null) {
				throw new FunctionException(RetCode.SYSTEM_PARAM_NULL, "搭伙费费率");
			}
			sfeetype.setBoardfeeflag("1");
			sfeetype.setBoardfeerate(feetype.getBoardfeerate());
		} else {
			sfeetype.setBoardfeeflag("0");
			sfeetype.setBoardfeerate(0.00);
		}
		sfeetype.setFeename(feetype.getFeename());
		sfeetype.setRemark(feetype.getRemark());
		sfeetype.setUseflag(feetype.getUseflag());
		return feetypeDao.updateFeetype(sfeetype);
	}

}
