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

package com.liferay.portlet.journal.service.persistence;

/**
 * <a href="JournalTemplateHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalTemplateHBMUtil {
	public static com.liferay.portlet.journal.model.JournalTemplate model(
		JournalTemplateHBM journalTemplateHBM) {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = JournalTemplatePool.get(journalTemplateHBM.getPrimaryKey());

		if (journalTemplate == null) {
			journalTemplate = new com.liferay.portlet.journal.model.JournalTemplate(journalTemplateHBM.getTemplateId(),
					journalTemplateHBM.getPortletId(),
					journalTemplateHBM.getGroupId(),
					journalTemplateHBM.getCompanyId(),
					journalTemplateHBM.getUserId(),
					journalTemplateHBM.getUserName(),
					journalTemplateHBM.getCreateDate(),
					journalTemplateHBM.getModifiedDate(),
					journalTemplateHBM.getStructureId(),
					journalTemplateHBM.getName(),
					journalTemplateHBM.getDescription(),
					journalTemplateHBM.getXsl(),
					journalTemplateHBM.getSmallImage(),
					journalTemplateHBM.getSmallImageURL());
			JournalTemplatePool.put(journalTemplate.getPrimaryKey(),
				journalTemplate);
		}

		return journalTemplate;
	}
}