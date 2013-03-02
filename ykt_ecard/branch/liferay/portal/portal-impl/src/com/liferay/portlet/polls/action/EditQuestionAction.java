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

package com.liferay.portlet.polls.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.polls.DuplicateVoteException;
import com.liferay.portlet.polls.NoSuchChoiceException;
import com.liferay.portlet.polls.NoSuchQuestionException;
import com.liferay.portlet.polls.QuestionChoiceException;
import com.liferay.portlet.polls.QuestionDescriptionException;
import com.liferay.portlet.polls.QuestionExpirationDateException;
import com.liferay.portlet.polls.QuestionExpiredException;
import com.liferay.portlet.polls.QuestionTitleException;
import com.liferay.portlet.polls.model.PollsChoice;
import com.liferay.portlet.polls.service.PollsQuestionServiceUtil;
import com.liferay.portlet.polls.service.persistence.PollsChoiceUtil;
import com.liferay.util.servlet.SessionErrors;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Enumeration;
import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditQuestionAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditQuestionAction extends PortletAction {

	public static final String CHOICE_DESCRIPTION_PREFIX = "choiceDescription";

	public static final String CHOICE_NAME_PREFIX = "choiceName";

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateQuestion(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteQuestion(req);
			}

			if (Validator.isNotNull(cmd)) {
				sendRedirect(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchQuestionException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.polls.error");
			}
			else if (e instanceof DuplicateVoteException ||
					 e instanceof NoSuchChoiceException ||
					 e instanceof QuestionChoiceException ||
					 e instanceof QuestionDescriptionException ||
					 e instanceof QuestionExpirationDateException ||

					 e instanceof QuestionTitleException) {

				SessionErrors.add(req, e.getClass().getName());
			}
			else if (e instanceof QuestionExpiredException) {
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
			ActionUtil.getQuestion(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchQuestionException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.polls.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.polls.edit_question"));
	}

	protected void deleteQuestion(ActionRequest req) throws Exception {
		long questionId = ParamUtil.getLong(req, "questionId");

		PollsQuestionServiceUtil.deleteQuestion(questionId);

	}

	protected void updateQuestion(ActionRequest req) throws Exception {
		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long questionId = ParamUtil.getLong(req, "questionId");

		String title = ParamUtil.getString(req, "title");
		String description = ParamUtil.getString(req, "description");

		int expirationDateMonth = ParamUtil.getInteger(
			req, "expirationDateMonth");
		int expirationDateDay = ParamUtil.getInteger(req, "expirationDateDay");
		int expirationDateYear = ParamUtil.getInteger(
			req, "expirationDateYear");
		int expirationDateHour = ParamUtil.getInteger(
			req, "expirationDateHour");
		int expirationDateMinute = ParamUtil.getInteger(
			req, "expirationDateMinute");
		int expirationDateAmPm = ParamUtil.getInteger(
			req, "expirationDateAmPm");
		boolean neverExpire = ParamUtil.getBoolean(req, "neverExpire");

		if (expirationDateAmPm == Calendar.PM) {
			expirationDateHour += 12;
		}

		List choices = new ArrayList();

		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String param = (String)enu.nextElement();

			if (param.startsWith(CHOICE_DESCRIPTION_PREFIX)) {
				try {
					String id = param.substring(
						CHOICE_DESCRIPTION_PREFIX.length(), param.length());

					String choiceName = ParamUtil.getString(
						req, CHOICE_NAME_PREFIX + id);
					String choiceDescription = ParamUtil.getString(req, param);

					PollsChoice choice = PollsChoiceUtil.create(0);

					choice.setName(choiceName);
					choice.setDescription(choiceDescription);

					choices.add(choice);
				}
				catch (Exception e) {
				}
			}
		}

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (questionId <= 0) {

			// Add question

			PollsQuestionServiceUtil.addQuestion(
				layout.getPlid(), title, description, expirationDateMonth,
				expirationDateDay, expirationDateYear, expirationDateHour,
				expirationDateMinute, neverExpire, choices,
				communityPermissions, guestPermissions);
		}
		else {

			// Update question

			PollsQuestionServiceUtil.updateQuestion(
				questionId, title, description, expirationDateMonth,
				expirationDateDay, expirationDateYear, expirationDateHour,
				expirationDateMinute, neverExpire, choices);
		}
	}

}