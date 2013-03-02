package org.king.check.service;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.CardInfo;

public interface CardInfoService {

	public void save(CardInfo cardInfo);
	
	public void delete(CardInfo cardInfo);
	
	public void update(CardInfo cardInfo);
	
	public List getAll();
	
	public CardInfo get(Serializable id);
	
	public List find(String query);
}
