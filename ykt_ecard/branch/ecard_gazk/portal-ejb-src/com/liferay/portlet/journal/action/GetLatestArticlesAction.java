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
import com.liferay.portal.util.Constants;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.StringReader;

import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.DocumentFactory;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="GetLatestArticlesAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Raymond Auge
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class GetLatestArticlesAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String templateId = ParamUtil.getString(req, "template_id");
			int number = ParamUtil.getInteger(req, "number");
			String languageId = LanguageUtil.getLanguageId(req);

			List articles = new ArrayList();

			Date today = new Date();

			Iterator itr = JournalArticleServiceUtil.getArticlesByTemplate(
				templateId).iterator();

			while (itr.hasNext()) {
				JournalArticle article = (JournalArticle)itr.next();

				Date createDate = article.getCreateDate();
				Date displayDate = article.getDisplayDate();
				Date expireDate = article.getExpirationDate();

				if (article.isApproved() && today.after(displayDate) &&
					((expireDate == null) || today.before(expireDate))) {

					boolean added = false;

					for (int i = 0; i < articles.size(); i++) {
						JournalArticle tempArticle =
							(JournalArticle)articles.get(i);

						if (article.getDisplayDate().before(
								tempArticle.getDisplayDate())) {

							articles.add(i, article);

							added = true;

							break;
						}
					}

					if (!added) {
						articles.add(article);
					}
				}
			}

			Document resultsDoc =
				DocumentFactory.getInstance().createDocument();

			Element resultSetEl = resultsDoc.addElement("result-set");

			SAXReader reader = new SAXReader();

			itr = articles.iterator();

			while (itr.hasNext() && (number > 0)) {
				JournalArticle article = (JournalArticle)itr.next();

				Element resultEl = resultSetEl.addElement("result");

				resultEl.addAttribute("article-id", article.getArticleId());

				Document articleDoc = reader.read(
					new StringReader(article.getContentByLocale(languageId)));

				resultEl.content().add(
					articleDoc.getRootElement().createCopy());

				number--;
			}

			String fileName = "latest-" + articles.size() + "-articles.xml";
			byte[] byteArray = JournalUtil.formatXML(resultsDoc).getBytes();

			ServletResponseUtil.sendFile(res, fileName, byteArray);

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}