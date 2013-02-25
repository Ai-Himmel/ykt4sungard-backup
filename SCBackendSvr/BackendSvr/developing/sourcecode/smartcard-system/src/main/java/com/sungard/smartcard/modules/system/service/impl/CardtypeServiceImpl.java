/*
 * CardtypeServiceImpl.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtypeServiceImpl.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service.impl;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.Constant;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Cardtype;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.CardtypeDao;
import com.sungard.smartcard.modules.system.service.CardtypeService;

/**
 * [TODO 类功能说明、代码引用实例.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@Service
public class CardtypeServiceImpl implements CardtypeService{
	private static final Logger logger = LoggerFactory.getLogger(CardtypeServiceImpl.class);
	
	@Autowired
	@Qualifier("cardtypeDaoImpl")
	private CardtypeDao cardtypeDao;
	
	public void setCardtypeDao(CardtypeDao cardtypeDao) {
		this.cardtypeDao = cardtypeDao;
	}

	/*
	 * (添加卡类型)
	 * 
	 * @see com.sungard.smartcard.modules.system.service.CardtypeService#add(com.sungard.smartcard.domain.Cardtype)
	 * 卡类型id通过数据库sequence获得
	 * 如果卡名称已存在则不能添加
	 * 库里已有匿名卡不能再添加匿名卡
	 * 匿名卡收费类型不能为空
	 */
	@Override
	@Transactional
	public boolean add(Cardtype cardtype) throws FunctionException {
		List l = cardtypeDao.findbyparam("select * from t_cardtype where cardtypename = ?", new Object[]{cardtype.getCardtypename()});
		if(l!=null&&l.size()>0){
			throw new FunctionException(RetCode.E_EXIST_CARDTYPENAME,cardtype.getCardtypename());
		}
		if("1".equals(cardtype.getAnonymflag())){
			l = cardtypeDao.findbyparam("select * from t_cardtype where anonymflag=? and cardtype<>?", new Object[]{1,0});
			if(l!=null&&l.size()>0){
				throw new FunctionException(RetCode.E_EXIST_ANONYMCARDTYPE,"");
			}
			if(cardtype.getFeetype()<=0){
				throw new FunctionException(RetCode.E_NULL_ANONYMCARD_FEETYPE,"");
			}
		}
		int cardtypeid = cardtypeDao.getNetCardtype();
		cardtype.setCardtype(cardtypeid);
		cardtype.setUseflag("0");
		return cardtypeDao.add(cardtype)>0;
	}

	@Override
	@Transactional
	public boolean delete(int cardtype) throws FunctionException {
		if(cardtype<=0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"此卡类型");
		}
		if(cardtype==Constant.CARDTYPE_TEMP){
			throw new FunctionException(RetCode.E_CARDTYPE_SYSRESERVED,"");
		}
		Cardtype temp = this.cardtypeDao.getCardtype(""+cardtype);
		if(temp==null){
			throw new FunctionException(RetCode.RECORD_NOT_EXIST,"此卡类型");
		}
		if("1".equals(temp.getUseflag())){
			throw new FunctionException(RetCode.E_CARDTYPE_USED,"此卡类型");
		}
		return this.delete(cardtype);
	}

	@Override
	@Transactional
	public List<Cardtype> query(Cardtype cardtype) throws FunctionException {
		return this.cardtypeDao.findCardtype(cardtype);
	}

	@Override
	@Transactional
	public boolean update(Cardtype cardtype) throws FunctionException {
		if(cardtype==null||cardtype.getCardtype()<=0){
			throw new FunctionException(RetCode.SYSTEM_PARAM_NULL,"卡类型");
		}
		List l = cardtypeDao.findbyparam("select * from t_cardtype where cardtypename = ? and cardtype<>?", new Object[]{cardtype.getCardtypename(),cardtype.getCardtype()});
		if(l!=null&&l.size()>0){
			throw new FunctionException(RetCode.E_EXIST_CARDTYPENAME,cardtype.getCardtypename());
		}
		if("1".equals(cardtype.getAnonymflag())){
			l = cardtypeDao.findbyparam("select * from t_cardtype where anonymflag=? and cardtype<>?", new Object[]{1,cardtype.getCardtype()});
			if(l!=null&&l.size()>0){
				throw new FunctionException(RetCode.E_EXIST_ANONYMCARDTYPE,"");
			}
			if(cardtype.getFeetype()<=0){
				throw new FunctionException(RetCode.E_NULL_ANONYMCARD_FEETYPE,"");
			}
		}
		Cardtype scardtype = this.cardtypeDao.getCardtype(""+cardtype.getCardtype());
		if(scardtype==null){
			throw new FunctionException(RetCode.E_NOTEXIST_CARDTYPE,"");
		}
		scardtype.setCardcostfee(cardtype.getCardcostfee());
		scardtype.setFixdaycnt(cardtype.getFixdaycnt());
		scardtype.setPurpose(cardtype.getPurpose());
		scardtype.setCardphytype(cardtype.getCardphytype());
		if(Constant.CARDTYPE_TEMP!=cardtype.getCardtype()){
			scardtype.setCardtypename(cardtype.getCardtypename());
			scardtype.setAnonymflag(cardtype.getAnonymflag());
			scardtype.setReuseable(cardtype.getReuseable());
			scardtype.setRenewable(cardtype.getRenewable());
			scardtype.setRecycleable(cardtype.getRecycleable());
			scardtype.setFeetype(cardtype.getFeetype());
			scardtype.setFixdayflag(cardtype.getFixdayflag());
		}else{
			if(!StringUtils.equals(scardtype.getAnonymflag(), cardtype.getAnonymflag())||
			   !StringUtils.equals(scardtype.getReuseable(), cardtype.getReuseable())||
			   !StringUtils.equals(scardtype.getRenewable(), cardtype.getRenewable())||
			   !StringUtils.equals(scardtype.getRecycleable(), cardtype.getRecycleable())||
			   !StringUtils.equals(scardtype.getFixdayflag(), cardtype.getFixdayflag())){
				throw new FunctionException(RetCode.E_TMPCARDPARA_FORBID_UPDATED,"");
			}else{
				if(scardtype.getFixdaycnt()<=0){
					throw new FunctionException(RetCode.E_TMPCARD_NEED_FIXDAYCNT,"");
				}
			}
		}
		//scardtype.setCardtype(cardtype.getCardtype());
		scardtype.setMultipurse(cardtype.getMultipurse());
		//scardtype.setUseflag(cardtype.getUseflag());
		return this.cardtypeDao.update(scardtype)>0; 
	}

}
