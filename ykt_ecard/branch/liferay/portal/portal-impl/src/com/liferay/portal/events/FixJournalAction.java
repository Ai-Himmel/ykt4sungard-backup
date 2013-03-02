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

package com.liferay.portal.events;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.kernel.events.SimpleAction;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalStructureLocalServiceUtil;
import com.liferay.portlet.journal.util.JournalUtil;

import java.util.List;

/**
 * <a href="FixJournalAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class FixJournalAction extends SimpleAction {

	public void run(String[] ids) throws ActionException {
		try {
			_fixOldContent();
		}
		catch (Exception e) {
			throw new ActionException(e);
		}
	}

	private void _fixOldContent() throws PortalException, SystemException {
		List articles = JournalArticleLocalServiceUtil.getArticles();

		for (int i = 0; i < articles.size(); i++) {
			JournalArticle article = (JournalArticle)articles.get(i);

			String structureId = article.getStructureId();

			if (Validator.isNotNull(structureId)) {
				long groupId = article.getGroupId();
				String articleId = article.getArticleId();
				double version = article.getVersion();
				String content = article.getContent();

				JournalStructure structure =
					JournalStructureLocalServiceUtil.getStructure(
						groupId, structureId);

				content = JournalUtil.removeOldContent(
					content, structure.getXsd());

				JournalArticleLocalServiceUtil.updateContent(
					groupId, articleId, version, content);
			}
		}
	}

}