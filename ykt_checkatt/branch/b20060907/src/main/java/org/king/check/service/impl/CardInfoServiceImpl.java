package org.king.check.service.impl;

import java.io.Serializable;
import java.util.List;

import org.king.check.dao.CardInfoDAO;
import org.king.check.domain.CardInfo;
import org.king.check.service.CardInfoService;

public class CardInfoServiceImpl implements CardInfoService{
	
	private CardInfoDAO cardInfoDao;

	public void setCardInfoDao(CardInfoDAO cardInfoDao) {
		this.cardInfoDao = cardInfoDao;
	}
	
	
	
	public void save(CardInfo cardInfo)
	{
		cardInfoDao.save(cardInfo);
	}
	public void delete(CardInfo cardInfo)
	{
		cardInfoDao.delete(cardInfo);
	}

	public void update(CardInfo cardInfo)
	{
		cardInfoDao.update(cardInfo);
	}
	
	public List getAll()
	{
		return cardInfoDao.getAll();
	}
	
	public CardInfo get(Serializable id)
	{
		return cardInfoDao.get(id);
	}
	
	public List find(String query)
	{
		return cardInfoDao.find(query);
	}
}
