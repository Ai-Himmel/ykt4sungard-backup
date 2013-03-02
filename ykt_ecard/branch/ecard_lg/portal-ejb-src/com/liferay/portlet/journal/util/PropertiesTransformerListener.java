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

import com.liferay.util.CollectionFactory;
import com.liferay.util.MapUtil;
import com.liferay.util.PropertiesUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;

import java.util.Iterator;
import java.util.Map;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PropertiesTransformerListener.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class PropertiesTransformerListener extends TransformerListener {

	public String onXml(String s) {
		_log.debug("onXml");

		return s;
	}

	public String onXsl(String s) {
		_log.debug("onXsl");

		s = replaceProperties(s);

		return s;
	}

	public String onOutput(String s) {
		_log.debug("onOutput");

		s = replaceProperties(s);

		return s;
	}

	/**
	 * Replace the properties in a given string with their values fetched from
	 * the template GLOBAL-PROPERTIES.
	 *
     * @param		s the given string
     * @return		the processed string
	 */
	protected String replaceProperties(String s) {
		Map tokens = getTokens();

		String templateId = (String)tokens.get("template_id");

		if ((templateId != null) && (templateId.equals(_GLOBAL_PROPERTIES))) {

			// Prevent an infinite loop

			return s;
		}

		Properties props = new Properties();

		try {
			Map newTokens = CollectionFactory.getHashMap();

			MapUtil.copy(tokens, newTokens);

			newTokens.put("template_id", _GLOBAL_PROPERTIES);

			String xsl = JournalUtil.getTemplateXsl(
				_GLOBAL_PROPERTIES, newTokens, getLanguageId());

			PropertiesUtil.load(props, xsl);
		}
		catch (Exception e) {
			_log.error("Template " + templateId + " could not be found");
		}

		if (props.size() == 0) {
			return s;
		}

		String[] escapedKeys = new String[props.size()];
		String[] escapedValues = new String[props.size()];

		String[] keys = new String[props.size()];
		String[] values = new String[props.size()];

		String[] tempEscapedKeys = new String[props.size()];
		String[] tempEscapedValues = new String[props.size()];

		int counter = 0;

		Iterator itr = props.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String key = (String)entry.getKey();
			String value = (String)entry.getValue();

			String escapedKey =
				StringPool.AT + StringPool.AT + key + StringPool.AT +
					StringPool.AT;

			String actualKey = StringPool.AT + key + StringPool.AT;

			String tempEscapedKey =
				TokensTransformerListener.TEMP_ESCAPED_AT_OPEN +
					key + TokensTransformerListener.TEMP_ESCAPED_AT_CLOSE;

			escapedKeys[counter] = escapedKey;
			escapedValues[counter] = tempEscapedKey;

			keys[counter] = actualKey;
			values[counter] = value;

			tempEscapedKeys[counter] = tempEscapedKey;
			tempEscapedValues[counter] = actualKey;

			counter++;
		}

		s = StringUtil.replace(s, escapedKeys, escapedValues);

		s = StringUtil.replace(s, keys, values);

		s = StringUtil.replace(s, tempEscapedKeys, tempEscapedValues);

		return  s;
	}

	private static final Log _log =
		LogFactory.getLog(PropertiesTransformerListener.class);

	public static final String _GLOBAL_PROPERTIES = "GLOBAL-PROPERTIES";

}