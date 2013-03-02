/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Query;

import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: ResultPage.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-7  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ResultPage {

	/**
	 * 页中的记录
	 */
	private List results;
	
	/**
	 * 页包含记录数
	 */
	private int pageSize; 
	/**
	 * 页码
	 */
	private int page;
	
	private int totalPage;
	
	public ResultPage(Query query, int page, int pageSize) throws HibernateException { 
		this(page, pageSize);		
		query.setFirstResult(page * pageSize);
		if (pageSize != EcardConstants.MAX_RESULT_SIZE) {
			query.setMaxResults(pageSize+1);
		}		 
		results = query.list();  
	}
	
	public ResultPage(Criteria criteria, int page, int pageSize) throws HibernateException { 
		this(page, pageSize);
		criteria.setFirstResult(page * pageSize);
		if (pageSize != EcardConstants.MAX_RESULT_SIZE) {
			criteria.setMaxResults(pageSize+1);
		}		 
		results = criteria.list();  
	} 
	
	public ResultPage(int page, int pageSize) {
		this.page = page;
		this.pageSize = pageSize;
	}
	
	/**
	 * Description: 是否还有下一页?
	 * @return
	 * Modify History:
	 */
	public boolean isNextPage() { 
		return results.size() > pageSize; 
	} 
    
	/**
	 * Description:是否还有上一页?
	 * @return
	 * Modify History:
	 */
	public boolean isPreviousPage() { 
		return page > 0; 
	} 
    
	/**
	 * Description:得出页中包含的记录
	 * @return
	 * Modify History:
	 */
	public List getList() { 
		return isNextPage() ? 
				results.subList(0, pageSize) : results; 
	}
	
	public int getPage() {
		return page;
	}
	
	public void setList(List list) {
		this.results = list;
	}
	
	public List getFullList() {
		return results;
	}
	
	public int getTotalPage() {
		return totalPage;
	}
	
	public void setTotalPage(int totalPage) {
		this.totalPage = totalPage;
	}
}
