package com.sungard.ticketsys.dao;

import hibernate.HibernateSessionFactory;

import java.util.Date;
import java.util.LinkedList;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.FlushMode;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import sun.util.logging.resources.logging;

import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.RefundLog;
import com.sungard.ticketsys.model.Seat;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.page.ticket.BackTickePanel;
import com.sungard.ticketsys.common.Page;

public class TicketDao extends BaseDao {
	private static TicketDao ticketDao;
	private static final Logger logger = Logger.getLogger(TicketDao.class);

	public static TicketDao getInstance() {
		if (ticketDao == null) {
			ticketDao = new TicketDao();
		}
		return ticketDao;
	}

	/**
	 * 批量修改车次状态为停止售票
	 * 
	 * @param selBusserDayS
	 * @throws Exception
	 */
	public void stopSale(List<BusserDay> selBusserDayS) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();
			for (int i = 0; i < selBusserDayS.size(); i++) {
				BusserDay busserDay = selBusserDayS.get(i);
				busserDay.setStatus(BusserDay.STATE_STOP_SALE);
				session.update(busserDay);
			}
			tx.commit();
		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			throw new Exception("停止售票失败" + e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	public Page getResSeatBySerDay(int pageNo, int pageSize,
			BusserDay sleBusserDay, String orderBy) {
		if (sleBusserDay != null) {
			StringBuffer hql = new StringBuffer("from Seat t where 1=1 ");
			List<Object> conditions = new LinkedList<Object>();
			hql.append(" and t.serdayId = ? ");
			conditions.add(sleBusserDay.getSerdayId().trim());

			hql.append(" and t.status = ? ");
			conditions.add(Seat.STATE_READY_SALE);

			if (orderBy != null && !"".equals(orderBy)) {
				hql.append(" order by t." + orderBy);
			}

			return super.pageQuery(hql.toString(), pageNo, pageSize, conditions
					.toArray());
		} else {
			return null;
		}
	}

	public Seat getSeat(String seatId) {
		List seatList = super.find("from Seat t where t.id ='" + seatId + "'");
		return (Seat) seatList.get(0);
	}

	public void cancelReserve(List<Seat> selSeatS) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();
			for (int i = 0; i < selSeatS.size(); i++) {
				Seat seat = selSeatS.get(i);
				seat.setStatus(Seat.STATE_WAIT_SALE);
				session.update(seat);
			}
			// 更新车次预留票数、剩余票数
			String serdayId = selSeatS.get(0).getSerdayId();
			BusserDay busserDay = SerSetDao.getInstance()
					.getBusserDay(serdayId);
			if (busserDay == null) {
				throw new Exception("更新车次预留票数、剩余票数失败。");
			}
			if (busserDay.getReserveCount() < selSeatS.size()) {
				throw new Exception("车次预留票数有误。");
			}
			busserDay.setReserveCount(busserDay.getReserveCount() - selSeatS.size());
			busserDay.setRemainCount(busserDay.getRemainCount() + selSeatS.size());
			session.update(busserDay);
			tx.commit();
		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			throw new Exception("停止售票失败" + e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	/**
	 * 退票
	 * @param ticketId
	 * @param handFee
	 */
	public void backTicket(TicketLog ticketLog, String handFee) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();
			
			// 更新车次剩余票数、售出票数
			logger.info("1.获取售票记录");
			String serdayId = ticketLog.getSerdayId();
			
			logger.info("2.更新车次信息");
			BusserDay busserDay = SerSetDao.getInstance()
					.getBusserDay(serdayId);
			if (busserDay == null) {
				throw new Exception("更新车次["+serdayId+"]信息失败。");
			}
			if (busserDay.getTicketCount()>0) {
				busserDay.setTicketCount(busserDay.getTicketCount() - 1);
				busserDay.setRemainCount(busserDay.getRemainCount() + 1);
				session.update(busserDay);
			}else {
				throw new Exception("更新车次["+serdayId+"]信息失败,售出票数与实际卖出票数不相符。");
			}
			
			//更新售票记录为退票
			logger.info("3.更新售票记录,状态为退票");
			ticketLog.setIsback(true);
			session.update(ticketLog);
			
			logger.info("4.更新座位信息,状态为待售");
			String seathql = "from Seat s where s.serdayId = '" + serdayId
			               + "' and s.seatNo = " + ticketLog.getSeatNo()
			               + " and s.status = '" + Seat.STATE_SALED + "'";
	       Query seatObject = session.createQuery(seathql);
           Seat seat = (Seat) seatObject.list().get(0);
	       if (seat == null) {
	    	  logger.error("更新座号的状态为失败。");
	    	  throw new Exception("更新座号的状态失败。");
	    	  }
	       seat.setStatus(Seat.STATE_WAIT_SALE);
	       session.update(seat);
			
			
			//记录退票记录
	        logger.info("5.记录退票记录");
			RefundLog refundLog = new RefundLog();
			refundLog.setHandFee(handFee);
			refundLog.setRefuntTime(new Date());
			refundLog.setSerdayId(serdayId);
			refundLog.setTicketId(ticketLog.getTicketId());
			session.save(refundLog);
			
			logger.info("6.提交完成！");
			tx.commit();
		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			throw new Exception(e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}
	

	public TicketLog getTicketLog(String ticketId) {
		String hql = "from TicketLog t where t.ticketId = '"+ticketId+ "'";
		List ticketLogList = super.find(hql);
		
		if (ticketLogList == null || ticketLogList.size() < 1) {
			return null;
		} else {
			return (TicketLog)ticketLogList.get(0);
		}
	}
		
}
