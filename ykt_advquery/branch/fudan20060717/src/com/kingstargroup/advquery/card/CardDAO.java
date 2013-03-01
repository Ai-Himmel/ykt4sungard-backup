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
/**
 * @author 
 *
 */
public class CardDAO {
	/**
	 * ���ظ������ʹ�����
	 * @param beginTime
	 * @returnʹ������б�
	 */
	public List getCardUseStatistics(String beginTime) {
		Session s = HibernateSessionFactory.currentSession();
		try {
			Query query = s.getNamedQuery("CardUseSQL");
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
	 * ͳ�Ƶ�λ���࿨ռ�е�����
	 * @param departmentNo
	 * @param code
	 * @return
	 */
	public List getCardUseStatByCondition(String departmentNo,String code){
		StringBuffer finallyStr = new StringBuffer(2048);
		HashMap map = new HashMap();
		finallyStr.append("select new map(dict.dictCaption as dictCaption,count(card.cardId)as cardNum) from ");
		finallyStr.append("TPifCard card,TCifCustomer cust,TPifDictionary dict");
		finallyStr.append(" where card.typeId = integer(dict.id.dictValue) and dict.id.dictNo=18");
		finallyStr.append(" and card.cosumerId=cust.cutId and card.stateId='1000'");
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
