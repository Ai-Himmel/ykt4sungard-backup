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

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalFeed;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.model.impl.JournalArticleImpl;
import com.liferay.portlet.journal.service.JournalArticleServiceUtil;
import com.liferay.portlet.journal.service.JournalFeedServiceUtil;
import com.liferay.portlet.journal.service.JournalStructureServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionUtil {

	public static void getArticle(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getArticle(httpReq);

		JournalArticle article =
			(JournalArticle)req.getAttribute(WebKeys.JOURNAL_ARTICLE);

		JournalUtil.addRecentArticle(req, article);
	}

	public static void getArticle(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getArticle(httpReq);

		JournalArticle article =
			(JournalArticle)req.getAttribute(WebKeys.JOURNAL_ARTICLE);

		JournalUtil.addRecentArticle(req, article);
	}

	public static void getArticle(HttpServletRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");
		String articleId = ParamUtil.getString(req, "articleId");
		double version = ParamUtil.getDouble(
			req, "version", JournalArticleImpl.DEFAULT_VERSION);

		JournalArticle article = null;

		if (Validator.isNotNull(articleId)) {
			article = JournalArticleServiceUtil.getArticle(
				groupId, articleId, version);
		}

		req.setAttribute(WebKeys.JOURNAL_ARTICLE, article);
	}

	public static void getFeed(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFeed(httpReq);
	}

	public static void getFeed(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFeed(httpReq);
	}

	public static void getFeed(HttpServletRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");
		String feedId = ParamUtil.getString(req, "feedId");

		JournalFeed feed = null;

		if (Validator.isNotNull(feedId)) {
			feed = JournalFeedServiceUtil.getFeed(groupId, feedId);
		}

		req.setAttribute(WebKeys.JOURNAL_FEED, feed);
	}

	public static void getStructure(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getStructure(httpReq);

		JournalStructure structure =
			(JournalStructure)req.getAttribute(WebKeys.JOURNAL_STRUCTURE);

		JournalUtil.addRecentStructure(req, structure);
	}

	public static void getStructure(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getStructure(httpReq);

		JournalStructure structure =
			(JournalStructure)req.getAttribute(WebKeys.JOURNAL_STRUCTURE);

		JournalUtil.addRecentStructure(req, structure);
	}

	public static void getStructure(HttpServletRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");
		String structureId = ParamUtil.getString(req, "structureId");

		JournalStructure structure = null;

		if (Validator.isNotNull(structureId)) {
			structure = JournalStructureServiceUtil.getStructure(
				groupId, structureId);
		}

		req.setAttribute(WebKeys.JOURNAL_STRUCTURE, structure);
	}

	public static void getTemplate(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getTemplate(httpReq);

		JournalTemplate template =
			(JournalTemplate)req.getAttribute(WebKeys.JOURNAL_TEMPLATE);

		JournalUtil.addRecentTemplate(req, template);
	}

	public static void getTemplate(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getTemplate(httpReq);

		JournalTemplate template =
			(JournalTemplate)req.getAttribute(WebKeys.JOURNAL_TEMPLATE);

		JournalUtil.addRecentTemplate(req, template);
	}

	public static void getTemplate(HttpServletRequest req) throws Exception {
		long groupId = ParamUtil.getLong(req, "groupId");
		String templateId = ParamUtil.getString(req, "templateId");

		JournalTemplate template = null;

		if (Validator.isNotNull(templateId)) {
			template = JournalTemplateServiceUtil.getTemplate(
				groupId, templateId);
		}

		req.setAttribute(WebKeys.JOURNAL_TEMPLATE, template);
	}

}