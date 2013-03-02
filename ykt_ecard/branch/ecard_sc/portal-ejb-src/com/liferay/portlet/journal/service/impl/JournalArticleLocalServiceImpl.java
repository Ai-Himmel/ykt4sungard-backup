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

import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.service.spring.CompanyLocalServiceUtil;
import com.liferay.portal.service.spring.ImageServiceUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.admin.model.EmailConfig;
import com.liferay.portlet.admin.model.JournalConfig;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.service.persistence.JournalArticlePK;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleLocalService;
import com.liferay.portlet.journal.util.Indexer;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.mail.MailMessage;

import java.io.IOException;

import java.util.Iterator;
import java.util.List;

import javax.mail.internet.InternetAddress;

/**
 * <a href="JournalArticleLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class JournalArticleLocalServiceImpl
	implements JournalArticleLocalService {

	// Business methods

	public void deleteAll(String groupId)
		throws PortalException, SystemException {

		Iterator itr = JournalArticleUtil.findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			JournalArticle article = (JournalArticle)itr.next();

			deleteArticle(article, false);
		}
	}

	public void deleteArticle(
			String articleId, double version, boolean sendEmail)
		throws PortalException, SystemException {

		JournalArticlePK pk = new JournalArticlePK(articleId, version);

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		deleteArticle(article, sendEmail);
	}

	public void deleteArticle(JournalArticle article, boolean sendEmail)
		throws PortalException, SystemException {

		// Send email

		if (sendEmail) {
			sendEmail(article.getPrimaryKey(), "denied", StringPool.BLANK);
		}

		// Delete article

		JournalArticleUtil.remove(article.getPrimaryKey());

		// Delete all images associated with this article

		Iterator itr = ImageServiceUtil.getImageById(
			"%.journal.article." + article.getArticleId() + ".%." +
				article.getVersion()).iterator();

		while (itr.hasNext()) {
			Image image = (Image)itr.next();

			ImageLocalUtil.remove(image.getImageId());
		}

		// Update lucene

		try {
			if (article.isApproved()) {
				Indexer.deleteArticle(
					article.getCompanyId(), article.getPortletId(),
					article.getArticleId());
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public List getArticles(String portletId, String groupId, String companyId)
		throws SystemException {

		return JournalArticleUtil.findByP_G_C(portletId, groupId, companyId);
	}

	public void sendEmail(JournalArticlePK pk, String type, String articleURL)
		throws PortalException, SystemException {

		JournalArticle article = JournalArticleUtil.findByPrimaryKey(pk);

		Company company = CompanyLocalServiceUtil.getCompany(
			article.getCompanyId());

		JournalConfig journalConfig = AdminConfigServiceUtil.getJournalConfig(
			company.getCompanyId(), article.getPortletId());

		EmailConfig approvalEmail = null;

		if (type.equals("requested")) {
			approvalEmail = journalConfig.getApprovalRequestedEmail();
		}
		else if (type.equals("granted")) {
			approvalEmail = journalConfig.getApprovalGrantedEmail();
		}
		else if (type.equals("denied")) {
			approvalEmail = journalConfig.getApprovalDeniedEmail();
		}

		if (approvalEmail == null || !approvalEmail.isSend()) {
			return;
		}

		User user = UserLocalServiceUtil.getUserById(article.getUserId());

		String subject = approvalEmail.getSubject();
		subject = StringUtil.replace(
			subject,
			new String[] {
				"[$ADMIN_NAME$]",
				"[$ARTICLE_ID$]",
				"[$ARTICLE_TITLE$]",
				"[$ARTICLE_URL$]",
				"[$ARTICLE_VERSION$]",
				"[$PORTLET_NAME$]",
				"[$USER_NAME$]"},
			new String[] {
				company.getAdminName(),
				article.getArticleId(),
				article.getTitle(),
				articleURL,
				Double.toString(article.getVersion()),
				LanguageUtil.get(
					user,
					WebKeys.JAVAX_PORTLET_TITLE + "." + article.getPortletId()),
				user.getFullName()});

		String body = approvalEmail.getBody();
		body = StringUtil.replace(
			body,
			new String[] {
				"[$ADMIN_NAME$]",
				"[$ARTICLE_ID$]",
				"[$ARTICLE_TITLE$]",
				"[$ARTICLE_URL$]",
				"[$ARTICLE_VERSION$]",
				"[$PORTLET_NAME$]",
				"[$USER_NAME$]"},
			new String[] {
				company.getAdminName(),
				article.getArticleId(),
				article.getTitle(),
				articleURL,
				Double.toString(article.getVersion()),
				LanguageUtil.get(
					user,
					WebKeys.JAVAX_PORTLET_TITLE + "." + article.getPortletId()),
				user.getFullName()});

		try {
			InternetAddress from = new InternetAddress(
				company.getEmailAddress(), company.getAdminName());

			InternetAddress[] to = new InternetAddress[] {
				new InternetAddress(
					user.getEmailAddress(), user.getFullName())
			};

			if (type.equals("requested")) {
				InternetAddress tempAddress = from;

				from = to[0];
				to[0] = tempAddress;
			}

			InternetAddress[] cc = null;

			Role journalAdminRole = RoleLocalServiceUtil.getRoleByName(
				company.getCompanyId(), Role.JOURNAL_ADMIN);

			List users = RoleLocalServiceUtil.getUsers(
				journalAdminRole.getRoleId());

			InternetAddress[] bcc = new InternetAddress[users.size()];

			for (int i = 0; i < users.size(); i++) {
				User journalAdminUser = (User)users.get(i);

				bcc[i] = new InternetAddress(
					journalAdminUser.getEmailAddress(),
					journalAdminUser.getFullName());
			}

			MailServiceUtil.sendEmail(new MailMessage(
				from, to, cc, bcc, subject, body));
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

}