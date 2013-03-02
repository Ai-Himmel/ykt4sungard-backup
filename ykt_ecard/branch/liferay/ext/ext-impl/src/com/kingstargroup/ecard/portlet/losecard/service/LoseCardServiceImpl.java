package com.kingstargroup.ecard.portlet.losecard.service;

import java.util.List;
import java.util.Map;

import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardinfo;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardinfoId;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardshop;
import com.kingstargroup.ecard.util.DateUtil;

public class LoseCardServiceImpl extends LoseCardServiceBase{

	public TLosscardshop getInfoByShopCode(String shopCode)
			throws PortalException {
		return loseCardPersistence.getInfoByShopCode(shopCode);
	}

	public void add(String shopCode,String shopName) throws PortalException {
		TLosscardshop info = new TLosscardshop();
		info.setShopcode(shopCode);
		info.setShopname(shopName);
		loseCardPersistence.add(info);
		//return info;
	}

	public boolean update(String shopCode, String shopName, String addr,
			String tel, String getCardPlace)
			throws PortalException {
		TLosscardshop info = loseCardPersistence.getInfoByShopCode(shopCode);
		info.setShopname(shopName);
		info.setAddr(addr);
		info.setGetcardplace(getCardPlace);
		info.setTel(tel);
		info.setLastsaved(DateUtil.getNow("yyyyMMddHHmmss"));
		try {
			loseCardPersistence.update(info);
			return true;
		} catch (PortalException pe) {
			throw pe;
		}
	}

	public Map getStuempInfo(String cardPhyId) throws PortalException {
		return loseCardPersistence.getStuempInfo(cardPhyId);
	}

	public String cardStatus(String cardPhyId) throws PortalException {
		return loseCardPersistence.cardStatus(cardPhyId);
	}

	public void addLossCardInfo(String shopcode,int cardno,String cardphyid,String getcardplace,
			String addr,String tel) throws PortalException {
		String nowDate = DateUtil.getNow("yyyyMMdd");
		int defDay= Integer.parseInt(KSConfiguration.getInstance().getProperty("lose_card_end_date", "0"));
		String endDate = DateUtil.getOtherDate(nowDate,defDay);
		
		TLosscardinfo cardinfo = loseCardPersistence.getCardInfoBy(shopcode,cardno,new Integer(1));
		TLosscardinfoId cardinfoId = null;
		if (cardinfo==null){
			cardinfo = new TLosscardinfo();
			cardinfoId = new TLosscardinfoId();
			cardinfoId.setCardno(new Integer(cardno));
			cardinfoId.setRegdate(nowDate);
			cardinfoId.setShopcode(shopcode);
			cardinfo.setCardphyid(cardphyid);
			cardinfo.setIdtype(new Integer(0));
			cardinfo.setStatus(new Integer(1));
			cardinfo.setId(cardinfoId);
			cardinfo.setRegtime(DateUtil.getNow("HHmmss"));
			cardinfo.setEnddate(endDate);
		}else{
			cardinfoId = cardinfo.getId();
		}
		 
		cardinfo.setGetcardplace(getcardplace);
		cardinfo.setAddr(addr);
		cardinfo.setTel(tel);
		loseCardPersistence.addLossCardInfo(cardinfo);
		//return info;
	}

	public List getLossCardBy(String shopCode, Integer cardNo)
			throws PortalException {
		String regDate = DateUtil.getNow("yyyyMMdd");
		return loseCardPersistence.getLossCardBy(shopCode, cardNo, regDate);
	}

	public List getLossCardInfo(String shopCode, String bDate, String eDate,
			Integer cardNo, String showCardNo, String StuempNo, String custName,
			String cardStatus) throws PortalException {
		return loseCardPersistence.getLossCardInfo(shopCode, bDate, eDate, cardNo, showCardNo, StuempNo, custName,cardStatus);
	}

	public List getCardType() throws PortalException {
		return loseCardPersistence.getCardType();
	}

	public String getCardPhyId(Integer cardNo) throws PortalException {
		return loseCardPersistence.getCardPhyId(cardNo);
	}

	public Map getIdNo(Integer cardNo) throws PortalException {
		return loseCardPersistence.getIdNo(cardNo);
	}

	public int haveCard(String shopCode, Integer cardNo) throws PortalException {
		TLosscardinfo cardinfo = loseCardPersistence.getCardInfoBy(shopCode,cardNo,new Integer(1));
		if (cardinfo==null){
			return 0;
		}else{
			return 1;
		}		
	}

	public void updateLossCardInfo(String shopcode,int cardno,String idType,
			String idNo,String reMark) throws PortalException {
		TLosscardinfo cardinfo = loseCardPersistence.getCardInfoBy(shopcode,cardno,new Integer(1));
		TLosscardinfoId cardinfoId = cardinfo.getId();;
		cardinfo.setId(cardinfoId);
		cardinfo.setGettime(DateUtil.getNow("HHmmss"));
		cardinfo.setGetdate(DateUtil.getNow("yyyyMMdd"));
		cardinfo.setStatus(new Integer(2));
		cardinfo.setIdtype(new Integer(idType));
		cardinfo.setIdno(idNo);
		cardinfo.setRemark(reMark);
		loseCardPersistence.updateLossCardInfo(cardinfo);
	}

	public List getDictListBy(Integer dictNo) throws PortalException {
		return loseCardPersistence.getDictListBy(dictNo);
	}

	public List getLossStatList(String beginDate, String endDate,
			String shopCode) throws PortalException {
		String nowDate = DateUtil.getNow("yyyyMMdd");
		return loseCardPersistence.getLossStatList(beginDate, endDate, nowDate, shopCode);
	}

	public Map getGetCardInfo(String cardNo) throws PortalException {
		return loseCardPersistence.getGetCardInfo(cardNo);
	}
	
	
}
