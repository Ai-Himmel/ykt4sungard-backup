/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import org.apache.commons.beanutils.BeanUtils;
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
	
	public static TCifDept getDept(String deptNo) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
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
	public static void processLostCard(String stuempNo, String cardId)
    throws PortalException
{
    CardPersistence cardPst = (CardPersistence)getPersistence(com.kingstargroup.ecard.hibernate.card.CardPersistence.class.getName());
    SysDatePersistence sysPst = (SysDatePersistence)getPersistence(com.kingstargroup.ecard.hibernate.sysdate.SysDatePersistence.class.getName());
    String customerId = CustomerUtil.getCustomerByStuempNo(stuempNo).getCutId().toString();
    Transaction t = beginTransaction();
    try
    {
        TPifCard card = cardPst.getCardById(new Integer(cardId));
        if(card == null)
            throw new ProcessCardLossException();
        if(card.getStateId().equals("2000"))
            throw new CardAlreadyOffException();
        if(card.getStateId().charAt(1) == '1')
            throw new CardAlreadyLostException();
        String dateTime = sysPst.getSysDate(0);
        String operateDate = dateTime.substring(0, 8);
        String operateTime = dateTime.substring(8);
        String endDateTime = sysPst.getSysDate(cardPst.getReapplyDays());
        TPifCardlossinfoKey lossKey = new TPifCardlossinfoKey();
        lossKey.setCardId(card.getCardId());
        lossKey.setOperateDate(operateDate);
        lossKey.setOperateTime(operateTime);
        TPifCardlossinfo lossInfo = new TPifCardlossinfo();
        lossInfo.setId(lossKey);
        lossInfo.setBeginDate(operateDate);
        lossInfo.setEndDate(endDateTime.substring(0, 8));
        lossInfo.setStateId(Integer.valueOf(String.valueOf('1')));
        cardPst.addCardLossInfo(lossInfo);
        if(card.getStateId().charAt(2) == '0')
        {
            TTifBlackSheet blackSheet = new TTifBlackSheet();
            blackSheet.setCardId(card.getCardId());
            blackSheet.setIsAd(new Integer(0));
            blackSheet.setOperateDate(operateDate);
            blackSheet.setOperateTime(operateTime);
            blackSheet.setStateId(new Integer(1));
            blackSheet.setVolume(dateTime.substring(2));
            blackSheet.setValiddate("501230121212");
            cardPst.addBlackSheet(blackSheet);
            TTifMeslist mesList = new TTifMeslist();
            FastStringBuffer mesContent = new FastStringBuffer();
            mesContent.append("<CARDID>").append(card.getCardId()).append("</CARDID>").append("<VERNUM>").append(blackSheet.getVolume()).append("</VERNUM>").append("<ADDDELSIGN>").append(blackSheet.getIsAd()).append("</ADDDELSIGN>");
            mesList.setIncontent(mesContent.toString());
            mesList.setFunid(new Integer(0xe30d5));
            mesList.setLevel(new Integer(3));
            mesList.setCardNo(card.getCardId());
            mesList.setMaxSendCnt(new Integer(10));
            mesList.setDelFlag("0");
            mesList.setEcode(new Integer(9999));
            mesList.setStateid(new Integer(3));
            mesList.setIndt(dateTime);
            mesList.setRecvcount(Integer.valueOf("0"));
            mesList.setSeq(Integer.valueOf("0"));
            mesList.setMsgtype(Integer.valueOf("1"));
            List subsysList = cardPst.getSubSysIdByTypeAndState(12, 3);
            for(int i = 0; i < subsysList.size(); i++)
            {
                TTifMeslist cloneMesList = new TTifMeslist();
                BeanUtils.copyProperties(cloneMesList, mesList);
                cloneMesList.setDeviceId(((TPifSubsystem)subsysList.get(i)).getSystemId());
                cardPst.addMsg(cloneMesList);
            }

        }
       // card.setStateId("1100");
        String oldstateId = card.getStateId();
		//System.out.println("oldstarted="+oldstateId);
		oldstateId =oldstateId.substring(0,1)+"1"+oldstateId.substring(2,4);
		//System.out.println("oldstarted="+oldstateId);
		card.setStateId(oldstateId);
        
        cardPst.update(card);
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
        tradeSerial.setSerialType(new Integer(0xe30d1));
        tradeSerial.setCustomerId(Integer.valueOf(customerId));
        tradeSerial.setCardId(card.getCardId());
        cardPst.addTradeSerial(tradeSerial);
        t.commit();
    }
    catch(PortalException e)
    {
        t.rollback();
        e.printStackTrace();
        throw e;
    }
    catch(Exception he)
    {
        t.rollback();
        he.printStackTrace();
        throw new DBSystemException(he);
    }
    finally
    {
        closeSession();
    }
    return;
}

}
