package com.sungard.ticketsys.dao;

import hibernate.HibernateSessionFactory;

import java.util.LinkedList;
import java.util.List;

import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.common.Page;
import com.sungard.ticketsys.model.BusSer;

public class BusSerDao extends BaseDao {

	private static BusSerDao busSerDao;

	public static BusSerDao getInstance() {
		if (busSerDao == null) {
			busSerDao = new BusSerDao();
		}
		return busSerDao;
	}
	
	public boolean checkBusSer(String serilNo) {
		String hql = "from BusSer t where t.serilNo = ? ";
		List busList = super.find(hql, serilNo);
		if (busList == null || busList.size() < 1) {
			return false;
		} else {
			return true;
		}
	}

	public void saveBusSer(BusSer busSer) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		session.save(busSer);
		tx.commit();
	}

	public BusSer getBusSer(String serilNo) {
		List busSerList = super.find("from BusSer t where t.serilNo ='" + serilNo
				+ "'");
		return (BusSer) busSerList.get(0);
	}

	public Page getBusByCondition(int pageNo, int pageSize,
			BusSer searchBusSer, String orderBy) {
		if (searchBusSer != null) {
			StringBuffer hql = new StringBuffer("from BusSer t where 1=1 ");
			List<Object> conditions = new LinkedList<Object>();
			if (searchBusSer.getSerilNo() != null && !"".equals(searchBusSer.getSerilNo())) {
				hql.append(" and t.serilNo like ? ");
				conditions.add("%" + searchBusSer.getSerilNo().trim()+ "%");
			}

			if (searchBusSer.getLineName() != null && !"".equals(searchBusSer.getLineName())) {
				hql.append(" and t.lineName = ? ");
				conditions.add(searchBusSer.getLineName().trim());
			}

			if (orderBy != null && !"".equals(orderBy)) {
				hql.append(" order by t." + orderBy + " desc");
			} 

			return super.pageQuery(hql.toString(), pageNo, pageSize, conditions
					.toArray());
		} else {
			return null;
		}
	}

	public void updateBusSer(BusSer infoBusSer) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		session.update(infoBusSer);
		tx.commit();
	}

	public List<BusSer> getAllBusSer() {
		return this.getAll(BusSer.class);
	}

	public boolean busSerIsUsed(String serilNo) {
		List busSerList = super.find("from BusserDay t where t.busSerNo ='" + serilNo
				+ "'");
		if(busSerList.size()>0){
			return true;
		}
		
		return false;
	}


}
