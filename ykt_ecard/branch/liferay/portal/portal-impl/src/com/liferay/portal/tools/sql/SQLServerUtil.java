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
 * <a href="SQLServerUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class SQLServerUtil extends DBUtil {

	public static DBUtil getInstance() {
		return _instance;
	}

	public String buildSQL(String template) throws IOException {
		template = convertTimestamp(template);
		template = StringUtil.replace(template, TEMPLATE, getTemplate());

		template = reword(template);
		template = StringUtil.replace(template, "\ngo;\n", "\ngo\n");
		template = StringUtil.replace(
			template,
			new String[] {"\\\\", "\\'", "\\\"", "\\n", "\\r"},
			new String[] {"\\", "''", "\"", "\n", "\r"});

		return template;
	}

	protected SQLServerUtil() {
	}

	protected void buildCreateFile(String databaseName, boolean minimal)
		throws IOException {

		String minimalSuffix = getMinimalSuffix(minimal);

		File file = new File(
			"../sql/create" + minimalSuffix + "/create" + minimalSuffix +
				"-sql-server.sql");

		StringMaker sm = new StringMaker();

		sm.append("drop database " + databaseName + ";\n");
		sm.append("create database " + databaseName + ";\n");
		sm.append("\n");
		sm.append("go\n");
		sm.append("\n");
		sm.append("use " + databaseName + ";\n\n");
		sm.append(
			FileUtil.read(
				"../sql/portal" + minimalSuffix + "/portal" + minimalSuffix +
					"-sql-server.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/indexes/indexes-sql-server.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/sequences/sequences-sql-server.sql"));

		FileUtil.write(file, sm.toString());
	}

	protected String getServerName() {
		return "sql-server";
	}

	protected String[] getTemplate() {
		return _SQL_SERVER;
	}

	protected String reword(String data) throws IOException {
		BufferedReader br = new BufferedReader(new StringReader(data));

		StringMaker sm = new StringMaker();

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.startsWith(ALTER_COLUMN_TYPE)) {
				String[] template = buildColumnTypeTokens(line);

				line = StringUtil.replace(
					"alter table @table@ alter column @old-column@ @type@;",
					REWORD_TEMPLATE, template);
			}
			else if (line.startsWith(ALTER_COLUMN_NAME)) {
				String[] template = buildColumnNameTokens(line);

				line = StringUtil.replace(
					"exec sp_rename '@table@.@old-column@', '@new-column@', " +
						"'column';",
					REWORD_TEMPLATE, template);
			}

			sm.append(line);
			sm.append("\n");
		}

		br.close();

		return sm.toString();
	}

	private static String[] _SQL_SERVER = {
		"--", "1", "0",
		"'19700101'", "GetDate()",
		" bit", " datetime", " float",
		" int", " bigint",
		" varchar(2000)", " text", " varchar",
		"  identity(1,1)", "go"
	};

	private static SQLServerUtil _instance = new SQLServerUtil();

}