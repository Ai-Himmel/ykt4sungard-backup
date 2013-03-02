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

package com.liferay.portal.action;

import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.service.spring.PortletPreferencesServiceUtil;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestFactory;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseFactory;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.CachePortlet;
import com.liferay.portlet.LiferayWindowState;
import com.liferay.portlet.PortletConfigFactory;
import com.liferay.portlet.PortletInstanceFactory;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.portlet.RenderParametersPool;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

/**
 * <a href="LayoutAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.30 $
 *
 */
public class LayoutAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		String layoutId = ParamUtil.getString(req, "p_l_id");
		String action = ParamUtil.getString(req, "p_p_action");

		if (Validator.isNotNull(layoutId)) {
			try {
				if (action.equals("1")) {
					_processActionRequest(req, res);

					ActionResponseImpl actionResponseImpl =
						(ActionResponseImpl)req.getAttribute(
							WebKeys.JAVAX_PORTLET_RESPONSE);

					String redirectLocation =
						actionResponseImpl.getRedirectLocation();

					if (Validator.isNotNull(redirectLocation)) {
						res.sendRedirect(redirectLocation);

						return null;
					}

					String windowState = req.getParameter("p_p_state");

					if (LiferayWindowState.EXCLUSIVE.toString().equals(
							windowState)) {

						return null;
					}
				}
				else if (action.equals("0")) {
					_processRenderRequest(req, res);
				}

				Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

				if (layout != null) {
					_updateLayout(req, res, layout);
				}

				return mapping.findForward("portal.layout");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
			finally {
				try {
					if (action.equals("1")) {
						ActionRequestImpl actionRequestImpl =
							(ActionRequestImpl)req.getAttribute(
								WebKeys.JAVAX_PORTLET_REQUEST);

						ActionRequestFactory.recycle(actionRequestImpl);
					}
				}
				catch (Exception e) {
					_log.error(e.getMessage());
				}

				try {
					if (action.equals("1")) {
						ActionResponseImpl actionResponseImpl =
							(ActionResponseImpl)req.getAttribute(
								WebKeys.JAVAX_PORTLET_RESPONSE);

						ActionResponseFactory.recycle(actionResponseImpl);
					}
				}
				catch (Exception e) {
					_log.error(e.getMessage());
				}
			}
		}
		else {
			try {
				_forwardLayout(req);

				return mapping.findForward(Constants.COMMON_FORWARD);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
	}

	private void _forwardLayout(HttpServletRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);
		String layoutId = Layout.DEFAULT_LAYOUT_ID;
		String layoutFriendlyURL = null;

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		if (layout != null) {
			layoutId = layout.getLayoutId();
			layoutFriendlyURL =
				PortalUtil.getLayoutFriendlyURL(layout, themeDisplay);
		}

		String forwardURL = layoutFriendlyURL;

		if (Validator.isNull(forwardURL)) {
			forwardURL =
				themeDisplay.getPathMain() + "/portal/layout?p_l_id=" +
					layoutId;
		}

		req.setAttribute(WebKeys.FORWARD_URL, forwardURL);
	}

	private void _processPortletRequest(
			HttpServletRequest req, HttpServletResponse res, boolean action)
		throws Exception {

		HttpSession ses = req.getSession();

		String companyId = PortalUtil.getCompanyId(req);
		User user = PortalUtil.getUser(req);
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);
		String portletId = ParamUtil.getString(req, "p_p_id");

		Portlet portlet =
			PortletServiceUtil.getPortletById(companyId, portletId);

		ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

		CachePortlet cachePortlet = PortletInstanceFactory.create(portlet, ctx);

		if (user != null) {
			CachePortlet.clearResponse(ses, layout.getPrimaryKey(), portletId);
		}

		PortletPreferences portletPrefs =
			PortletPreferencesServiceUtil.getPreferences(
				companyId, PortalUtil.getPortletPreferencesPK(req, portletId));

		PortletConfig portletConfig = PortletConfigFactory.create(portlet, ctx);
		PortletContext portletCtx = portletConfig.getPortletContext();

		WindowState windowState = new WindowState(
			ParamUtil.getString(req, "p_p_state"));

		PortletMode portletMode = new PortletMode(
			ParamUtil.getString(req, "p_p_mode"));

		if (action) {
			ActionRequestImpl actionRequestImpl = ActionRequestFactory.create(
				req, portlet, cachePortlet, portletCtx, windowState,
				portletMode, portletPrefs, layout.getLayoutId());

			ActionResponseImpl actionResponseImpl =
				ActionResponseFactory.create(
					actionRequestImpl, res, portletId, user, layout,
					windowState, portletMode);

			actionRequestImpl.defineObjects(portletConfig, actionResponseImpl);

			cachePortlet.processAction(actionRequestImpl, actionResponseImpl);

			RenderParametersPool.put(
				req, layout.getLayoutId(), portletId,
				actionResponseImpl.getRenderParameters());
		}
		else {
			PortalUtil.updateWindowState(portletId, user, layout, windowState);

			PortalUtil.updatePortletMode(portletId, user, layout, portletMode);
		}
	}

	private void _processActionRequest(
			HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		_processPortletRequest(req, res, true);
	}

	private void _processRenderRequest(
			HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		_processPortletRequest(req, res, false);
	}

	private void _updateLayout(HttpServletRequest req, HttpServletResponse res, Layout layout)
		throws Exception {

		HttpSession ses = req.getSession();

		LayoutTypePortlet layoutType =
			(LayoutTypePortlet)layout.getLayoutType();

		// Make sure portlets show up in the correct columns

		boolean updateLayout = false;

		if (layoutType.getNumOfColumns() > 1) {
			Portlet[] narrow1Portlets = layoutType.getNarrow1Portlets();

			for (int i = 0; i < narrow1Portlets.length; i++) {
				if (!narrow1Portlets[i].isNarrow()) {
					layoutType.removePortletId(
						narrow1Portlets[i].getPortletId());
					layoutType.addPortletId(narrow1Portlets[i].getPortletId());

					updateLayout = true;
				}
			}

			Portlet[] narrow2Portlets = layoutType.getNarrow2Portlets();

			for (int i = 0; i < narrow2Portlets.length; i++) {
				if (!narrow2Portlets[i].isNarrow()) {
					layoutType.removePortletId(
						narrow2Portlets[i].getPortletId());
					layoutType.addPortletId(narrow2Portlets[i].getPortletId());

					updateLayout = true;
				}
			}

			Portlet[] wide1Portlets = layoutType.getWide1Portlets();

			for (int i = 0; i < wide1Portlets.length; i++) {
				if (wide1Portlets[i].isNarrow()) {
					layoutType.removePortletId(wide1Portlets[i].getPortletId());
					layoutType.addPortletId(wide1Portlets[i].getPortletId());

					updateLayout = true;
				}
			}
		}
		
		
		// See action path /my_account/edit_profile
		if (layoutType.hasStateMax()) {
			String maxPortletId = StringUtil.split(layoutType.getStateMax())[0];
			String selPortletId = ParamUtil.getString(req, "p_p_id");

			if ((!selPortletId.equals(maxPortletId))) {
				//(!layoutType.hasPortletId(maxPortletId))) {

				layoutType.setStateMax(StringPool.BLANK);
				layoutType.removeModesPortletId(maxPortletId);

				updateLayout = true;
				//for multiple layout
				if (layoutType.getPortlets().length > 1) {
					String requestState = ParamUtil.get(req, "p_p_state", "");
					if (requestState.equals("")) {
						PortletURL redirectURL = new PortletURLImpl(req, maxPortletId, layout.getLayoutId(), true);
						if (layoutType.getPortlets().length > 1) {
							redirectURL.setWindowState(WindowState.NORMAL);
						} else {
							redirectURL.setWindowState(WindowState.MAXIMIZED);
						}
						redirectURL.setPortletMode(PortletMode.VIEW);
						res.sendRedirect(redirectURL.toString());
					}
				}
			} else {
				
				String requestState = ParamUtil.get(req, "p_p_state", "");
				if (requestState.equals("")) {
					PortletURL redirectURL = new PortletURLImpl(req, maxPortletId, layout.getLayoutId(), true);
					if (layoutType.getPortlets().length > 1) {
						redirectURL.setWindowState(WindowState.NORMAL);
					} else {
						redirectURL.setWindowState(WindowState.MAXIMIZED);
					}
					redirectURL.setPortletMode(PortletMode.VIEW);
					res.sendRedirect(redirectURL.toString());
				}
			    /*
			     * End
			     */
			}
		}
		
		if (updateLayout) {
			CachePortlet.clearResponses(ses);

			// Update layout without checking for permissions

			LayoutLocalServiceUtil.updateLayout(
				layout.getPrimaryKey(), layout.getTypeSettings());
		}
	}

	private static final Log _log = LogFactory.getLog(LayoutAction.class);

}