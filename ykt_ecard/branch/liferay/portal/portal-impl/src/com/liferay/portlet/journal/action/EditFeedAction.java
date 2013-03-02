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

package com.liferay.portlet.journal.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.DuplicateFeedIdException;
import com.liferay.portlet.journal.FeedContentFieldException;
import com.liferay.portlet.journal.FeedDescriptionException;
import com.liferay.portlet.journal.FeedIdException;
import com.liferay.portlet.journal.FeedNameException;
import com.liferay.portlet.journal.FeedTargetLayoutFriendlyUrlException;
import com.liferay.portlet.journal.FeedTargetPortletIdException;
import com.liferay.portlet.journal.NoSuchFeedException;
import com.liferay.portlet.journal.service.JournalFeedServiceUtil;
import com.liferay.util.RSSUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditFeedAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class EditFeedAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateFeed(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteFeeds(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchFeedException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.journal.error");
			}
			else if (e instanceof DuplicateFeedIdException ||
					 e instanceof FeedContentFieldException ||
					 e instanceof FeedDescriptionException ||
					 e instanceof FeedIdException ||
					 e instanceof FeedNameException ||
					 e instanceof FeedTargetLayoutFriendlyUrlException ||
					 e instanceof FeedTargetPortletIdException) {

				SessionErrors.add(req, e.getClass().getName());
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

		try {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			if (!cmd.equals(Constants.ADD)) {
				ActionUtil.getFeed(req);
			}
		}
		catch (NoSuchFeedException nssfe) {

			// Let this slide because the user can manually input a feed id for
			// a new syndicated feed that does not yet exist.

		}
		catch (Exception e) {
			if (e instanceof PrincipalException) {
				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.journal.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.journal.edit_feed"));
	}

	protected void deleteFeeds(ActionRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");

		String[] deleteFeedIds = StringUtil.split(
			ParamUtil.getString(req, "deleteFeedIds"));

		for (int i = 0; i < deleteFeedIds.length; i++) {
			JournalFeedServiceUtil.deleteFeed(groupId, deleteFeedIds[i]);
		}
	}

	protected void updateFeed(ActionRequest req) throws Exception {
		String cmd = ParamUtil.getString(req, Constants.CMD);

		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long groupId = ParamUtil.getLong(req, "groupId");

		String feedId = ParamUtil.getString(req, "feedId");
		boolean autoFeedId = ParamUtil.getBoolean(req, "autoFeedId");

		String name = ParamUtil.getString(req, "name");
		String description = ParamUtil.getString(req, "description");
		String type = ParamUtil.getString(req, "type");
		String structureId = ParamUtil.getString(req, "structureId");
		String templateId = ParamUtil.getString(req, "templateId");
		String rendererTemplateId = ParamUtil.getString(
			req, "rendererTemplateId");
		int delta = ParamUtil.getInteger(req, "delta");
		String orderByCol = ParamUtil.getString(req, "orderByCol");
		String orderByType = ParamUtil.getString(req, "orderByType");
		String targetLayoutFriendlyUrl = ParamUtil.getString(
			req, "targetLayoutFriendlyUrl");
		String targetPortletId = ParamUtil.getString(req, "targetPortletId");
		String contentField = ParamUtil.getString(req, "contentField");

		String feedType = RSSUtil.DEFAULT_TYPE;
		double feedVersion = RSSUtil.DEFAULT_VERSION;

		String feedTypeAndVersion = ParamUtil.getString(
			req, "feedTypeAndVersion");

		if (Validator.isNotNull(feedTypeAndVersion)) {
			String[] parts = feedTypeAndVersion.split(StringPool.COLON);

			try {
				feedType = parts[0];
				feedVersion = GetterUtil.getDouble(parts[1]);
			}
			catch (Exception e) {
			}
		}
		else {
			feedType = ParamUtil.getString(req, "feedType", feedType);
			feedVersion = ParamUtil.getDouble(req, "feedVersion", feedVersion);
		}

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (cmd.equals(Constants.ADD)) {

			// Add feed

			JournalFeedServiceUtil.addFeed(
				layout.getPlid(), feedId, autoFeedId, name, description,
				type, structureId, templateId, rendererTemplateId, delta,
				orderByCol, orderByType, targetLayoutFriendlyUrl,
				targetPortletId, contentField, feedType, feedVersion,
				communityPermissions, guestPermissions);
		}
		else {

			// Update feed

			JournalFeedServiceUtil.updateFeed(
				groupId, feedId, name, description, type, structureId,
				templateId, rendererTemplateId, delta, orderByCol, orderByType,
				targetLayoutFriendlyUrl, targetPortletId, contentField,
				feedType, feedVersion);
		}
	}

}