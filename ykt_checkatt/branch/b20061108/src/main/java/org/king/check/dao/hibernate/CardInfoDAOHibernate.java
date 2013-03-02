package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.king.check.dao.CardInfoDAO;
import org.king.check.domain.CardInfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

public class CardInfoDAOHibernate implements CardInfoDAO {
	 //private static final Log log = LogFactory.getLog(CardInfoDAOHibernate.class);

		protected void initDao() {
			//do nothing
		}
	    
	    private BaseDAO baseDAO;
	    
	    public void setBaseDAO(BaseDAO baseDAO) {
			    this.baseDAO = baseDAO;
		  }
public List find(MyQuery myQuery)
{
	return null;
}
	
	public List find(String query)
	{
		return baseDAO.findEntity(query);
	}
	 
	public CardInfo get(Serializable id)
	{
		return (CardInfo)baseDAO.getEntity(CardInfo.class,id);
	}
	
	public List getAll()
	{
		return baseDAO.findEntity("from CardInfo");
		
	}
	
	public void save(CardInfo transientInstance)
	{
		baseDAO.saveEntity(transientInstance);
	}
	
    public void update(CardInfo transientInstance)
    {
    	baseDAO.updateEntity(transientInstance);
    }
    
    public void delete(CardInfo persistentInstance)
    {
    	baseDAO.removeEntity(persistentInstance);
    }
    public List getCardInfoByCardNumber(String cardNumber)throws Exception
    {
    	Date now=new Date();
		//Calendar calendar=Calendar.getInstance();
		String strCalendar=DateFormat.getDateInstance().format(now);
		List recordList=new ArrayList();
		List tmp;
		  
    	String hql="from CardInfo c where c.cardnumber='"+cardNumber+"' and c.recordtime='"+strCalendar+"' order by cardinfoid asc";
    	tmp=find(hql);
    	
    	recordList.set(1,tmp.get(0));
    	recordList.set(2,tmp.get(tmp.size()-1));
    	
    	
    	return recordList;
    }

}
