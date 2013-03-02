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

import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.PwdGenerator;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.servlet.UploadServletRequest;

import java.io.File;
import java.io.StringReader;

import java.util.Date;
import java.util.Iterator;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ViewArticleContentAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class ViewArticleContentAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			String articleId = ParamUtil.getString(req, "article_id");
			double version = ParamUtil.get(
				req, "article_version", JournalArticle.DEFAULT_VERSION);
			String languageId = LanguageUtil.getLanguageId(req);
			String rootPath = (String)req.getAttribute(WebKeys.ROOT_PATH);

			String output = null;

			if (cmd.equals("preview")) {
				String title = ParamUtil.getString(req, "article_title");

				Date now = new Date();

				Date createDate = now;
				Date modifiedDate = now;
				Date displayDate = now;

				String xml = ParamUtil.getString(req, "xml");
				String xsl = ParamUtil.getString(req, "xsl");

				SAXReader reader = new SAXReader();

				Document doc = reader.read(new StringReader(xml));

				Element root = doc.getRootElement();

				String previewArticleId =
					"PREVIEW_" +
					PwdGenerator.getPassword(PwdGenerator.KEY3, 10);

				String companyId = PortalUtil.getCompanyId(req);

				_format(
					articleId, version, previewArticleId, companyId, root,
					(UploadServletRequest)req);

				Map tokens = JournalUtil.getTokens(companyId, rootPath);

				JournalUtil.addReservedEl(
					root, tokens, JournalStructure.RESERVED_ARTICLE_ID,
					articleId);

				JournalUtil.addReservedEl(
					root, tokens, JournalStructure.RESERVED_ARTICLE_VERSION,
					Double.toString(version));

				JournalUtil.addReservedEl(
					root, tokens, JournalStructure.RESERVED_ARTICLE_TITLE,
					title);

				JournalUtil.addReservedEl(
					root, tokens, JournalStructure.RESERVED_ARTICLE_CREATE_DATE,
					createDate.toString());

				JournalUtil.addReservedEl(
					root, tokens,
					JournalStructure.RESERVED_ARTICLE_MODIFIED_DATE,
					modifiedDate.toString());

				JournalUtil.addReservedEl(
					root, tokens,
					JournalStructure.RESERVED_ARTICLE_DISPLAY_DATE,
					displayDate.toString());

				xml = JournalUtil.formatXML(doc);

				output = JournalUtil.transform(tokens, languageId, xml, xsl);
			}
			else {
				output = JournalArticleServiceUtil.getArticleContent(
					articleId, version, languageId, rootPath);
			}

			req.setAttribute(WebKeys.JOURNAL_ARTICLE_CONTENT, output);

			return mapping.findForward("portlet.journal.view_article_content");
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

	private void _format(
			String articleId, double version, String previewArticleId,
			String companyId, Element root, UploadServletRequest req)
		throws Exception {

		Iterator itr = root.elements().iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			Element dynamicContent = el.element("dynamic-content");

			String elName = el.attributeValue("name", StringPool.BLANK);
			String elType = el.attributeValue("type", StringPool.BLANK);
			String elLanguage = "";

			if (dynamicContent != null) {
				elLanguage = dynamicContent.attributeValue(
					"language-id", StringPool.BLANK);

				if (!elLanguage.equals(StringPool.BLANK)) {
					elLanguage = "_" + elLanguage;
				}
			}

			if (elType.equals("image")) {
				File file = req.getFile(
					"structure_image_" + elName + elLanguage);
				byte[] bytes = FileUtil.getBytes(file);

				if (bytes != null && bytes.length > 0) {
					String imageId =
						previewArticleId + "." + elName + elLanguage;

					dynamicContent.setText(
						"/image/journal/article?img_id=" + imageId);

					ImageLocalUtil.put(
						companyId + ".journal.article." + imageId, bytes);
				}
				else {
					if (Validator.isNotNull(articleId)) {
						String imageId = articleId + "." + elName + elLanguage;

						dynamicContent.setText(
							"/image/journal/article?img_id=" + imageId +
								"&version=" + version);
					}
				}
			}

			_format(articleId, version, previewArticleId, companyId, el, req);
		}
	}

}