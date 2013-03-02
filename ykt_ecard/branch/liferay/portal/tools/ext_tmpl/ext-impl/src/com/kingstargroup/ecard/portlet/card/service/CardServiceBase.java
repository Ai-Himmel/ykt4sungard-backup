package com.kingstargroup.ecard.portlet.card.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.area.AreaPersistence;
import com.kingstargroup.ecard.hibernate.card.CardPersistence;
import com.kingstargroup.ecard.hibernate.device.DevicePersistence;
import com.kingstargroup.ecard.hibernate.photo.PhotoPersistence;
import com.kingstargroup.ecard.hibernate.sysdate.SysDatePersistence;
import com.kingstargroup.ecard.hibernate.tradecode.TradeCodePersistence;
import com.kingstargroup.ecard.hibernate.tradedetail.ErrorMsgPersistence;
import com.kingstargroup.ecard.hibernate.tradedetail.GateHisTradeDetailPersistence;
import com.kingstargroup.ecard.hibernate.tradedetail.TradeDetailPersistence;
import com.kingstargroup.ecard.hibernate.util.AreaUtil;
import com.kingstargroup.ecard.hibernate.util.CardUtil;
import com.kingstargroup.ecard.hibernate.util.DeviceUtil;
import com.kingstargroup.ecard.hibernate.util.ErrorMsgUtil;
import com.kingstargroup.ecard.hibernate.util.GateHisTradeDetailUtil;
import com.kingstargroup.ecard.hibernate.util.PhotoUtil;
import com.kingstargroup.ecard.hibernate.util.SysDateUtil;
import com.kingstargroup.ecard.hibernate.util.TradeCodeUtil;
import com.kingstargroup.ecard.hibernate.util.TradeDetailUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class CardServiceBase extends PrincipalBean implements
		CardService, InitializingBean {
	

	public CardService getCardService() {
		return cardService;
	}
	public void setCardService(CardService cardService) {
		this.cardService = cardService;
	}
	public CardPersistence getCardPersistence() {
		return cardPersistence;
	}
	public void setCardPersistence(CardPersistence cardPersistence) {
		this.cardPersistence = cardPersistence;
	}
	
	
	public TradeDetailPersistence getTradeDetailPersistence() {
		return tradeDetailPersistence;
	}
	public void setTradeDetailPersistence(
			TradeDetailPersistence tradeDetailPersistence) {
		this.tradeDetailPersistence = tradeDetailPersistence;
	}
	
	
	public TradeCodePersistence getTradeCodePersistence() {
		return tradeCodePersistence;
	}
	public void setTradeCodePersistence(TradeCodePersistence tradeCodePersistence) {
		this.tradeCodePersistence = tradeCodePersistence;
	}
	
	
	public SysDatePersistence getSysDatePersistence() {
		return sysDatePersistence;
	}
	public void setSysDatePersistence(SysDatePersistence sysDatePersistence) {
		this.sysDatePersistence = sysDatePersistence;
	}
	
	
	public DevicePersistence getDevicePersistence() {
		return devicePersistence;
	}
	public void setDevicePersistence(DevicePersistence devicePersistence) {
		this.devicePersistence = devicePersistence;
	}
	
	public PhotoPersistence getPhotoPersistence() {
		return photoPersistence;
	}
	public void setPhotoPersistence(PhotoPersistence photoPersistence) {
		this.photoPersistence = photoPersistence;
	}
	
	public GateHisTradeDetailPersistence getGateHisTradeDetailPersistence() {
		return gateHisTradeDetailPersistence;
	}
	public void setGateHisTradeDetailPersistence(
			GateHisTradeDetailPersistence gateHisTradeDetailPersistence) {
		this.gateHisTradeDetailPersistence = gateHisTradeDetailPersistence;
	}
	
	public AreaPersistence getAreaPersistence() {
		return areaPersistence;
	}
	public void setAreaPersistence(AreaPersistence areaPersistence) {
		this.areaPersistence = areaPersistence;
	}
	
	
	public ErrorMsgPersistence getErrorMsgPersistence() {
		return errorMsgPersistence;
	}
	public void setErrorMsgPersistence(ErrorMsgPersistence errorMsgPersistence) {
		this.errorMsgPersistence = errorMsgPersistence;
	}
	public void afterPropertiesSet() throws Exception {
		// TODO Auto-generated method stub
		if(cardService==null){
			cardService = CardServiceFactory.getImpl();
		}
		if(cardPersistence == null){
			cardPersistence = CardUtil.getPersistence();
		}
		if(tradeDetailPersistence == null){
			tradeDetailPersistence = TradeDetailUtil.getPersistence();
		}
		if(tradeCodePersistence == null){
			tradeCodePersistence = TradeCodeUtil.getPersistence();
		}
		if(sysDatePersistence == null){
			sysDatePersistence = SysDateUtil.getPersistence();
		}
		if(devicePersistence ==null){
			devicePersistence = DeviceUtil.getPersistence();
		}
		if(photoPersistence == null){
			photoPersistence = PhotoUtil.getPersistence();
		}
		
		if(gateHisTradeDetailPersistence == null){
			gateHisTradeDetailPersistence = GateHisTradeDetailUtil.getPersistence();
		}
		if(areaPersistence ==null){
			areaPersistence = AreaUtil.getPersistence();
		}
		if(errorMsgPersistence ==null){
			errorMsgPersistence = ErrorMsgUtil.getPersistence();
		}
	}
	
	
	protected CardService cardService;
	protected CardPersistence cardPersistence;
	protected TradeDetailPersistence tradeDetailPersistence;
	protected TradeCodePersistence tradeCodePersistence;
	protected SysDatePersistence sysDatePersistence;
	protected DevicePersistence devicePersistence;
	protected PhotoPersistence photoPersistence;
	protected GateHisTradeDetailPersistence gateHisTradeDetailPersistence;
	protected AreaPersistence areaPersistence;
	protected ErrorMsgPersistence errorMsgPersistence;
	

}
