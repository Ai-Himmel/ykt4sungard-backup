package com.sungard.ticketsys.dao;

import hibernate.HibernateSessionFactory;

import java.util.LinkedList;
import java.util.List;

import org.hibernate.FlushMode;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.common.Page;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Seat;

public class SerSetDao extends BaseDao {

	private static SerSetDao serSetDao;

	public static SerSetDao getInstance() {
		if (serSetDao == null) {
			serSetDao = new SerSetDao();
		}
		return serSetDao;
	}

	public void updateBusserDay(BusserDay busserDay) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();
			session.update(busserDay);
			tx.commit();
		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			throw new Exception("更新车次信息失败" + e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}
	}

	public BusserDay getBusserDay(String serdayId) {
		List busserDayList = super.find("from BusserDay t where t.serdayId ='"
				+ serdayId + "'");
		return (BusserDay) busserDayList.get(0);
	}

	public void removeBusserDay(BusserDay newBusserDay) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();
			// 删除车次对应的座位信息
			Query query = session
					.createQuery("delete Seat s where s.serdayId = '"
							+ newBusserDay.getSerdayId() + "'");
			query.executeUpdate();

			// 删除车次信息
			session.delete(newBusserDay);
			tx.commit();
		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			throw new Exception("删除车次信息失败" + e.getMessage());
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	public Page getSerSetByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String startTime, String endTime,
			String orderBy) {
		if (searchSerSet != null) {
			StringBuffer hql = new StringBuffer("from BusserDay t where 1=1 ");
			List<Object> conditions = new LinkedList<Object>();
			if (searchSerSet.getSerdayId() != null
					&& !"".equals(searchSerSet.getSerdayId())) {
				hql.append(" and t.serdayId like ? ");
				conditions.add("%"+ searchSerSet.getSerdayId().trim()+ "%");
			}

			if (searchSerSet.getBusSerNo() != null
					&& !"".equals(searchSerSet.getBusSerNo())) {
				hql.append(" and t.busSerNo = ? ");
				conditions.add(searchSerSet.getBusSerNo().trim());
			}

			if (startTime != null && !"".equals(startTime)) {
				hql.append(" and t.departDate >= ? ");
				conditions.add(startTime.trim());
			}

			if (endTime != null && !"".equals(endTime)) {
				hql.append(" and t.departDate <= ? ");
				conditions.add(endTime.trim());
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

	public Boolean checkBusSer(String departDate, String serilNo) {
		String hql = "from BusserDay t where t.departDate = '" + departDate
				+ "' " + "and t.busSerNo = '" + serilNo + "'";

		List busserDayList = super.find(hql);
		if (busserDayList == null || busserDayList.size() < 1) {
			return false;
		} else {
			return true;
		}
	}

	public void addBusserDay(String departDate, BusSer myBusSer, Session session) {
		// 构造车次信息
		BusserDay busserDay = new BusserDay();
		busserDay.setSerdayId(myBusSer.getSerilNo() + departDate);
		busserDay.setBusSerNo(myBusSer.getSerilNo());
		busserDay.setDepartDate(departDate);
		busserDay.setTicketCount(0);
		busserDay.setRemainCount(myBusSer.getMaxCount());
		session.save(busserDay);
		int seatcount = myBusSer.getMaxCount();
		for (int j = 1; j <= seatcount; j++) {
			// 构造座位号信息
			Seat seat = new Seat();
			seat.setSerdayId(myBusSer.getSerilNo() + departDate);
			seat.setSeatNo(j);
			seat.setStatus(Seat.STATE_WAIT_SALE);
			session.save(seat);
		}

	}

	public Page getSerSetByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String departDate, String startAddr,
			String endAddr, String orderBy, String status) {

		StringBuffer hql = new StringBuffer("from BusserDay t where 1=1 ");
		List<Object> conditions = new LinkedList<Object>();

		if (status != null) {
			hql.append(" and t.status = ? ");
			conditions.add(status);
		}

		if (searchSerSet != null) {

			if (searchSerSet.getSerdayId() != null
					&& !"".equals(searchSerSet.getSerdayId())) {
				hql.append(" and t.serdayId like ? ");
				conditions.add("%"+ searchSerSet.getSerdayId().trim()+ "%");
			}

			if (searchSerSet.getBusSerNo() != null
					&& !"".equals(searchSerSet.getBusSerNo())) {
				hql.append(" and t.busSerNo = ? ");
				conditions.add(searchSerSet.getBusSerNo().trim());
			}
		}

		if (departDate != null && !"".equals(departDate)) {
			hql.append(" and t.departDate = ? ");
			conditions.add(departDate);
		}

		if (startAddr != null && !"".equals(startAddr)) {
			if (endAddr != null && !"".equals(endAddr)) {

				hql.append(" and exists" + "(select 1 from BusSer bs,Line ln "
						+ "where t.busSerNo = bs.serilNo "
						+ "and bs.lineName = ln.lineName "
						+ "and ln.startAddr like ? "
						+ "and ln.endAddr like ?) ");
				conditions.add("%" + startAddr + "%");
				conditions.add("%" + endAddr + "%");
			} else {
				hql.append(" and exists" + "(select 1 from BusSer bs,Line ln "
						+ "where t.busSerNo = bs.serilNo "
						+ "and bs.lineName = ln.lineName "
						+ "and ln.startAddr like ?) ");
				conditions.add("%" + startAddr + "%");
			}

		} else {
			if (endAddr != null && !"".equals(endAddr)) {

				hql.append(" and exists" + "(select 1 from BusSer bs,Line ln "
						+ "where t.busSerNo = bs.serilNo "
						+ "and bs.lineName = ln.lineName "
						+ "and ln.endAddr like ?) ");
				conditions.add("%" + endAddr + "%");
			}
		}

		if (orderBy != null && !"".equals(orderBy)) {
			hql.append(" order by t." + orderBy + " desc");
		}

		return super.pageQuery(hql.toString(), pageNo, pageSize, conditions
				.toArray());
	}

	public Page geBusserDayByConditions(int pageNo, int pageSize,
			BusserDay searchSerSet, String startDate, String endDate,
			String lineName, String orderBy, String status) {

		StringBuffer hql = new StringBuffer("from BusserDay t where 1=1 ");
		List<Object> conditions = new LinkedList<Object>();

		if (status != null) {
			hql.append(" and t.status = ? ");
			conditions.add(status);
		}

		if (searchSerSet != null) {
			
			if (searchSerSet.getSerdayId() != null
					&& !"".equals(searchSerSet.getSerdayId())) {
				hql.append(" and t.serdayId like ? ");
				conditions.add("%"+ searchSerSet.getSerdayId().trim() + "%");
			}

			if (searchSerSet.getBusSerNo() != null
					&& !"".equals(searchSerSet.getBusSerNo())) {
				hql.append(" and t.busSerNo = ? ");
				conditions.add(searchSerSet.getBusSerNo().trim());
			}

			if (searchSerSet.getBusNo() != null
					&& !"".equals(searchSerSet.getBusNo())) {
				hql.append(" and t.busNo = ? ");
				conditions.add(searchSerSet.getBusNo().trim());
			}
		}

		if (startDate != null && !"".equals(startDate)) {
			hql.append(" and t.departDate >= ? ");
			conditions.add(startDate.trim());
		}

		if (endDate != null && !"".equals(endDate)) {
			hql.append(" and t.departDate <= ? ");
			conditions.add(endDate.trim());
		}

		if (lineName != null && !"".equals(lineName)) {

			hql.append(" and exists" + "(select 1 from BusSer bs "
					+ "where t.busSerNo = bs.serilNo "
					+ "and bs.lineName = ?) ");
			conditions.add(lineName);

		}

		if (orderBy != null && !"".equals(orderBy)) {
			hql.append(" order by t." + orderBy + " desc");
		}

		return super.pageQuery(hql.toString(), pageNo, pageSize, conditions
				.toArray());
	}

}
