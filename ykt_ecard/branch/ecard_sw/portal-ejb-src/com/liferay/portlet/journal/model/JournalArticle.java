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

package com.liferay.portlet.journal.model;

import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.journal.service.persistence.JournalArticlePK;
import com.liferay.portlet.journal.util.LocaleTransformerListener;
import com.liferay.util.Validator;

import java.util.Date;

/**
 * <a href="JournalArticle.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.20 $
 *
 */
public class JournalArticle extends JournalArticleModel {

	public static final double DEFAULT_VERSION = 1.0;

	public static final String[] TYPES =
		PropsUtil.getArray(PropsUtil.JOURNAL_ARTICLE_TYPES);

	public static final String PORTLET = "portlet";

	public static final String STAND_ALONE = "stand-alone";

	public JournalArticle() {
		super();
	}

	public JournalArticle(JournalArticlePK pk) {
		super(pk);
	}

	public JournalArticle(String articleId, double version, String portletId,
						  String groupId, String companyId, String userId,
						  String userName, Date createDate, Date modifiedDate,
						  String title, String content, String type,
						  String structureId, String templateId,
						  Date displayDate, Date expirationDate,
						  boolean approved, String approvedByUserId,
						  String approvedByUserName) {

		super(articleId, version, portletId, groupId, companyId, userId,
			  userName, createDate, modifiedDate, title, content, type,
			  structureId, templateId, displayDate, expirationDate, approved,
			  approvedByUserId, approvedByUserName);
	}

	public String getContentByLocale(String languageId){
		LocaleTransformerListener listener = new LocaleTransformerListener();

		listener.setLanguageId(languageId);

		return listener.onXml(getContent());
	}

	public boolean isTemplateDriven() {
		if (Validator.isNull(getStructureId())) {
			return false;
		}
		else {
			return true;
		}
	}

}