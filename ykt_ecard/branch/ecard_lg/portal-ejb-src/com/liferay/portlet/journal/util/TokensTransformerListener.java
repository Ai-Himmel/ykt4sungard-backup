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

package com.liferay.portlet.journal.util;

import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="TokensTransformerListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class TokensTransformerListener extends TransformerListener {

	public static final String TEMP_ESCAPED_AT_OPEN =
		"[$TEMP_ESCAPED_AT_OPEN$]";

	public static final String TEMP_ESCAPED_AT_CLOSE =
		"[$_TEMP_ESCAPED_AT_CLOSE$]";

	public String onXml(String s) {
		_log.debug("onXml");

		return s;
	}

	public String onXsl(String s) {
		_log.debug("onXsl");

		return replaceTokens(s);
	}

	public String onOutput(String s) {
		_log.debug("onOutput");

		return replaceTokens(s);
	}

	/**
	 * Replace the standard tokens in a given string with their values.
	 *
     * @param		s the given string
     * @return		the processed string
	 */
	protected String replaceTokens(String s) {
		Map tokens = getTokens();

		Set tokensSet = tokens.entrySet();

		if (tokensSet.size() == 0) {
			return s;
		}

		List escapedKeysList = new ArrayList();
		List escapedValuesList = new ArrayList();

		List keysList = new ArrayList();
		List valuesList = new ArrayList();

		List tempEscapedKeysList = new ArrayList();
		List tempEscapedValuesList = new ArrayList();

		Iterator itr = tokensSet.iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			String value = GetterUtil.getString((String)entry.getValue());

			if (Validator.isNotNull(key)) {
				String escapedKey =
					StringPool.AT + StringPool.AT + key + StringPool.AT +
						StringPool.AT;

				String actualKey = StringPool.AT + key + StringPool.AT;

				String tempEscapedKey =
					TEMP_ESCAPED_AT_OPEN + key + TEMP_ESCAPED_AT_CLOSE;

				escapedKeysList.add(escapedKey);
				escapedValuesList.add(tempEscapedKey);

				keysList.add(actualKey);
				valuesList.add(value);

				tempEscapedKeysList.add(tempEscapedKey);
				tempEscapedValuesList.add(actualKey);
			}
		}

		s = StringUtil.replace(
			s,
			(String[])escapedKeysList.toArray(new String[0]),
			(String[])escapedValuesList.toArray(new String[0]));

		s = StringUtil.replace(
			s,
			(String[])keysList.toArray(new String[0]),
			(String[])valuesList.toArray(new String[0]));

		s = StringUtil.replace(
			s,
			(String[])tempEscapedKeysList.toArray(new String[0]),
			(String[])tempEscapedValuesList.toArray(new String[0]));

		return s;
	}

	private static final Log _log =
		LogFactory.getLog(TokensTransformerListener.class);

}