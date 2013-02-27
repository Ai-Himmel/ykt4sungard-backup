package com.kingstargroup.action.dictionary;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.DeviceResult;
import com.kingstargroup.utils.XMLGenerateUtil;

public class InitialDictionary extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(InitialDictionary.class);

	/**
	 * 设备类型数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward SetTypeList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("SetTypeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {
				// MessageResources msgResources = (MessageResources) this
				// .getServlet().getServletContext().getAttribute(
				// Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("select new com.kingstargroup.form.DeviceResult"
								+ "(a.id.dictval,a.dictcaption) from TDictionary a where a.id.dicttype=47 ");
				List list = query.list();				
				
				Query queryService = session
				.createQuery("select new com.kingstargroup.form.DeviceResult"
						+ "(a.dictCode,a.dictCaption) from MapSysDictionary a where a.id.dictNo=4 ");
				List listService = queryService.list();
				
				list.addAll(listService);
				
				DeviceResult server = new DeviceResult("0000", "服务器");				
				list.add(server);

				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"SetTypeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("SetTypeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * 流水错误码数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward SerialErrorList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("SerialErrorList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				//查询数据字典中错误代码相关的字典
				Query query = session
						.createQuery("select new com.kingstargroup.form.DeviceResult"
								+ "(a.id.dictValue,a.dictCaption) from MapSysDictionary a where a.id.dictNo=1 or a.id.dictNo=5 ");
				List list = query.list();
				//查询设备状态代码中错误代码相关的部分
				Query dicQuery = session.createQuery("select distinct new com.kingstargroup.form.DeviceResult(101||a.errorcode,a.statename) from MapStateDic a where a.errornot=1" );
				List diclist =  dicQuery.list();
				list.addAll(diclist);
				
				Query reversedicQuery = session.createQuery("select distinct new com.kingstargroup.form.DeviceResult(151||a.errorcode,a.statename) from MapStateDic a where a.errornot=0" );
				List reversediclist =  reversedicQuery.list();
				list.addAll(reversediclist);
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"SerialErrorList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("SerialErrorList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	
	
	/**
		* Method name: DeviceErrorList<br>
		* Description: 返回设备错误码<br>
		* Return: ActionForward<br>
		* Args: @param mapping
		* Args: @param form
		* Args: @param request
		* Args: @param response
		* Args: @return
		* Args: @throws Exception
		*/
	public ActionForward DeviceErrorList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("DeviceErrorList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";

				//查询设备状态代码中错误代码相关的部分
				Query dicQuery = session.createQuery("select distinct new com.kingstargroup.form.DeviceResult"
								+ "(a.tagcode,a.statename) from MapStateDic a where a.errornot=1 order by a.tagcode" );
				List diclist =  dicQuery.list();
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(diclist.size()), diclist);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"DeviceErrorList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("DeviceErrorList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	
	public ActionForward DeviceErrSelection(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("DeviceErrSelection(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";

				//查询设备状态代码中错误代码相关的部分
				Query dicQuery = session.createQuery("from MapStateDic order by tagcode" );
				List diclist =  dicQuery.list();
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(diclist.size()), diclist);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"DeviceErrSelection(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("DeviceErrSelection(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	/**
	 * 流水状态数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward SerialStatueList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("SerialStatueList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("select new com.kingstargroup.form.DeviceResult"
								+ "(a.id.dictval,a.dictcaption) from TDictionary a where a.id.dicttype=3 ");
				List list = query.list();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"SerialStatueList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("SerialStatueList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * 设备状态数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward SetStatueList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("SetStatueList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("select new com.kingstargroup.form.DeviceResult"
								+ "(a.id.dictval,a.dictcaption) from TDictionary a where a.id.dicttype=5 ");
				List list = query.list();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"SetStatueList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("SetStatueList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * 设备地址数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward AreaList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("AreaList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("select new com.kingstargroup.form.AreaResult"
								+ "(a.areacode,a.areaname) from TArea a ");
				List list = query.list();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"AreaList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("AreaList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * 卡类型数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward CardTypeList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("CardTypeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("select new com.kingstargroup.form.DeviceResult"
								+ "(a.id.dictval,a.dictcaption) from TDictionary a where a.id.dicttype=18 ");
				List list = query.list();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"CardTypeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("CardTypeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * 交易码数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward TradeCodeList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("TradeCodeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");

			try {

				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("select new com.kingstargroup.form.DictionaryResult"
								+ "(a.transcode,a.transname) from TTranscode a ");
				List list = query.list();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"TradeCodeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("TradeCodeList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * 服务类型数据字典
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward ServiceTypeList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		String xmlOut = "";
		HttpSession httpSession = request.getSession();
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");
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
								"ServiceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
				e.printStackTrace();

			} catch (Exception e) {
				logger
						.error(
								"ServiceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}
		if (logger.isDebugEnabled()) {
			logger
					.debug("deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

}
