/**
 * 
 */
package com.kingstargroup.ecard.hibernate.infotype;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.util.lang.FastStringBuffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: InfoTypePersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-22  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class InfoTypePersistence extends BasicPersistence {

	/**
	 * Description:根据用户提供的查询项取得对应数据
	 * @param title 查询标题
	 * @param content 查询内容
	 * @param infoType 查询信息内容
	 * @param page 需要查询的页码
	 * @return
	 * Modify History:修正排序顺序
	 */
	public ResultPage search(String infoType, String infoName, int page, int size) throws DBSystemException {
		Session s = getSession();
		try {
			FastStringBuffer buff = new FastStringBuffer();
			FastStringBuffer countBuff = new FastStringBuffer("select count(*) as countRecords");
			buff.append(" from InfoType type where 1 = 1");						
			if (infoType != null && !infoType.equals("")) {
				buff.append(" and type.infoType like '%")
					.append(infoType)
					.append("%'");				
			}
			if (infoName != null && !infoName.equals("")) {
				buff.append(" and type.infoName like '%")
				.append(infoName)
				.append("%'");
			}			
			Query countQuery = s.createQuery(countBuff.append(buff).toString());				
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();//查询出总共的条数
			buff.append(" order by substr(type.infoType, 3) desc");
			Query query = s.createQuery(buff.toString());
			ResultPage result = new ResultPage(query, page, size);
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}			
			return result;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description: 增加或者更新一种信息类型
	 * @param type 信息类型对象
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void saveOrUpdate(InfoType type) throws DBSystemException {
		Session s = getSession();
		try {
			s.save(type);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:根据类型id得到类型对象
	 * @param id
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public InfoType getTypeById(String id) throws DBSystemException {		
		InfoType type = null;
		Session s = getSession();
		try {			
			type = (InfoType) s.get(InfoType.class, id);			
			return type;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description:根据传入的类型ID删除对应的信息类型对象
	 * @param ids
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public boolean deleteTypesByIds(String[] ids) throws DBSystemException {
		Session s = getSession();
		try {			
			for (int i = 0; i < ids.length; i++) {
				s.delete(getTypeById(ids[i]));
			}			
			return true;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(InfoTypePersistence.class);
}
