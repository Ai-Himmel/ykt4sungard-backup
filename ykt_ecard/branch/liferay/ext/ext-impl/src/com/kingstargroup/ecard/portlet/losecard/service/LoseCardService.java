package com.kingstargroup.ecard.portlet.losecard.service;

import java.util.List;
import java.util.Map;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardinfo;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardshop;

public interface LoseCardService {

	public TLosscardshop getInfoByShopCode(String shopCode)throws PortalException;
	
	public void add(String shopCode,String shopName)throws PortalException;
	
	public boolean update(String shopCode,String shopName,String addr,
			String tel,String getCardPlace)throws PortalException;
	
	public Map getStuempInfo(String cardPhyId)throws PortalException;
	
	public String cardStatus(String cardPhyId)throws PortalException;
	
	public void addLossCardInfo(String shopcode,int cardno,String cardphyid,String getcardplace,
			String addr,String tel) throws PortalException;
	
	public List getLossCardBy(String shopCode,Integer cardNo)throws PortalException;

	public List getLossCardInfo(String shopCode,String bDate,String eDate,
			Integer cardNo,String showCardNo,String StuempNo,String custName,
			String cardStatus)throws PortalException;
	
	public List getCardType()throws PortalException;
	
	public String getCardPhyId(Integer cardNo)throws PortalException;
	
	public Map getIdNo(Integer cardNo)throws PortalException;
	
	//是否有正常状态的卡
	public int haveCard(String shopCode,Integer cardNo)throws PortalException; 
	
	public void updateLossCardInfo(String shopcode,int cardno,String idType,
			String idNo,String reMark) throws PortalException;
	
	public List getDictListBy(Integer dictNo)throws PortalException; 
	
	public List getLossStatList(String beginDate,String endDate,String shopCode)throws PortalException; 
	public Map getGetCardInfo(String cardNo)throws PortalException; 
}
