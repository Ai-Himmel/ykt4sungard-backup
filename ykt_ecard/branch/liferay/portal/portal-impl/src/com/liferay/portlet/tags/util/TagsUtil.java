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

package com.liferay.portlet.tags.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.journal.model.JournalArticle;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.tags.NoSuchEntryException;
import com.liferay.portlet.tags.model.TagsEntry;
import com.liferay.portlet.tags.model.TagsProperty;
import com.liferay.portlet.tags.service.TagsEntryLocalServiceUtil;
import com.liferay.portlet.tags.service.TagsPropertyLocalServiceUtil;
import com.liferay.portlet.wiki.model.WikiPage;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="TagsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsUtil {

	public static final String[] ASSET_TYPE_CLASS_NAMES = {
		BlogsEntry.class.getName(), BookmarksEntry.class.getName(),
		DLFileEntry.class.getName(), IGImage.class.getName(),
		JournalArticle.class.getName(), MBMessage.class.getName(),
		WikiPage.class.getName()
	};

	public static final String[] ASSET_TYPE_PORTLET_IDS = {
		PortletKeys.BLOGS, PortletKeys.BOOKMARKS, PortletKeys.DOCUMENT_LIBRARY,
		PortletKeys.IMAGE_GALLERY, PortletKeys.JOURNAL,
		PortletKeys.MESSAGE_BOARDS, PortletKeys.WIKI
	};

	public static boolean isValidWord(String word) {
		if (Validator.isNull(word)) {
			return false;
		}
		else {
			char[] c = word.toCharArray();

			for (int i = 0; i < c.length; i++) {
				if (!Validator.isChar(c[i]) && !Validator.isDigit(c[i]) &&
					(c[i] != ' ') && (c[i] != '.') && (c[i] != '-') &&
					(c[i] != '_') && (c[i] != '(') && (c[i] != ')')) {

					return false;
				}
			}
		}

		return true;
	}

	public static String substitutePropertyVariables(
			long companyId, String entryName, String s)
		throws PortalException, SystemException {

		String result = s;

		TagsEntry entry = null;

		if (entryName != null) {
			try {
				entry = TagsEntryLocalServiceUtil.getEntry(
					companyId, entryName);
			}
			catch (NoSuchEntryException nsee) {
			}
		}

		if (entry != null) {
			List properties = TagsPropertyLocalServiceUtil.getProperties(
				entry.getEntryId());

			Iterator it = properties.iterator();

			while (it.hasNext()) {
				TagsProperty property = (TagsProperty) it.next();

				result = StringUtil.replace(
					result, "[$" + property.getKey() + "$]",
					property.getValue());
			}
		}

		return StringUtil.stripBetween(result, "[$", "$]");
	}

}