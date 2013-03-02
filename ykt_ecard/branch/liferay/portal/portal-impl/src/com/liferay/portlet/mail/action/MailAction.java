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

package com.liferay.portlet.mail.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.struts.JSONAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrettyDateFormat;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.model.MailEnvelope;
import com.liferay.portlet.mail.model.MailFolder;
import com.liferay.portlet.mail.search.MailDisplayTerms;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.portlet.mail.util.comparator.DateComparator;
import com.liferay.portlet.mail.util.comparator.RecipientComparator;
import com.liferay.portlet.mail.util.comparator.SizeComparator;
import com.liferay.portlet.mail.util.comparator.StateComparator;
import com.liferay.portlet.mail.util.comparator.SubjectComparator;
import com.liferay.portlet.mail.util.recipient.RecipientFinder;
import com.liferay.portlet.mail.util.recipient.RecipientFinderLocator;
import com.liferay.util.Autocomplete;
import com.liferay.util.ListUtil;
import com.liferay.util.TextFormatter;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

import javax.portlet.PortletPreferences;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.collections.map.MultiValueMap;
import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="MailAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ming-Gih Lam
 *
 */
public class MailAction extends JSONAction {

	public String getJSON(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals("addFolder")) {
				addFolder(req);
			}
			else if (cmd.equals("deleteFolder")) {
				deleteFolder(req);
			}
			else if (cmd.equals("deleteMessages")) {
				deleteMessages(req);
			}
			else if (cmd.equals("emptyFolder")) {
				return emptyFolder(req);
			}
			else if (cmd.equals("getFolders")) {
				return getFolders(req);
			}
			else if (cmd.equals("getMessage")) {
				return getMessage(req);
			}
			else if (cmd.equals("getPreview")) {
				return getPreview(req);
			}
			else if (cmd.equals("getRecipients")) {
				return getRecipients(req);
			}
			else if (cmd.equals("getSearch")) {
				return getSearch(req);
			}
			else if (cmd.equals("getSearchCached")) {
				return getSearchCached(req);
			}
			else if (cmd.equals("moveMessages")) {
				moveMessages(req);
			}
			else if (cmd.equals("renameFolder")) {
				renameFolder(req);
			}
			else if (cmd.equals("updatePreferences")) {
				updatePreferences(req);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		return null;
	}

	protected void addFolder(HttpServletRequest req) throws Exception {
		String folderId = ParamUtil.getString(req, "folderId");

		MailUtil.createFolder(req, folderId);
	}

	protected void deleteFolder(HttpServletRequest req) throws Exception {
		String folderId = ParamUtil.getString(req, "folderId");

		MailUtil.removeFolder(req, folderId);
	}

	protected void deleteMessages(HttpServletRequest req) throws Exception {
		MultiValueMap messages = _convertMessages(req);

		MailUtil.deleteMessages(req, messages);
	}

	protected String emptyFolder(HttpServletRequest req) throws Exception {
		JSONObject jsonObj = new JSONObject();

		String folderId = ParamUtil.getString(req, "folderId");

		MailUtil.emptyFolder(req, folderId);

		jsonObj.put("folderId", folderId);

		return jsonObj.toString();
	}

	protected Comparator getComparator(HttpServletRequest req)
		throws Exception {

		String sortBy = ParamUtil.getString(req, "sortBy");
		boolean asc = ParamUtil.getBoolean(req, "asc");

		Comparator comparator;

		if (sortBy.equals("state")) {
			comparator = new StateComparator(asc);
		}
		else if (sortBy.equals("name")) {
			comparator = new RecipientComparator(asc);
		}
		else if (sortBy.equals("subject")) {
			comparator = new SubjectComparator(asc);
		}
		else if (sortBy.equals("size")) {
			comparator = new SizeComparator(asc);
		}
		else {
			comparator = new DateComparator(asc);
		}

		return comparator;
	}

	protected String getFolders(HttpServletRequest req) throws Exception {
		JSONObject jsonObj = new JSONObject();

		_getFolders(req, jsonObj);

		return jsonObj.toString();
	}

	protected String getMessage(HttpServletRequest req) throws Exception {
		JSONObject jsonObj = new JSONObject();

		String folderId = ParamUtil.getString(req, "folderId");
		long messageId = ParamUtil.getLong(req, "messageId");

		MailUtil.setFolder(req, folderId);

		MailUtil.setMessageId(req, messageId);

		jsonObj.put("id", messageId);
		jsonObj.put("folderId", folderId);

		return jsonObj.toString();
	}

	protected String getPreview(HttpServletRequest req) throws Exception {
		StopWatch stopWatch = null;

		if (_log.isInfoEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		JSONObject jsonObj = new JSONObject();

		String folderId = ParamUtil.getString(req, "folderId");

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		MailUtil.setFolder(req, folderId);

		Set envelopes = MailUtil.getEnvelopes(req, getComparator(req));

		JSONArray jsonEnvelopes = _convertEnvelopes(envelopes, themeDisplay);

		jsonObj.put("folderId", folderId);
		jsonObj.put("headers", jsonEnvelopes);

		if (_log.isInfoEnabled()) {
			_log.info(
				"Total time to get preview " + stopWatch.getTime() + "ms");
		}

		return jsonObj.toString();
	}

	protected String getRecipients(HttpServletRequest req) throws Exception {
		long userId = PortalUtil.getUserId(req);

		String data = ParamUtil.getString(req, "data");

		PortletPreferences prefs = PortalUtil.getPreferences(req);

		List finders = RecipientFinderLocator.getInstances();

		SortedSet recipients = new TreeSet();

		for (int i = 0; i < finders.size(); i++) {
			RecipientFinder finder = (RecipientFinder)finders.get(i);

			boolean enabled =
				GetterUtil.getBoolean(
					prefs.getValue(
						finder.getClass().getName(), null),
					true);

			if (enabled) {
				recipients.addAll(
					finder.getRecipients(userId, data, new HashMap()));
			}
		}

		String[] recipientsArray = (String[])ListUtil.fromCollection(
			recipients).toArray(new String[0]);

		JSONArray jsonArray = Autocomplete.arrayToJson(recipientsArray, 50);

		return jsonArray.toString();
	}

	protected String getSearch(HttpServletRequest req) throws Exception {
		JSONObject jsonObj = new JSONObject();

		HttpSession ses = req.getSession();

		MailDisplayTerms displayTerms = new MailDisplayTerms(req);

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
				WebKeys.THEME_DISPLAY);

		Set envelopes = MailUtil.search(req, displayTerms, getComparator(req));

		ses.setAttribute(WebKeys.MAIL_SEARCH_RESULTS, envelopes);

		JSONArray jsonEnvelopes = _convertEnvelopes(envelopes, themeDisplay);

		jsonObj.put("headers", jsonEnvelopes);

		return jsonObj.toString();
	}

	protected String getSearchCached(HttpServletRequest req) throws Exception {
		JSONObject jsonObj = new JSONObject();

		HttpSession ses = req.getSession();

		ThemeDisplay themeDisplay = (ThemeDisplay)req.getAttribute(
			WebKeys.THEME_DISPLAY);

		Set envelopes = new TreeSet(getComparator(req));

		envelopes.addAll((Set)ses.getAttribute(WebKeys.MAIL_SEARCH_RESULTS));

		ses.setAttribute(WebKeys.MAIL_SEARCH_RESULTS, envelopes);

		JSONArray jsonEnvelopes = _convertEnvelopes(envelopes, themeDisplay);

		jsonObj.put("headers", jsonEnvelopes);

		return jsonObj.toString();
	}

	protected void moveMessages(HttpServletRequest req) throws Exception {
		MultiValueMap messages = _convertMessages(req);

		String folderId = ParamUtil.getString(req, "folderId");

		MailUtil.moveMessages(req, messages, folderId);
	}

	protected void renameFolder(HttpServletRequest req) throws Exception {
		String folderId = ParamUtil.getString(req, "folderId");
		String newFolderId = ParamUtil.getString(req, "newFolderId");

		MailUtil.renameFolder(req, folderId, newFolderId);
	}

	protected void updatePreferences(HttpServletRequest req) throws Exception {
		PortletPreferences prefs = PortalUtil.getPreferences(req);

		String[] keys = StringUtil.split(ParamUtil.getString(req, "key"));
		String[] values = StringUtil.split(ParamUtil.getString(req, "value"));

		for (int i = 0; i < keys.length && i < values.length; i++) {
			prefs.setValue(keys[i], values[i]);
		}

		prefs.store();
	}

	private JSONArray _convertEnvelopes(
		Set envelopes, ThemeDisplay themeDisplay) {

		PrettyDateFormat dateFormat =
			new PrettyDateFormat(themeDisplay.getCompanyId(),
				themeDisplay.getLocale(), themeDisplay.getTimeZone());

		JSONArray jsonEnvelopes = new JSONArray();

		Iterator itr = envelopes.iterator();

		while (itr.hasNext()) {
			MailEnvelope mailEnvelope = (MailEnvelope)itr.next();

			JSONObject jsonEnvelope = new JSONObject();

			String recipient = GetterUtil.getString(
				mailEnvelope.getRecipient(), StringPool.NBSP);

			String subject = GetterUtil.getString(
				mailEnvelope.getSubject(), StringPool.NBSP);

			jsonEnvelope.put("id", mailEnvelope.getMessageId());
			jsonEnvelope.put("folderId", mailEnvelope.getFolderName());
			jsonEnvelope.put("email", recipient);
			jsonEnvelope.put("subject", subject);
			jsonEnvelope.put("date", dateFormat.format(mailEnvelope.getDate()));
			jsonEnvelope.put(
				"size",
				TextFormatter.formatKB(
					mailEnvelope.getSize(), themeDisplay.getLocale()) + "k");
			jsonEnvelope.put("read", mailEnvelope.isRead());
			jsonEnvelope.put("replied", mailEnvelope.isAnswered());
			jsonEnvelope.put("flagged", mailEnvelope.isFlagged());

			jsonEnvelopes.put(jsonEnvelope);
		}

		return jsonEnvelopes;
	}

	private MultiValueMap _convertMessages(HttpServletRequest req) {
		String[] messagesArray = StringUtil.split(
			ParamUtil.getString(req, "messages"), ",");

		MultiValueMap messages = new MultiValueMap();

		for (int i = 0; i < messagesArray.length; i += 2) {
			messages.put(messagesArray[i], messagesArray[i+1]);
		}
		return messages;
	}

	private void _getFolders(HttpServletRequest req, JSONObject jsonObj)
		throws Exception {

		StopWatch stopWatch = null;

		if (_log.isInfoEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		JSONArray jsonFolders = new JSONArray();

		int count = 1;

		Iterator itr = MailUtil.getFolders(req).iterator();

		while (itr.hasNext()) {
			MailFolder folder = (MailFolder)itr.next();

			JSONObject jsonFolder = new JSONObject();

			String name = folder.getName();

			jsonFolder.put("name", name);
			jsonFolder.put("id", name);
			jsonFolder.put("newCount", folder.getUnreadMessageCount());
			jsonFolder.put("totalCount", folder.getMessageCount());

			if (name.equals(MailUtil.MAIL_INBOX_NAME)) {
				jsonFolders.put(0, jsonFolder);
			}
			else {
				jsonFolders.put(count++, jsonFolder);
			}
		}

		jsonObj.put("folders", jsonFolders);

		if (_log.isInfoEnabled()) {
			_log.info(
				"Total time to get folders " + stopWatch.getTime() + "ms");
		}
	}

	private static Log _log = LogFactory.getLog(MailAction.class);

}