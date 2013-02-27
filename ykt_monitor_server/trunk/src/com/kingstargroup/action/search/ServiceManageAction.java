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
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapServiceTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class ServiceManageAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ServiceManageAction.class);

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

		String serviceName = request.getParameter("ServiceName");
		String serviceType = request.getParameter("ServiceType");
		String serverId = request.getParameter("ServerId");
		String serverName = request.getParameter("ServerName");

		String url = request.getParameter("URL");
		String ip = request.getParameter("Ip");
		String port = request.getParameter("Port");
		String dbname = request.getParameter("Dbname");
		String username = request.getParameter("Username");
		String password = request.getParameter("Password");

		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			MapServiceTable mapServiceTable = new MapServiceTable();
			mapServiceTable.setServiceName(serviceName);
			mapServiceTable.setServiceType(serviceType);
			mapServiceTable.setServerId(Long.parseLong(serverId));
			mapServiceTable.setServerName(serverName);
			mapServiceTable.setIp(ip);
			mapServiceTable.setUrl(url);
			if (null != port && !"".equals(port)) {
				mapServiceTable.setPort(Long.parseLong(port));
			}
			mapServiceTable.setDbname(dbname);
			mapServiceTable.setUsername(username);
			mapServiceTable.setPassword(password);
			session.save(mapServiceTable);
			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("service.ServiceManager.SERVICE_ADD_SUCCESS"),
							null);

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

		} catch (Exception e) {
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
		String serviceId = request.getParameter("ServiceId");
		String serviceName = request.getParameter("ServiceName");
		String serviceType = request.getParameter("ServiceType");
		String serverId = request.getParameter("ServerId");
		String serverName = request.getParameter("ServerName");

		String url = request.getParameter("URL");
		String ip = request.getParameter("Ip");
		String port = request.getParameter("Port");
		String dbname = request.getParameter("Dbname");
		String username = request.getParameter("Username");
		String password = request.getParameter("Password");

		try {

			Session session = HibernateSessionFactory.currentSession();

			Query query = session
					.createQuery("from MapServiceTable a where a.serviceId= :serviceId");
			query.setInteger("serviceId", Integer.parseInt(serviceId));
			List list = query.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				tx = session.beginTransaction();
				MapServiceTable mapServiceTable = (MapServiceTable) iter.next();
				mapServiceTable.setServiceName(serviceName);
				mapServiceTable.setServiceType(serviceType);
				mapServiceTable.setServerId(Long.parseLong(serverId));
				mapServiceTable.setServerName(serverName);
				mapServiceTable.setIp(ip);
				mapServiceTable.setUrl(url);
				if (null != port && !"".equals(port)) {
					mapServiceTable.setPort(Long.parseLong(port));
				}
				mapServiceTable.setDbname(dbname);
				mapServiceTable.setUsername(username);
				mapServiceTable.setPassword(password);
				session.update(mapServiceTable);
				tx.commit();
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.SUCCESS,
								msgResources
										.getMessage("service.ServiceManager.SERVICE_UPDATE_SUCCESS"),
								null);
			} else {
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.CAN_NOT_RESET,
								msgResources
										.getMessage("service.ServiceManager.SERVICE_NOT_EXIST"),
								null);
			}

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"update(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
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

		} catch (Exception e) {
			logger
					.error(
							"update(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
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
	public ActionForward ServiceList(ActionMapping mapping, ActionForm form,
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

		String serviceName = request.getParameter("ServiceName");
		String serviceType = request.getParameter("ServiceType");
		String serverName = request.getParameter("ServerName");

		StringBuffer sqlBuff = new StringBuffer();
		sqlBuff.append("from MapServiceTable a where 1=1");

		if (!"".equals(serviceName) && null != serviceName) {
			sqlBuff.append(" and a.serviceName like :serviceName");
		}
		if (!"".equals(serviceType) && null != serviceType
				&& !"-".equals(serviceType)) {
			sqlBuff.append(" and a.serviceType = :serviceType");
		}
		if (!"".equals(serverName) && null != serverName) {
			sqlBuff.append(" and a.serverName like :serverName");
		}
		try {

			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session.createQuery(sqlBuff.toString());
			if (!"".equals(serviceName) && null != serviceName) {
				query.setString("serviceName", "%" + serviceName + "%");
			}

			if (!"".equals(serviceType) && null != serviceType
					&& !"-".equals(serviceType)) {
				query.setString("serviceType", serviceType);
			}

			if (!"".equals(serverName) && null != serverName) {
				query.setString("serverName", "%" + serverName + "%");
			}
			List list = query.list();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(ErrorCode.SUCCESS,
					String.valueOf(list.size()), list, "2");
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

	public ActionForward deleteService(ActionMapping mapping, ActionForm form,
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
		String serviceId = request.getParameter("ServiceId");
		try {

			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			// delete
			session.createQuery(
					"delete MapServiceTable where serviceId=:serviceId")
					.setInteger("serviceId", Integer.parseInt(serviceId))
					.executeUpdate();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS,
					msgResources
							.getMessage("service.ServiceManager.DELETE_SUCCESS"),
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

	public ActionForward ServiceTypeList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(a.dictCode,a.dictCaption) from MapSysDictionary a where a.id.dictNo=4 ");
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

	public ActionForward ServerTypeList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DictionaryResult(a.id,a.systemname) from MapFathersetsTable a ");
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
