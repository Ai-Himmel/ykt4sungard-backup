/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.log4j.Logger;
import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.CardAlreadyLostException;
import com.kingstargroup.ecard.exceptions.CardAlreadyOffException;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.exceptions.ProcessCardLossException;
import com.kingstargroup.ecard.hibernate.card.CardPersistence;
import com.kingstargroup.ecard.hibernate.card.TCifDept;
import com.kingstargroup.ecard.hibernate.card.TPifCard;
import com.kingstargroup.ecard.hibernate.card.TPifCardlossinfo;
import com.kingstargroup.ecard.hibernate.card.TPifCardlossinfoKey;
import com.kingstargroup.ecard.hibernate.card.TPifSubsystem;
import com.kingstargroup.ecard.hibernate.card.TTifBlackSheet;
import com.kingstargroup.ecard.hibernate.card.TTifMeslist;
import com.kingstargroup.ecard.hibernate.card.TTifTradeserial;
import com.kingstargroup.ecard.hibernate.sysdate.SysDatePersistence;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.lang.FastStringBuffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: CardUtil.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CardUtil extends BasicUtil {
	/**
	 * Description:
	 * @param customerId
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static List getAvailableCards(String customerId) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class.getName());
		List cards = null;
		Transaction t = beginTransaction();		
		try {
			cards = persistence.getAvailableCards(customerId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return cards;	
	}
	
	public static TCifDept getDept(String deptNo)  throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class.getName());		
		TCifDept dept = null;
		Transaction t = beginTransaction();
		try {
			dept = persistence.getDept(deptNo);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();			
		}
		return dept;
	}
	
	public static TPifCard getCardById(Integer cardId) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class.getName());		
		TPifCard card = null;
		Transaction t = beginTransaction();
		try {
			card = persistence.getCardById(cardId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();			
		}
		return card;
	}
	
	/**
	 * Description:
	 * @param customerId
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TPifCard getCurrentCard(String customerId) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class.getName());
		Transaction t = beginTransaction();
		TPifCard card = null;		
		try {
			card = persistence.getCurrentValidCard(customerId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return card;
	}
	
	/**
	 * Description:
	 * @param customerId
	 * @param state
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static int getCardStatus(String customerId, String state) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class.getName());		
		int status = 0;	
		Transaction t = beginTransaction();
		try {
			TPifCard card = persistence.getCardByCusIdAndState(customerId, state);
			if (card != null) {
				int type = card.getTypeId().intValue();
				if (type == 1) {
					status = 100559;//该客户正式卡未挂失,不能办临时卡
				} else {
					status = 100560;//该客户有一张临时卡可正常使用,不能再办临时卡
				}
			}
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return status;
	}
	
	/**
	 * Description:根据用户的学/工号挂失对应的卡
	 * @param customerId
	 * Modify History:
	 */
	public static void processLostCard(String stuempNo, String cardId) throws PortalException {
		CardPersistence cardPst = (CardPersistence) getPersistence(CardPersistence.class.getName());
		SysDatePersistence sysPst = (SysDatePersistence) getPersistence(SysDatePersistence.class.getName());
		String customerId = CustomerUtil.getCustomerByStuempNo(stuempNo).getCutId().toString();
		Transaction t = beginTransaction();
		try {			
			TPifCard card = cardPst.getCardById(new Integer(cardId));//先得到对应的主卡对象			
			if (card == null) {
				throw new ProcessCardLossException();
			}
			/*
			 * 如果卡已经为被注销状态
			 */
			if (card.getStateId().equals(EcardConstants.CARD_WRITE_OFF_STATUS)) {
				throw new CardAlreadyOffException();
			}
			/*
			 * 如果卡已经为挂失状态
			 */
			if (card.getStateId().charAt(1) == EcardConstants.CARD_LOST_FLAG) {
				throw new CardAlreadyLostException();
			}
			/*
			 * 得到数据库日期时间
			 */
			String dateTime = sysPst.getSysDate(0);
			String operateDate = dateTime.substring(0, 8);
			String operateTime = dateTime.substring(8);
			/*
			 * 得到卡截至日期
			 */
			String endDateTime = sysPst.getSysDate(cardPst.getReapplyDays());
			/*
			 * 设置挂失信息主键
			 */
			TPifCardlossinfoKey lossKey = new TPifCardlossinfoKey();
			lossKey.setCardId(card.getCardId());
			lossKey.setOperateDate(operateDate);
			lossKey.setOperateTime(operateTime);
			/*
			 * 设置挂失信息
			 */
			TPifCardlossinfo lossInfo = new TPifCardlossinfo();
			lossInfo.setId(lossKey);
			lossInfo.setBeginDate(operateDate);
			lossInfo.setEndDate(endDateTime.substring(0, 8));
			lossInfo.setStateId(Integer.valueOf(String.valueOf(EcardConstants.CARD_LOST_FLAG)));
			cardPst.addCardLossInfo(lossInfo);//添加挂失信息到数据库中
			/*
			 * 处理黑名单和广播消息队列
			 */
			if (card.getStateId().charAt(2) == '0') {
				/*
				 * 设置黑名单消息
				 */
				TTifBlackSheet blackSheet = new TTifBlackSheet();
				blackSheet.setCardId(card.getCardId());
				blackSheet.setIsAd(new Integer(0));
				blackSheet.setOperateDate(operateDate);
				blackSheet.setOperateTime(operateTime);
				blackSheet.setStateId(new Integer(1));
				blackSheet.setVolume(dateTime.substring(2));//去掉日期时间的前2位
				blackSheet.setValiddate("501230121212");
				cardPst.addBlackSheet(blackSheet);
				/*
				 * 设置广播名单信息
				 */
				TTifMeslist mesList = new TTifMeslist();
				//mesList.setMesid(new Integer(cardPst.getKeyvalueByCode("T_TIF_MESLIST")));
				FastStringBuffer mesContent = new FastStringBuffer();
				mesContent.append("<CARDID>")
						.append(card.getCardId())
						.append("</CARDID>")
						.append("<VERNUM>")
						.append(blackSheet.getVolume())
						.append("</VERNUM>")
						.append("<ADDDELSIGN>")
						.append(blackSheet.getIsAd())
						.append("</ADDDELSIGN>");
				mesList.setIncontent(mesContent.toString());
				mesList.setFunid(new Integer(930005));
				mesList.setLevel(new Integer(3));
				mesList.setCardNo(card.getCardId());//set card_no
				mesList.setMaxSendCnt(new Integer(3));//magic number 3
				mesList.setDelFlag("0");
				mesList.setEcode(new Integer(9999));
				mesList.setStateid(new Integer(1));
				mesList.setIndt(dateTime);
				//get subsystem list
				List subsysList = cardPst.getSubSysIdByTypeAndState(12, 3);
				for (int i = 0; i < subsysList.size(); i++) {
					TTifMeslist cloneMesList = new TTifMeslist();
					BeanUtils.copyProperties(cloneMesList, mesList);
					//cloneMesList.setMesid(new Integer(cardPst.getKeyvalueByCode("T_TIF_MESLIST")));//temporary use
					cloneMesList.setDeviceId(((TPifSubsystem) subsysList.get(i)).getSystemId());
					cardPst.addMsg(cloneMesList);
				}							
			}
			/*
			 * 更新卡状态为已挂失
			 */
			card.setStateId("1100");
			cardPst.update(card);
			/*
			 * 插入卡挂失流水
			 */
			TTifTradeserial tradeSerial = new TTifTradeserial();
			tradeSerial.setSerialNo(new Integer(cardPst.getKeyvalueByCode("T_TIF_TRADESERIAL")));
			tradeSerial.setOperateDate(operateDate);
			tradeSerial.setOperateTime(operateTime);
			tradeSerial.setCollectDate(operateDate);
			tradeSerial.setCollectTime(operateTime);
			tradeSerial.setEnteractDate(operateDate);
			tradeSerial.setEnteractTime(operateTime);
			tradeSerial.setMaindeviceId(new Integer(0));
			tradeSerial.setDeviceId(new Integer(0));
			tradeSerial.setOperCode("ecardweb");
			tradeSerial.setSerialState(new Integer(9));
			tradeSerial.setSerialType(new Integer(930001));
			tradeSerial.setCustomerId(Integer.valueOf(customerId));
			tradeSerial.setCardId(card.getCardId());
			cardPst.addTradeSerial(tradeSerial);
			t.commit();			
		} catch(PortalException e) {
			t.rollback();
			throw e;
		} catch(Exception he) {
			t.rollback();
			throw new DBSystemException(he);			
		} finally {
			closeSession();
		}
	}

}
