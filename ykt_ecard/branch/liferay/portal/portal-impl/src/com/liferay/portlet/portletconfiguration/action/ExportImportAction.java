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

package com.liferay.portlet.portletconfiguration.action;

import com.liferay.portal.LayoutImportException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.kernel.lar.UserIdStrategy;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.LayoutServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.util.servlet.ServletResponseUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.ByteArrayInputStream;
import java.io.File;

import java.util.HashMap;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="ExportImportAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class ExportImportAction extends EditConfigurationAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		Portlet portlet = null;

		try {
			portlet = getPortlet(req);
		}
		catch (PrincipalException pe) {
			SessionErrors.add(req, PrincipalException.class.getName());

			setForward(req, "portlet.portlet_configuration.error");
		}

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals("copy_from_live")) {
				copyFromLive(req, portlet);

				sendRedirect(req, res);
			}
			else if (cmd.equals("export")) {
				exportData(req, res, portlet);
			}
			else if (cmd.equals("import")) {
				importData(req, portlet);

				sendRedirect(req, res);
			}
			else if (cmd.equals("publish_to_live")) {
				publishToLive(req, portlet);

				sendRedirect(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchLayoutException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.portlet_configuration.error");
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		Portlet portlet = null;

		try {
			portlet = getPortlet(req);
		}
		catch (PrincipalException pe) {
			SessionErrors.add(req, PrincipalException.class.getName());

			return mapping.findForward("portlet.portlet_configuration.error");
		}

		res.setTitle(getTitle(portlet, req));

		return mapping.findForward(getForward(
			req, "portlet.portlet_configuration.export_import"));
	}

	protected void copyFromLive(ActionRequest req, Portlet portlet)
		throws Exception {

		long plid = ParamUtil.getLong(req, "plid");

		Layout targetLayout = LayoutLocalServiceUtil.getLayout(plid);

		Group stagingGroup = targetLayout.getGroup();
		Group liveGroup = stagingGroup.getLiveGroup();

		Layout sourceLayout = LayoutLocalServiceUtil.getLayout(
			liveGroup.getGroupId(), targetLayout.isPrivateLayout(),
			targetLayout.getLayoutId());

		copyPortletInfo(
			sourceLayout.getPlid(), targetLayout.getPlid(),
			portlet.getPortletId(), req.getParameterMap());
	}

	protected void copyPortletInfo(
			long sourcePlid, long targetPlid, String portletId, Map parameters)
		throws Exception {

		Map parameterMap = getStagingParameters(parameters);

		byte[] data = LayoutLocalServiceUtil.exportPortletInfo(
			sourcePlid, portletId, parameterMap);

		ByteArrayInputStream bais = new ByteArrayInputStream(data);

		LayoutServiceUtil.importPortletInfo(
			targetPlid, portletId, parameterMap, bais);
	}

	private void exportData(
			ActionRequest req, ActionResponse res, Portlet portlet)
		throws Exception {

		try {
			long plid = ParamUtil.getLong(req, "plid");
			String fileName = ParamUtil.getString(req, "exportFileName");

			byte[] byteArray = LayoutServiceUtil.exportPortletInfo(
				plid, portlet.getPortletId(), req.getParameterMap());

			HttpServletResponse httpRes =
				((ActionResponseImpl)res).getHttpServletResponse();

			ServletResponseUtil.sendFile(httpRes, fileName, byteArray);

			setForward(req, ActionConstants.COMMON_NULL);
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	protected static Map getStagingParameters(Map parameters) {
		Map parameterMap = new HashMap();

		parameterMap.putAll(parameters);

		parameterMap.put(
			PortletDataHandlerKeys.PORTLET_DATA_ALL, Boolean.TRUE.toString());
		parameterMap.put(
			PortletDataHandlerKeys.THEME, Boolean.FALSE.toString());
		parameterMap.put(
			PortletDataHandlerKeys.DELETE_MISSING_LAYOUTS,
			Boolean.TRUE.toString());
		parameterMap.put(
			PortletDataHandlerKeys.DATA_STRATEGY,
			PortletDataHandlerKeys.DATA_STRATEGY_MIRROR);
		parameterMap.put(
			PortletDataHandlerKeys.USER_ID_STRATEGY,
			UserIdStrategy.CURRENT_USER_ID);

		return parameterMap;
	}

	private void importData(ActionRequest req, Portlet portlet)
		throws Exception {

		try {
			UploadPortletRequest uploadReq =
				PortalUtil.getUploadPortletRequest(req);

			long plid = ParamUtil.getLong(uploadReq, "plid");
			File file = uploadReq.getFile("importFileName");

			LayoutServiceUtil.importPortletInfo(
				plid, portlet.getPortletId(), req.getParameterMap(), file);

			SessionMessages.add(req, "request_processed");
		}
		catch (Exception e) {
			_log.error(e, e);

			SessionErrors.add(req, LayoutImportException.class.getName());
		}
	}

	protected void publishToLive(ActionRequest req, Portlet portlet)
		throws Exception {

		long plid = ParamUtil.getLong(req, "plid");

		Layout sourceLayout = LayoutLocalServiceUtil.getLayout(plid);

		Group stagingGroup = sourceLayout.getGroup();
		Group liveGroup = stagingGroup.getLiveGroup();

		Layout targetLayout = LayoutLocalServiceUtil.getLayout(
			liveGroup.getGroupId(), sourceLayout.isPrivateLayout(),
			sourceLayout.getLayoutId());

		copyPortletInfo(
			sourceLayout.getPlid(), targetLayout.getPlid(),
			portlet.getPortletId(), req.getParameterMap());
	}

	private static Log _log = LogFactory.getLog(ExportImportAction.class);

}