package com.kingstargroup.action.search;

import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapFathersetsTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class ServerManageAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ServerManageAction.class);

	/**
	 * Description: 重置用户信息
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		// HttpSession httpSession = request.getSession();
		// 判断信息
		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		String systemid = request.getParameter("systemid");
		String systemname = request.getParameter("systemname");
		String operationsystem = request.getParameter("operationsystem");
		String ip = request.getParameter("ip");
		String hostname = request.getParameter("hostname");
		String area = request.getParameter("area");
		String mac = request.getParameter("mac");

		try {

			Session session = HibernateSessionFactory.currentSession();
			
			
			Query query = session
					.createQuery("from MapFathersetsTable a where a.systemid= :systemid");
			query.setString("systemid", systemid);
			List list = query.list();
			if (list.size() > 0) {
				// 不能添加
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.CAN_NOT_RESET,
								msgResources
										.getMessage("server.ServerManager.SERVER_EXIST"),
								null);
			} else {
				tx = session.beginTransaction();
				Query queryTwo = session
				.createSQLQuery(
						"select (max(a.id)+1) as maxId from YKT_MON.MAP_FATHERSETS_TABLE a")
				.addScalar("maxId", Hibernate.INTEGER);
				List listTwo = queryTwo.list();
				Iterator iterTwo = listTwo.iterator();
				long maxId = 1;
				if(iterTwo.hasNext()){
					Object tmp = iterTwo.next();
					if(tmp!=null){
						maxId = Long.parseLong(tmp.toString());
					}
				}
				MapFathersetsTable mapFathersetsTable = new MapFathersetsTable();
				mapFathersetsTable.setId(maxId);
				mapFathersetsTable.setSystemid(systemid);
				mapFathersetsTable.setSystemname(systemname);
				mapFathersetsTable.setIp(ip);
				mapFathersetsTable.setArea(area);
				mapFathersetsTable.setCoordx(Double.parseDouble("0"));
				mapFathersetsTable.setCoordy(Double.parseDouble("0"));
				mapFathersetsTable.setFeature("1");
				mapFathersetsTable.setHostname(hostname);
				mapFathersetsTable.setMacaddress(mac);
				mapFathersetsTable.setOperationsystem(operationsystem);
				mapFathersetsTable.setStatus(Long.parseLong("0"));
				session.save(mapFathersetsTable);				
				tx.commit();
				xmlOut = XMLGenerateUtil
				.XMLGenerate(
						ErrorCode.SUCCESS,
						msgResources
								.getMessage("server.ServerManager.SERVER_ADD_SUCCESS"),
						null);
			}
			
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {				
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		// HttpSession httpSession = request.getSession();
		// 判断信息
		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		String systemid = request.getParameter("systemid");
		String systemname = request.getParameter("systemname");
		String operationsystem = request.getParameter("operationsystem");
		String ip = request.getParameter("ip");
		String hostname = request.getParameter("hostname");
		String area = request.getParameter("area");
		String mac = request.getParameter("mac");

		try {

			Session session = HibernateSessionFactory.currentSession();

			Query query = session
					.createQuery("from MapFathersetsTable a where a.systemid= :systemid");
			query.setString("systemid", systemid);
			List list = query.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				tx = session.beginTransaction();
				MapFathersetsTable mapFathersetsTable = (MapFathersetsTable) iter
						.next();
				mapFathersetsTable.setSystemname(systemname);
				mapFathersetsTable.setIp(ip);
				mapFathersetsTable.setArea(area);
				mapFathersetsTable.setFeature("1");
				mapFathersetsTable.setHostname(hostname);
				mapFathersetsTable.setMacaddress(mac);
				mapFathersetsTable.setOperationsystem(operationsystem);
				mapFathersetsTable.setStatus(Long.parseLong("0"));
				session.update(mapFathersetsTable);
				tx.commit();
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.SUCCESS,
								msgResources
										.getMessage("server.ServerManager.SERVER_UPDATE_SUCCESS"),
								null);
			} else {
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.CAN_NOT_RESET,
								msgResources
										.getMessage("server.ServerManager.SERVER_NOT_EXIST"),
								null);
			}

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 查询用户信息列表
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward ServerList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		String systemid = request.getParameter("systemid");
		String systemname = request.getParameter("ServerName");
		String operationsystem = request.getParameter("OpSystem");
		String ip = request.getParameter("IpAddr");

		StringBuffer sqlBuff = new StringBuffer();
		sqlBuff.append("from MapFathersetsTable a where 1=1");

		if (!"".equals(systemid) && null != systemid) {
			sqlBuff.append(" and a.systemid = :systemid");
		}
		if (!"".equals(systemname) && null != systemname) {
			sqlBuff.append(" and a.systemname like :systemname");
		}
		if (!"".equals(ip) && null != ip) {
			sqlBuff.append(" and a.ip like :ip");
		}
		if (!"".equals(operationsystem) && null != operationsystem) {
			sqlBuff.append(" and a.operationsystem = '")
					.append(operationsystem).append("'");
		}

		try {

			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session.createQuery(sqlBuff.toString());
			if (!"".equals(systemid) && null != systemid) {
				query.setString("systemid", systemid);
			}
			if (!"".equals(systemname) && null != systemname) {
				query.setString("systemname", "%"+systemname+"%");
			}
			if (!"".equals(ip) && null != ip) {
				query.setString("ip", "%"+ip+"%");
			}
			List list = query.list();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 管理员删除用户
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-13 创建
	 */

	public ActionForward deleteServer(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("deleteUser(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		String systemid = request.getParameter("systemid");
		try {

			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			// delete
			session.createQuery(
					"delete MapFathersetsTable where systemid=:systemid")
					.setString("systemid", systemid).executeUpdate();
			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("server.ServerManager.DELETE_SUCCESS"),
							null);

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"deleteServer(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("deleteUser(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	
	public ActionForward areaList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.AreaResult(a.areacode,a.areaname) from TArea a where a.arealevel=2 ");
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	
	
	
}
