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

package com.liferay.portal.wsrp;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.PortletPreferencesServiceUtil;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.wsrp.util.WSRPUtil;
import com.liferay.portlet.ActionRequestFactory;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.CachePortlet;
import com.liferay.portlet.PortletConfigFactory;
import com.liferay.portlet.PortletInstanceFactory;
import com.liferay.portlet.RenderRequestFactory;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.RenderResponseImpl;
import com.liferay.util.CollectionFactory;

import java.io.IOException;

import java.util.List;
import java.util.Locale;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.WindowState;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;

import oasis.names.tc.wsrp.v1.types.BlockingInteractionResponse;
import oasis.names.tc.wsrp.v1.types.GetMarkup;
import oasis.names.tc.wsrp.v1.types.InteractionParams;
import oasis.names.tc.wsrp.v1.types.MarkupContext;
import oasis.names.tc.wsrp.v1.types.MarkupParams;
import oasis.names.tc.wsrp.v1.types.MarkupResponse;
import oasis.names.tc.wsrp.v1.types.NamedString;
import oasis.names.tc.wsrp.v1.types.PerformBlockingInteraction;
import oasis.names.tc.wsrp.v1.types.UpdateResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.producer.provider.PortletInvoker;
import org.apache.wsrp4j.producer.provider.Provider;
import org.apache.wsrp4j.producer.util.Base64;
import org.apache.wsrp4j.producer.util.ObjectDeserializer;
import org.apache.wsrp4j.producer.util.ObjectSerializer;
import org.apache.wsrp4j.util.LocaleHelper;

/**
 * <a href="PortletInvokerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @version $Revision: 1.38 $
 *
 */
public class PortletInvokerImpl implements PortletInvoker {

	public PortletInvokerImpl(Provider provider) {
		_provider = provider;
	}

	public MarkupResponse invokeGetMarkup(GetMarkup getMarkup)
			throws WSRPException {
		String portletHandle = getMarkup.getPortletContext().getPortletHandle();

		MarkupResponse markupResponse = new MarkupResponse();
		MarkupContext markupContext = new MarkupContext();
		markupResponse.setMarkupContext(markupContext);

		try {
			MarkupParams markupParams = getMarkup.getMarkupParams();

			// window state
			String wsrpWindowState = markupParams.getWindowState();
			WindowState windowState = WSRPUtil
					.fromWsrpWindowState(wsrpWindowState);

			// portlet mode
			String wsrpMode = markupParams.getMode();
			PortletMode mode = WSRPUtil.fromWsrpMode(wsrpMode);

			ServletContext ctx = WSRPUtil.getServletContext();
			String companyId = WSRPUtil.getCompanyId();

			ServletContext portalCtx = ctx.getContext(PropsUtil
					.get(PropsUtil.PORTAL_CTX));

			Portlet portlet = PortletServiceUtil.getPortletById(companyId,
					portletHandle);
			CachePortlet cachePortlet = PortletInstanceFactory.create(portlet,
					portalCtx);
			PortletConfig portletConfig = PortletConfigFactory.create(portlet,
					portalCtx);
			PortletContext portletCtx = portletConfig.getPortletContext();

			Locale reqLocale = LocaleHelper
					.getLocale(markupParams.getLocales()[0]);
			String reqMimeType = markupParams.getMimeTypes()[0];
			Map renderParameters = _getRenderParameters(markupParams);
			HttpServletRequest httpReq = new WSRPServletRequest(WSRPUtil
					.getHttpServletRequest(), reqLocale, reqMimeType,
					renderParameters);
			PortletPreferences portletPrefs = PortletPreferencesServiceUtil
					.getPreferences(companyId, PortalUtil
							.getPortletPreferencesPK(httpReq, portlet
									.getPortletId()));

			// this gets the default layout of the general guest
			User user = UserServiceUtil.getDefaultUser(companyId);
			Layout layout = _getDefaultUserLayout(user.getActualCompanyId());

			RenderRequestImpl renderRequest = RenderRequestFactory.create(httpReq,
					portlet, cachePortlet, portletCtx, windowState, mode,
					portletPrefs, layout.getLayoutId());
			WSRPServletResponse res = new WSRPServletResponse();

			RenderResponseImpl renderResponse = new WSRPRenderResponseImpl(
					getMarkup, _provider, (RenderRequestImpl) renderRequest,
					res, portlet.getPortletId(), companyId,
					layout.getLayoutId());
			renderResponse.setContentType("text/html");
			renderRequest.defineObjects(portletConfig, renderResponse);
			cachePortlet.render(renderRequest, renderResponse);
			markupContext.setMarkupString(res.getString());
			String contentType = renderResponse.getContentType();
			if (contentType == null) {
				contentType = Constants.TEXT_HTML;
			}
			markupContext.setMimeType(contentType);
			markupContext.setLocale(renderResponse.getLocale().getLanguage());
			markupContext.setPreferredTitle(renderResponse.getTitle());

			RenderRequestFactory.recycle(renderRequest);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return markupResponse;
	}

	public BlockingInteractionResponse invokePerformBlockingInteraction(
			PerformBlockingInteraction pbo) throws WSRPException {
		String portletHandle = pbo.getPortletContext().getPortletHandle();

		BlockingInteractionResponse bir = new BlockingInteractionResponse();
		UpdateResponse updateRes = new UpdateResponse();
		bir.setUpdateResponse(updateRes);

		try {
			MarkupParams markupParams = pbo.getMarkupParams();

			// window state
			String wsrpWindowState = markupParams.getWindowState();
			WindowState windowState = WSRPUtil
					.fromWsrpWindowState(wsrpWindowState);

			// portlet mode
			String wsrpMode = markupParams.getMode();
			PortletMode mode = WSRPUtil.fromWsrpMode(wsrpMode);

			ServletContext ctx = WSRPUtil.getServletContext();
			String companyId = WSRPUtil.getCompanyId();

			ServletContext portalCtx = ctx.getContext(PropsUtil
					.get(PropsUtil.PORTAL_CTX));

			Portlet portlet = PortletServiceUtil.getPortletById(companyId,
					portletHandle);
			CachePortlet cachePortlet = PortletInstanceFactory.create(portlet,
					portalCtx);
			PortletConfig portletConfig = PortletConfigFactory.create(portlet,
					portalCtx);
			PortletContext portletCtx = portletConfig.getPortletContext();

			Locale reqLocale = LocaleHelper
					.getLocale(markupParams.getLocales()[0]);
			String reqMimeType = markupParams.getMimeTypes()[0];
			InteractionParams interactionParams = pbo.getInteractionParams();
			Map actionParameters = _getActionParameters(interactionParams);
			HttpServletRequest httpReq = new WSRPServletRequest(WSRPUtil
					.getHttpServletRequest(), reqLocale, reqMimeType,
					actionParameters);
			PortletPreferences portletPrefs = PortletPreferencesServiceUtil
					.getPreferences(companyId, PortalUtil
							.getPortletPreferencesPK(httpReq, portlet
									.getPortletId()));

			// this gets the default layout of the general guest
			User user = UserServiceUtil.getDefaultUser(companyId);
			Layout layout = _getDefaultUserLayout(user.getActualCompanyId());

			ActionRequestImpl actionRequest = ActionRequestFactory.create(httpReq,
					portlet, cachePortlet, portletCtx, windowState, mode,
					portletPrefs, layout.getLayoutId());
			WSRPServletResponse res = new WSRPServletResponse();

			ActionResponseImpl actionResponse = new WSRPActionResponseImpl(pbo,
					_provider, actionRequest, res, portlet.getPortletId(),
					user, layout, windowState, mode);

			cachePortlet.processAction(actionRequest, actionResponse);
			String newNavState = null;

			Map renderParams = _getRenderParameters(httpReq, actionResponse);
			newNavState = Base64.encode(ObjectSerializer.serialize(renderParams));

			updateRes.setNavigationalState(newNavState);

			ActionRequestFactory.recycle(actionRequest);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return bir;
	}

	private Map _getActionParameters(InteractionParams interactionParams) {
		Map actionParams = _getParameters(interactionParams
				.getInteractionState());

		Map formParams = _getFormParameters(interactionParams
				.getFormParameters());

		actionParams.putAll(formParams);

		return actionParams;
	}

	private Layout _getDefaultUserLayout(String actualCompanyId)
		throws PortalException, SystemException {

		Group generalGuestGroup =
			GroupLocalServiceUtil.getGroupByName(
				actualCompanyId, Group.GENERAL_GUEST);

		List layoutsList = GroupLocalServiceUtil.getLayouts(
			generalGuestGroup.getGroupId(),
			Layout.DEFAULT_PARENT_LAYOUT_ID);

		return (Layout)layoutsList.get(0);
	}

	private static Map _getFormParameters(NamedString[] params) {
		Map formParameters = CollectionFactory.getSyncHashMap();

		if (params != null) {
			for (int i = 0; i < params.length; i++) {
				String parameterName = params[i].getName();

				if (formParameters.containsKey(parameterName)) {
					// Handle case in which parameter name has multiple values
					String[] currentValues = (String[]) formParameters
							.get(parameterName);
					String[] newValues = new String[currentValues.length + 1];
					System.arraycopy(currentValues, 0, newValues, 0,
							currentValues.length);
					newValues[currentValues.length] = params[i].getValue();
					formParameters.put(parameterName, newValues);
				}
				else {
					String[] values = { params[i].getValue() };
					formParameters.put(parameterName, values);
				}
			}
		}

		return formParameters;
	}

	private Map _getParameters(String paramString) {
		Map navParams = CollectionFactory.getSyncHashMap();

		if (paramString != null) {
			byte[] desMap = Base64.decode(paramString);

			Map naviState = null;

			try {
				naviState = ObjectDeserializer.deserializeMap(desMap);
			}
			catch (IOException iox) {
			}
			catch (ClassNotFoundException classNotFoundEx) {
			}

			if (naviState != null) {
				navParams.putAll(naviState);
			}
		}

		return navParams;
	}

	private Map _getRenderParameters(MarkupParams markupParams) {
		return _getParameters(markupParams.getNavigationalState());
	}

	private Map _getRenderParameters(HttpServletRequest req, ActionResponseImpl res) {
		Map params = CollectionFactory.getHashMap();
		params.putAll(res.getRenderParameters());

		String[] layoutId = req.getParameterValues("p_l_id");
		params.put("p_l_id", layoutId);

		String[] portletName = req.getParameterValues("p_p_id");
		params.put("p_p_id", portletName);

		String[] action = {"0"};
		params.put("p_p_action", action);

		String[] windowState = req.getParameterValues("p_p_state");
		params.put("p_p_state", windowState.toString());

		String[] portletMode = req.getParameterValues("p_p_mode");
		params.put("p_p_mode", portletMode);

		return params;
	}

	private Provider _provider;

	private static final Log _log = LogFactory.getLog(PortletInvokerImpl.class);

}