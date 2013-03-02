/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    DeptServiceImpl.java
 * 创建日期： 2007-6-5 下午02:32:32
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-5 下午02:32:32     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service.impl;

import java.sql.SQLException;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.king.common.dao.AllDAO;
import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IDeptService;
import org.springframework.orm.hibernate3.HibernateCallback;

public class DeptServiceImpl   implements IDeptService{

	private AllDAO allDAO;
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}

	public boolean addOrUpdateDept(TabSsDept dept) {
		if (dept == null) return false;
		dept.setStatus("N");
		allDAO.getHibernateTemplate().saveOrUpdate(dept);
		return true;
	}

	public boolean deleteDept(final List deptIds) {
		if(deptIds == null || deptIds.isEmpty()) return false;
		
		allDAO.getHibernateTemplate().execute(new HibernateCallback(){
				public Object doInHibernate(Session session) throws HibernateException, SQLException {
					session.createQuery("update TabSsDept d set d.status='Y' where d.id in (:deptIds)")
					.setParameterList("deptIds", deptIds).executeUpdate();
					return null;
				}
				
			});
		
		return false;
	}

	public List getDepts() {
		return allDAO.getHibernateTemplate().find("select new Map(d.id as id,d.name as name,d.right as right) " +
				" from TabSsDept d where d.status='N'");
		
	}

	
	public TabSsDept getDept(String deptId){
		return (TabSsDept)allDAO.getHibernateTemplate().get(TabSsDept.class, deptId);
	}

}
