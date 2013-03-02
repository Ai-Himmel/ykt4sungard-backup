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

import com.liferay.portal.LayoutFriendlyURLException;
import com.liferay.portal.LayoutNameException;
import com.liferay.portal.LayoutTypeException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.RequiredLayoutException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.form.LayoutForm;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.persistence.PortletPreferencesPK;
import com.liferay.portal.service.spring.GroupServiceUtil;
import com.liferay.portal.service.spring.LayoutServiceUtil;
import com.liferay.portal.service.spring.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.LayoutClonePool;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.CachePortlet;
import com.liferay.portlet.PortletPreferencesImpl;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="PersonalizeAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Javier Bermejo
 * @version $Revision: 1.24 $
 *
 */
public class PersonalizeAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		LayoutForm layoutForm = (LayoutForm)form;

		if (!User.isLayoutsRequired(req.getRemoteUser())) {
			SessionErrors.add(req, PrincipalException.class.getName());

			return mapping.findForward("portal.error");
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) && (cmd.equals(Constants.ADD))) {
			try {
				_addLayout(req);

				return mapping.findForward(Constants.COMMON_REFERER);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof LayoutNameException ||
					e instanceof LayoutTypeException) {

					SessionErrors.add(req, e.getClass().getName());

					return mapping.findForward("portal.personalize");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals(Constants.DELETE))) {
			try {
				_deleteLayout(req);

				return mapping.findForward(Constants.COMMON_REFERER);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		else if ((cmd != null) && (cmd.equals(Constants.UPDATE))) {
			try {
				_updateLayout(req, layoutForm);

				return mapping.findForward(Constants.COMMON_REFERER);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof LayoutFriendlyURLException ||
					e instanceof LayoutNameException) {

					SessionErrors.add(req, e.getClass().getName(), e);

					_getLayout(req, layoutForm);

					return mapping.findForward("portal.personalize");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals("update_display_order"))) {
			try {
				_updateDisplayOrder(req);

				return mapping.findForward(Constants.COMMON_REFERER);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof RequiredLayoutException) {

					SessionErrors.add(req, e.getClass().getName());

					_getLayout(req, layoutForm);

					return mapping.findForward("portal.personalize");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(Constants.COMMON_ERROR);
				}
			}
		}
		else {
			try {
				_getLayout(req, layoutForm);

				return mapping.findForward("portal.personalize");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
	}

	private void _addLayout(HttpServletRequest req) throws Exception {
		String parentLayoutId = ParamUtil.getString(req, "p_sel_l_id");
		String name = ParamUtil.getString(req, "p_l_name");
		String type = ParamUtil.getString(req, "p_l_type");

		Group group = (Group)req.getAttribute(WebKeys.GROUP);

		if (group == null) {
			LayoutServiceUtil.addUserLayout(parentLayoutId, name, type);
		}
		else {
			LayoutServiceUtil.addGroupLayout(
				group.getGroupId(), parentLayoutId, name, type);
		}
	}

	private void _copyPreferences(
			HttpServletRequest req, String selLayoutId, String copyLayoutId,
			LayoutTypePortlet copyLayoutType)
		throws Exception {

		String companyId = PortalUtil.getCompanyId(req);

		String[] copyPortletIds = copyLayoutType.getPortletIds();

		for (int i = 0; i < copyPortletIds.length; i++) {
			String copyPortletId = copyPortletIds[i];

			// Get preference to copy to so that we are sure it exists in the
			// database

			PortletPreferencesPK portletPrefsPK =
				PortalUtil.getPortletPreferencesPK(
					req, copyPortletId, selLayoutId);

			PortletPreferencesLocalServiceUtil.getPreferences(
				companyId, portletPrefsPK);

			// Get preference to copy from

			PortletPreferencesPK copyPortletPrefsPK =
				PortalUtil.getPortletPreferencesPK(
					req, copyPortletId, copyLayoutId);

			PortletPreferencesImpl copyPortletPrefsImpl =
				(PortletPreferencesImpl)
					PortletPreferencesLocalServiceUtil.getPreferences(
						companyId, copyPortletPrefsPK);

			// Copy preference

			PortletPreferencesLocalServiceUtil.updatePreferences(
				portletPrefsPK, copyPortletPrefsImpl);
		}
	}

	private void _deleteLayout(HttpServletRequest req) throws Exception {
		String layoutId = ParamUtil.getString(req, "p_sel_l_id");

		Group group = (Group)req.getAttribute(WebKeys.GROUP);

		if (group == null) {
			LayoutServiceUtil.deleteLayout(new LayoutPK(
				layoutId, req.getRemoteUser()));
		}
		else {
			LayoutServiceUtil.deleteLayout(new LayoutPK(
				layoutId, Layout.GROUP + group.getGroupId()));
		}
	}

	private void _getLayout(HttpServletRequest req, LayoutForm layoutForm)
		throws Exception {

		String columnOrder = req.getParameter("p_l_column_order");
		String narrow1 = req.getParameter("p_l_narrow_1_list");
		String narrow2 = req.getParameter("p_l_narrow_2_list");
		String wide1 = req.getParameter("p_l_wide_1_list");

		Group group = (Group)req.getAttribute(WebKeys.GROUP);

		Layout layout = _getSelLayout(req, group);

		if (layout == null) {
			return;
		}

		layoutForm.setTypeSettingsProperties(
			layout.getTypeSettingsProperties());

		LayoutTypePortlet layoutType =
			(LayoutTypePortlet)layout.getLayoutType();

		if (Validator.isNull(columnOrder)) {
			columnOrder = layoutType.getColumnOrder();
		}

		String[] columnOrderArray = StringUtil.split(columnOrder);

		Portlet[] narrow1Portlets = null;
		Portlet[] narrow2Portlets = null;
		Portlet[] wide1Portlets = null;

		if (((narrow1 != null) && (!narrow1.equals("null"))) ||
			((narrow2 != null) && (!narrow2.equals("null"))) ||
			((wide1 != null) && (!wide1.equals("null")))) {

			String companyId = PortalUtil.getCompanyId(req);

			List narrow1PortletsList = new ArrayList();

			String[] narrow1PortletIds = StringUtil.split(narrow1);

			for (int i = 0; i < narrow1PortletIds.length; i++) {
				Portlet portlet = PortletServiceUtil.getPortletById(
					companyId, narrow1PortletIds[i]);

				narrow1PortletsList.add(portlet);
			}

			List narrow2PortletsList = new ArrayList();

			String[] narrow2PortletIds = StringUtil.split(narrow2);

			for (int i = 0; i < narrow2PortletIds.length; i++) {
				Portlet portlet = PortletServiceUtil.getPortletById(
					companyId, narrow2PortletIds[i]);

				narrow2PortletsList.add(portlet);
			}

			List wide1PortletsList = new ArrayList();

			String[] wide1PortletIds = StringUtil.split(wide1);

			for (int i = 0; i < wide1PortletIds.length; i++) {
				Portlet portlet = PortletServiceUtil.getPortletById(
					companyId, wide1PortletIds[i]);

				// If you're moving from a single column layout to a
				// multiple column layout, the given wide portlets may have
				// narrow portlets in them and will need to be moved to the
				// narrow column

				if (columnOrderArray.length > 1) {
					if (portlet.isNarrow()) {
						narrow1PortletsList.add(portlet);
					}
					else {
						wide1PortletsList.add(portlet);
					}
				}
				else {
					wide1PortletsList.add(portlet);
				}
			}

			narrow1Portlets =
				(Portlet[])narrow1PortletsList.toArray(new Portlet[0]);
			narrow2Portlets =
				(Portlet[])narrow2PortletsList.toArray(new Portlet[0]);
			wide1Portlets =
				(Portlet[])wide1PortletsList.toArray(new Portlet[0]);
		}
		else {
			narrow1Portlets = layoutType.getNarrow1Portlets();
			narrow2Portlets = layoutType.getNarrow2Portlets();
			wide1Portlets = layoutType.getWide1Portlets();
		}

		req.setAttribute(WebKeys.SEL_LAYOUT, layout);
		req.setAttribute(WebKeys.LAYOUT_COLUMN_ORDER, columnOrder);
		req.setAttribute(WebKeys.LAYOUT_NARROW_1_PORTLETS, narrow1Portlets);
		req.setAttribute(WebKeys.LAYOUT_NARROW_2_PORTLETS, narrow2Portlets);
		req.setAttribute(WebKeys.LAYOUT_WIDE_1_PORTLETS, wide1Portlets);
	}

	private Layout _getSelLayout(HttpServletRequest req, Group group)
		throws Exception {

		Layout selLayout = null;

		String selLayoutId = req.getParameter("p_sel_l_id");

		if (group == null) {
			try {
				LayoutPK selLayoutPK = new LayoutPK(
					selLayoutId, req.getRemoteUser());

				selLayout = LayoutServiceUtil.getLayout(selLayoutPK);
			}
			catch (NoSuchLayoutException nsle) {
			}
		}
		else {
			try {
				LayoutPK selLayoutPK = new LayoutPK(
					selLayoutId, Layout.GROUP + group.getGroupId());

				selLayout = LayoutServiceUtil.getLayout(selLayoutPK);
			}
			catch (NoSuchLayoutException nsle) {
			}
		}

		return selLayout;
	}

	private void _updateDisplayOrder(HttpServletRequest req) throws Exception {
		String parentLayoutId = ParamUtil.getString(req, "p_sel_l_id");
		String[] layoutIds = StringUtil.split(
			ParamUtil.getString(req, "p_l_display_order"));

		Group group = (Group)req.getAttribute(WebKeys.GROUP);

		if (group == null) {
			UserServiceUtil.setLayouts(
				req.getRemoteUser(), parentLayoutId, layoutIds);
		}
		else {
			GroupServiceUtil.setLayouts(
				group.getGroupId(), parentLayoutId, layoutIds);
		}
	}

	private void _updateLayout(HttpServletRequest req, LayoutForm layoutForm)
		throws Exception {

		HttpSession ses = req.getSession();

		String name = ParamUtil.getString(req, "p_l_name");
		String friendlyURL = ParamUtil.getString(req, "p_l_friendly_url");

		String columnOrder = ParamUtil.getString(req, "p_l_column_order");
		String narrow1 = ParamUtil.getString(req, "p_l_narrow_1_list");
		String narrow2 = ParamUtil.getString(req, "p_l_narrow_2_list");
		String wide1 = ParamUtil.getString(req, "p_l_wide_1_list");

		String copyLayoutId = ParamUtil.getString(req, "p_l_copy_id");

		Group group = (Group)req.getAttribute(WebKeys.GROUP);

		Layout layout = _getSelLayout(req, group);

		if (layout.getType().equals(Layout.TYPE_PORTLET)) {
			LayoutTypePortlet layoutType =
				(LayoutTypePortlet)layout.getLayoutType();

			narrow1 = layoutType.qualifyPortletIds(narrow1);
			narrow2 = layoutType.qualifyPortletIds(narrow2);
			wide1 = layoutType.qualifyPortletIds(wide1);

			if (Validator.isNotNull(copyLayoutId)) {
				try {
					Layout copyLayout = LayoutServiceUtil.getLayout(
						new LayoutPK(copyLayoutId, layout.getUserId()));

					if (copyLayout.getType().equals(Layout.TYPE_PORTLET)) {
						LayoutTypePortlet copyLayoutType =
							(LayoutTypePortlet)copyLayout.getLayoutType();

						// Copy layout

						columnOrder = copyLayoutType.getColumnOrder();
						narrow1 = copyLayoutType.getNarrow1();
						narrow2 = copyLayoutType.getNarrow2();
						wide1 = copyLayoutType.getWide1();

						// Copy preferences

						_copyPreferences(
							req, layout.getLayoutId(), copyLayoutId,
							copyLayoutType);
					}
				}
				catch (NoSuchLayoutException nsle) {
				}
			}

			layoutType.setColumnOrder(columnOrder);
			layoutType.setNarrow1(narrow1);
			layoutType.setNarrow2(narrow2);
			layoutType.setWide1(wide1);
		}
		else {
			layout.setTypeSettingsProperties(
				layoutForm.getTypeSettingsProperties());
		}

		LayoutServiceUtil.updateLayout(
			layout.getPrimaryKey(), name, layout.getTypeSettings(),
			friendlyURL);

		if (group != null) {
			LayoutClonePool.refresh(req, layout);
		}

		CachePortlet.clearResponses(ses);
	}

}