/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portlet.layoutconfiguration.util;

import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.MethodInvoker;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.theme.PortletDisplay;
import com.liferay.portal.theme.PortletDisplayFactory;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portal.velocity.VelocityVariables;
import com.liferay.portlet.layoutconfiguration.util.velocity.TemplateProcessor;
import com.liferay.portlet.layoutconfiguration.util.xml.RuntimeLogic;

import java.io.StringWriter;

import java.util.Iterator;
import java.util.Map;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.Velocity;

/**
 * <a href="RuntimePortletUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class RuntimePortletUtil {

	public static void processPortlet(
			StringMaker sm, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res, RenderRequest renderRequest,
			RenderResponse renderResponse, String portletId, String queryString)
		throws Exception {

		processPortlet(
			sm, ctx, req, res, renderRequest, renderResponse, portletId,
			queryString, null, null, null);
	}

	public static void processPortlet(
			StringMaker sm, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res, RenderRequest renderRequest,
			RenderResponse renderResponse, String portletId, String queryString,
			String columnId, Integer columnPos, Integer columnCount)
		throws Exception {

		processPortlet(
			sm, ctx, req, res, renderRequest, renderResponse, null, portletId,
			queryString, columnId, columnPos, columnCount, null);
	}

	public static void processPortlet(
			StringMaker sm, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res, Portlet portlet, String queryString,
			String columnId, Integer columnPos, Integer columnCount,
			String path)
		throws Exception {

		processPortlet(
			sm, ctx, req, res, null, null, portlet, portlet.getPortletId(),
			queryString, columnId, columnPos, columnCount, path);
	}

	public static void processPortlet(
			StringMaker sm, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res, RenderRequest renderRequest,
			RenderResponse renderResponse, Portlet portlet, String portletId,
			String queryString, String columnId, Integer columnPos,
			Integer columnCount, String path)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		if (portlet == null) {
			portlet = PortletLocalServiceUtil.getPortletById(
				themeDisplay.getCompanyId(), portletId);
		}

		if ((portlet != null) && portlet.isInstanceable()) {
			String instanceId = portlet.getInstanceId();

			if (Validator.isNotNull(instanceId) &&
				Validator.isPassword(instanceId) &&
				(instanceId.length() == 4)) {

				/*portletId +=
					PortletImpl.INSTANCE_SEPARATOR + instanceId;

				portlet = PortletLocalServiceUtil.getPortletById(
					themeDisplay.getCompanyId(), portletId);*/
			}
			else {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Portlet " + portlet.getPortletId() +
							" is instanceable but does not have a " +
								"valid instance id");
				}

				portlet = null;
			}
		}

		if (portlet == null) {
			return;
		}

		// Capture the current portlet's settings to reset them once the child
		// portlet is rendered

		PortletDisplay portletDisplay = themeDisplay.getPortletDisplay();

		PortletDisplay portletDisplayClone = PortletDisplayFactory.create();

		portletDisplay.copyTo(portletDisplayClone);

		PortletConfig portletConfig = (PortletConfig)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		try {
			PortalUtil.renderPortlet(
				sm, ctx, req, res, portlet, queryString, columnId, columnPos,
				columnCount, path);
		}
		finally {
			portletDisplay.copyFrom(portletDisplayClone);

			try {
				PortletDisplayFactory.recycle(portletDisplayClone);
			}
			catch (Exception e) {
				_log.error(e);
			}

			_defineObjects(
				req, portletConfig, renderRequest, renderResponse);
		}
	}

	public static String processTemplate(
			ServletContext ctx, HttpServletRequest req, HttpServletResponse res,
			PageContext pageContext, String content)
		throws Exception {

		return processTemplate(ctx, req, res, pageContext, null, content);
	}

	public static String processTemplate(
			ServletContext ctx, HttpServletRequest req, HttpServletResponse res,
			PageContext pageContext, String portletId, String content)
		throws Exception {

		if (Validator.isNull(content)) {
			return StringPool.BLANK;
		}

		TemplateProcessor processor =
			new TemplateProcessor(ctx, req, res, portletId);

		VelocityContext vc = new VelocityContext();

		vc.put("processor", processor);

		// Velocity variables

		VelocityVariables.insertVariables(vc, req);

		// liferay:include tag library

		StringServletResponse stringServletResponse =
			new StringServletResponse(res);

		MethodWrapper methodWrapper = new MethodWrapper(
			"com.liferay.taglib.util.VelocityTaglib", "init",
			new Object[] {ctx, req, stringServletResponse, pageContext});

		Object velocityTaglib = MethodInvoker.invoke(methodWrapper);

		vc.put("taglibLiferay", velocityTaglib);
		vc.put("theme", velocityTaglib);

		StringWriter sw = new StringWriter();

		try {
			Velocity.evaluate(
				vc, sw, RuntimePortletUtil.class.getName(), content);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw e;
		}

		String output = sw.toString();

		Map columnsMap = processor.getColumnsMap();

		Iterator itr = columnsMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			String value = (String)entry.getValue();

			output = StringUtil.replace(output, key, value);
		}

		Map portletsMap = processor.getPortletsMap();

		itr = portletsMap.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			Portlet portlet = (Portlet)entry.getKey();
			Object[] value = (Object[])entry.getValue();

			String queryString = (String)value[0];
			String columnId = (String)value[1];
			Integer columnPos = (Integer)value[2];
			Integer columnCount = (Integer)value[3];

			StringMaker sm = new StringMaker();

			processPortlet(
				sm, ctx, req, res, portlet, queryString, columnId, columnPos,
				columnCount, null);

			output = StringUtil.replace(
				output, "[$TEMPLATE_PORTLET_" + portlet.getPortletId() + "$]",
				sm.toString());
		}

		return output;
	}

	public static String processXML(
			HttpServletRequest req, String content, RuntimeLogic runtimeLogic)
		throws Exception {

		if (Validator.isNull(content)) {
			return StringPool.BLANK;
		}

		try {
			req.setAttribute(WebKeys.RENDER_PORTLET_RESOURCE, Boolean.TRUE);

			StringMaker sm = new StringMaker();

			int x = 0;
			int y = content.indexOf(runtimeLogic.getOpenTag());

			while (y != -1) {
				sm.append(content.substring(x, y));

				int close1 = content.indexOf(runtimeLogic.getClose1Tag(), y);
				int close2 = content.indexOf(runtimeLogic.getClose2Tag(), y);

				if ((close2 == -1) || ((close1 != -1) && (close1 < close2))) {
					x = close1 + runtimeLogic.getClose1Tag().length();
				}
				else {
					x = close2 + runtimeLogic.getClose2Tag().length();
				}

				runtimeLogic.processXML(sm, content.substring(y, x));

				y = content.indexOf(runtimeLogic.getOpenTag(), x);
			}

			if (y == -1) {
				sm.append(content.substring(x, content.length()));
			}

			return sm.toString();
		}
		finally {
			req.removeAttribute(WebKeys.RENDER_PORTLET_RESOURCE);
		}
	}

	private static void _defineObjects(
		HttpServletRequest req, PortletConfig portletConfig,
		RenderRequest renderRequest, RenderResponse renderResponse) {

		if (portletConfig != null) {
			req.setAttribute(JavaConstants.JAVAX_PORTLET_CONFIG, portletConfig);
		}

		if (renderRequest != null) {
			req.setAttribute(
				JavaConstants.JAVAX_PORTLET_REQUEST, renderRequest);
		}

		if (renderResponse != null) {
			req.setAttribute(
				JavaConstants.JAVAX_PORTLET_RESPONSE, renderResponse);
		}
	}

	private static Log _log = LogFactory.getLog(RuntimePortletUtil.class);

}