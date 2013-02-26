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
	 * �����޸ĳ���״̬Ϊֹͣ��Ʊ
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
			throw new Exception("ֹͣ��Ʊʧ��" + e.getMessage());
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
			// ���³���Ԥ��Ʊ����ʣ��Ʊ��
			String serdayId = selSeatS.get(0).getSerdayId();
			BusserDay busserDay = SerSetDao.getInstance()
					.getBusserDay(serdayId);
			if (busserDay == null) {
				throw new Exception("���³���Ԥ��Ʊ����ʣ��Ʊ��ʧ�ܡ�");
			}
			if (busserDay.getReserveCount() < selSeatS.size()) {
				throw new Exception("����Ԥ��Ʊ������");
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
			throw new Exception("ֹͣ��Ʊʧ��" + e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	/**
	 * ��Ʊ
	 * @param ticketId
	 * @param handFee
	 */
	public void backTicket(TicketLog ticketLog, String handFee) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();
			
			// ���³���ʣ��Ʊ�����۳�Ʊ��
			logger.info("1.��ȡ��Ʊ��¼");
			String serdayId = ticketLog.getSerdayId();
			
			logger.info("2.���³�����Ϣ");
			BusserDay busserDay = SerSetDao.getInstance()
					.getBusserDay(serdayId);
			if (busserDay == null) {
				throw new Exception("���³���["+serdayId+"]��Ϣʧ�ܡ�");
			}
			if (busserDay.getTicketCount()>0) {
				busserDay.setTicketCount(busserDay.getTicketCount() - 1);
				busserDay.setRemainCount(busserDay.getRemainCount() + 1);
				session.update(busserDay);
			}else {
				throw new Exception("���³���["+serdayId+"]��Ϣʧ��,�۳�Ʊ����ʵ������Ʊ���������");
			}
			
			//������Ʊ��¼Ϊ��Ʊ
			logger.info("3.������Ʊ��¼,״̬Ϊ��Ʊ");
			ticketLog.setIsback(true);
			session.update(ticketLog);
			
			logger.info("4.������λ��Ϣ,״̬Ϊ����");
			String seathql = "from Seat s where s.serdayId = '" + serdayId
			               + "' and s.seatNo = " + ticketLog.getSeatNo()
			               + " and s.status = '" + Seat.STATE_SALED + "'";
	       Query seatObject = session.createQuery(seathql);
           Seat seat = (Seat) seatObject.list().get(0);
	       if (seat == null) {
	    	  logger.error("�������ŵ�״̬Ϊʧ�ܡ�");
	    	  throw new Exception("�������ŵ�״̬ʧ�ܡ�");
	    	  }
	       seat.setStatus(Seat.STATE_WAIT_SALE);
	       session.update(seat);
			
			
			//��¼��Ʊ��¼
	        logger.info("5.��¼��Ʊ��¼");
			RefundLog refundLog = new RefundLog();
			refundLog.setHandFee(handFee);
			refundLog.setRefuntTime(new Date());
			refundLog.setSerdayId(serdayId);
			refundLog.setTicketId(ticketLog.getTicketId());
			session.save(refundLog);
			
			logger.info("6.�ύ��ɣ�");
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
