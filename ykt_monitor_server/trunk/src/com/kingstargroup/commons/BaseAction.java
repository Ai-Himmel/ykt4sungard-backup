package com.kingstargroup.commons;

import org.apache.log4j.Logger;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: BaseAction.java
 * Description: 所有Action类的基类。
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-9-28    何林青    设计所有Action类的抽象方法
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import java.lang.reflect.Method;
import java.math.BigDecimal;
import java.sql.Timestamp;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map;
import java.util.ResourceBundle;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.beanutils.ConvertUtils;
import org.apache.commons.beanutils.converters.BigDecimalConverter;
import org.apache.commons.beanutils.converters.IntegerConverter;
import org.apache.commons.beanutils.converters.LongConverter;
import org.apache.commons.beanutils.converters.SqlTimeConverter;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.actions.LookupDispatchAction;
import org.apache.struts.config.MessageResourcesConfig;
import org.apache.struts.config.ModuleConfig;
import org.apache.struts.util.MessageResources;
import com.kingstargroup.Constants;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.SslUtil;

public class BaseAction extends LookupDispatchAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(BaseAction.class);

	protected transient final Log log = LogFactory.getLog(getClass());

	private static final String SECURE = "secure";

	private static Long defaultLong = null;

	/**
	 * NEW: added by Jaap
	 * 
	 * Message (key) name of default locale to message key lookup.
	 */
	protected Map defaultKeyNameKeyMap = null;

	static {

		ConvertUtils.register(new LongConverter(defaultLong), Long.class);
		ConvertUtils.register(new IntegerConverter(defaultLong), Integer.class);
		ConvertUtils.register(new SqlTimeConverter(), Timestamp.class);
		ConvertUtils.register(new BigDecimalConverter(null), BigDecimal.class);
	}

	/**
	 * Provides the mapping from resource key to method name
	 * 
	 * @return Resource key / method name map
	 */
	public Map getKeyMethodMap() {
		if (defaultKeyNameKeyMap == null) {
			Map map = new HashMap();

			String pkg = BaseAction.class.getPackage().getName();
			ResourceBundle methods = ResourceBundle.getBundle(pkg
					+ ".LookupMethods");

			Enumeration keys = methods.getKeys();

			while (keys.hasMoreElements()) {
				String key = (String) keys.nextElement();
				map.put(key, methods.getString(key));
			}
			defaultKeyNameKeyMap = map;
		}
		return defaultKeyNameKeyMap;
	}

	/**
	 * Convenience method to initialize messages in a subclass.
	 * 
	 * @param request
	 *            the current request
	 * @return the populated (or empty) messages
	 */
	public ActionMessages getMessages(HttpServletRequest request) {
		ActionMessages messages = null;
		HttpSession session = request.getSession();

		if (request.getAttribute(Globals.MESSAGE_KEY) != null) {
			messages = (ActionMessages) request
					.getAttribute(Globals.MESSAGE_KEY);
			saveMessages(request, messages);
		} else if (session.getAttribute(Globals.MESSAGE_KEY) != null) {
			messages = (ActionMessages) session
					.getAttribute(Globals.MESSAGE_KEY);
			saveMessages(request, messages);
			session.removeAttribute(Globals.MESSAGE_KEY);
		} else {
			messages = new ActionMessages();
		}

		return messages;
	}

	/**
	 * Override the execute method in LookupDispatchAction to parse URLs and
	 * forward to methods without parameters. Also will forward to unspecified
	 * method when no parameter is present. <p/> This is based on the following
	 * system: <p/>
	 * <ul>
	 * <li>edit*.html -> edit method</li>
	 * <li>update*.html -> update method</li>
	 * <li>view*.html -> view method</li>
	 * <li>create*.html -> create method</li>
	 * <li>find*.html -> find method</li>
	 * <li>other*.html -> another method</li>
	 * </ul>
	 * 
	 * @param mapping
	 *            The ActionMapping used to select this instance
	 * @param request
	 *            The HTTP request we are processing
	 * @param response
	 *            The HTTP response we are creating
	 * @param form
	 *            The optional ActionForm bean for this request (if any)
	 * @return Describes where and how control should be forwarded.
	 * @throws Exception
	 *             if an error occurs
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		request.setCharacterEncoding("GBK");
		HttpSession httpSession = request.getSession();
		if (httpSession.getAttribute("userLogin") != null) {
//			 Identify the request parameter containing the method name
			String parameter = mapping.getParameter();

			// don't set keyName unless it's defined on the action-mapping
			// no keyName -> unspecified will be called
			String keyName = null;

			if (parameter != null) {
				keyName = request.getParameter(parameter);
			}

			/*
			 * If there is no parameter set in the action mapping get the dispatcher
			 * method from the name of the action path
			 */
			if ((keyName == null) || (keyName.length() == 0)) {

				ActionForward returnActionForward = this.unspecified(mapping,
						form, request, response);
				if (logger.isDebugEnabled()) {
					logger
							.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
				}
				return returnActionForward;

			}

			// Identify the string to lookup

			ActionForward returnActionForward = dispatchMethod(mapping, form,
					request, response, keyName);
			if (logger.isDebugEnabled()) {
				logger
						.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
			}
			return returnActionForward;
		}else{
			if (logger.isInfoEnabled()) {
				logger
						.info("Some one Attack our web site at:"+DateUtil.getNow()); //$NON-NLS-1$
			}
			return null;
		}
		
		
	}

	/**
	 * Convenience method for getting an action form base on it's mapped scope.
	 * 
	 * @param mapping
	 *            The ActionMapping used to select this instance
	 * @param request
	 *            The HTTP request we are processing
	 * @return ActionForm the form from the specifies scope, or null if nothing
	 *         found
	 */
	protected ActionForm getActionForm(ActionMapping mapping,
			HttpServletRequest request) {
		ActionForm actionForm = null;

		// Remove the obsolete form bean
		if (mapping.getAttribute() != null) {
			if ("request".equals(mapping.getScope())) {
				actionForm = (ActionForm) request.getAttribute(mapping
						.getAttribute());
			} else {
				HttpSession session = request.getSession();

				actionForm = (ActionForm) session.getAttribute(mapping
						.getAttribute());
			}
		}

		return actionForm;
	}

	/**
	 * Convenience method to get the userForm from the session
	 * 
	 * @param session
	 *            the current user's session
	 * @return the user's populated form from the session
	 */
	protected MapUserTable getUser(HttpSession session) {
		// get the user form from the session
		return (MapUserTable) session.getAttribute(Constants.USER_KEY);
	}

	/**
	 * Convenience method to get the Configuration HashMap from the servlet
	 * context.
	 * 
	 * @return the user's populated form from the session
	 */
	public Map getConfiguration() {
		Map config = (HashMap) getServlet().getServletContext().getAttribute(
				Constants.CONFIG);
		// so unit tests don't puke when nothing's been set
		if (config == null) {
			return new HashMap();
		}
		return config;
	}

	// --------------------------------------------------------- Public Methods
	// Don't use class variables in Action objects. These are not session safe.

	/**
	 * Method to check and see if https is required for this resource
	 * 
	 * @param mapping
	 *            The ActionMapping used to select this instance
	 * @param request
	 *            The HTTP request we are processing
	 * @param response
	 *            The HTTP response we are creating
	 * @return boolean true if redirection to SSL is needed
	 */
	protected boolean checkSsl(ActionMapping mapping,
			HttpServletRequest request, HttpServletResponse response) {
		String redirectString = SslUtil.getRedirectString(request, getServlet()
				.getServletContext(), SECURE.equals(mapping.getParameter()));

		if (redirectString != null) {
			log.debug("protocol switch needed, redirecting...");

			try {
				// Redirect the page to the desired URL
				response.sendRedirect(response
						.encodeRedirectURL(redirectString));

				return true;
			} catch (Exception ioe) {
				log.error("redirect to new protocol failed...");

				// Handle appropriately
			}
		}

		return false;
	}

	/**
	 * Convenience method for removing the obsolete form bean.
	 * 
	 * @param mapping
	 *            The ActionMapping used to select this instance
	 * @param request
	 *            The HTTP request we are processing
	 */
	protected void removeFormBean(ActionMapping mapping,
			HttpServletRequest request) {
		// Remove the obsolete form bean
		if (mapping.getAttribute() != null) {
			if ("request".equals(mapping.getScope())) {
				request.removeAttribute(mapping.getAttribute());
			} else {
				HttpSession session = request.getSession();

				session.removeAttribute(mapping.getAttribute());
			}
		}
	}

	/**
	 * Convenience method to update a formBean in it's scope
	 * 
	 * @param mapping
	 *            The ActionMapping used to select this instance
	 * @param request
	 *            The HTTP request we are processing
	 * @param form
	 *            The ActionForm
	 */
	protected void updateFormBean(ActionMapping mapping,
			HttpServletRequest request, ActionForm form) {
		// Remove the obsolete form bean
		if (mapping.getAttribute() != null) {
			if ("request".equals(mapping.getScope())) {
				request.setAttribute(mapping.getAttribute(), form);
			} else {
				HttpSession session = request.getSession();

				session.setAttribute(mapping.getAttribute(), form);
			}
		}
	}

	/**
	 * 
	 * 
	 * This is the first time the default Locale is used so build the reverse
	 * lookup Map. Search for message keys in all configured MessageResources
	 * for the current module.
	 */
	protected Map initDefaultLookupMap(HttpServletRequest request) {
		Map lookupMap = new HashMap();
		this.keyMethodMap = this.getKeyMethodMap();

		ModuleConfig moduleConfig = (ModuleConfig) request
				.getAttribute(Globals.MODULE_KEY);

		MessageResourcesConfig[] mrc = moduleConfig
				.findMessageResourcesConfigs();

		// Look through all module's MessageResources
		for (int i = 0; i < mrc.length; i++) {
			MessageResources resources = this.getResources(request, mrc[i]
					.getKey());

			// Look for key in MessageResources
			Iterator iter = this.keyMethodMap.keySet().iterator();
			while (iter.hasNext()) {
				String key = (String) iter.next();
				String text = resources.getMessage(Locale.ENGLISH, key);

				// Found key and haven't added to Map yet, so add the text
				if ((text != null) && !lookupMap.containsKey(text)) {
					lookupMap.put(text, key);
				}
			}
		}

		return lookupMap;
	}
}
