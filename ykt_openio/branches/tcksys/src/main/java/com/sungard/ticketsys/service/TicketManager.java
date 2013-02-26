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
	 * 打印票务
	 * 
	 * @param ticketLog
	 * @throws Exception
	 */
	public void saleTicket(TicketLog ticketLog, Properties result)
			throws Exception {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = null;
		try {
			// 是否为预留票
			boolean isReserver = ticketLog.getIsReserve();

			String serdayId = ticketLog.getSerdayId();
			if (serdayId == null) {
				logger.error("获取车次信息失败。");
				throw new Exception("获取车次信息失败。");
			}

			logger.info("1、判断车次是否已过期");
			Date now = new Date();
			Calendar cnow = Calendar.getInstance();
			cnow.setTime(now);

			SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
			Date departTime = sdf.parse(ticketLog.getDepartDate()
					+ ticketLog.getDepartTime());
			Calendar cdepartTime = Calendar.getInstance();
			cdepartTime.setTime(departTime);
			if (cnow.after(cdepartTime)) {
				logger.error("发车时间已过，不可售票");
				throw new Exception("发车时间已过，不可售票");
			}

			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();

			logger.info("2、更新车次信息的票数");
			String busserDayhql = "from BusserDay t where t.serdayId ='"
					+ serdayId + "'";
			Query busserDayObject = session.createQuery(busserDayhql);
			BusserDay busserDay = (BusserDay) busserDayObject.list().get(0);

			if (isReserver) {
				int reserveCount = busserDay.getReserveCount();
				if (reserveCount < 1) {
					logger.error("该车次的预留票已打印完成。");
					throw new Exception("该车次的没有预留票。");
				}
				busserDay.setReserveCount(reserveCount - 1);
				busserDay.setTicketCount(busserDay.getTicketCount() + 1);
			} else {
				int remainCount = busserDay.getRemainCount();
				if (remainCount < 1) {
					logger.error("该车次的票已售完。");
					throw new Exception("该车次的票已售完。");
				}
				busserDay.setRemainCount(remainCount - 1);
				busserDay.setTicketCount(busserDay.getTicketCount() + 1);
			}

			// 更新票数
			session.update(busserDay);

			logger.info(" 3、获取座位号，并更新座位号信息为已售");
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
			// 记录票务信息
			ticketLog.setIsback(false);
			session.save(ticketLog);

			logger.info(" 4、扣款");
			if (ticketLog.getPayType().equals(TicketLog.PAY_TYPE_CARD)) {
				try {
					BigDecimal   b1   =   new   BigDecimal(ticketLog.getPrice()); 
				    BigDecimal   b2   =   new   BigDecimal("100");  
					int price = (int) b1.multiply(b2).doubleValue(); 
					cardPay(result, price);
				} catch (Exception e) {
					e.printStackTrace();
					logger.error("校园卡扣款失败," + e.getMessage());
					throw new Exception("校园卡扣款失败," + e.getMessage());
				}

			}

			logger.info(" 5、打印票务");
			Printer printer = new Printer();
			AbstractDocument doucument = new PosDocument();
			SimpleDateFormat printSdf = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");

			String content = "校车车票" + 
			                 "<br>票务号：" + ticketLog.getTicketId()+ 
			                 "<br>车次号：" + serdayId + 
			                 "<br>座位号：" + seat.getSeatNo() + 
			                 "<br>起点站：" + ticketLog.getStartAddr()+ 
			                 "<br>终点站：" + ticketLog.getEndAddr() + 
			                 "<br>发车时间：" + printSdf.format(departTime) + 
			                 "<br>票价：" + ticketLog.getPrice() + 
			                 "<br>支付方式："+ ticketLog.getPayType() + 
			                 "<br>票务类型："+ ticketLog.getTicketType() + 
			                 "<br>打印时间："+ printSdf.format(now) + 
			                 "<br>打印人：" + "测试";
			doucument.addPage(content);
			printer.setDocument(doucument);
			printer.print();

			// 提交，本次事物结束
			logger.info(" 6、提交，本次事物结束");
			tx.commit();

		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			logger.error("售票失败," + e.getMessage());
			throw new Exception(e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	/**
	 * 获取卡信息
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
		//获取卡信息
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
	 * 预留票
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
				logger.error("获取车次信息失败。");
				throw new Exception("获取车次信息失败。");
			}

			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();

			logger.info("1、更新车次信息的剩余票数和预留票数");
			String busserDayhql = "from BusserDay t where t.serdayId ='"
					+ serdayId + "'";
			Query busserDayObject = session.createQuery(busserDayhql);
			BusserDay busserDay = (BusserDay) busserDayObject.list().get(0);

			int remainCount = busserDay.getRemainCount();
			if (remainCount < reservecount) {
				logger.error("不足预留票数，当前剩余票数[" + remainCount + "]。");
				throw new Exception("不足预留票数，当前剩余票数[" + remainCount + "]。");
			}
			busserDay.setRemainCount(remainCount - reservecount);
			busserDay.setReserveCount(busserDay.getReserveCount()
					+ reservecount);

			// 更新票数
			session.update(busserDay);

			logger.info(" 2、获取座位号，并更新座位号信息为预留");
			String seathql = "from Seat s where rownum <= " + reservecount
					+ " and s.serdayId = '" + serdayId + "' and s.status = '"
					+ Seat.STATE_WAIT_SALE + "'";
			Query seatObject = session.createQuery(seathql);
			List<Seat> seats = (List<Seat>) seatObject.list();
			if (seats.size() != reservecount) {
				logger.error("获取的待预留的座位数错误，输入的预留数为[" + reservecount
						+ "],而获取的座位数为[" + seats.size() + "]");
				throw new Exception("获取的待预留的座位数错误，输入的预留数为[" + reservecount
						+ "],而获取的座位数为[" + seats.size() + "]");
			}
			for (int i = 0; i < seats.size(); i++) {
				Seat seat = seats.get(i);
				seat.setStatus(Seat.STATE_READY_SALE);
				seat.setMemo(memo);
				session.update(seat);
			}
			// 提交，结束本次事物
			logger.info(" 3、提交，本次事物结束");
			tx.commit();

		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			logger.error("预留票失败," + e.getMessage());
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
				logger.error("获取车次信息失败。");
				throw new Exception("获取车次信息失败。");
			}

			session.setFlushMode(FlushMode.COMMIT);
			tx = session.beginTransaction();

			logger.info("1、更新车次信息的预留票数和售出票数");
			String busserDayhql = "from BusserDay t where t.serdayId ='"
					+ serdayId + "'";
			Query busserDayObject = session.createQuery(busserDayhql);
			BusserDay busserDay = (BusserDay) busserDayObject.list().get(0);

			int reserveCount = busserDay.getReserveCount();
			if (reserveCount < 1) {
				logger.error("该车次的预留票已打印完成。");
				throw new Exception("该车次的预留票已打印完成。");
			}
			busserDay.setReserveCount(reserveCount - 1);
			busserDay.setTicketCount(busserDay.getTicketCount() + 1);
			// 更新票数
			session.update(busserDay);

			// 更新座号的状态
			logger.info("2、更新座号的状态为已售");
			String seathql = "from Seat s where s.serdayId = '" + serdayId
					+ "' and s.seatNo = " + ticketLog.getSeatNo()
					+ " and s.status = '" + Seat.STATE_READY_SALE + "'";
			Query seatObject = session.createQuery(seathql);
			Seat seat = (Seat) seatObject.list().get(0);
			if (seat == null) {
				logger.error("更新座号的状态为已售失败。");
				throw new Exception("更新座号的状态为已售失败。");
			}
			seat.setStatus(Seat.STATE_SALED);
			session.update(seat);
			ticketLog.setSeatNo(seat.getSeatNo());

			logger.info("3、记录票务日志");
			// 记录票务信息
			session.save(ticketLog);

			logger.info(" 4、打印票务");
			Configuration.load();
			Printer printer = new Printer();
			AbstractDocument doucument = new PosDocument();
			SimpleDateFormat printSdf = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");
			SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
			Date departTime = sdf.parse(ticketLog.getDepartDate()
					+ ticketLog.getDepartTime());

			String content = "校车车票" + "<br>车次号：" + serdayId + "<br>座位号："
					+ ticketLog.getSeatNo() + "<br>起点站："
					+ ticketLog.getStartAddr() + "<br>终点站："
					+ ticketLog.getEndAddr() + "<br>发车时间："
					+ printSdf.format(departTime) + "<br>票价："
					+ ticketLog.getPrice() + "<br>支付方式："
					+ ticketLog.getPayType() + "<br>票务类型："
					+ ticketLog.getTicketType() + "<br>打印时间："
					+ printSdf.format(ticketLog.getPrintTime()) + "<br>打印人："
					+ "测试";
			doucument.addPage(content);
			printer.setDocument(doucument);
			printer.print();

			// 提交，本次事物结束
			logger.info(" 4、提交，本次事物结束");
			tx.commit();

		} catch (Exception e) {
			if (tx != null) {
				tx.rollback();
			}
			e.printStackTrace();
			logger.error("打印预留票失败" + e.getMessage());
			throw new Exception("打印预留票失败" + e.getMessage());
		} finally {
			session.clear();
			HibernateSessionFactory.closeSession();
		}

	}

	/**
	 * 取消预留票
	 * 
	 * @param selBusserDayS
	 */
	public void cancelReserve(List<Seat> selSeatS) throws Exception {
		try {
			ticketDao.cancelReserve(selSeatS);
		} catch (Exception e) {
			logger.error("取消预留票失败" + e.getMessage());
			throw new Exception("取消预留票失败" + e.getMessage());
		}

	}

	public Seat getSeat(String seatId) {
		return ticketDao.getSeat(seatId);
	}

	/**
	 * 退票
	 * 
	 * @param ticketId
	 * @param handFee
	 * @throws Exception
	 */
	public void backTicket(String ticketId, String handFee) throws Exception {
		try {
			TicketLog ticketLog = ticketDao.getTicketLog(ticketId);
			if (ticketLog == null) {
				logger.error("查找不到对应的售票记录");
				throw new Exception("查找不到对应的售票记录");
			} else {
				if (ticketLog.getIsback()) {
					logger.error("该票已退");
					throw new Exception("该票已退");
				}
				ticketDao.backTicket(ticketLog, handFee);
			}

		} catch (Exception e) {
			logger.error("退票失败," + e.getMessage());
			throw new Exception("退票失败," + e.getMessage());
		}
	}

}
