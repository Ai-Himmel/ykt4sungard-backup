package org.king.check.dao;

import java.io.Serializable;
import java.util.Collection;
import java.util.List;

import org.king.check.domain.CardInfo;
import org.king.framework.dao.MyQuery;

public interface CardInfoDAO {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public CardInfo get(Serializable id);
	
	public List getAll();
	
	public void save(CardInfo transientInstance);
	
    public void update(CardInfo transientInstance);
    
    public void delete(CardInfo persistentInstance);
    
    public List getCardInfoByCardNumber(String cardNumber)throws Exception;
}
