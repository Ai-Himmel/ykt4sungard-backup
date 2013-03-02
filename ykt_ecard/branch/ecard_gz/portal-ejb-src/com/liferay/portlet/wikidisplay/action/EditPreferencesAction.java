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

package com.liferay.portlet.wikidisplay.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.wiki.NoSuchNodeException;
import com.liferay.portlet.wiki.NoSuchPageException;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.spring.WikiNodeServiceUtil;
import com.liferay.portlet.wiki.service.spring.WikiPageLocalServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditPreferencesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class EditPreferencesAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			if (!cmd.equals(Constants.UPDATE)) {
				return;
			}

			String portletTitle = ParamUtil.getString(req, "portlet_title");
			boolean showPortletBorders = ParamUtil.getBoolean(
				req, "show_portlet_borders");

			String publicNodeId = ParamUtil.getString(req, "public_node_id");
			String privateNodeId = ParamUtil.getString(req, "private_node_id");
			boolean showWikiBorders = ParamUtil.getBoolean(
				req, "show_wiki_borders");

			WikiNode wikiNode = null;

			if (Validator.isNotNull(publicNodeId)) {
				wikiNode = WikiNodeServiceUtil.getNode(publicNodeId);
			}
			else {
				wikiNode = WikiNodeServiceUtil.getNode(privateNodeId);
			}

			List wikiPages = WikiPageLocalServiceUtil.getPages(
				wikiNode.getNodeId(), WikiPage.FRONT_PAGE, true);

			if (wikiPages.size() == 0) {
				throw new NoSuchPageException();
			}

			WikiPage wikiPage = (WikiPage)wikiPages.get(0);

			PortletPreferences prefs = req.getPreferences();

			prefs.setValue("portlet-title", portletTitle);
			prefs.setValue(
				"show-portlet-borders", Boolean.toString(showPortletBorders));

			prefs.setValue("node-id", wikiNode.getNodeId());
			prefs.setValue(
				"show-wiki-borders", Boolean.toString(showWikiBorders));

			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doEdit");
		}
		catch (NoSuchNodeException nsne) {
			SessionErrors.add(req, nsne.getClass().getName());
		}
		catch (NoSuchPageException nspe) {
			SessionErrors.add(req, nspe.getClass().getName());
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		return mapping.findForward(
			getForward(req, "portlet.wiki_display.edit"));
	}

}