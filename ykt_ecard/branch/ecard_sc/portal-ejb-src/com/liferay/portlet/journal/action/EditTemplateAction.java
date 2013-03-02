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

package com.liferay.portlet.journal.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.DuplicateTemplateIdException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.RequiredTemplateException;
import com.liferay.portlet.journal.TemplateDescriptionException;
import com.liferay.portlet.journal.TemplateIdException;
import com.liferay.portlet.journal.TemplateNameException;
import com.liferay.portlet.journal.TemplateSmallImageNameException;
import com.liferay.portlet.journal.TemplateSmallImageSizeException;
import com.liferay.portlet.journal.TemplateXslException;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.spring.JournalTemplateServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.JS;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditTemplateAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.22 $
 *
 */
public class EditTemplateAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			_editTemplate(req);
		}
		catch (Exception e) {
			if (e != null &&
				//e instanceof NoSuchTemplateException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.journal.error");
			}
			else {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			if (cmd.equals(Constants.ADD)) {
				req.removeAttribute(WebKeys.JOURNAL_TEMPLATE);
			}

			try {
				_updateTemplate(config, req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTemplateException ||
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else if (e != null &&
						 e instanceof DuplicateTemplateIdException ||
						 e instanceof TemplateDescriptionException ||
						 e instanceof TemplateIdException ||
						 e instanceof TemplateNameException ||
						 e instanceof TemplateSmallImageNameException ||
						 e instanceof TemplateSmallImageSizeException ||
						 e instanceof TemplateXslException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.edit_template_content");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteTemplate(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchTemplateException ||
					e instanceof PrincipalException ||
					e instanceof RequiredTemplateException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.journal.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else {
			JournalTemplate template =
				(JournalTemplate)req.getAttribute(WebKeys.JOURNAL_TEMPLATE);

			String structureId = req.getParameter("structure_id");
			String structureBased = req.getParameter(
				"template_structure_based");

			if ((template != null) || (Validator.isNotNull(structureId))) {
				setForward(req, "portlet.journal.edit_template_content");
			}
			else if (Validator.isNotNull(structureBased)) {
				if (GetterUtil.getBoolean(structureBased)) {
					setForward(req, "portlet.journal.edit_template_structure");
				}
				else {
					setForward(req, "portlet.journal.edit_template_content");
				}
			}
			else {
				setForward(req, "portlet.journal.edit_template");
			}
		}
	}

	private void _deleteTemplate(ActionRequest req, ActionResponse res)
		throws Exception {

		String templateId = ParamUtil.getString(req, "template_id");

		JournalTemplateServiceUtil.deleteTemplate(templateId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editTemplate(ActionRequest req) throws Exception {
		String templateId = ParamUtil.getString(req, "template_id");

		// Find template

		JournalTemplate template = null;

		if (Validator.isNotNull(templateId)) {
			template = JournalTemplateServiceUtil.getTemplate(templateId);
		}

		req.setAttribute(WebKeys.JOURNAL_TEMPLATE, template);

		JournalUtil.addRecentTemplate(req, template);
	}

	private void _updateTemplate(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		String cmd = ParamUtil.getString(uploadReq, Constants.CMD);

		String templateId = ParamUtil.getString(uploadReq, "template_id");
		boolean autoTemplateId = ParamUtil.get(
			uploadReq, "auto_template_id", false);

		String structureId = ParamUtil.getString(uploadReq, "structure_id");
		String name = ParamUtil.getString(uploadReq, "template_name");
		String description = ParamUtil.getString(uploadReq, "template_desc");

		String xsl = ParamUtil.getString(uploadReq, "template_xsl");
		String xslContent = JS.decodeURIComponent(
			ParamUtil.getString(uploadReq, "template_xsl_content"));
		boolean formatXsl = ParamUtil.get(uploadReq, "format_xsl", false);

		if (Validator.isNull(xsl)) {
			xsl = xslContent;
		}

		boolean smallImage = ParamUtil.get(
			uploadReq, "template_small_image", false);
		String smallImageURL = ParamUtil.getString(
			uploadReq, "template_small_image_url");
		File smallFile = uploadReq.getFile("template_small_i");

		JournalTemplate template = null;

		if (cmd.equals(Constants.ADD)) {

			// Add template

			template = JournalTemplateServiceUtil.addTemplate(
				templateId, autoTemplateId, config.getPortletName(),
				PortalUtil.getPortletGroupId(req), structureId, name,
				description, xsl, formatXsl, smallImage, smallImageURL,
				smallFile);
		}
		else {

			// Update template

			template = JournalTemplateServiceUtil.updateTemplate(
				templateId, name, description, xsl, formatXsl, smallImage,
				smallImageURL, smallFile);
		}

		// Session messages

		SessionMessages.add(req, "template_saved");

		// Recent templates

		JournalUtil.addRecentTemplate(req, template);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}