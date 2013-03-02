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

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.util.FileUtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.StringReader;

/**
 * <a href="SybaseUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Bruno Farache
 *
 */
public class SybaseUtil extends DBUtil {

	public static DBUtil getInstance() {
		return _instance;
	}

	public String buildSQL(String template) throws IOException {
		template = convertTimestamp(template);
		template = StringUtil.replace(template, TEMPLATE, getTemplate());

		template = reword(template);
		template = StringUtil.replace(template, ");\n", ")\ngo\n");
		template = StringUtil.replace(template, "\ngo;\n", "\ngo\n");
		template = StringUtil.replace(
			template,
			new String[] {"\\\\", "\\'", "\\\"", "\\n", "\\r"},
			new String[] {"\\", "''", "\"", "\n", "\r"});

		return template;
	}

	protected SybaseUtil() {
	}

	protected void buildCreateFile(String databaseName, boolean minimal)
		throws IOException {

		String minimalSuffix = getMinimalSuffix(minimal);

		File file = new File(
			"../sql/create" + minimalSuffix + "/create" + minimalSuffix +
				"-sybase.sql");

		StringMaker sm = new StringMaker();

		sm = new StringMaker();

		sm.append("use master\n");
		sm.append(
			"exec sp_dboption '" + databaseName + "', " +
				"'allow nulls by default' , true\n");
		sm.append("go\n\n");
		sm.append(
			"exec sp_dboption '" + databaseName + "', " +
				"'select into/bulkcopy/pllsort' , true\n");
		sm.append("go\n\n");

		sm.append("use " + databaseName + "\n\n");
		sm.append(
			FileUtil.read(
				"../sql/portal" + minimalSuffix + "/portal" + minimalSuffix +
					"-sybase.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/indexes/indexes-sybase.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/sequences/sequences-sybase.sql"));

		FileUtil.write(file, sm.toString());
	}

	protected String getServerName() {
		return "sybase";
	}

	protected String[] getTemplate() {
		return _SYBASE;
	}

	protected String reword(String data) throws IOException {
		BufferedReader br = new BufferedReader(new StringReader(data));

		StringMaker sm = new StringMaker();

		String line = null;

		while ((line = br.readLine()) != null) {

			if (line.indexOf(DROP_COLUMN) != -1) {
				line = StringUtil.replace(line, " drop column ", " drop ");
			}

			if (line.startsWith(ALTER_COLUMN_TYPE)) {
				String[] template = buildColumnTypeTokens(line);

				line = StringUtil.replace(
					"alter table @table@ alter column @old-column@ @type@;",
					REWORD_TEMPLATE, template);
			}
			else if (line.startsWith(ALTER_COLUMN_NAME)) {
				String[] template = buildColumnNameTokens(line);

				line = StringUtil.replace(
					"exec sp_rename '@table@.@old-column@', '@new-column@', 'column';",
					REWORD_TEMPLATE, template);
			}

			sm.append(line);
			sm.append("\n");
		}

		br.close();

		return sm.toString();
	}

	protected static String DROP_COLUMN = "drop column";

	private static String[] _SYBASE = {
		"--", "1", "0",
		"'19700101'", "getdate()",
		" int", " datetime", " float",
		" int", " decimal(20,0)",
		" varchar(1000)", " text", " varchar",
		"  identity(1,1)", "go"
	};

	private static SybaseUtil _instance = new SybaseUtil();

}