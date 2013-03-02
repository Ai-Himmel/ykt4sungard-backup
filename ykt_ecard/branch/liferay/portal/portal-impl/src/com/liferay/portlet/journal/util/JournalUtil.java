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

package com.liferay.portlet.journal.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.TransformException;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.model.impl.JournalStructureImpl;
import com.liferay.portlet.journal.model.impl.JournalTemplateImpl;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.journal.util.comparator.ArticleCreateDateComparator;
import com.liferay.portlet.journal.util.comparator.ArticleDisplayDateComparator;
import com.liferay.portlet.journal.util.comparator.ArticleIDComparator;
import com.liferay.portlet.journal.util.comparator.ArticleModifiedDateComparator;
import com.liferay.portlet.journal.util.comparator.ArticleReviewDateComparator;
import com.liferay.portlet.journal.util.comparator.ArticleTitleComparator;
import com.liferay.util.CollectionFactory;
import com.liferay.util.FiniteUniqueStack;
import com.liferay.util.Http;
import com.liferay.util.Time;
import com.liferay.util.xml.XMLFormatter;

import java.io.IOException;
import java.io.StringReader;
import java.io.UnsupportedEncodingException;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import javax.portlet.PortletPreferences;
import javax.portlet.PortletRequest;
import javax.portlet.PortletSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentFactory;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.Node;
import org.dom4j.XPath;
import org.dom4j.io.SAXReader;

/**
 * <a href="JournalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class JournalUtil {

	public static final int MAX_STACK_SIZE = 20;

	public static final String XML_INDENT = "  ";

	public static void addRecentArticle(
		PortletRequest req, JournalArticle article) {

		if (article != null) {
			Stack stack = getRecentArticles(req);

			stack.push(article);
		}
	}

	public static void addRecentStructure(
		PortletRequest req, JournalStructure structure) {

		if (structure != null) {
			Stack stack = getRecentStructures(req);

			stack.push(structure);
		}
	}

	public static void addRecentTemplate(
		PortletRequest req, JournalTemplate template) {

		if (template != null) {
			Stack stack = getRecentTemplates(req);

			stack.push(template);
		}
	}

	public static void addReservedEl(
		Element root, Map tokens, String name, double value) {

		addReservedEl(root, tokens, name, String.valueOf(value));
	}

	public static void addReservedEl(
		Element root, Map tokens, String name, Date value) {

		addReservedEl(root, tokens, name, Time.getRFC822(value));
	}

	public static void addReservedEl(
		Element root, Map tokens, String name, String value) {

		// XML

		if (root != null) {
			DocumentFactory docFactory = DocumentFactory.getInstance();

			Element dynamicEl = docFactory.createElement("dynamic-element");

			dynamicEl.add(docFactory.createAttribute(dynamicEl, "name", name));
			dynamicEl.add(
				docFactory.createAttribute(dynamicEl, "type", "text"));

			Element dynamicContent =
				docFactory.createElement("dynamic-content");

			//dynamicContent.setText("<![CDATA[" + value + "]]>");
			dynamicContent.setText(value);

			dynamicEl.add(dynamicContent);

			root.add(dynamicEl);
		}

		// Tokens

		tokens.put(
			StringUtil.replace(name, StringPool.DASH, StringPool.UNDERLINE),
			value);
	}

	public static void addAllReservedEls(
		Element root, Map tokens, JournalArticle article) {

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_ID,
			article.getArticleId());

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_VERSION,
			article.getVersion());

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_TITLE,
			article.getTitle());

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_DESCRIPTION,
			article.getDescription());

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_TYPE,
			article.getType());

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_CREATE_DATE,
			article.getCreateDate());

		JournalUtil.addReservedEl(
			root, tokens,
			JournalStructureImpl.RESERVED_ARTICLE_MODIFIED_DATE,
			article.getModifiedDate());

		if (article.getDisplayDate() != null) {
			JournalUtil.addReservedEl(
				root, tokens,
				JournalStructureImpl.RESERVED_ARTICLE_DISPLAY_DATE,
				article.getDisplayDate());
		}

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_SMALL_IMAGE_URL,
			article.getSmallImageURL());

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_AUTHOR_ID,
			String.valueOf(article.getUserId()));

		String userName = StringPool.BLANK;
		String userEmailAddress = StringPool.BLANK;
		String userComments = StringPool.BLANK;
		String userJobTitle = StringPool.BLANK;

		User user = null;

		try {
			user = UserLocalServiceUtil.getUserById(article.getUserId());

			userName = user.getFullName();
			userEmailAddress = user.getEmailAddress();
			userComments = user.getComments();

			Contact contact = user.getContact();

			if (contact != null) {
				userJobTitle = contact.getJobTitle();
			}
		}
		catch (PortalException pe) {
		}
		catch (SystemException se) {
		}

		JournalUtil.addReservedEl(
			root, tokens, JournalStructureImpl.RESERVED_ARTICLE_AUTHOR_NAME,
			userName);

		JournalUtil.addReservedEl(
			root, tokens,
			JournalStructureImpl.RESERVED_ARTICLE_AUTHOR_EMAIL_ADDRESS,
			userEmailAddress);

		JournalUtil.addReservedEl(
			root, tokens,
			JournalStructureImpl.RESERVED_ARTICLE_AUTHOR_COMMENTS,
			userComments);

		JournalUtil.addReservedEl(
			root, tokens,
			JournalStructureImpl.RESERVED_ARTICLE_AUTHOR_JOB_TITLE,
			userJobTitle);
	}

	public static String formatVM(String vm) {
		return vm;
	}

	public static String formatXML(String xml)
		throws DocumentException, IOException {

		// This is only supposed to format your xml, however, it will also
		// unwantingly change &#169; and other characters like it into their
		// respective readable versions

		xml = StringUtil.replace(xml, "&#", "[$SPECIAL_CHARACTER$]");

		xml = XMLFormatter.toString(xml, XML_INDENT);

		xml = StringUtil.replace(xml, "[$SPECIAL_CHARACTER$]", "&#");

		return xml;
	}

	public static String formatXML(Document doc)
		throws DocumentException, IOException {

		return XMLFormatter.toString(doc, XML_INDENT);
	}

	public static OrderByComparator getArticleOrderByComparator(
		String orderByCol, String orderByType) {

		boolean orderByAsc = false;

		if (orderByType.equals("asc")) {
			orderByAsc = true;
		}

		OrderByComparator orderByComparator = null;

		if (orderByCol.equals("create-date")) {
			orderByComparator = new ArticleCreateDateComparator(orderByAsc);
		}
		else if (orderByCol.equals("display-date")) {
			orderByComparator = new ArticleDisplayDateComparator(orderByAsc);
		}
		else if (orderByCol.equals("id")) {
			orderByComparator = new ArticleIDComparator(orderByAsc);
		}
		else if (orderByCol.equals("modified-date")) {
			orderByComparator = new ArticleModifiedDateComparator(orderByAsc);
		}
		else if (orderByCol.equals("review-date")) {
			orderByComparator = new ArticleReviewDateComparator(orderByAsc);
		}
		else if (orderByCol.equals("title")) {
			orderByComparator = new ArticleTitleComparator(orderByAsc);
		}
		else if (orderByCol.equals("version")) {
			orderByComparator = new ArticleModifiedDateComparator(orderByAsc);
		}

		return orderByComparator;
	}

	public static String getEmailFromAddress(PortletPreferences prefs) {
		String emailFromAddress = PropsUtil.get(
			PropsUtil.JOURNAL_EMAIL_FROM_ADDRESS);

		return prefs.getValue("email-from-address", emailFromAddress);
	}

	public static String getEmailFromName(PortletPreferences prefs) {
		String emailFromName = PropsUtil.get(
			PropsUtil.JOURNAL_EMAIL_FROM_NAME);

		return prefs.getValue("email-from-name", emailFromName);
	}

	public static boolean getEmailArticleApprovalDeniedEnabled(
		PortletPreferences prefs) {

		String emailArticleApprovalDeniedEnabled = prefs.getValue(
			"email-article-approval-denied-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalDeniedEnabled)) {
			return GetterUtil.getBoolean(emailArticleApprovalDeniedEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_DENIED_ENABLED));
		}
	}

	public static String getEmailArticleApprovalDeniedBody(
			PortletPreferences prefs)
		throws IOException {

		String emailArticleApprovalDeniedBody = prefs.getValue(
			"email-article-approval-denied-body", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalDeniedBody)) {
			return emailArticleApprovalDeniedBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_DENIED_BODY));
		}
	}

	public static String getEmailArticleApprovalDeniedSubject(
			PortletPreferences prefs)
		throws IOException {

		String emailArticleApprovalDeniedSubject = prefs.getValue(
			"email-article-approval-denied-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalDeniedSubject)) {
			return emailArticleApprovalDeniedSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_DENIED_SUBJECT));
		}
	}

	public static boolean getEmailArticleApprovalGrantedEnabled(
		PortletPreferences prefs) {

		String emailArticleApprovalGrantedEnabled = prefs.getValue(
			"email-article-approval-granted-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalGrantedEnabled)) {
			return GetterUtil.getBoolean(emailArticleApprovalGrantedEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_GRANTED_ENABLED));
		}
	}

	public static String getEmailArticleApprovalGrantedBody(
			PortletPreferences prefs)
		throws IOException {

		String emailArticleApprovalGrantedBody = prefs.getValue(
			"email-article-approval-granted-body", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalGrantedBody)) {
			return emailArticleApprovalGrantedBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_GRANTED_BODY));
		}
	}

	public static String getEmailArticleApprovalGrantedSubject(
			PortletPreferences prefs)
		throws IOException {

		String emailArticleApprovalGrantedSubject = prefs.getValue(
			"email-article-approval-granted-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalGrantedSubject)) {
			return emailArticleApprovalGrantedSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_GRANTED_SUBJECT));
		}
	}

	public static boolean getEmailArticleApprovalRequestedEnabled(
		PortletPreferences prefs) {

		String emailArticleApprovalRequestedEnabled = prefs.getValue(
			"email-article-approval-requested-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalRequestedEnabled)) {
			return GetterUtil.getBoolean(emailArticleApprovalRequestedEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_REQUESTED_ENABLED));
		}
	}

	public static String getEmailArticleApprovalRequestedBody(
			PortletPreferences prefs)
		throws IOException {

		String emailArticleApprovalRequestedBody = prefs.getValue(
			"email-article-approval-requested-body", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalRequestedBody)) {
			return emailArticleApprovalRequestedBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_REQUESTED_BODY));
		}
	}

	public static String getEmailArticleApprovalRequestedSubject(
			PortletPreferences prefs)
		throws IOException {

		String emailArticleApprovalRequestedSubject = prefs.getValue(
			"email-article-approval-requested-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleApprovalRequestedSubject)) {
			return emailArticleApprovalRequestedSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_APPROVAL_REQUESTED_SUBJECT));
		}
	}

	public static boolean getEmailArticleReviewEnabled(
		PortletPreferences prefs) {

		String emailArticleReviewEnabled = prefs.getValue(
			"email-article-review-enabled", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleReviewEnabled)) {
			return GetterUtil.getBoolean(emailArticleReviewEnabled);
		}
		else {
			return GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_REVIEW_ENABLED));
		}
	}

	public static String getEmailArticleReviewBody(PortletPreferences prefs)
		throws IOException {

		String emailArticleReviewBody = prefs.getValue(
			"email-article-review-body", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleReviewBody)) {
			return emailArticleReviewBody;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_REVIEW_BODY));
		}
	}

	public static String getEmailArticleReviewSubject(PortletPreferences prefs)
		throws IOException {

		String emailArticleReviewSubject = prefs.getValue(
			"email-article-review-subject", StringPool.BLANK);

		if (Validator.isNotNull(emailArticleReviewSubject)) {
			return emailArticleReviewSubject;
		}
		else {
			return ContentUtil.get(PropsUtil.get(
				PropsUtil.JOURNAL_EMAIL_ARTICLE_REVIEW_SUBJECT));
		}
	}

	public static Stack getRecentArticles(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Stack recentArticles =
			(Stack)ses.getAttribute(WebKeys.JOURNAL_RECENT_ARTICLES);

		if (recentArticles == null) {
			recentArticles = new FiniteUniqueStack(MAX_STACK_SIZE);

			ses.setAttribute(WebKeys.JOURNAL_RECENT_ARTICLES, recentArticles);
		}

		return recentArticles;
	}

	public static Stack getRecentStructures(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Stack recentStructures =
			(Stack)ses.getAttribute(WebKeys.JOURNAL_RECENT_STRUCTURES);

		if (recentStructures == null) {
			recentStructures = new FiniteUniqueStack(MAX_STACK_SIZE);

			ses.setAttribute(
				WebKeys.JOURNAL_RECENT_STRUCTURES, recentStructures);
		}

		return recentStructures;
	}

	public static Stack getRecentTemplates(PortletRequest req) {
		PortletSession ses = req.getPortletSession();

		Stack recentTemplates =
			(Stack)ses.getAttribute(WebKeys.JOURNAL_RECENT_TEMPLATES);

		if (recentTemplates == null) {
			recentTemplates = new FiniteUniqueStack(MAX_STACK_SIZE);

			ses.setAttribute(WebKeys.JOURNAL_RECENT_TEMPLATES, recentTemplates);
		}

		return recentTemplates;
	}

	public static String getTemplateScript(
			long groupId, String templateId, Map tokens, String languageId)
		throws PortalException, SystemException {

		return getTemplateScript(groupId, templateId, tokens, languageId, true);
	}

	public static String getTemplateScript(
			long groupId, String templateId, Map tokens, String languageId,
			boolean transform)
		throws PortalException, SystemException {

		JournalTemplate template = JournalTemplateLocalServiceUtil.getTemplate(
			groupId, templateId);

		return getTemplateScript(template, tokens, languageId, transform);
	}

	public static String getTemplateScript(
			JournalTemplate template, Map tokens, String languageId,
			boolean transform)
		throws PortalException, SystemException {

		String script = template.getXsl();

		if (transform) {

			// Listeners

			String[] listeners =
				PropsUtil.getArray(PropsUtil.JOURNAL_TRANSFORMER_LISTENER);

			for (int i = 0; i < listeners.length; i++) {
				TransformerListener listener = null;

				try {
					listener =
						(TransformerListener)Class.forName(
							listeners[i]).newInstance();

					listener.setTemplateDriven(true);
					listener.setLanguageId(languageId);
					listener.setTokens(tokens);
				}
				catch (Exception e) {
					e.printStackTrace();
				}

				// Modify transform script

				if (listener != null) {
					script = listener.onScript(script);
				}
			}
		}

		return script;
	}

	public static Map getTokens(long groupId, ThemeDisplay themeDisplay) {
		Map tokens = CollectionFactory.getHashMap();

		if (themeDisplay == null) {
			return tokens;
		}

		tokens.put("cdn_host", themeDisplay.getCDNHost());
		tokens.put("company_id", String.valueOf(themeDisplay.getCompanyId()));
		tokens.put("group_id", String.valueOf(groupId));
		tokens.put("cms_url", themeDisplay.getPathContext() + "/cms/servlet");
		tokens.put("image_path", themeDisplay.getPathImage());
		tokens.put(
			"friendly_url_private_group",
			themeDisplay.getPathFriendlyURLPrivateGroup());
		tokens.put(
			"friendly_url_private_user",
			themeDisplay.getPathFriendlyURLPrivateUser());
		tokens.put(
			"friendly_url_public", themeDisplay.getPathFriendlyURLPublic());
		tokens.put("main_path", themeDisplay.getPathMain());
		tokens.put("portal_ctx", themeDisplay.getPathContext());
		tokens.put(
			"portal_url", Http.removeProtocol(themeDisplay.getURLPortal()));
		tokens.put("root_path", themeDisplay.getPathContext());
		tokens.put("theme_image_path", themeDisplay.getPathThemeImages());

		// Deprecated tokens

		tokens.put("friendly_url", themeDisplay.getPathFriendlyURLPublic());
		tokens.put(
			"friendly_url_private",
			themeDisplay.getPathFriendlyURLPrivateGroup());
		tokens.put("page_url", themeDisplay.getPathFriendlyURLPublic());

		return tokens;
	}

	public static String mergeLocaleContent(
		String curContent, String newContent, String xsd) {

		try {
			SAXReader reader = new SAXReader();

			Document curContentDoc = reader.read(new StringReader(curContent));
			Document newContentDoc = reader.read(new StringReader(newContent));
			Document xsdDoc = reader.read(new StringReader(xsd));

			Element curContentRoot = curContentDoc.getRootElement();
			Element newContentRoot = newContentDoc.getRootElement();
			Element xsdRoot = xsdDoc.getRootElement();

			curContentRoot.addAttribute(
				"default-locale",
				newContentRoot.attributeValue("default-locale"));
			curContentRoot.addAttribute(
				"available-locales",
				newContentRoot.attributeValue("available-locales"));

			Stack path = new Stack();

			path.push(xsdRoot.getName());

			_mergeLocaleContent(
				path, curContentDoc, newContentDoc, xsdRoot,
				LocaleUtil.toLanguageId(LocaleUtil.getDefault()));

			curContent = formatXML(curContentDoc);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return curContent;
	}

	public static String removeArticleLocale(
		String content, String languageId) {

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(content));

			Element root = doc.getRootElement();

			String availableLocales = root.attributeValue("available-locales");

			if (availableLocales == null) {
				return content;
			}

			availableLocales = StringUtil.remove(availableLocales, languageId);

			if (availableLocales.endsWith(",")) {
				availableLocales = availableLocales.substring(
					0, availableLocales.length() - 1);
			}

			root.addAttribute("available-locales", availableLocales);

			removeArticleLocale(root, languageId);

			content = formatXML(doc);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return content;
	}

	public static void removeArticleLocale(Element el, String languageId)
		throws SystemException {

		Iterator itr1 = el.elements("dynamic-element").iterator();

		while (itr1.hasNext()) {
			Element dynamicEl = (Element)itr1.next();

			Iterator itr2 = dynamicEl.elements("dynamic-content").iterator();

			while (itr2.hasNext()) {
				Element dynamicContentEl = (Element)itr2.next();

				String curLanguageId = GetterUtil.getString(
					dynamicContentEl.attributeValue("language-id"));

				if (curLanguageId.equals(languageId)) {
					long id = GetterUtil.getLong(
						dynamicContentEl.attributeValue("id"));

					if (id > 0) {
						ImageLocalUtil.deleteImage(id);
					}

					dynamicContentEl.detach();
				}
			}

			removeArticleLocale(dynamicEl, languageId);
		}
	}

	public static String removeOldContent(String content, String xsd) {
		try {
			SAXReader reader = new SAXReader();

			Document contentDoc = reader.read(new StringReader(content));
			Document xsdDoc = reader.read(new StringReader(xsd));

			Element contentRoot = contentDoc.getRootElement();

			Stack path = new Stack();

			path.push(contentRoot.getName());

			_removeOldContent(path, contentRoot, xsdDoc);

			content = formatXML(contentDoc);
		}
		catch (Exception e) {
			_log.error(e);
		}

		return content;
	}

	public static void removeRecentArticle(
		PortletRequest req, String articleId) {

		Stack stack = getRecentArticles(req);

		Iterator itr = stack.iterator();

		while (itr.hasNext()) {
			JournalArticle journalArticle = (JournalArticle)itr.next();

			if (journalArticle.getArticleId().equals(articleId)) {
				itr.remove();

				break;
			}
		}
	}

	public static void removeRecentStructure(
		PortletRequest req, String structureId) {

		Stack stack = getRecentStructures(req);

		Iterator itr = stack.iterator();

		while (itr.hasNext()) {
			JournalStructure journalStructure = (JournalStructure)itr.next();

			if (journalStructure.getStructureId().equals(structureId)) {
				itr.remove();

				break;
			}
		}
	}

	public static void removeRecentTemplate(
		PortletRequest req, String templateId) {

		Stack stack = getRecentTemplates(req);

		Iterator itr = stack.iterator();

		while (itr.hasNext()) {
			JournalTemplate journalTemplate = (JournalTemplate)itr.next();

			if (journalTemplate.getTemplateId().equals(templateId)) {
				itr.remove();

				break;
			}
		}
	}

	public static String transform(
			Map tokens, String languageId, String xml, String script,
			String langType)
		throws TransformException, UnsupportedEncodingException {

		// Setup Listeners

		if (_log.isDebugEnabled()) {
			_log.debug("Language " + languageId);
		}

		if (_logTokens.isDebugEnabled()) {
			String tokensString = PropertiesUtil.list(tokens);

			_logTokens.debug(tokensString);
		}

		if (_logTransformBefore.isDebugEnabled()) {
			_logTransformBefore.debug(xml);
		}

		List listenersList = new ArrayList();

		String[] listeners = PropsUtil.getArray(
			PropsUtil.JOURNAL_TRANSFORMER_LISTENER);

		for (int i = 0; i < listeners.length; i++) {
			TransformerListener listener = null;

			try {
				if (_log.isDebugEnabled()) {
					_log.debug("Instantiate listener " + listeners[i]);
				}

				boolean templateDriven = Validator.isNotNull(langType);

				listener = (TransformerListener)Class.forName(
					listeners[i]).newInstance();

				listener.setTemplateDriven(templateDriven);
				listener.setLanguageId(languageId);
				listener.setTokens(tokens);

				listenersList.add(listener);
			}
			catch (Exception e) {
				_log.error(e, e);
			}

			// Modify XML

			if (_logXmlBeforeListener.isDebugEnabled()) {
				_logXmlBeforeListener.debug(xml);
			}

			if (listener != null) {
				xml = listener.onXml(xml);

				if (_logXmlAfterListener.isDebugEnabled()) {
					_logXmlAfterListener.debug(xml);
				}
			}

			// Modify script

			if (_logScriptBeforeListener.isDebugEnabled()) {
				_logScriptBeforeListener.debug(script);
			}

			if (listener != null) {
				script = listener.onScript(script);

				if (_logScriptAfterListener.isDebugEnabled()) {
					_logScriptAfterListener.debug(script);
				}
			}
		}

		// Transform

		String output = null;

		if (Validator.isNull(langType)) {
			output = xml;
		}
		else if (langType.equals(JournalTemplateImpl.LANG_TYPE_VM)) {
			output = JournalVmUtil.transform(tokens, languageId, xml, script);
		}
		else if (langType.equals(JournalTemplateImpl.LANG_TYPE_XSL)) {
			output = JournalXslUtil.transform(tokens, languageId, xml, script);
		}

		// Postprocess output

		for (int i = 0; i < listenersList.size(); i++) {
			TransformerListener listener =
				(TransformerListener)listenersList.get(i);

			// Modify output

			if (_logOutputBeforeListener.isDebugEnabled()) {
				_logOutputBeforeListener.debug(output);
			}

			output = listener.onOutput(output);

			if (_logOutputAfterListener.isDebugEnabled()) {
				_logOutputAfterListener.debug(output);
			}
		}

		if (_logTransfromAfter.isDebugEnabled()) {
			_logTransfromAfter.debug(output);
		}

		return output;
	}

	private static void _mergeLocaleContent(
			Stack path, Document curDoc, Document newDoc, Element xsdEl,
			String defaultLocale)
		throws SystemException {

		String elPath = "";

		for (int i = 0; i < path.size(); i++) {
			elPath += "/" + path.elementAt(i);
		}

		for (int i = 0; i < xsdEl.nodeCount(); i++) {
			Node xsdNode = xsdEl.node(i);

			if ((xsdNode instanceof Element) &&
				(xsdNode.getName().equals("dynamic-element"))) {

				_mergeLocaleContent(
					path, curDoc, newDoc, (Element)xsdNode, defaultLocale,
					elPath);
			}
		}
	}

	private static void _mergeLocaleContent(
			Stack path, Document curDoc, Document newDoc, Element xsdEl,
			String defaultLocale, String elPath)
		throws SystemException {

		String name = xsdEl.attributeValue("name");

		String localPath = "dynamic-element[@name='" + name + "']";

		String fullPath = elPath + "/" + localPath;

		XPath xPathSelector = DocumentHelper.createXPath(fullPath);

		List curElements = xPathSelector.selectNodes(curDoc);

		Element newEl = (Element)xPathSelector.selectNodes(newDoc).get(0);

		if (curElements.size() > 0) {
			Element curEl = (Element)curElements.get(0);

			List curDynamicContents = curEl.elements("dynamic-content");

			Element newContentEl = newEl.element("dynamic-content");

			String newContentLanguageId = newContentEl.attributeValue(
				"language-id", StringPool.BLANK);

			if (newContentLanguageId.equals(StringPool.BLANK)) {
				for (int k = curDynamicContents.size() - 1; k >= 0 ; k--) {
					Element curContentEl = (Element)curDynamicContents.get(k);

					String curContentLanguageId = curContentEl.attributeValue(
						"language-id", StringPool.BLANK);

					if ((curEl.attributeValue("type").equals("image")) &&
						(!curContentLanguageId.equals(defaultLocale) &&
						 !curContentLanguageId.equals(StringPool.BLANK))) {

						long id = GetterUtil.getLong(
							curContentEl.attributeValue("id"));

						ImageLocalUtil.deleteImage(id);
					}

					curContentEl.detach();
				}

				curEl.content().add(newContentEl.createCopy());
			}
			else {
				boolean match = false;

				for (int k = curDynamicContents.size() - 1; k >= 0 ; k--) {
					Element curContentEl = (Element)curDynamicContents.get(k);

					String curContentLanguageId = curContentEl.attributeValue(
						"language-id", StringPool.BLANK);

					if ((newContentLanguageId.equals(curContentLanguageId)) ||
						(newContentLanguageId.equals(defaultLocale) &&
						 curContentLanguageId.equals(StringPool.BLANK))) {

						curContentEl.detach();

						curEl.content().add(k, newContentEl.createCopy());

						match = true;
					}

					if (curContentLanguageId.equals(StringPool.BLANK)) {
						curContentEl.addAttribute("language-id", defaultLocale);
					}
				}

				if (!match) {
					curEl.content().add(newContentEl.createCopy());
				}
			}
		}
		else {
			xPathSelector = DocumentHelper.createXPath(elPath);

			Element parentEl =
				(Element)xPathSelector.selectNodes(curDoc).get(0);

			parentEl.content().add(newEl.createCopy());
		}

		String type = xsdEl.attributeValue("type", StringPool.BLANK);

		if (!type.equals("list") && !type.equals("multi-list")) {
			path.push(localPath);

			_mergeLocaleContent(path, curDoc, newDoc, xsdEl, defaultLocale);

			path.pop();
		}
	}

	private static void _removeOldContent(
			Stack path, Element contentEl, Document xsdDoc)
		throws SystemException {

		String elPath = "";

		for (int i = 0; i < path.size(); i++) {
			elPath += "/" + path.elementAt(i);
		}

		for (int i = 0; i < contentEl.nodeCount(); i++) {
			Node contentNode = contentEl.node(i);

			if (contentNode instanceof Element) {
				_removeOldContent(path, (Element)contentNode, xsdDoc, elPath);
			}
		}
	}

	private static void _removeOldContent(
			Stack path, Element contentEl, Document xsdDoc, String elPath)
		throws SystemException {

		String name = contentEl.attributeValue("name");

		if (Validator.isNull(name)) {
			return;
		}

		String localPath = "dynamic-element[@name='" + name + "']";

		String fullPath = elPath + "/" + localPath;

		XPath xPathSelector = DocumentHelper.createXPath(fullPath);

		List curElements = xPathSelector.selectNodes(xsdDoc);

		if (curElements.size() == 0) {
			contentEl.detach();
		}

		path.push(localPath);

		_removeOldContent(path, contentEl, xsdDoc);

		path.pop();
	}

	private static Log _log = LogFactory.getLog(JournalUtil.class);

	private static Log _logOutputAfterListener = LogFactory.getLog(
		JournalUtil.class.getName() + ".OutputAfterListener");

	private static Log _logOutputBeforeListener = LogFactory.getLog(
		JournalUtil.class.getName() + ".OutputBeforeListener");

	private static Log _logScriptAfterListener = LogFactory.getLog(
		JournalUtil.class.getName() + ".ScriptAfterListener");

	private static Log _logScriptBeforeListener = LogFactory.getLog(
		JournalUtil.class.getName() + ".ScriptBeforeListener");

	private static Log _logTransfromAfter = LogFactory.getLog(
		JournalUtil.class.getName() + ".TransformAfter");

	private static Log _logTransformBefore = LogFactory.getLog(
		JournalUtil.class.getName() + ".BeforeTransform");

	private static Log _logTokens = LogFactory.getLog(
		JournalUtil.class.getName() + ".Tokens");

	private static Log _logXmlAfterListener = LogFactory.getLog(
		JournalUtil.class.getName() + ".XmlAfterListener");

	private static Log _logXmlBeforeListener = LogFactory.getLog(
		JournalUtil.class.getName() + ".XmlBeforeListener");

}