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

package com.liferay.portal.lucene;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.InstancePool;

import java.io.File;
import java.io.IOException;

import java.util.Date;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.document.DateField;
import org.apache.lucene.document.Field;

/**
 * <a href="LuceneFields.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class LuceneFields {

	public static final String UID = "uid";

	public static final String COMPANY_ID = "companyId";
	public static final String PORTLET_ID = "portletId";
	public static final String GROUP_ID = "groupId";

	public static final String TITLE = "title";
	public static final String CONTENT = "content";

	public static final String MODIFIED = "modified";

	public static String getUID(String portletId, String field1) {
		return getUID(portletId, field1, null);
	}

	public static String getUID(
		String portletId, String field1, String field2) {

		String uid = portletId + _UID_PORTLET + field1;

		if (field2 != null) {
			uid += _UID_FIELD + field2;
		}

		return uid;
	}

	public static Field getDate(String field) {
		return getDate(field, new Date());
	}

	public static Field getDate(String field, Date date) {
		if (date == null) {
			return getDate(field);
		}
		else {
			return Field.Keyword(field, DateField.dateToString(date));
		}
	}

	public static Field getFile(String field, File file, String fileExt)
		throws IOException {

		LuceneFileExtractor fileExtractor =
			(LuceneFileExtractor)InstancePool.get(
				PropsUtil.get(PropsUtil.LUCENE_FILE_EXTRACTOR));

		return fileExtractor.getFile(field, file, fileExt);
	}

	public static Field getKeyword(String field, String keyword) {
		//keyword = KeywordsUtil.escape(keyword);

		Field fieldObj = Field.Keyword(field, keyword);

		fieldObj.setBoost(0);

		return fieldObj;
	}

	private static final Log _log = LogFactory.getLog(LuceneFields.class);

	private static final String _UID_PORTLET = "_PORTLET_";
	private static final String _UID_FIELD = "_FIELD_";

}