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

package com.liferay.portlet.polls.lar;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.polls.DuplicateVoteException;
import com.liferay.portlet.polls.NoSuchChoiceException;
import com.liferay.portlet.polls.NoSuchQuestionException;
import com.liferay.portlet.polls.model.PollsChoice;
import com.liferay.portlet.polls.model.PollsQuestion;
import com.liferay.portlet.polls.model.PollsVote;
import com.liferay.portlet.polls.service.PollsChoiceLocalServiceUtil;
import com.liferay.portlet.polls.service.PollsQuestionLocalServiceUtil;
import com.liferay.portlet.polls.service.PollsVoteLocalServiceUtil;
import com.liferay.portlet.polls.service.persistence.PollsChoiceFinderUtil;
import com.liferay.portlet.polls.service.persistence.PollsChoiceUtil;
import com.liferay.portlet.polls.service.persistence.PollsQuestionUtil;
import com.liferay.portlet.polls.service.persistence.PollsVoteUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.MapUtil;

import com.thoughtworks.xstream.XStream;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletPreferences;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="PollsPortletDataHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class PollsPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Questions

			if (!context.addPrimaryKey(
					PollsPortletDataHandlerImpl.class, "deleteData")) {

				PollsQuestionLocalServiceUtil.deleteQuestions(
					context.getGroupId());
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public String exportData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = DocumentHelper.createDocument();

			Element root = doc.addElement("polls-data");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Questions

			List questions = PollsQuestionUtil.findByGroupId(
				context.getGroupId());

			List choices = new ArrayList();

			List votes = new ArrayList();

			Iterator itr = questions.iterator();

			while (itr.hasNext()) {
				PollsQuestion question = (PollsQuestion)itr.next();

				if (context.addPrimaryKey(
						PollsQuestion.class, question.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					List questionChoices = PollsChoiceUtil.findByQuestionId(
						question.getQuestionId());

					choices.addAll(questionChoices);

					if (context.getBooleanParameter(_NAMESPACE, "votes")) {
						question.setUserUuid(question.getUserUuid());

						List questionVotes = PollsVoteUtil.findByQuestionId(
							question.getQuestionId());

						votes.addAll(questionVotes);
					}
				}
			}

			String xml = xStream.toXML(questions);

			Element el = root.addElement("poll-questions");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Choices

			itr = choices.iterator();

			while (itr.hasNext()) {
				PollsChoice choice = (PollsChoice)itr.next();

				if (context.addPrimaryKey(
						PollsChoice.class, choice.getPrimaryKeyObj())) {

					itr.remove();
				}
			}

			xml = xStream.toXML(choices);

			el = root.addElement("poll-choices");

			tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			// Votes

			itr = votes.iterator();

			while (itr.hasNext()) {
				PollsVote vote = (PollsVote)itr.next();

				if (context.addPrimaryKey(
						PollsVote.class, vote.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					vote.setUserUuid(vote.getUserUuid());
				}
			}

			xml = xStream.toXML(votes);

			el = root.addElement("poll-votes");

			tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			return doc.asXML();
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public PortletDataHandlerControl[] getExportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_questions, _votes};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_questions, _votes};
	}

	public PortletPreferences importData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs, String data)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = PortalUtil.readDocumentFromXML(data);

			Element root = doc.getRootElement();

			// Questions

			Element el = root.element("poll-questions").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map questionPKs = CollectionFactory.getHashMap();

			List questions = (List)xStream.fromXML(tempDoc.asXML());

			Iterator itr = questions.iterator();

			while (itr.hasNext()) {
				PollsQuestion question = (PollsQuestion)itr.next();

				importQuestion(context, questionPKs, question);
			}

			// Choices

			el = root.element("poll-choices").element("list");

			tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			Map choicePKs = CollectionFactory.getHashMap();

			List choices = (List)xStream.fromXML(tempDoc.asXML());

			itr = choices.iterator();

			while (itr.hasNext()) {
				PollsChoice choice = (PollsChoice)itr.next();

				importChoice(context, questionPKs, choicePKs, choice);
			}

			// Votes

			if (context.getBooleanParameter(_NAMESPACE, "votes")) {
				el = root.element("poll-votes").element("list");

				tempDoc = DocumentHelper.createDocument();

				tempDoc.content().add(el.createCopy());

				List votes = (List)xStream.fromXML(tempDoc.asXML());

				itr = votes.iterator();

				while (itr.hasNext()) {
					PollsVote vote = (PollsVote)itr.next();

					importVote(context, questionPKs, choicePKs, vote);
				}
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected void importChoice(
			PortletDataContext context, Map questionPKs, Map choicePKs,
			PollsChoice choice)
		throws Exception {

		long questionId = MapUtil.getLong(
			questionPKs, choice.getQuestionId(), choice.getQuestionId());

		PollsChoice existingChoice = null;

		try {
			PollsQuestionUtil.findByPrimaryKey(questionId);

			if (context.getDataStrategy().equals(
					PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

				try {
					existingChoice = PollsChoiceFinderUtil.findByUuid_G(
						choice.getUuid(), context.getGroupId());

					existingChoice = PollsChoiceLocalServiceUtil.updateChoice(
						existingChoice.getChoiceId(), questionId,
						choice.getName(), choice.getDescription());
				}
				catch (NoSuchChoiceException nsce) {
					existingChoice = PollsChoiceLocalServiceUtil.addChoice(
						choice.getUuid(), questionId, choice.getName(),
						choice.getDescription());
				}
			}
			else {
				existingChoice = PollsChoiceLocalServiceUtil.addChoice(
					questionId, choice.getName(), choice.getDescription());
			}

			choicePKs.put(
				choice.getPrimaryKeyObj(), existingChoice.getPrimaryKeyObj());
		}
		catch (NoSuchQuestionException nsqe) {
			_log.error(
				"Could not find the question for choice " +
					choice.getChoiceId());
		}
	}

	protected void importQuestion(
			PortletDataContext context, Map questionPKs, PollsQuestion question)
		throws SystemException, PortalException {

		long userId = context.getUserId(question.getUserUuid());
		long plid = context.getPlid();

		Date expirationDate = question.getExpirationDate();

		int expirationMonth = 0;
		int expirationDay = 0;
		int expirationYear = 0;
		int expirationHour = 0;
		int expirationMinute = 0;
		boolean neverExpire = true;

		if (expirationDate != null) {
			Calendar expirationCal = CalendarFactoryUtil.getCalendar();

			expirationCal.setTime(expirationDate);

			expirationMonth = expirationCal.get(Calendar.MONTH);
			expirationDay = expirationCal.get(Calendar.DATE);
			expirationYear = expirationCal.get(Calendar.YEAR);
			expirationHour = expirationCal.get(Calendar.HOUR);
			expirationMinute = expirationCal.get(Calendar.MINUTE);
			neverExpire = false;
		}

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		PollsQuestion existingQuestion = null;

		if (context.getDataStrategy().equals(
				PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {
			existingQuestion =  PollsQuestionUtil.fetchByUUID_G(
				question.getUuid(), context.getGroupId());

			if (existingQuestion == null) {
				existingQuestion = PollsQuestionLocalServiceUtil.addQuestion(
					question.getUuid(), userId, plid, question.getTitle(),
					question.getDescription(), expirationMonth, expirationDay,
					expirationYear, expirationHour, expirationMinute,
					neverExpire, addCommunityPermissions, addGuestPermissions);
			}
			else {
				existingQuestion = PollsQuestionLocalServiceUtil.updateQuestion(
					userId, existingQuestion.getQuestionId(),
					question.getTitle(), question.getDescription(),
					expirationMonth, expirationDay, expirationYear,
					expirationHour, expirationMinute, neverExpire);
			}
		}
		else {
			existingQuestion = PollsQuestionLocalServiceUtil.addQuestion(
				userId, plid, question.getTitle(), question.getDescription(),
				expirationMonth, expirationDay, expirationYear, expirationHour,
				expirationMinute, neverExpire, addCommunityPermissions,
				addGuestPermissions);
		}

		questionPKs.put(
			question.getPrimaryKeyObj(), existingQuestion.getPrimaryKeyObj());
	}

	protected void importVote(
			PortletDataContext context, Map questionPKs, Map choicePKs,
			PollsVote vote)
		throws Exception {

		long userId = context.getUserId(vote.getUserUuid());
		long questionId = MapUtil.getLong(
			questionPKs, vote.getQuestionId(), vote.getQuestionId());
		long choiceId = MapUtil.getLong(
			choicePKs, vote.getChoiceId(), vote.getChoiceId());

		try {
			PollsQuestionUtil.findByPrimaryKey(questionId);
			PollsChoiceUtil.findByPrimaryKey(choiceId);

			PollsVoteLocalServiceUtil.addVote(
				userId, questionId, choiceId);
		}
		catch (DuplicateVoteException dve) {
		}
		catch (NoSuchQuestionException nsqe) {
			_log.error(
				"Could not find the question for vote " + vote.getVoteId());
		}
		catch (NoSuchChoiceException nsve) {
			_log.error(
				"Could not find the choice for vote " + vote.getVoteId());
		}
	}

	private static final String _NAMESPACE = "polls";

	private static final PortletDataHandlerBoolean _questions =
		new PortletDataHandlerBoolean(_NAMESPACE, "questions", true, true);

	private static final PortletDataHandlerBoolean _votes =
		new PortletDataHandlerBoolean(_NAMESPACE, "votes");

	private static Log _log =
		LogFactory.getLog(PollsPortletDataHandlerImpl.class);

}