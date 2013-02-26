package com.sungard.ticketsys.dao;

import hibernate.HibernateSessionFactory;

import java.util.LinkedList;
import java.util.List;

import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.common.Page;
import com.sungard.ticketsys.model.Bus;

public class BusDao extends BaseDao {

	private static BusDao busDao;

	public static BusDao getInstance() {
		if (busDao == null) {
			busDao = new BusDao();
		}
		return busDao;
	}

	public boolean checkBus(String busNo) {
		String hql = "from Bus t where t.busNo = ? ";
		List busList = super.find(hql, busNo);
		if (busList == null || busList.size() < 1) {
			return false;
		} else {
			return true;
		}
	}

	public List<Bus> getAllBus() {
		return this.getAll(Bus.class);
	}

	public Page getBusByCondition(int pageNo, int pageSize, Bus bus,
			String orderBy) {
		if (bus != null) {
			StringBuffer hql = new StringBuffer("from Bus t where 1=1 ");
			List<Object> conditions = new LinkedList<Object>();
			if (bus.getBusNo() != null && !"".equals(bus.getBusNo())) {
				hql.append(" and t.busNo like ? ");
				conditions.add("%" + bus.getBusNo().trim()
						+ "%");
			}

			if (bus.getBusState() != null && !"".equals(bus.getBusState())) {
				hql.append(" and t.busState = ? ");
				conditions.add(bus.getBusState().trim());
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

	public Bus getBus(String busNo) {
		List busList = super.find("from Bus t where t.busNo ='" + busNo
				+ "'");
		return (Bus) busList.get(0);
	}

	public Bus getBusById(Integer busId) {
		return this.get(Bus.class, busId);
	}

	public void removeBus(Bus bus) {
		remove(bus);

	}

	public void saveBus(Bus bus) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		session.save(bus);
		tx.commit();
	}

	public void updateBus(Bus bus) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		session.update(bus);
		tx.commit();
	}

	public boolean busIsUsed(String busNo) {
		List busSerList = super.find("from BusserDay t where t.busNo ='" + busNo
				+ "'");
		if(busSerList.size()>0){
			return true;
		}
		
		return false;
	}

}
