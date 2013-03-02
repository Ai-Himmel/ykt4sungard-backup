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

package com.liferay.portlet.communities.action;

import com.germinus.easyconf.Filter;

import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.service.LayoutServiceUtil;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.struts.JSONAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.communities.util.CommunitiesUtil;
import com.liferay.util.Http;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.json.JSONObject;

/**
 * <a href="UpdatePageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ming-Gih Lam
 *
 */
public class UpdatePageAction extends JSONAction {

	public String getJSON(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		PermissionChecker permissionChecker =
			themeDisplay.getPermissionChecker();

		String portletId = ParamUtil.getString(req, "portletId");

		if (!PortletPermissionUtil.contains(
				permissionChecker, themeDisplay.getPlid(), portletId,
				ActionKeys.CONFIGURATION)) {

			return null;
		}

		String cmd = ParamUtil.getString(req, Constants.CMD);

		JSONObject jsonObj = new JSONObject();

		if (cmd.equals("add")) {
			String[] array = addPage(themeDisplay, req, res);

			jsonObj.put("layoutId", array[0]);
			jsonObj.put("url", array[1]);
		}
		else if (cmd.equals("delete")) {
			CommunitiesUtil.deleteLayout(req, res);
		}
		else if (cmd.equals("display_order")) {
			updateDisplayOrder(req);
		}
		else if (cmd.equals("name")) {
			updateName(req);
		}
		else if (cmd.equals("parent_layout_id")) {
			updateParentLayoutId(req);
		}
		else if (cmd.equals("priority")) {
			updatePriority(req);
		}

		return jsonObj.toString();
	}

	protected String[] addPage(
			ThemeDisplay themeDisplay, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		String doAsUserId = ParamUtil.getString(req, "doAsUserId");

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
		long parentLayoutId = ParamUtil.getLong(req, "parentLayoutId");
		String name = ParamUtil.getString(req, "name", "New Page");
		String title = StringPool.BLANK;
		String description = StringPool.BLANK;
		String type = LayoutImpl.TYPE_PORTLET;
		boolean hidden = false;
		String friendlyURL = StringPool.BLANK;

		Layout layout = LayoutServiceUtil.addLayout(
			groupId, privateLayout, parentLayoutId, name, title, description,
			type, hidden, friendlyURL);

		LayoutTypePortlet layoutTypePortlet =
			(LayoutTypePortlet)layout.getLayoutType();

		layoutTypePortlet.setLayoutTemplateId(
			0, PropsValues.LAYOUT_DEFAULT_TEMPLATE_ID, false);

		LayoutServiceUtil.updateLayout(
			layout.getGroupId(), layout.isPrivateLayout(), layout.getLayoutId(),
			layout.getTypeSettings());

		String[] eventClasses = StringUtil.split(
			PropsUtil.getComponentProperties().getString(
				PropsUtil.LAYOUT_CONFIGURATION_ACTION_UPDATE,
				Filter.by(layout.getType())));

		EventsProcessor.process(eventClasses, req, res);

		String layoutURL = PortalUtil.getLayoutURL(layout, themeDisplay);

		if (Validator.isNotNull(doAsUserId)) {
			layoutURL = Http.addParameter(
				layoutURL, "doAsUserId", themeDisplay.getDoAsUserId());
		}

		return new String[] {String.valueOf(layout.getLayoutId()), layoutURL};
	}

	protected void updateDisplayOrder(HttpServletRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
		long parentLayoutId = ParamUtil.getLong(req, "parentLayoutId");
		long[] layoutIds = StringUtil.split(
			ParamUtil.getString(req, "layoutIds"), 0L);

		LayoutServiceUtil.setLayouts(
			groupId, privateLayout, parentLayoutId, layoutIds);
	}

	protected void updateName(HttpServletRequest req) throws Exception {
		long plid = ParamUtil.getLong(req, "plid");

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
		long layoutId = ParamUtil.getLong(req, "layoutId");
		String name = ParamUtil.getString(req, "name");
		String languageId = ParamUtil.getString(req, "languageId");

		if (plid <= 0) {
			LayoutServiceUtil.updateName(
				groupId, privateLayout, layoutId, name, languageId);
		}
		else {
			LayoutServiceUtil.updateName(plid, name, languageId);
		}
	}

	protected void updateParentLayoutId(HttpServletRequest req)
		throws Exception {

		long plid = ParamUtil.getLong(req, "plid");

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
		long layoutId = ParamUtil.getLong(req, "layoutId");
		long parentPlid = ParamUtil.getLong(req, "parentPlid");
		long parentLayoutId = ParamUtil.getLong(
			req, "parentLayoutId", LayoutImpl.DEFAULT_PARENT_LAYOUT_ID);

		if (plid <= 0) {
			LayoutServiceUtil.updateParentLayoutId(
				groupId, privateLayout, layoutId, parentLayoutId);
		}
		else {
			LayoutServiceUtil.updateParentLayoutId(plid, parentPlid);
		}
	}

	protected void updatePriority(HttpServletRequest req) throws Exception {
		long plid = ParamUtil.getLong(req, "plid");

		long groupId = ParamUtil.getLong(req, "groupId");
		boolean privateLayout = ParamUtil.getBoolean(req, "privateLayout");
		long layoutId = ParamUtil.getLong(req, "layoutId");
		int priority = ParamUtil.getInteger(req, "priority");

		if (plid <= 0) {
			LayoutServiceUtil.updatePriority(
				groupId, privateLayout, layoutId, priority);
		}
		else {
			LayoutServiceUtil.updatePriority(plid, priority);
		}
	}

}