/**
 * 
 */
package com.kingstargroup.advquery.card;

import java.util.HashMap;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
import com.kingstargroup.advquery.util.WebKeys;
/**
 * @author 
 *
 */
public class CardDAO {
	/**
	 * 返回各卡类的使用情况
	 * @param beginTime
	 * @return使用情况列表
	 */
	public List getCardUseStatistics(String beginTime) {
		Session s = HibernateSessionFactory.currentSession();
		try {
			Query query = null;
			if ("ORACLE".equals(WebKeys.DATABASE)){
				query = s.getNamedQuery("CardUseSQL_ORACLE");
			}else if ("DB2".equals(WebKeys.DATABASE)){
				query = s.getNamedQuery("CardUseSQL_DB2");
			}
			query.setString("begintime", beginTime);
			List list = query.list(); 
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 统计单位各类卡占有的数量
	 * @param departmentNo
	 * @param code
	 * @return
	 */
	public List getCardUseStatByCondition(String departmentNo,String code){
		StringBuffer finallyStr = new StringBuffer(2048);
		HashMap map = new HashMap();
		if ("ORACLE".equals(WebKeys.DATABASE)){
			finallyStr.append("select new map(dict.dictCaption as dictCaption,count(card.cardId)as cardNum) from ");
			finallyStr.append("TPifCard card,TCifCustomer cust,TPifDictionary dict");
			finallyStr.append(" where card.typeId = to_number(dict.id.dictValue) and dict.id.dictNo=18");
			finallyStr.append(" and card.cosumerId=cust.cutId and card.stateId='1000'");
		}else if ("DB2".equals(WebKeys.DATABASE)){
			finallyStr.append("select new map(dict.dictCaption as dictCaption,count(card.cardId)as cardNum) from ");
			finallyStr.append("TPifCard card,TCifCustomer cust,TPifDictionary dict");
			finallyStr.append(" where card.typeId = integer(dict.id.dictValue) and dict.id.dictNo=18");
			finallyStr.append(" and card.cosumerId=cust.cutId and card.stateId='1000'");
		}
		if (!"".equals(departmentNo.trim())){
			finallyStr.append("  and cust.classdeptNo=:depno");
		}
		if (!"".equals(code.trim())){
			finallyStr.append(" and cust.scode=:code");
		}
		finallyStr.append(" group by dict.dictCaption");
		
		Session s = HibernateSessionFactory.currentSession();
		try {
			Query sqlQuery = s.createQuery(finallyStr.toString());
			System.out.println(finallyStr.toString());
			if (("".equals(departmentNo.trim()))&&("".equals(code.trim()))){
				
			}else if ("".equals(departmentNo.trim())){
				sqlQuery.setString("code",code);
			}else if ("".equals(code.trim())){
				sqlQuery.setString("depno",departmentNo);
			}else{
				sqlQuery.setString("depno",departmentNo);
				sqlQuery.setString("code",code);				
			}
			List list = sqlQuery.list();
			return list;
		} catch (Exception e) {
			_log.error(e);
			e.printStackTrace();
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}	
	
	private Log _log = LogFactory.getLog(CardDAO.class);

}
