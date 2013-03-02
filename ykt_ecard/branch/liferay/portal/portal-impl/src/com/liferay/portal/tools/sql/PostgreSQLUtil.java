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
 * <a href="PostgreSQLUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class PostgreSQLUtil extends DBUtil {

	public static DBUtil getInstance() {
		return _instance;
	}

	public String buildSQL(String template) throws IOException {
		template = convertTimestamp(template);
		template = StringUtil.replace(template, TEMPLATE, getTemplate());

		template = reword(template);

		return template;
	}

	protected PostgreSQLUtil() {
	}

	protected void buildCreateFile(String databaseName, boolean minimal)
		throws IOException {

		String minimalSuffix = getMinimalSuffix(minimal);

		File file = new File(
			"../sql/create" + minimalSuffix + "/create" + minimalSuffix +
				"-postgresql.sql");

		StringMaker sm = new StringMaker();

		sm.append("drop database " + databaseName + ";\n");
		sm.append(
			"create database " + databaseName + " encoding = 'UNICODE';\n");
		sm.append("\\c " + databaseName + ";\n\n");
		sm.append(
			FileUtil.read(
				"../sql/portal" + minimalSuffix + "/portal" + minimalSuffix +
					"-postgresql.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/indexes/indexes-postgresql.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/sequences/sequences-postgresql.sql"));

		FileUtil.write(file, sm.toString());
	}

	protected String getServerName() {
		return "postgresql";
	}

	protected String[] getTemplate() {
		return _POSTGRESQL;
	}

	protected String reword(String data) throws IOException {
		BufferedReader br = new BufferedReader(new StringReader(data));

		StringMaker sm = new StringMaker();

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.startsWith(ALTER_COLUMN_TYPE)) {
				String[] template = buildColumnTypeTokens(line);

				line = StringUtil.replace(
					"alter table @table@ alter @old-column@ type @type@;",
					REWORD_TEMPLATE, template);
			}
			else if (line.startsWith(ALTER_COLUMN_NAME)) {
				String[] template = buildColumnNameTokens(line);

				line = StringUtil.replace(
					"alter table @table@ rename @old-column@ to @new-column@;",
					REWORD_TEMPLATE, template);
			}
			else if (line.indexOf(DROP_PRIMARY_KEY) != -1) {
				String[] tokens = StringUtil.split(line, " ");

				line = StringUtil.replace(
					"alter table @table@ drop constraint @table@_pkey;",
					"@table@", tokens[2]);
			}

			sm.append(line);
			sm.append("\n");
		}

		br.close();

		return sm.toString();
	}

	private static String[] _POSTGRESQL = {
		"--", "true", "false",
		"'01/01/1970'", "current_timestamp",
		" bool", " timestamp", " double precision",
		" integer", " bigint",
		" text", " text", " varchar",
		"", "commit"
	};

	private static PostgreSQLUtil _instance = new PostgreSQLUtil();

}