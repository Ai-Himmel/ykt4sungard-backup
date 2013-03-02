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

package com.liferay.portal.tools.sql;

import com.liferay.portal.kernel.util.StringUtil;

import java.io.IOException;

/**
 * <a href="JDataStoreUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class JDataStoreUtil extends FirebirdUtil {

	public static DBUtil getInstance() {
		return _instance;
	}

	public String buildSQL(String template) throws IOException {
		template = convertTimestamp(template);
		template = StringUtil.replace(template, TEMPLATE, getTemplate());

		template = reword(template);
		template = StringUtil.replace(
			template,
			new String[] {"\\'", "\\\"", "\\\\",  "\\n", "\\r"},
			new String[] {"''", "\"", "\\", "\n", "\r"});

		return template;
	}

	protected JDataStoreUtil() {
	}

	protected String getServerName() {
		return "jdatastore";
	}

	protected String[] getTemplate() {
		return _JDATASTORE;
	}

	private static String[] _JDATASTORE = {
		"--", "TRUE", "FALSE",
		"'1970-01-01'", "current_timestamp",
		" boolean", " date", " double",
		" integer", " bigint",
		" long varchar", " long varchar", " varchar",
		"", "commit"
	};

	private static JDataStoreUtil _instance = new JDataStoreUtil();

}