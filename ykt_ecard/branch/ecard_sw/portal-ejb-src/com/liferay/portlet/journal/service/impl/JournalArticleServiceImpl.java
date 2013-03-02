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

package com.liferay.portlet.journal.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.journal.ArticleContentException;
import com.liferay.portlet.journal.ArticleDisplayDateException;
import com.liferay.portlet.journal.ArticleExpirationDateException;
import com.liferay.portlet.journal.ArticleIdException;
import com.liferay.portlet.journal.ArticleTitleException;
import com.liferay.portlet.journal.DuplicateArticleIdException;
import com.liferay.portlet.journal.NoSuchArticleException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.persistence.JournalArticlePK;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.journal.service.persistence.JournalStructureUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplateUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleService;
import com.liferay.portlet.journal.util.Indexer;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.LocaleUtil;
import com.liferay.util.MathUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lucene.Hits;

import java.io.IOException;
import java.io.StringReader;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.WhitespaceAnalyzer;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.Sort;
import org.apache.lucene.search.SortField;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="JournalArticleServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 *
 */
public class JournalArticleServiceImpl
	extends PrincipalBean implements JournalArticleService {

	// Business methods

	public JournalArticle addArticle(
			String articleId, boolean autoArticleId, String portletId,
			String groupId, String title, String content, String type,
			String structureId, String templateId, int displayMonth,
			int displayDay, int displayYear, int expMonth, int expDay,
			int expYear, boolean neverExpires, String articleURL, Map images)
		throws PortalException, SystemException {

		articleId = articleId.trim().toUpperCase();

		_validate(
			articleId, autoArticleId, title, content, structureId, templateId,
			displayMonth, displayDay, displayYear, expMonth, expDay, expYear,
			neverExpires);

		User user = getUser();

		if (autoArticleId) {
			articleId = Long.toString(CounterServiceUtil.increment(
				JournalArticle.class.getName()));
		}

		JournalArticlePK pk = new JournalArticlePK(
			articleId, JournalArticle.DEFAULT_VERSION);

		JournalArticle article = JournalArticleUtil.create(pk);

		Date now = new Date();

		content = _format(
			articleId, pk.getVersion(), false, user.getCompanyId(), content,
			structureId, images);

		Date displayDate = PortalUtil.getDate(
			displayMonth, displayDay, displayYear,
			new ArticleDisplayDateException());

		Date expirationDate = null;
		if (!neverExpires) {
			Calendar expCal = new GregorianCalendar(
				user.getTimeZone(), user.getLocale());
			expCal.set(Calendar.MONTH, expMonth);
			expCal.set(Calendar.DATE, expDay);
			expCal.set(Calendar.YEAR, expYear);

			expirationDate = expCal.getTime();
		}

		article.setPortletId(portletId);
		article.setGroupId(groupId);
		article.setCompanyId(user.getCompanyId());
		article.setUserId(user.getUserId());
		article.setUserName(user.getFullName());
		article.setCreateDate(now);
		article.setModifiedDate(now);
		article.setTitle(title);
		article.setContent(content);
		int i = content.length();
		article.setType(type);
		article.setStructureId(structureId);
		article.setTemplateId(templateId);
		article.setDisplayDate(displayDate);
		article.setExpirationDate(expirationDate);
		article.setApproved(false);

		JournalArticleUtil.update(article);

		// Send email

		articleURL =
			articleURL + "&article_id=" + Http.encodeURL(pk.getArticleId()) +
				"&article_version=" + pk.getVersion();

		JournalArticleLocalServiceUtil.sendEmail(pk, "requested", articleURL);

		return article;
	}

	public JournalArticle approveArticle(String articleId, String articleURL)
		throws PortalException, SystemException {

		JournalArticlePK pk = new JournalArticlePK(
			articleId, getLatestVersion(articleId));

		if (!hasAdmin() && !hasEditor()) {
			throw new PrincipalException();
		}

		User user = getUser();

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		article.setModifiedDate(new Date());
		article.setApproved(true);
		article.setApprovedByUserId(user.getUserId());
		article.setApprovedByUserName(user.getFullName());

		JournalArticleUtil.update(article);

		// Only one article may be approved for publication at a time

		List articles = JournalArticleUtil.findByArticleId(articleId);

		for (int i = 1; i < articles.size(); i++) {
			JournalArticle curArticle = (JournalArticle)articles.get(i);

			curArticle.setApproved(false);

			JournalArticleUtil.update(curArticle);
		}

		// Send email

		articleURL =
			articleURL + "&article_id=" + Http.encodeURL(pk.getArticleId()) +
				"&article_version=" + pk.getVersion();

		JournalArticleLocalServiceUtil.sendEmail(pk, "granted", articleURL);

		// Update lucene

		try {
			Indexer.updateArticle(
				article.getCompanyId(), article.getPortletId(),
				article.getGroupId(), article.getArticleId(),
				article.getVersion(), article.getTitle(), article.getContent(),
				article.getType(), article.getDisplayDate());
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return article;
	}

	public void checkArticles() throws PortalException, SystemException {
		List articles = JournalArticleUtil.findAll();

		Date now = new Date();

		for (int i = 0; i < articles.size(); i++) {
			JournalArticle article = (JournalArticle)articles.get(i);

			if (article.getExpirationDate() != null &&
				article.getExpirationDate().before(now)) {

				JournalArticleLocalServiceUtil.deleteArticle(article, false);
			}
		}
	}

	public void deleteArticle(String articleId, double version)
		throws PortalException, SystemException {

		JournalArticlePK pk = new JournalArticlePK(articleId, version);

		if (!hasAdmin() && !hasEditor()) {
			throw new PrincipalException();
		}

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		boolean sendEmail = false;

		if (!article.isApproved() &&
			isLatestVersion(article.getArticleId(), article.getVersion())) {

			sendEmail = true;
		}

		JournalArticleLocalServiceUtil.deleteArticle(
			articleId, version, sendEmail);
	}

	public JournalArticle getArticle(String articleId)
		throws PortalException, SystemException {

		// Get the latest article that is approved, if none are approved, get
		// the latest unapproved article

		try {
			return getLatestArticle(articleId, Boolean.TRUE);
		}
		catch (NoSuchArticleException nsae) {
			return getLatestArticle(articleId, Boolean.FALSE);
		}
	}

	public JournalArticle getArticle(String articleId, double version)
		throws PortalException, SystemException {

		JournalArticlePK pk = new JournalArticlePK(articleId, version);

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		if (!article.isApproved()) {
			if (!hasAdmin() && !hasEditor() &&
				!article.getUserId().equals(getUserId())) {

				throw new PrincipalException();
			}
		}

		return article;
	}

	public String getArticleContent(
			String articleId, String languageId, String rootPath)
		throws PortalException, SystemException {

		JournalArticle article = getLatestArticle(articleId, Boolean.TRUE);

		return getArticleContent(
			articleId, article.getVersion(), languageId, rootPath);
	}

	public String getArticleContent(
			String articleId, double version, String languageId,
			String rootPath)
		throws PortalException, SystemException {

		JournalArticlePK pk = new JournalArticlePK(articleId, version);

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		if (!article.isTemplateDriven()) {
			return article.getContent();
		}

		JournalTemplate template =
			JournalTemplateUtil.findByPrimaryKey(article.getTemplateId());

		String xml = article.getContent();
		String xsl = template.getXsl();

		Map tokens = JournalUtil.getTokens(article.getCompanyId(), rootPath);

		try {
			SAXReader reader = new SAXReader();

			Document doc = reader.read(new StringReader(xml));

			Element root = doc.getRootElement();

			JournalUtil.addReservedEl(
				root, tokens, JournalStructure.RESERVED_ARTICLE_ID,
				article.getArticleId());

			JournalUtil.addReservedEl(
				root, tokens, JournalStructure.RESERVED_ARTICLE_VERSION,
				Double.toString(article.getVersion()));

			JournalUtil.addReservedEl(
				root, tokens, JournalStructure.RESERVED_ARTICLE_TITLE,
				article.getTitle());

			JournalUtil.addReservedEl(
				root, tokens, JournalStructure.RESERVED_ARTICLE_CREATE_DATE,
				article.getCreateDate().toString());

			JournalUtil.addReservedEl(
				root, tokens, JournalStructure.RESERVED_ARTICLE_MODIFIED_DATE,
				article.getModifiedDate().toString());

			if (article.getDisplayDate() != null) {
				JournalUtil.addReservedEl(
					root, tokens,
					JournalStructure.RESERVED_ARTICLE_DISPLAY_DATE,
					article.getDisplayDate().toString());
			}

			xml = JournalUtil.formatXML(doc);
		}
		catch (DocumentException de) {
			throw new SystemException(de);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}

		try {
			_log.debug(
				"Transforming " + articleId + " " + version + " " + languageId);

			return JournalUtil.transform(tokens, languageId, xml, xsl);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public List getArticlesByCompany(
			String portletId, String groupId, String companyId)
		throws SystemException {

		return JournalArticleUtil.findByP_G_C(portletId, groupId, companyId);
	}

	public List getArticlesByCompany(
			String portletId, String groupId, String companyId, String type,
			boolean approved)
		throws SystemException {

		if (Validator.isNull(type)) {
			return JournalArticleUtil.findByP_G_C_A(
				portletId, groupId, companyId, approved);
		}
		else {
			return JournalArticleUtil.findByP_G_C_T_A(
				portletId, groupId, companyId, type, approved);
		}
	}

	public List getArticlesByCompany(
			String portletId, String groupId, String companyId, String type,
			boolean approved, int begin, int end)
		throws SystemException {

		if (Validator.isNull(type)) {
			return JournalArticleUtil.findByP_G_C_A(
				portletId, groupId, companyId, approved, begin, end);
		}
		else {
			return JournalArticleUtil.findByP_G_C_T_A(
				portletId, groupId, companyId, type, approved, begin, end);
		}
	}

	public List getArticlesByCompany(
			String portletId, String groupId, String companyId, String type,
			boolean approved, int begin, int end, OrderByComparator obc)
		throws SystemException {

		if (Validator.isNull(type)) {
			return JournalArticleUtil.findByP_G_C_A(
				portletId, groupId, companyId, approved, begin, end, obc);
		}
		else {
			return JournalArticleUtil.findByP_G_C_T_A(
				portletId, groupId, companyId, type, approved, begin, end, obc);
		}
	}

	public int getArticlesByCompanySize(
			String portletId, String groupId, String companyId, String type,
			boolean approved)
		throws SystemException {

		if (Validator.isNull(type)) {
			return JournalArticleUtil.countByP_G_C_A(
				portletId, groupId, companyId, approved);
		}
		else {
			return JournalArticleUtil.countByP_G_C_T_A(
				portletId, groupId, companyId, type, approved);
		}
	}

	public List getArticlesByStructure(String structureId, int begin, int end)
		throws SystemException {

		return JournalArticleUtil.findByStructureId(structureId, begin, end);
	}

	public int getArticlesByStructureSize(String structureId)
		throws SystemException {

		return JournalArticleUtil.countByStructureId(structureId);
	}

	public List getArticlesByTemplate(String templateId)
		throws SystemException {

		return JournalArticleUtil.findByTemplateId(templateId);
	}

	public List getArticlesByTemplate(String templateId, int begin, int end)
		throws SystemException {

		return JournalArticleUtil.findByTemplateId(templateId, begin, end);
	}

	public int getArticlesByTemplateSize(String templateId)
		throws SystemException {

		return JournalArticleUtil.countByTemplateId(templateId);
	}

	public List getArticlesByUser(
			String portletId, String groupId, String type, boolean approved,
			int begin, int end)
		throws PortalException, SystemException {

		if (Validator.isNull(type)) {
			return JournalArticleUtil.findByP_G_U_A(
				portletId, groupId, getUserId(), approved, begin, end);
		}
		else {
			return JournalArticleUtil.findByP_G_U_T_A(
				portletId, groupId, getUserId(), type, approved, begin, end);
		}
	}

	public int getArticlesByUserSize(
			String portletId, String groupId, String type, boolean approved)
		throws PortalException, SystemException {

		if (Validator.isNull(type)) {
			return JournalArticleUtil.countByP_G_U_A(
				portletId, groupId, getUserId(), approved);
		}
		else {
			return JournalArticleUtil.countByP_G_U_T_A(
				portletId, groupId, getUserId(), type, approved);
		}
	}

	public JournalArticle getLatestArticle(String articleId)
		throws PortalException, SystemException {

		return getLatestArticle(articleId, null);
	}

	public JournalArticle getLatestArticle(String articleId, Boolean approved)
		throws PortalException, SystemException {

		List articles = null;

		if (approved == null) {
			articles = JournalArticleUtil.findByArticleId(articleId, 0, 1);
		}
		else {
			articles = JournalArticleUtil.findByA_A(
				articleId, approved.booleanValue(), 0, 1);
		}

		if (articles.size() == 0) {
			throw new NoSuchArticleException();
		}

		JournalArticle article = (JournalArticle)articles.get(0);

		if (!article.isApproved()) {
			if (!hasAdmin() && !hasEditor() &&
				!article.getUserId().equals(getUserId())) {

				throw new PrincipalException();
			}
		}

		return article;
	}

	public double getLatestVersion(String articleId)
		throws PortalException, SystemException {

		return getLatestArticle(articleId).getVersion();
	}

	public boolean isLatestVersion(String articleId, double version)
		throws PortalException, SystemException {

		if (getLatestVersion(articleId) == version) {
			return true;
		}
		else {
			return false;
		}
	}

	public void reIndex(String[] ids) throws SystemException {
		try {
			String companyId = ids[0];

			Iterator itr = JournalArticleUtil.findByCompanyId(
				companyId).iterator();

			while (itr.hasNext()) {
				JournalArticle article = (JournalArticle)itr.next();

				String portletId = article.getPortletId();
				String groupId = article.getGroupId();
				String articleId = article.getArticleId();
				double version = article.getVersion();
				String title = article.getTitle();
				String content = article.getContent();
				String type = article.getType();
				Date displayDate = article.getDisplayDate();

				if (article.isApproved()) {
					try {
						Indexer.addArticle(
							companyId, portletId, groupId, articleId, version,
							title, content, type, displayDate);
					}
					catch (Exception e1) {

						// Continue indexing even if one article fails

						_log.error(e1.getMessage());
					}
				}
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e2) {
			throw new SystemException(e2);
		}
	}

	public Hits search(
			String companyId, String portletId, String groupId, String title,
			String content, String type)
		throws SystemException {

		try {
			Hits hits = new Hits();

			if ((Validator.isNull(title)) && (Validator.isNull(content)) &&
				(Validator.isNull(type))) {

				return hits;
			}

			BooleanQuery booleanQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.PORTLET_ID, portletId);
			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.GROUP_ID, groupId);

			LuceneUtil.addTerm(booleanQuery, LuceneFields.TITLE, title);
			LuceneUtil.addTerm(booleanQuery, LuceneFields.CONTENT, content);

			if (Validator.isNotNull(type)) {
				LuceneUtil.addRequiredTerm(booleanQuery, "type", type);
			}

			Searcher searcher = LuceneUtil.getSearcher(companyId);

			Query query = QueryParser.parse(
				booleanQuery.toString(), LuceneFields.CONTENT,
				new WhitespaceAnalyzer());

			Sort sort = new Sort(new SortField("displayDate", true));

			hits.recordHits(searcher.search(query, sort));

			return hits;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (ParseException pe) {
			throw new SystemException(pe);
		}
	}

	public JournalArticle updateArticle(
			String articleId, boolean incrementVersion, String title,
			String content, String type, String structureId, String templateId,
			int displayMonth, int displayDay, int displayYear, int expMonth,
			int expDay, int expYear, boolean neverExpires, String articleURL,
			Map images)
		throws PortalException, SystemException {

		articleId = articleId.trim().toUpperCase();

		_validate(
			title, content, structureId, templateId, displayMonth, displayDay,
			displayYear, expMonth, expDay, expYear, neverExpires);

		User user = getUser();

		JournalArticlePK oldPK = new JournalArticlePK(
			articleId, getLatestVersion(articleId));

		JournalArticle oldArticle = JournalArticleUtil.findByPrimaryKey(oldPK);

		JournalArticle article = null;

		Date now = new Date();

		if (incrementVersion) {
			JournalArticlePK pk = new JournalArticlePK(
				articleId, MathUtil.format(oldPK.getVersion() + 0.1, 1, 1));

			article = JournalArticleUtil.create(pk);

			article.setPortletId(oldArticle.getPortletId());
			article.setGroupId(oldArticle.getGroupId());
			article.setCompanyId(user.getCompanyId());
			article.setUserId(user.getUserId());
			article.setUserName(user.getFullName());
			article.setCreateDate(now);
		}
		else {
			article = oldArticle;
		}

		content = _format(
			articleId, article.getVersion(), incrementVersion,
			user.getCompanyId(), content, structureId, images);

		Date displayDate = PortalUtil.getDate(
			displayMonth, displayDay, displayYear,
			new ArticleDisplayDateException());

		Date expirationDate = null;
		if (!neverExpires) {
			Calendar expCal = new GregorianCalendar(
				user.getTimeZone(), user.getLocale());
			expCal.set(Calendar.MONTH, expMonth);
			expCal.set(Calendar.DATE, expDay);
			expCal.set(Calendar.YEAR, expYear);

			expirationDate = expCal.getTime();
		}

		boolean approved = oldArticle.isApproved();
		if (incrementVersion) {
			approved = false;
		}

		article.setModifiedDate(now);
		article.setTitle(title);
		article.setContent(content);
		article.setType(type);
		article.setStructureId(structureId);
		article.setTemplateId(templateId);
		article.setDisplayDate(displayDate);
		article.setExpirationDate(expirationDate);
		article.setApproved(approved);

		JournalArticleUtil.update(article);

		// Send email

		articleURL =
			articleURL + "&article_id=" +
				Http.encodeURL(article.getArticleId()) + "&article_version=" +
					article.getVersion();

		JournalArticleLocalServiceUtil.sendEmail(
			article.getPrimaryKey(), "requested", articleURL);

		// Update lucene

		try {
			if (article.isApproved()) {
				Indexer.updateArticle(
					article.getCompanyId(), article.getPortletId(),
					article.getGroupId(), article.getArticleId(),
					article.getVersion(), article.getTitle(),
					article.getContent(), article.getType(),
					article.getDisplayDate());
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return article;
	}

	// Permission methods

	public boolean hasAdmin() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.JOURNAL_ADMIN)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasAdmin(JournalArticlePK pk)
		throws PortalException, SystemException {

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		if (getUser().getCompanyId().equals(article.getCompanyId()) &&
			RoleServiceUtil.hasRole(getUserId(), Role.JOURNAL_ADMIN)) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasDesigner() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.JOURNAL_DESIGNER)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasEditor() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.JOURNAL_EDITOR)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasWriter() throws PortalException, SystemException {
		String userId = null;

		try {
			userId = getUserId();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if (RoleServiceUtil.hasRole(userId, Role.JOURNAL_WRITER)) {
			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private String _format(
		String articleId, double version, boolean incrementVersion,
		String companyId, String content, String structureId, Map images) {

		if (Validator.isNotNull(structureId)) {
			try {
				SAXReader reader = new SAXReader();

				Document doc = reader.read(new StringReader(content));

				Element root = doc.getRootElement();

				_format(
					articleId, version, incrementVersion, companyId, root,
					images);

				content = JournalUtil.formatXML(doc);
			}
			catch (DocumentException de) {
				de.printStackTrace();
			}
			catch (IOException ioe) {
				ioe.printStackTrace();
			}
		}

		return content;
	}

	private void _format(
		String articleId, double version, boolean incrementVersion,
		String companyId, Element root, Map images) {

		Iterator itr = root.elements().iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String elName = el.attributeValue("name", StringPool.BLANK);
			String elType = el.attributeValue("type", StringPool.BLANK);

			if (elType.equals("image")) {
				_formatImage(
					articleId, version, incrementVersion, companyId, el, elName,
					images);
			}
			else if (elType.equals("text_area")) {
				Element dynamicContent = el.element("dynamic-content");

				String text = dynamicContent.getText();

				if (Validator.isNull(Html.stripHtml(text))) {
					dynamicContent.setText(StringPool.BLANK);
				}
			}

			_format(
				articleId, version, incrementVersion, companyId, el, images);
		}
	}

	private void _formatImage(
		String articleId, double version, boolean incrementVersion,
		String companyId, Element el, String elName, Map images) {

		List imageContents = el.elements("dynamic-content");

		Iterator itr = imageContents.listIterator();

		while (itr.hasNext()) {
			Element dynamicContent = (Element)itr.next();

			boolean deleteImage = false;
			boolean exists = false;

			String elLanguage = dynamicContent.attributeValue(
				"language-id", StringPool.BLANK);

			if (!elLanguage.equals(StringPool.BLANK)) {
				elLanguage = "_" + elLanguage;
			}

			String imageId =
				companyId + ".journal.article." + articleId + "." + elName +
					elLanguage + "." + version;

			double oldVersion = MathUtil.format(version - 0.1, 1, 1);

			String oldImageId =
				companyId + ".journal.article." + articleId + "." + elName +
					elLanguage + "." + oldVersion;

			String elContent =
				"/image/journal/article?img_id=" + articleId + "." + elName +
					elLanguage + "&version=" + version;

			if (dynamicContent.getText().equals("delete")) {
				dynamicContent.setText(StringPool.BLANK);
				ImageLocalUtil.remove(imageId);

				String defaultElLanguage = "";
				if (!Validator.isNotNull(elLanguage)) {
					defaultElLanguage =
						"_" + LocaleUtil.toLanguageId(Locale.getDefault());
				}

				String defaultImageId =
					companyId + ".journal.article." + articleId + "." + elName +
						defaultElLanguage + "." + version;

				ImageLocalUtil.remove(defaultImageId);

				continue;
			}

			byte[] bytes = (byte[])images.get(elName + elLanguage);

			if (bytes != null && (bytes.length > 0)) {
				dynamicContent.setText(elContent);
				dynamicContent.addAttribute("id", imageId);

				ImageLocalUtil.put(imageId, bytes);

				continue;
			}

			if ((version > JournalArticle.DEFAULT_VERSION) &&
				(incrementVersion)) {

				Image oldImage = ImageLocalUtil.get(oldImageId);

				if (oldImage != null) {
					dynamicContent.setText(elContent);
					dynamicContent.addAttribute("id", imageId);

					bytes = oldImage.getTextObj();

					ImageLocalUtil.put(imageId, bytes);
				}

				continue;
			}

			Image image = ImageLocalUtil.get(imageId);

			if (image != null) {
				dynamicContent.setText(elContent);
				dynamicContent.addAttribute("id", imageId);

				continue;
			}

			String defaultElLanguage = "";
			if (!Validator.isNotNull(elLanguage)) {
				defaultElLanguage =
					"_" + LocaleUtil.toLanguageId(Locale.getDefault());
			}

			String defaultImageId =
				companyId + ".journal.article." + articleId + "." + elName +
					defaultElLanguage + "." + version;

			Image defaultImage = ImageLocalUtil.get(defaultImageId);

			if (defaultImage != null) {
				dynamicContent.setText(elContent);
				dynamicContent.addAttribute("id", imageId);

				bytes = defaultImage.getTextObj();

				ImageLocalUtil.put(imageId, bytes);

				continue;
			}

			dynamicContent.setText(StringPool.BLANK);
		}
	}

	private void _validate(
			String articleId, boolean autoArticleId, String title,
			String content, String structureId, String templateId,
			int displayMonth, int displayDay, int displayYear, int expMonth,
			int expDay, int expYear, boolean neverExpires)
		throws PortalException, SystemException {

		if (!autoArticleId) {
			if ((Validator.isNull(articleId)) ||
				(Validator.isNumber(articleId)) ||
				(articleId.indexOf(StringPool.SPACE) != -1)) {

				throw new ArticleIdException();
			}

			try {
				JournalArticlePK pk = new JournalArticlePK(
					articleId, JournalArticle.DEFAULT_VERSION);

				JournalArticleUtil.findByPrimaryKey(pk);

				throw new DuplicateArticleIdException();
			}
			catch (NoSuchArticleException nste) {
			}
		}

		_validate(
			title, content, structureId, templateId, displayMonth, displayDay,
			displayYear, expMonth, expDay, expYear, neverExpires);
	}

	private void _validate(
			String title, String content, String structureId, String templateId,
			int displayMonth, int displayDay, int displayYear, int expMonth,
			int expDay, int expYear, boolean neverExpires)
		throws PortalException, SystemException {

		if (Validator.isNull(title)) {
			throw new ArticleTitleException();
		}
		else if (Validator.isNull(content)) {
			throw new ArticleContentException();
		}

		if (Validator.isNotNull(structureId)) {
			JournalStructureUtil.findByPrimaryKey(structureId);

			JournalTemplate template =
				JournalTemplateUtil.findByPrimaryKey(templateId);

			if (!template.getStructureId().equals(structureId)) {
				throw new NoSuchTemplateException();
			}
		}

		if (!Validator.isDate(displayMonth, displayDay, displayYear)) {
			throw new ArticleDisplayDateException();
		}

		if (!neverExpires) {
			if (!Validator.isDate(expMonth, expDay, expYear)) {
				throw new ArticleExpirationDateException();
			}
		}
	}

	private static final Log _log =
		LogFactory.getLog(JournalArticleServiceImpl.class);

}