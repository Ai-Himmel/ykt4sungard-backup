package com.sungard.ticketsys.service;

import hibernate.HibernateSessionFactory;

import java.math.BigDecimal;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Properties;

import org.apache.log4j.Logger;
import org.hibernate.FlushMode;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.common.Configuration;
import com.sungard.ticketsys.dao.TicketDao;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Seat;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.service.card.KsCardInterfaceUtil;
import com.sungard.ticketsys.service.print.AbstractDocument;
import com.sungard.ticketsys.service.print.PosDocument;
import com.sungard.ticketsys.service.print.Printer;
import com.sungard.ticketsys.common.Page;

public class TicketManager {
	private static final Logger logger = Logger.getLogger(TicketManager.class);
	private static TicketManager ticketManager;

	private TicketDao ticketDao = TicketDao.getInstance();

	public static TicketManager getInstance() {
		if (ticketManager == null) {
			ticketManager = new TicketManager();
		}
		return ticketManager;
	}

	/**
	 * ��ӡƱ��
	 * 
	 * @param ticketLog
	 * @throws Exception
	 */
	public void saleTicket(TicketLog ticketLog, Properties result)
			throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			// �Ƿ�ΪԤ��Ʊ
			boolean isReserver = ticketLog.getIsReserve();

			String serdayId = ticketLog.getSerdayId();
			if (serdayId == null) {
				logger.error("��ȡ������Ϣʧ�ܡ�");
				throw new Exception("��ȡ������Ϣʧ�ܡ�");
			}

			logger.info("1���жϳ����Ƿ��ѹ���");
			Date now = new Date();
			Calendar cnow = Calendar.getInstance();
			cnow.setTime(now);

			SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
			Date departTime = sdf.parse(ticketLog.getDepartDate()
					+ ticketLog.getDepartTime());
			Calendar cdepartTime = Calendar.getInstance();
			cdepartTime.setTime(departTime);
			if (cnow.after(cdepartTime)) {
				logger.error("����ʱ���ѹ���������Ʊ");
				throw new Exception("����ʱ���ѹ���������Ʊ");
			}

			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();

			logger.info("2�����³�����Ϣ��Ʊ��");
			String busserDayhql = "from BusserDay t where t.serdayId ='"
					+ serdayId + "'";
			Query busserDayObject = session.createQuery(busserDayhql);
			BusserDay busserDay = (BusserDay) busserDayObject.list().get(0);

			if (isReserver) {
				int reserveCount = busserDay.getReserveCount();
				if (reserveCount < 1) {
					logger.error("�ó��ε�Ԥ��Ʊ�Ѵ�ӡ��ɡ�");
					throw new Exception("�ó��ε�û��Ԥ��Ʊ��");
				}
				busserDay.setReserveCount(reserveCount - 1);
				busserDay.setTicketCount(busserDay.getTicketCount() + 1);
			} else {
				int remainCount = busserDay.getRemainCount();
				if (remainCount < 1) {
					logger.error("�ó��ε�Ʊ�����ꡣ");
					throw new Exception("�ó��ε�Ʊ�����ꡣ");
				}
				busserDay.setRemainCount(remainCount - 1);
				busserDay.setTicketCount(busserDay.getTicketCount() + 1);
			}

			// ����Ʊ��
			session.update(busserDay);

			logger.info(" 3����ȡ��λ�ţ���������λ����ϢΪ����");
			String seathql;
			if (isReserver) {
				seathql = "from Seat s where rownum = 1 and s.serdayId = '"
						+ serdayId + "' and s.status = '"
						+ Seat.STATE_READY_SALE + "'";
			} else {
				seathql = "from Seat s where rownum = 1 and s.serdayId = '"
						+ serdayId + "' and s.status = '"
						+ Seat.STATE_WAIT_SALE + "'";
			}

			Query seatObject = session.createQuery(seathql);
			Seat seat = (Seat) seatObject.list().get(0);
			if (seat != null) {
				seat.setStatus(Seat.STATE_SALED);
				session.update(seat);
				ticketLog.setSeatNo(seat.getSeatNo());
				ticketLog.setMemo(seat.getMemo());
			}

			ticketLog.setPrintTime(now);
			// ��¼Ʊ����Ϣ
			ticketLog.setIsback(false);
			session.save(ticketLog);

			logger.info(" 4���ۿ�");
			if (ticketLog.getPayType().equals(TicketLog.PAY_TYPE_CARD)) {
				try {
					BigDecimal   b1   =   new   BigDecimal(ticketLog.getPrice()); 
				    BigDecimal   b2   =   new   BigDecimal("100");  
					int price = (int) b1.multiply(b2).doubleValue(); 
					cardPay(result, price);
				} catch (Exception e) {
					e.printStackTrace();
					logger.error("У԰���ۿ�ʧ��," + e.getMessage());
					throw new Exception("У԰���ۿ�ʧ��," + e.getMessage());
				}

			}

			logger.info(" 5����ӡƱ��");
			Printer printer = new Printer();
			AbstractDocument doucument = new PosDocument();
			SimpleDateFormat printSdf = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");

			String content = "У����Ʊ" + 
			                 "<br>Ʊ��ţ�" + ticketLog.getTicketId()+ 
			                 "<br>���κţ�" + serdayId + 
			                 "<br>��λ�ţ�" + seat.getSeatNo() + 
			                 "<br>���վ��" + ticketLog.getStartAddr()+ 
			                 "<br>�յ�վ��" + ticketLog.getEndAddr() + 
			                 "<br>����ʱ�䣺" + printSdf.format(departTime) + 
			                 "<br>Ʊ�ۣ�" + ticketLog.getPrice() + 
			                 "<br>֧����ʽ��"+ ticketLog.getPayType() + 
			                 "<br>Ʊ�����ͣ�"+ ticketLog.getTicketType() + 
			                 "<br>��ӡʱ�䣺"+ printSdf.format(now) + 
			                 "<br>��ӡ�ˣ�" + "����";
			doucument.addPage(content);
			printer.setDocument(doucument);
			printer.print();

			// �ύ�������������
			logger.info(" 6���ύ�������������");
			tx.commit();

		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			logger.error("��Ʊʧ��," + e.getMessage());
			throw new Exception(e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	/**
	 * ��ȡ����Ϣ
	 * @param result
	 */
	private void getCardInfo(Properties result) {
		KsCardInterfaceUtil.ksReset();
		KsCardInterfaceUtil.ksSetReadFieldName("CARDNO");
		KsCardInterfaceUtil.ksSetReadFieldName("SHOWCARDNO");
		KsCardInterfaceUtil.ksSetReadFieldName("FEETYPE");
		KsCardInterfaceUtil.ksSetReadFieldName("CARDSTATUS");
		KsCardInterfaceUtil.ksSetReadFieldName("EXPIREDATE");
		KsCardInterfaceUtil.ksSetReadFieldName("STUEMPNO");
		KsCardInterfaceUtil.ksSetReadFieldName("NAME");
		KsCardInterfaceUtil.ksSetReadFieldName("SEX");
		KsCardInterfaceUtil.ksSetReadFieldName("DEPTCODE");
		KsCardInterfaceUtil.ksSetReadFieldName("IDNO");
		KsCardInterfaceUtil.ksSetReadFieldName("IDTYPE");
		KsCardInterfaceUtil.ksSetReadFieldName("CARDBAL");
		KsCardInterfaceUtil.ksSetReadFieldName("PAYCNT");
		KsCardInterfaceUtil.ksSetReadFieldName("DPSCNT");
		KsCardInterfaceUtil.ksReadCard();
		KsCardInterfaceUtil.ksGetFieldVal("CARDNO", result);
		KsCardInterfaceUtil.ksGetFieldVal("SHOWCARDNO", result);
		KsCardInterfaceUtil.ksGetFieldVal("FEETYPE", result);
		KsCardInterfaceUtil.ksGetFieldVal("CARDSTATUS", result);
		KsCardInterfaceUtil.ksGetFieldVal("EXPIREDATE", result);
		KsCardInterfaceUtil.ksGetFieldVal("STUEMPNO", result);
		KsCardInterfaceUtil.ksGetFieldVal("NAME", result);
		KsCardInterfaceUtil.ksGetFieldVal("SEX", result);
		KsCardInterfaceUtil.ksGetFieldVal("DEPTCODE", result);
		KsCardInterfaceUtil.ksGetFieldVal("IDNO", result);
		KsCardInterfaceUtil.ksGetFieldVal("IDTYPE", result);
		KsCardInterfaceUtil.ksGetFieldVal("CARDBAL", result);
		KsCardInterfaceUtil.ksGetFieldVal("PAYCNT", result);
		KsCardInterfaceUtil.ksGetFieldVal("DPSCNT", result);
	}

	private void cardPay(Properties result, int price) throws Exception {
		//��ȡ����Ϣ
		getCardInfo(result);

		if (!KsCardInterfaceUtil.ksRequestCard(result)) {
			throw new Exception(result.getProperty("errMsg"));
		}
		String cardPhyId = result.getProperty("cardPhyId");
		int cardno = Integer.parseInt(result.getProperty("CARDNO"));
		int cardBal = Integer.parseInt(result.getProperty("CARDBAL"));
		int payCnt = Integer.parseInt(result.getProperty("PAYCNT"));
		if (!KsCardInterfaceUtil.ksPayPrepare(cardPhyId, cardno, cardBal,
				payCnt, price, result)) {
			throw new Exception(result.getProperty("errMsg"));
		}

		if (!KsCardInterfaceUtil.ksCardBalanceDec(result)) {
			throw new Exception(result.getProperty("errMsg"));
		}

		if (!KsCardInterfaceUtil.ksPayProcess(result)) {
			throw new Exception(result.getProperty("errMsg"));
		}
		String refNo = result.getProperty("refNo");
		String mac = result.getProperty("mac");

		if (!KsCardInterfaceUtil.getFieldValue("CARDBAL", result)) {
			throw new Exception(result.getProperty("errMsg"));
		}

		KsCardInterfaceUtil.ksBeep();
	}

	public void stopSale(List<BusserDay> selBusserDayS) throws Exception {
		ticketDao.stopSale(selBusserDayS);
	}

	/**
	 * Ԥ��Ʊ
	 * 
	 * @param sleBusserDay
	 * @param reservecount
	 * @param memo
	 * @throws Exception
	 */
	public void reserveTicket(BusserDay sleBusserDay, int reservecount,
			String memo) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			String serdayId = sleBusserDay.getSerdayId();
			if (serdayId == null) {
				logger.error("��ȡ������Ϣʧ�ܡ�");
				throw new Exception("��ȡ������Ϣʧ�ܡ�");
			}

			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();

			logger.info("1�����³�����Ϣ��ʣ��Ʊ����Ԥ��Ʊ��");
			String busserDayhql = "from BusserDay t where t.serdayId ='"
					+ serdayId + "'";
			Query busserDayObject = session.createQuery(busserDayhql);
			BusserDay busserDay = (BusserDay) busserDayObject.list().get(0);

			int remainCount = busserDay.getRemainCount();
			if (remainCount < reservecount) {
				logger.error("����Ԥ��Ʊ������ǰʣ��Ʊ��[" + remainCount + "]��");
				throw new Exception("����Ԥ��Ʊ������ǰʣ��Ʊ��[" + remainCount + "]��");
			}
			busserDay.setRemainCount(remainCount - reservecount);
			busserDay.setReserveCount(busserDay.getReserveCount()
					+ reservecount);

			// ����Ʊ��
			session.update(busserDay);

			logger.info(" 2����ȡ��λ�ţ���������λ����ϢΪԤ��");
			String seathql = "from Seat s where rownum <= " + reservecount
					+ " and s.serdayId = '" + serdayId + "' and s.status = '"
					+ Seat.STATE_WAIT_SALE + "'";
			Query seatObject = session.createQuery(seathql);
			List<Seat> seats = (List<Seat>) seatObject.list();
			if (seats.size() != reservecount) {
				logger.error("��ȡ�Ĵ�Ԥ������λ�����������Ԥ����Ϊ[" + reservecount
						+ "],����ȡ����λ��Ϊ[" + seats.size() + "]");
				throw new Exception("��ȡ�Ĵ�Ԥ������λ�����������Ԥ����Ϊ[" + reservecount
						+ "],����ȡ����λ��Ϊ[" + seats.size() + "]");
			}
			for (int i = 0; i < seats.size(); i++) {
				Seat seat = seats.get(i);
				seat.setStatus(Seat.STATE_READY_SALE);
				seat.setMemo(memo);
				session.update(seat);
			}
			// �ύ��������������
			logger.info(" 3���ύ�������������");
			tx.commit();

		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			logger.error("Ԥ��Ʊʧ��," + e.getMessage());
			throw new Exception(e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	@SuppressWarnings("unchecked")
	public List<Seat> getReserveSeat(int pageNo, int pageSize,
			BusserDay sleBusserDay, String orderBy) {
		List<Seat> seats = new ArrayList<Seat>();
		Page page = ticketDao.getResSeatBySerDay(pageNo, pageSize,
				sleBusserDay, orderBy);
		if (page != null) {
			seats = (List<Seat>) page.getResult();
		}
		return seats;
	}

	public Page getReserveSeat(int pageNo, int pageSize, BusserDay sleBusserDay) {
		Page page = new Page();
		page = ticketDao.getResSeatBySerDay(pageNo, pageSize, sleBusserDay,
				null);
		return page;
	}

	public void PrintRerTicket(TicketLog ticketLog) throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			String serdayId = ticketLog.getSerdayId();
			if (serdayId == null) {
				logger.error("��ȡ������Ϣʧ�ܡ�");
				throw new Exception("��ȡ������Ϣʧ�ܡ�");
			}

			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();

			logger.info("1�����³�����Ϣ��Ԥ��Ʊ�����۳�Ʊ��");
			String busserDayhql = "from BusserDay t where t.serdayId ='"
					+ serdayId + "'";
			Query busserDayObject = session.createQuery(busserDayhql);
			BusserDay busserDay = (BusserDay) busserDayObject.list().get(0);

			int reserveCount = busserDay.getReserveCount();
			if (reserveCount < 1) {
				logger.error("�ó��ε�Ԥ��Ʊ�Ѵ�ӡ��ɡ�");
				throw new Exception("�ó��ε�Ԥ��Ʊ�Ѵ�ӡ��ɡ�");
			}
			busserDay.setReserveCount(reserveCount - 1);
			busserDay.setTicketCount(busserDay.getTicketCount() + 1);
			// ����Ʊ��
			session.update(busserDay);

			// �������ŵ�״̬
			logger.info("2���������ŵ�״̬Ϊ����");
			String seathql = "from Seat s where s.serdayId = '" + serdayId
					+ "' and s.seatNo = " + ticketLog.getSeatNo()
					+ " and s.status = '" + Seat.STATE_READY_SALE + "'";
			Query seatObject = session.createQuery(seathql);
			Seat seat = (Seat) seatObject.list().get(0);
			if (seat == null) {
				logger.error("�������ŵ�״̬Ϊ����ʧ�ܡ�");
				throw new Exception("�������ŵ�״̬Ϊ����ʧ�ܡ�");
			}
			seat.setStatus(Seat.STATE_SALED);
			session.update(seat);
			ticketLog.setSeatNo(seat.getSeatNo());

			logger.info("3����¼Ʊ����־");
			// ��¼Ʊ����Ϣ
			session.save(ticketLog);

			logger.info(" 4����ӡƱ��");
			Configuration.load();
			Printer printer = new Printer();
			AbstractDocument doucument = new PosDocument();
			SimpleDateFormat printSdf = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");
			SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
			Date departTime = sdf.parse(ticketLog.getDepartDate()
					+ ticketLog.getDepartTime());

			String content = "У����Ʊ" + "<br>���κţ�" + serdayId + "<br>��λ�ţ�"
					+ ticketLog.getSeatNo() + "<br>���վ��"
					+ ticketLog.getStartAddr() + "<br>�յ�վ��"
					+ ticketLog.getEndAddr() + "<br>����ʱ�䣺"
					+ printSdf.format(departTime) + "<br>Ʊ�ۣ�"
					+ ticketLog.getPrice() + "<br>֧����ʽ��"
					+ ticketLog.getPayType() + "<br>Ʊ�����ͣ�"
					+ ticketLog.getTicketType() + "<br>��ӡʱ�䣺"
					+ printSdf.format(ticketLog.getPrintTime()) + "<br>��ӡ�ˣ�"
					+ "����";
			doucument.addPage(content);
			printer.setDocument(doucument);
			printer.print();

			// �ύ�������������
			logger.info(" 4���ύ�������������");
			tx.commit();

		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			logger.error("��ӡԤ��Ʊʧ��" + e.getMessage());
			throw new Exception("��ӡԤ��Ʊʧ��" + e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	/**
	 * ȡ��Ԥ��Ʊ
	 * 
	 * @param selBusserDayS
	 */
	public void cancelReserve(List<Seat> selSeatS) throws Exception {
		try {
			ticketDao.cancelReserve(selSeatS);
		} catch (Exception e) {
			logger.error("ȡ��Ԥ��Ʊʧ��" + e.getMessage());
			throw new Exception("ȡ��Ԥ��Ʊʧ��" + e.getMessage());
		}

	}

	public Seat getSeat(String seatId) {
		return ticketDao.getSeat(seatId);
	}

	/**
	 * ��Ʊ
	 * 
	 * @param ticketId
	 * @param handFee
	 * @throws Exception
	 */
	public void backTicket(String ticketId, String handFee) throws Exception {
		try {
			TicketLog ticketLog = ticketDao.getTicketLog(ticketId);
			if (ticketLog == null) {
				logger.error("���Ҳ�����Ӧ����Ʊ��¼");
				throw new Exception("���Ҳ�����Ӧ����Ʊ��¼");
			} else {
				if (ticketLog.getIsback()) {
					logger.error("��Ʊ����");
					throw new Exception("��Ʊ����");
				}
				ticketDao.backTicket(ticketLog, handFee);
			}

		} catch (Exception e) {
			logger.error("��Ʊʧ��," + e.getMessage());
			throw new Exception("��Ʊʧ��," + e.getMessage());
		}
	}

}
