/**
 * 
 */
package com.kingstargroup.conference.util;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.dbutils.BasicRowProcessor;
import org.apache.commons.dbutils.DbUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.MapListHandler;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.Encryptor;
import com.kingstargroup.conference.dao.AssemblyRoomDAO;
import com.kingstargroup.conference.dao.AttendeeDAO;
import com.kingstargroup.conference.dao.AttendeeGroupDAO;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.ConferenceTypeDAO;
import com.kingstargroup.conference.dao.FuncListDAO;
import com.kingstargroup.conference.dao.OperatorDAO;
import com.kingstargroup.conference.hibernate.HibernateSessionFactory;
import com.kingstargroup.conference.hibernate.form.TAssemblyRoom;
import com.kingstargroup.conference.hibernate.form.TAttendeeGroup;
import com.kingstargroup.conference.hibernate.form.TAttendeeGroupKey;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TAttendeeListKey;
import com.kingstargroup.conference.hibernate.form.TCifCustomer;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TConferenceType;
import com.kingstargroup.conference.hibernate.form.TDelegate;
import com.kingstargroup.conference.hibernate.form.TDeptLimit;
import com.kingstargroup.conference.hibernate.form.TDeptLimitKey;
import com.kingstargroup.conference.hibernate.form.TFuncList;
import com.kingstargroup.conference.hibernate.form.TGroup;
import com.kingstargroup.conference.hibernate.form.TOperLimit;
import com.kingstargroup.conference.hibernate.form.TOperLimitKey;
import com.kingstargroup.conference.hibernate.form.TOperator;
import com.kingstargroup.conference.hibernate.form.TRecordhis;

public class SynchronizeUtil extends BasicUtil {

	/**
	 * File name: SynchronizeUtil.java<br>
	 * Description: 数据库是否连通<br>
	 * Return:
	 * 
	 * @param databaseIP
	 *            Return:
	 * @param port
	 *            Return:
	 * @param dbname
	 *            Return:
	 * @param username
	 *            Return:
	 * @param password
	 *            Return:
	 * @return<br>
	 *         Modify History: <br>
	 *         操作类型 操作人 操作时间 操作内容<br>
	 *         ======================================<br>
	 *         创建 何林青 2007-1-15 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */

	public boolean Chekdatabase(String databaseIP, String port, String dbname,
			String username, String password) {
		return SynchDBUtils.checkDBstatus("db2", databaseIP, port, dbname,
				username, password);
	}

	public boolean checkuser(String databaseIP, String port, String dbname,
			String dbusername, String dbpassword, String username,
			String password) {
		SynchDBUtils dbutil = new SynchDBUtils("db2", databaseIP, port, dbname,
				dbusername, dbpassword);
		Connection conn = null;
		password = Encryptor.digest(password);// 加密

		try {
			conn = dbutil.getConnection();
			QueryRunner qr = new QueryRunner();
			ResultSetHandler rsh = new BeanListHandler(TConference.class,
					BasicRowProcessor.instance());
			String strsql = "select * from YKT_CONF.T_OPERATOR where OPER_CODE='"
					+ username + "' and OPER_PWD='" + password + "'";
			List list = (List) qr.query(conn, strsql, rsh);
			dbutil.closeConnecttion(conn);

			if (list == null || list.size() == 0) {
				return false;
			} else {
				return true;
			}
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}

	public List getConferenceList(String databaseIP, String port,
			String dbname, String dbusername, String dbpassword, String username) {
		SynchDBUtils dbutil = new SynchDBUtils("db2", databaseIP, port, dbname,
				dbusername, dbpassword);
		List confList = null;
		Connection conn = null;
		try {
			conn = dbutil.getConnection();
			QueryRunner qr = new QueryRunner();
			ResultSetHandler rsh = new BeanListHandler(TConference.class,
					BasicRowProcessor.instance());
			String strsql = "select a.* from ykt_conf.t_conference a "
					+ "where a.CON_BEGINDATE>='"
					+ DateUtilExtend.getNowDate2()
					+ "' and a.STATUS<>'9' and a.CON_BEGINTIME>='"
					+ DateUtilExtend.getNowTime2()
					+ "' and a.ORGANIGER_ID in (select b.DEPT_ID from YKT_CONF.T_OPERATOR b where b.OPER_CODE='"
					+ username + "')";
			confList = (List) qr.query(conn, strsql, rsh);
			DbUtils.close(conn);
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return confList;
	}

	public boolean synchData(String databaseIP, String port, String dbname,
			String dbusername, String dbpassword, String username, String confs) {
		SynchDBUtils dbutil = new SynchDBUtils("db2", databaseIP, port, dbname,
				dbusername, dbpassword);
		Connection conn = null;
		Transaction t = beginTransaction();
		Session session = HibernateSessionFactory.currentSession();
		try {
			conn = dbutil.getConnection();
			QueryRunner qr = new QueryRunner();
			ResultSetHandler rsh = new BeanListHandler(TConference.class);
			String strsql = "select * from ykt_conf.T_CONFERENCE where CON_ID in ("
					+ confs + ")";
			List T_CONFERENCE = (List) qr.query(conn, strsql, rsh);

			rsh = new BeanListHandler(TAssemblyRoom.class);
			strsql = "select * from ykt_conf.T_ASSEMBLY_ROOM";
			List T_ASSEMBLY_ROOM = (List) qr.query(conn, strsql, rsh);

			rsh = new MapListHandler();
			strsql = "select CUST_ID as custId, GROUP_ID as groupId, COMMENTS from ykt_conf.T_ATTENDEE_GROUP";
			List T_ATTENDEE_GROUP = (List) qr.query(conn, strsql, rsh);

			rsh = new MapListHandler();
			strsql = "select CON_ID as conId, CUST_ID as custId, PHYSICAL_NO as physicalNo, CARD_NO as cardNo, "
					+ "ALLOT_DATE as allotDate, ALLOT_TIME as allotTime, SEND_SIGN as sendSign, "
					+ "DEL_SIGN as delSign, ATTENDEE_TYPE as attendeeType, ATTEND_SIGN as attendSign,"
					+ " ATTEND_DATE as attendDate, ATTEND_TIME as attendTime, LEAVE_REASON as leaveReason, "
					+ "REPLACER_ID as replacerId, REPLACER_NAME replacerName, REPLACER_DEPT as replacerDept, "
					+ "REPLACER_DUTY as replacerDuty, REPLACER_COMMENTS as replacerComments, DELEGRAY "
					+ "from ykt_conf.T_ATTENDEE_LIST left join ykt_cur.t_pif_card on card_no=card_id where CON_ID in("
					+ confs + ")";
			List T_ATTENDEE_LIST = (List) qr.query(conn, strsql, rsh);

			rsh = new BeanListHandler(TConferenceType.class);
			strsql = "select * from ykt_conf.T_CONFERENCE_TYPE";
			List T_CONFERENCE_TYPE = (List) qr.query(conn, strsql, rsh);

			rsh = new MapListHandler();
			strsql = "select OPER_CODE as operCode, DEPT_ID as deptId from ykt_conf.T_DEPT_LIMIT where OPER_CODE='"
					+ username + "'";
			List T_DEPT_LIMIT = (List) qr.query(conn, strsql, rsh);

			// rsh = new MapListHandler();
			// strsql = "select CON_ID as conId, DEVICE_ID as deviceId, "
			// + "CON_BEGINDATE as conBegindate, CON_BEGINTIME as conBegintime,
			// "
			// + "CON_ENDTIME as conEndtime, CON_SIGNTIME as conSigntime "
			// + "from ykt_conf.T_DEV_CONFERENCE where CON_ID in(" + confs
			// + ")";
			// List T_DEV_CONFERENCE = (List) qr.query(conn, strsql, rsh);

			strsql = "select * from YKT_CONF.T_DELEGATE";
			rsh = new BeanListHandler(TDelegate.class);
			List T_DELEGATE = (List) qr.query(conn, strsql, rsh);

			strsql = "select * from ykt_conf.T_FUNC_LIST where FUNC_CODE>='5' and FUNC_CODE<'7'";
			rsh = new BeanListHandler(TFuncList.class);
			List T_FUNC_LIST = (List) qr.query(conn, strsql, rsh);

			rsh = new BeanListHandler(TGroup.class);
			strsql = "select * from ykt_conf.T_GROUP where OPER_ID='"
					+ username + "'";
			List T_GROUP = (List) qr.query(conn, strsql, rsh);

			rsh = new BeanListHandler(TOperator.class);
			strsql = "select * from ykt_conf.T_OPERATOR where OPER_CODE='"
					+ username + "'";
			List T_OPERATOR = (List) qr.query(conn, strsql, rsh);

			rsh = new MapListHandler();
			strsql = "select OPER_CODE as operCode, FUNC_CODE as funcCode from ykt_conf.T_OPER_LIMIT where OPER_CODE='"
					+ username + "' and FUNC_CODE>='5' and FUNC_CODE<'7'";
			List T_OPER_LIMIT = (List) qr.query(conn, strsql, rsh);

			rsh = new BeanListHandler(TCifCustomer.class);
			strsql = "select * from ykt_cur.T_CIF_CUSTOMER where CUT_ID in "
					+ "(select CUST_ID from ykt_conf.T_ATTENDEE_LIST where CON_ID in("
					+ confs + "))";
			List T_CIF_CUSTOMER = (List) qr.query(conn, strsql, rsh);

			Iterator iter = T_CONFERENCE.iterator();
			ConferenceDAO conf = ConferenceDAO.getInstance();
			conf.deleteAllConference();
			while (iter.hasNext()) {
				TConference temp = (TConference) iter.next();
				session.save(temp);
			}

			iter = T_ASSEMBLY_ROOM.iterator();
			AssemblyRoomDAO ass = AssemblyRoomDAO.getInstance();
			ass.deleteAllAssemblyRoom();
			while (iter.hasNext()) {
				TAssemblyRoom assroom = (TAssemblyRoom) iter.next();
				session.save(assroom);
			}

			iter = T_ATTENDEE_GROUP.iterator();
			AttendeeGroupDAO attendgroup = AttendeeGroupDAO.getInstance();
			attendgroup.deleteAllCustGroup();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				TAttendeeGroup attendeegroup = new TAttendeeGroup();
				TAttendeeGroupKey key = new TAttendeeGroupKey();
				key.setCustId(Integer.valueOf(map.get("custId").toString()));
				key.setGroupId(Integer.valueOf(map.get("groupId").toString()));
				attendeegroup.setId(key);
				attendeegroup.setComments(map.get("comments") == null ? ""
						: map.get("comments").toString());
				session.save(attendeegroup);
			}

			iter = T_ATTENDEE_LIST.iterator();
			AttendeeDAO attend = AttendeeDAO.getInstance();
			attend.deleteAllAttendeeList();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				TAttendeeList attendeelist = new TAttendeeList();
				TAttendeeListKey key = new TAttendeeListKey();
				key.setConId(Integer.valueOf(map.get("conId").toString()));
				key.setCustId(Integer.valueOf(map.get("custId").toString()));
				attendeelist.setAllotDate(map.get("allotDate") == null ? ""
						: map.get("allotDate").toString());
				attendeelist.setAllotTime(map.get("allotTime") == null ? ""
						: map.get("allotTime").toString());
				attendeelist.setAttendDate(map.get("attendDate") == null ? ""
						: map.get("attendDate").toString());
				attendeelist
						.setAttendeeType(map.get("attendeeType") == null ? ""
								: map.get("attendeeType").toString());
				attendeelist.setAttendSign(map.get("attendSign") == null ? ""
						: map.get("attendSign").toString());
				attendeelist.setAttendTime(map.get("attendTime") == null ? ""
						: map.get("attendTime").toString());
				attendeelist.setCardNo(map.get("cardNo") == null ? Integer
						.valueOf("0") : Integer.valueOf(map.get("cardNo")
						.toString()));
				attendeelist.setDelegray(map.get("delegray") == null ? Integer
						.valueOf("0") : (Integer) map.get("delegray"));
				attendeelist.setDelSign(map.get("delSign") == null ? "" : map
						.get("delSign").toString());
				attendeelist.setId(key);
				attendeelist.setPhysicalNo(map.get("physicalNo") == null ? ""
						: map.get("physicalNo").toString());
				attendeelist.setLeaveReason(map.get("leaveReason") == null ? ""
						: map.get("leaveReason").toString());
				attendeelist
						.setReplacerComments(map.get("replacerComments") == null ? ""
								: map.get("replacerComments").toString());
				attendeelist
						.setReplacerDept(map.get("replacerDept") == null ? ""
								: map.get("replacerDept").toString());
				attendeelist
						.setReplacerDuty(map.get("replacerDuty") == null ? ""
								: map.get("replacerDuty").toString());
				attendeelist.setReplacerId(map.get("replacerId") == null ? ""
						: map.get("replacerId").toString());
				attendeelist
						.setReplacerName(map.get("replacerName") == null ? ""
								: map.get("replacerName").toString());
				attendeelist.setSendSign(map.get("sendSign") == null ? "" : map
						.get("sendSign").toString());

				session.save(attendeelist);
			}

			iter = T_CONFERENCE_TYPE.iterator();
			ConferenceTypeDAO type = ConferenceTypeDAO.getInstance();
			type.deleteAllConferenceType();
			while (iter.hasNext()) {
				TConferenceType conftype = (TConferenceType) iter.next();
				session.save(conftype);
			}

			iter = T_DEPT_LIMIT.iterator();
			conf.deleteAllDeptLimit();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				TDeptLimit deptlimit = new TDeptLimit();
				TDeptLimitKey id = new TDeptLimitKey();
				id.setDeptId(map.get("deptId").toString());
				id.setOperCode(map.get("operCode").toString());
				deptlimit.setId(id);
				session.save(deptlimit);
			}

			// iter = T_DEV_CONFERENCE.iterator();
			// conf.deleteAllDevConference();
			// while (iter.hasNext()) {
			// HashMap map = (HashMap) iter.next();
			// TDevConference devconference = new TDevConference();
			// TDevConferenceKey id = new TDevConferenceKey();
			// id.setConId(Integer.valueOf(map.get("conId").toString()));
			// id.setDeviceId(Integer.valueOf(map.get("deviceId").toString()));
			// devconference
			// .setConBegindate(map.get("conBegindate") == null ? ""
			// : map.get("conBegindate").toString());
			// devconference
			// .setConBegintime(map.get("conBegintime") == null ? ""
			// : map.get("conBegintime").toString());
			// devconference.setConEndtime(map.get("conEndtime") == null ? ""
			// : map.get("conEndtime").toString());
			// devconference
			// .setConSigntime(map.get("conSigntime") == null ? ""
			// : map.get("conSigntime").toString());
			// devconference.setId(id);
			//
			// session.save(devconference);
			// }

			iter = T_DELEGATE.iterator();
			conf.deleteAllDelegate();
			while (iter.hasNext()) {
				TDelegate dlgt = (TDelegate) iter.next();
				session.save(dlgt);
			}

			iter = T_FUNC_LIST.iterator();
			FuncListDAO func = FuncListDAO.getInstance();
			func.deleteAllFuncList();
			while (iter.hasNext()) {
				TFuncList funclist = (TFuncList) iter.next();
				session.save(funclist);
			}
			TFuncList temp = new TFuncList();
			temp.setFuncCode("7");
			temp.setFuncName("单机管理");
			temp.setFuncUrl(null);
			session.save(temp);
			TFuncList temp1 = new TFuncList();
			temp1.setFuncCode("7.1");
			temp1.setFuncName("数据同步");
			temp1.setFuncUrl("/dbconfigure.do");
			session.save(temp1);
			TFuncList temp2 = new TFuncList();
			temp2.setFuncCode("7.2");
			temp2.setFuncName("设备管理");
			temp2.setFuncUrl("/deviceconfigure.do");
			session.save(temp2);

			TFuncList temp3 = new TFuncList();
			temp3.setFuncCode("7.3");
			temp3.setFuncName("数据回归");
			temp3.setFuncUrl("/backdbconfigure.do");
			session.save(temp3);

			iter = T_GROUP.iterator();
			conf.deleteAllGroup();
			while (iter.hasNext()) {
				TGroup group = (TGroup) iter.next();
				session.save(group);
			}

			iter = T_OPERATOR.iterator();
			OperatorDAO oper = OperatorDAO.getInstance();
			oper.deleteAllOperator();
			while (iter.hasNext()) {
				TOperator operator = (TOperator) iter.next();
				session.save(operator);
			}

			iter = T_OPER_LIMIT.iterator();
			oper.deleteAllOperLimit();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				TOperLimit operlimit = new TOperLimit();
				TOperLimitKey id = new TOperLimitKey();
				id.setFuncCode(map.get("funcCode").toString());
				id.setOperCode(map.get("operCode").toString());
				operlimit.setId(id);
				session.save(operlimit);
			}
			TOperLimit operlimit1 = new TOperLimit();
			TOperLimitKey id1 = new TOperLimitKey();
			id1.setFuncCode("7");
			id1.setOperCode(username);
			operlimit1.setId(id1);
			session.save(operlimit1);
			TOperLimit operlimit2 = new TOperLimit();
			TOperLimitKey id2 = new TOperLimitKey();
			id2.setFuncCode("7.1");
			id2.setOperCode(username);
			operlimit2.setId(id2);
			session.save(operlimit2);
			TOperLimit operlimit3 = new TOperLimit();
			TOperLimitKey id3 = new TOperLimitKey();
			id3.setFuncCode("7.2");
			id3.setOperCode(username);
			operlimit3.setId(id3);
			session.save(operlimit3);
			TOperLimit operlimit4 = new TOperLimit();
			TOperLimitKey id4 = new TOperLimitKey();
			id4.setFuncCode("7.3");
			id4.setOperCode(username);
			operlimit4.setId(id4);
			session.save(operlimit4);

			iter = T_CIF_CUSTOMER.iterator();
			oper.deleteAllCustomer();
			while (iter.hasNext()) {
				TCifCustomer cifcustomer = (TCifCustomer) iter.next();
				session.save(cifcustomer);
			}
			session.flush();
			session.clear();
			t.commit();
			dbutil.closeConnecttion(conn);
		} catch (Exception e) {
			if (null != t) {
				t.rollback();
			}
			e.printStackTrace();
			return false;
		} finally {
			HibernateSessionFactory.closeSession();
		}

		return true;
	}

	public boolean backsynchData(String databaseIP, String port, String dbname,
			String dbusername, String dbpassword, String username, String confs) {
		SynchDBUtils dbutil = new SynchDBUtils("db2", databaseIP, port, dbname,
				dbusername, dbpassword);
		Connection conn = null;
		Session session = HibernateSessionFactory.currentSession();
		try {
			conn = dbutil.getConnection();
			QueryRunner delqr = new QueryRunner();
			String delsql = ("delete from ykt_conf.t_recordhis where confid in("+confs+")");
			delqr.update(conn, delsql);
			
			
			Query query = session
					.createQuery("from TAttendeeList a where a.id.conId in ("
							+ confs + ")");
			List list = query.list();
			Iterator iter = list.iterator();
			QueryRunner qr = new QueryRunner();
			while (iter.hasNext()) {
				TAttendeeList attendee = (TAttendeeList) iter.next();

				String sql = ("update ykt_conf.t_attendee_list set attend_sign= '"
						+ attendee.getAttendSign()
						+ "',"
						+ "attend_date='"
						+ attendee.getAttendDate()
						+ "',attend_time='"
						+ attendee.getAttendTime()
						+ "',"
						+ "leave_reason='"
						+ attendee.getLeaveReason()
						+ "',replacer_id='"
						+ attendee.getReplacerId()
						+ "',"
						+ " replacer_name='"
						+ attendee.getReplacerName()
						+ "', replacer_dept='"
						+ attendee.getReplacerDept()
						+ "', "
						+ "replacer_duty='"
						+ attendee.getReplacerDuty()
						+ "', replacer_comments='"
						+ attendee.getReplacerComments()
						+ "', delegray="
						+ attendee.getDelegray()
						+ " where con_id="
						+ attendee.getId().getConId() + " and cust_id=" + attendee
						.getId().getCustId());
				qr.update(conn, sql);

			}

			Query query_his = session.createQuery("from TRecordhis");
			List list_his = query_his.list();
			Iterator iter_his = list_his.iterator();
			QueryRunner qr_his = new QueryRunner();
			while (iter_his.hasNext()) {
				TRecordhis rh = (TRecordhis) iter_his.next();

				// String sql = ("update ykt_conf.t_recordhis set confid= "
				// + rh.getConfid()
				// + ","
				// + "physical_no='"
				// + rh.getPhysicalNo()
				// + "',checktime='"
				// + rh.getChecktime()
				// + "'");

				String sql = ("insert into ykt_conf.t_recordhis(confid,physical_no,checktime,attend_sign,dealornot) values("
						+ rh.getConfid()
						+ ",'"
						+ rh.getPhysicalNo()
						+ "','"
						+ rh.getChecktime()
						+ "','"
						+ rh.getAttendSign()
						+ "','" + rh.getDealornot() + "')");
				qr_his.update(conn, sql);

			}

			DbUtils.commitAndClose(conn);
		} catch (Exception e) {
			try {
				DbUtils.rollback(conn);
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			e.printStackTrace();
			return false;
		} finally {
			HibernateSessionFactory.closeSession();
		}

		return true;
	}

}
