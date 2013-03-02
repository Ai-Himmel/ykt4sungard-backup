/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portlet.wsrp;

import com.liferay.portal.util.WebKeys;
import com.liferay.portal.wsrp.util.WSRPUtil;
import com.liferay.portlet.StrutsPortlet;
import com.liferay.util.CollectionFactory;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.servlet.SessionMessages;

import java.io.IOException;

import java.security.Principal;

import java.util.Enumeration;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletException;
import javax.portlet.PortletMode;
import javax.portlet.PortletModeException;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletRequest;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowStateException;

import oasis.names.tc.wsrp.v1.types.BlockingInteractionResponse;
import oasis.names.tc.wsrp.v1.types.MarkupContext;
import oasis.names.tc.wsrp.v1.types.MarkupResponse;
import oasis.names.tc.wsrp.v1.types.PersonName;
import oasis.names.tc.wsrp.v1.types.PortletDescription;
import oasis.names.tc.wsrp.v1.types.RegistrationData;
import oasis.names.tc.wsrp.v1.types.SessionContext;
import oasis.names.tc.wsrp.v1.types.UpdateResponse;
import oasis.names.tc.wsrp.v1.types.UserContext;
import oasis.names.tc.wsrp.v1.types.UserProfile;

import org.apache.wsrp4j.consumer.ConsumerEnvironment;
import org.apache.wsrp4j.consumer.GroupSession;
import org.apache.wsrp4j.consumer.InteractionRequest;
import org.apache.wsrp4j.consumer.MarkupRequest;
import org.apache.wsrp4j.consumer.PortletDriver;
import org.apache.wsrp4j.consumer.PortletKey;
import org.apache.wsrp4j.consumer.PortletSession;
import org.apache.wsrp4j.consumer.PortletWindowSession;
import org.apache.wsrp4j.consumer.Producer;
import org.apache.wsrp4j.consumer.ProducerRegistry;
import org.apache.wsrp4j.consumer.URLGenerator;
import org.apache.wsrp4j.consumer.URLTemplateComposer;
import org.apache.wsrp4j.consumer.User;
import org.apache.wsrp4j.consumer.UserSession;
import org.apache.wsrp4j.consumer.WSRPPortlet;
import org.apache.wsrp4j.consumer.driver.PortletKeyImpl;
import org.apache.wsrp4j.consumer.driver.ProducerImpl;
import org.apache.wsrp4j.consumer.driver.UserImpl;
import org.apache.wsrp4j.consumer.driver.WSRPPortletImpl;
import org.apache.wsrp4j.exception.ErrorCodes;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.exception.WSRPXHelper;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.util.ParameterChecker;

/**
 * <a href="WSRPProxyPortlet.java.html"> <b><i>View Source </i> </b> </a>
 *
 * @author Michael Young
 * @version $Revision: 1.6 $
 *
 */
public class WSRPProxyPortlet extends StrutsPortlet {
	public void init(PortletConfig config) throws PortletException {
		_portletConfig = config;
		super.init(config);
	}

	public void processAction(ActionRequest request, ActionResponse response)
			throws PortletException, IOException {
		boolean remoteInvocation = ParamUtil.get(request,
				REMOTE_INVOCATION, false);

		if (remoteInvocation) {
			_processActionRemote(request, response);
		}
		else {
			super.processAction(request, response);
		}
	}

	public void render(RenderRequest request, RenderResponse response)
			throws PortletException, IOException {

		Exception producerConfigError = null;
		try {
			Producer producer = _createProducer(request.getPreferences());
			request.setAttribute(WebKeys.WSRP_PRODUCER, producer);
		}
		catch (WSRPException e) {
			producerConfigError = e;
			SessionMessages.add(request, _portletConfig.getPortletName()
					+ ".configError", e);
		}

		PortletMode mode = request.getPortletMode();
		if (mode.equals(PortletMode.VIEW)) {
			if (producerConfigError == null) {
				_renderRemote(request, response);
			}
			else {
				super.render(request, response);
			}
		}
		else {
			boolean remoteInvocation = ParamUtil.get(request,
					REMOTE_INVOCATION, false);

			if (remoteInvocation && producerConfigError == null) {
				_renderRemote(request, response);
			}
			else {
				super.render(request, response);
			}
		}
	}

	private Producer _createProducer(PortletPreferences preferences)
			throws WSRPException {

		String wsrpServiceUrl = preferences.getValue("wsrp-service-url",
				StringPool.BLANK);
		String markupEndpoint = preferences.getValue("markup-endpoint",
				StringPool.BLANK);
		String serviceDescriptionEndpoint = preferences.getValue(
				"service-description-endpoint", StringPool.BLANK);
		String registrationEndpoint = preferences.getValue(
				"registration-endpoint", StringPool.BLANK);
		String portletManagementEndpoint = preferences.getValue(
				"portlet-management-endpoint", StringPool.BLANK);

		markupEndpoint = wsrpServiceUrl + "/" + markupEndpoint;
		serviceDescriptionEndpoint = wsrpServiceUrl + "/"
				+ serviceDescriptionEndpoint;
		registrationEndpoint = wsrpServiceUrl + "/" + registrationEndpoint;
		portletManagementEndpoint = wsrpServiceUrl + "/"
				+ portletManagementEndpoint;

		RegistrationData regData = new RegistrationData();
		regData.setConsumerName("Liferay WSRP Agent");
		regData.setConsumerAgent("Liferay WSRP Agent");

		Producer producer = new ProducerImpl(PRODUCER_ID, markupEndpoint,
				serviceDescriptionEndpoint, registrationEndpoint,
				portletManagementEndpoint, regData);

		return producer;
	}

	public void _processActionRemote(ActionRequest request,
			ActionResponse actionResponse) throws PortletException {
		String MN = "processAction";
		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		try {
			// get the user on which request this call is being done
			User user = _getUser(request);
			String userID = null;
			if (user != null) {
				userID = user.getUserID();
			}

			_registerProducer(request.getPreferences(), request
					.getPortletSession());

			// get all information and objects which are needed to perform the
			// interaction
			Map preferences = _getPreferences(request);

			PortletKey portletKey = _getPortletKey(preferences);
			WSRPPortlet portlet = _getPortlet(portletKey, preferences);
			PortletWindowSession windowSession = _getWindowSession(userID,
					portlet, request);
			PortletDriver portletDriver = _consumerEnv
					.getPortletDriverRegistry().getPortletDriver(portlet);
			InteractionRequest actionRequest = new WSRPRequestImpl(
					windowSession, request);

			// do the actual call and check the response from the producer
			BlockingInteractionResponse response = null;
			try {
				response = portletDriver.performBlockingInteraction(
						actionRequest, userID);
				_checker.check(response);

			}
			catch (java.rmi.RemoteException wsrpFault) {
				WSRPXHelper.handleWSRPFault(_logger, wsrpFault);
			}

			// process the reponse
			if (response != null) {
				// the producer can either send a update response or a redirect
				UpdateResponse updateResponse = response.getUpdateResponse();
				String redirectURL = response.getRedirectURL();

				if (updateResponse != null) {
					// process the update response
					if (windowSession != null) {
						_updateSessionContext(updateResponse
								.getSessionContext(), windowSession
								.getPortletSession());
						windowSession.updateMarkupCache(updateResponse
								.getMarkupContext());
					}
					_updatePortletContext(request, updateResponse
							.getPortletContext(), portlet);

					// pass navState to next getMarkup by using the render
					// params
					String navState = updateResponse.getNavigationalState();
					if (navState != null) {
						actionResponse.setRenderParameter(NAVIGATIONAL_STATE,
								navState);
					}

					// if the remote portlet requested to change the portlet
					// mode
					// we try to solve this request.
					String newMode = updateResponse.getNewMode();
					if (newMode != null) {
						try {
							actionResponse.setPortletMode(WSRPUtil
									.fromWsrpMode(newMode));
						}
						catch (PortletModeException e) {
							// means portlet does not support this mode
							if (_logger.isLogging(Logger.INFO)) {
								_logger.text(Logger.INFO, MN, "The portlet='"
										+ portlet.getPortletKey()
												.getPortletHandle()
										+ "' does not support the mode="
										+ e.getMode());
							}
						}
					}

					// if the remote portlet requested to change the window
					// state
					// we try to solve this request. If the window state
					String newWindowState = updateResponse.getNewWindowState();
					if (newWindowState != null) {
						try {
							actionResponse.setWindowState(WSRPUtil
									.fromWsrpWindowState(newWindowState));
						}
						catch (WindowStateException e) {
							// means portlet does not support the window state
							if (_logger.isLogging(Logger.INFO)) {
								_logger
										.text(
												Logger.INFO,
												MN,
												"The portlet='"
														+ portlet
																.getPortletKey()
																.getPortletHandle()
														+ "' does not support the window state="
														+ e.getState());
							}
						}
					}
				}
				else if (redirectURL != null) {
					// if we got a redirect forward this redirect to the
					// container
					try {
						actionResponse.sendRedirect(redirectURL);
					}
					catch (IOException ioEx) {
						WSRPXHelper.throwX(_logger, Logger.ERROR,
								"processAction",
								ErrorCodes.COULD_NOT_FOLLOW_REDIRECT);
					}
				}
			}

		}
		catch (WSRPException e) {
			throw new PortletException(e);
		}
		finally {
			if (_logger.isLogging(Logger.TRACE_HIGH)) {
				_logger.exit(Logger.TRACE_HIGH, MN);
			}
		}
	}

	public void _renderRemote(RenderRequest request,
			RenderResponse renderResponse) throws PortletException, IOException {

		String MN = "render";
		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		try {
			// set content type in response
			renderResponse.setContentType(request.getResponseContentType());

			// get the user on which request this call is being done
			User user = _getUser(request);
			String userID = null;
			if (user != null) {
				userID = user.getUserID();
			}

			_registerProducer(request.getPreferences(), request
					.getPortletSession());

			// get all information and objects which are needed to perform the
			// interaction
			Map preferences = _getPreferences(request);

			PortletKey portletKey = _getPortletKey(preferences);
			WSRPPortlet portlet = _getPortlet(portletKey, preferences);
			PortletWindowSession windowSession = _getWindowSession(userID,
					portlet, request);
			PortletDriver portletDriver = _consumerEnv
					.getPortletDriverRegistry().getPortletDriver(portlet);
			MarkupRequest markupRequest = new WSRPRequestImpl(windowSession,
					request);

			// feed the url generator with the current response
			synchronized (_urlGenLock) {
				// update url generator
				URLGenerator urlGenerator = URLGeneratorImpl.getInstance(
						renderResponse, getPortletConfig());
				URLTemplateComposer templateComposer = _consumerEnv
						.getTemplateComposer();
				if (templateComposer != null) {
					templateComposer.setURLGenerator(urlGenerator);
				}

				_consumerEnv.getURLRewriter().setURLGenerator(urlGenerator);
			}

			// do a getMarkup call and check the response
			MarkupResponse response = null;
			try {
				response = portletDriver.getMarkup(markupRequest, userID);
				_checker.check(response);

			}
			catch (java.rmi.RemoteException wsrpFault) {
				WSRPXHelper.handleWSRPFault(_logger, wsrpFault);
			}

			// process the markup response
			if (response != null) {
				if (windowSession != null) {
					_updateSessionContext(response.getSessionContext(),
							windowSession.getPortletSession());
				}
				_processMarkupContext(response.getMarkupContext(), request,
						renderResponse);
			}

			// delete any cached markup
			if (windowSession != null) {
				windowSession.updateMarkupCache(null);
			}

		}
		catch (WSRPException e) {
			throw new PortletException("Error occured while retrieving markup",
					e);
		}
		finally {
			if (_logger.isLogging(Logger.TRACE_HIGH)) {
				_logger.exit(Logger.TRACE_HIGH, MN);
			}
		}
	}

	private String _processMarkupContext(MarkupContext markupContext,
			RenderRequest renderRequest, RenderResponse renderResponse)
			throws IOException, WSRPException {
		final String MN = "processMarkupContext";

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}
		String markup = null;

		if (markupContext != null && renderResponse != null) {
			// set prefered title if found
			String title = markupContext.getPreferredTitle();
			if (title != null) {
				renderResponse
						.setTitle(getTitle(renderRequest) + " - " + title);
			}

			markup = markupContext.getMarkupString();
			if (markup != null) {
				try {
					renderResponse.getWriter().write(markup);
				}
				catch (IOException e) {
					WSRPXHelper.throwX(0, e);
				}
			}

			// TODO: need to handle markup binary
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}

		return markup;
	}

	private PortletWindowSession _getWindowSession(String userID,
			WSRPPortlet portlet, PortletRequest request) throws WSRPException {
		PortletKey portletKey = portlet.getPortletKey();

		javax.portlet.PortletSession jsrPortletSession = request
				.getPortletSession();

		// to ensure that producer is added to the producer registry
		// throws exception which we pass
		_getProducer(portletKey.getProducerId());

		// now we can get our sessions
		UserSession userSession = null;
		synchronized (_sessionHdlrLock) {
			SessionHandler sessionHandler = (SessionHandler) _consumerEnv
					.getSessionHandler();
			sessionHandler.setPortletSession(jsrPortletSession);
			// get the user session
			userSession = sessionHandler.getUserSession(portletKey
					.getProducerId(), userID);
		}

		if (userSession != null) {
			// get the group session
			String groupID = _getPortletDescription(portlet).getGroupID();
			groupID = groupID == null ? "default" : groupID;

			GroupSession groupSession = userSession.getGroupSession(groupID);
			if (groupSession != null) {
				// get the portlet session
				String handle = _portletConfig.getPortletName();

				PortletSession portletSession = groupSession
						.getPortletSession(handle);

				int sessionScope = javax.portlet.PortletSession.PORTLET_SCOPE;
				boolean clearSessionCtx = GetterUtil.get(
						(String) jsrPortletSession.getAttribute(
								WebKeys.WSRP_NEW_SESSION, sessionScope), false);

				if (clearSessionCtx) {
					portletSession.setSessionContext(null);
					jsrPortletSession.setAttribute(WebKeys.WSRP_NEW_SESSION,
							"false");
				}

				if (portletSession != null) {
					// get the window session
					PortletWindowSession windowSession = portletSession
							.getPortletWindowSession(handle);

					return windowSession;
				}
				else {
					WSRPXHelper.throwX(ErrorCodes.PORTLET_SESSION_NOT_FOUND);
				}
			}
			else {
				WSRPXHelper.throwX(ErrorCodes.GROUP_SESSION_NOT_FOUND);
			}
		}
		else {
			WSRPXHelper.throwX(ErrorCodes.USER_SESSION_NOT_FOUND);
		}
		// we will never reach this
		return null;
	}

	private void _registerProducer(PortletPreferences preferences,
			javax.portlet.PortletSession portletSession) throws WSRPException {

		int sessionScope = javax.portlet.PortletSession.PORTLET_SCOPE;
		boolean regProducer = GetterUtil.get((String) portletSession
				.getAttribute(WebKeys.WSRP_REGISTER_PRODUCER, sessionScope),
				false);

		ProducerRegistry producerReg = _consumerEnv.getProducerRegistry();
		Producer producer = producerReg.getProducer(PRODUCER_ID);

		if (!regProducer && producer != null) {
			return;
		}

		producer = _createProducer(preferences);

		producerReg.addProducer(producer);

		portletSession.setAttribute(WebKeys.WSRP_REGISTER_PRODUCER, "false");

	}

	private void _updateSessionContext(SessionContext sessionContext,
			PortletSession portletSession) {

		if (portletSession != null && sessionContext != null) {
			portletSession.setSessionContext(sessionContext);
		}
	}

	private void _updatePortletContext(PortletRequest request,
			oasis.names.tc.wsrp.v1.types.PortletContext portletContext,
			WSRPPortlet portlet) throws WSRPException {

		if (portletContext != null && portlet != null) {

			String newPortletHandle = portletContext.getPortletHandle();
			PortletKey portletKey = portlet.getPortletKey();

			if (newPortletHandle != null
					&& !newPortletHandle.equals(portletKey.getPortletHandle())) {

				// seems like the producer made a clone
				String producerID = portletKey.getProducerId();
				PortletKey newPortletKey = new PortletKeyImpl(newPortletHandle,
						producerID);
				portlet = _createPortlet(newPortletKey, portlet.getParent());
				_consumerEnv.getPortletRegistry().addPortlet(portlet);

				// set new portlet key in portlet preferences
				PortletPreferences preferences = request.getPreferences();
				try {
					preferences.setValue("portlet-handle", newPortletHandle);
					preferences.setValue("parent-handle", portlet.getParent());
					preferences.store();
				}
				catch (Exception e) {
					// ups
					WSRPXHelper.throwX(0, e);
				}

			}

			portlet.setPortletContext(portletContext);
		}
	}

	private User _getUser(PortletRequest request) {

		User user = null;

		Principal userPrincipal = request.getUserPrincipal();
		if (userPrincipal != null) {
			String userKey = userPrincipal.getName();

			user = _consumerEnv.getUserRegistry().getUser(userKey);
			if (user == null) {
				user = new UserImpl(userKey);
				UserContext userContext = new UserContext();
				userContext.setProfile(_fillUserProfile(request));

				userContext.setUserContextKey(userKey);
				user.setUserContext(userContext);
				_consumerEnv.getUserRegistry().addUser(user);
			}
		}

		return user;
	}

	private UserProfile _fillUserProfile(PortletRequest request) {

		UserProfile userProfile = null;

		Map userInfo = (Map) request.getAttribute(PortletRequest.USER_INFO);
		if (userInfo != null) {
			userProfile = new UserProfile();

			PersonName personName = new PersonName();
			personName.setPrefix((String) userInfo.get("user.name.prefix"));
			personName.setGiven((String) userInfo.get("user.name.given"));
			personName.setFamily((String) userInfo.get("user.name.family"));
			personName.setMiddle((String) userInfo.get("user.name.middle"));
			personName.setSuffix((String) userInfo.get("user.name.suffix"));
			personName.setNickname((String) userInfo.get("user.name.nickName"));

			userProfile.setName(personName);
		}

		return userProfile;
	}

	private Map _getPreferences(PortletRequest request) {

		Map preferences = CollectionFactory.getSyncHashMap();
		Enumeration keys = request.getPreferences().getNames();

		while (keys.hasMoreElements()) {
			String key = (String) keys.nextElement();
			String value = request.getPreferences().getValue(key, null);

			preferences.put(key, value);
		}

		return preferences;
	}

	private PortletKey _getPortletKey(Map preferences) {
		PortletKey portletKey = null;

		String portletHandle = (String) preferences.get("portlet-handle");

		if (portletHandle != null) {
			String producerID = PRODUCER_ID;
			if (producerID != null) {
				portletKey = new PortletKeyImpl(portletHandle, producerID);
			}
		}

		return portletKey;
	}

	private WSRPPortlet _getPortlet(PortletKey portletKey, Map preferences)
			throws WSRPException {

		WSRPPortlet portlet = null;

		if (portletKey != null) {
			portlet = _consumerEnv.getPortletRegistry().getPortlet(portletKey);
			if (portlet == null) {
				// not yet in registry, create new one
				String parentHandle = GetterUtil.get((String) preferences
						.get("parent-handle"), (String) preferences
						.get("portlet-handle"));

				portlet = _createPortlet(portletKey, parentHandle);
				_consumerEnv.getPortletRegistry().addPortlet(portlet);
			}
		}

		return portlet;
	}

	private WSRPPortlet _createPortlet(PortletKey portletKey,
			String parentHandle) {

		WSRPPortlet portlet = new WSRPPortletImpl(portletKey);

		oasis.names.tc.wsrp.v1.types.PortletContext portletContext = new oasis.names.tc.wsrp.v1.types.PortletContext();
		portletContext.setPortletHandle(portletKey.getPortletHandle());
		portletContext.setPortletState(null);
		portletContext.setExtensions(null);
		portlet.setPortletContext(portletContext);

		if (parentHandle != null) {
			portlet.setParent(parentHandle);
		}
		else {
			// assume a POP -> parentHandle = portletHandle
			portlet.setParent(portletKey.getPortletHandle());
		}

		return portlet;
	}

	private PortletDescription _getPortletDescription(WSRPPortlet portlet)
			throws WSRPException {
		String producerID = portlet.getPortletKey().getProducerId();
		Producer producer = _getProducer(producerID);

		PortletDescription portletDesc = producer.getPortletDescription(portlet
				.getParent());
		if (portletDesc == null) {
			WSRPXHelper.throwX(ErrorCodes.PORTLET_DESC_NOT_FOUND);
		}

		return portletDesc;
	}

	private Producer _getProducer(String producerID) throws WSRPException {
		final String MN = "getProducer";

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.text(Logger.TRACE_HIGH, MN,
					"Trying to load producer with ID :" + producerID);
		}

		Producer producer = _consumerEnv.getProducerRegistry().getProducer(
				producerID);

		if (producer == null) {
			WSRPXHelper.throwX(_logger, Logger.ERROR, MN,
					ErrorCodes.PRODUCER_DOES_NOT_EXIST);
		}

		return producer;
	}

	// stores consumer specific information
	private static final ConsumerEnvironment _consumerEnv = new ConsumerEnvironmentImpl();

	// used to validate producer responses
	private static final ParameterChecker _checker = new ParameterChecker();

	// logger
	private static final Logger _logger = LogManager.getLogManager().getLogger(
			WSRPProxyPortlet.class);

	// lock object for thread synchronization while setting the urlgenerator
	private static final Object _urlGenLock = new Object();

	// lock object for thread synchronization while updating session handler
	private static final Object _sessionHdlrLock = new Object();

	private static final String PRODUCER_ID = "1";

	// used as keys in render params
	public static final String NAVIGATIONAL_STATE = "proxyportlet-updateResponse-navState";
	public static final String REMOTE_INVOCATION = "proxyportlet-remoteInvocation";

	private PortletConfig _portletConfig;

}