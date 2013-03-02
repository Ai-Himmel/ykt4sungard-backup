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
 * <a href="OracleUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class OracleUtil extends DBUtil {

	public static DBUtil getInstance() {
		return _instance;
	}

	public String buildSQL(String template) throws IOException {
		template = _preBuildSQL(template);
		template = _postBuildSQL(template);

		return template;
	}

	public void buildSQLFile(String fileName) throws IOException {
		String oracle = buildTemplate(fileName);

		oracle = _preBuildSQL(oracle);

		BufferedReader br = new BufferedReader(new StringReader(oracle));

		StringMaker imageSM = new StringMaker();
		StringMaker journalArticleSM = new StringMaker();
		StringMaker journalStructureSM = new StringMaker();
		StringMaker journalTemplateSM = new StringMaker();

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.startsWith("insert into Image")) {
				_convertToOracleCSV(line, imageSM);
			}
			else if (line.startsWith("insert into JournalArticle (")) {
				_convertToOracleCSV(line, journalArticleSM);
			}
			else if (line.startsWith("insert into JournalStructure (")) {
				_convertToOracleCSV(line, journalStructureSM);
			}
			else if (line.startsWith("insert into JournalTemplate (")) {
				_convertToOracleCSV(line, journalTemplateSM);
			}
		}

		br.close();

		if (imageSM.length() > 0) {
			FileUtil.write(
				"../sql/" + fileName + "/" + fileName + "-oracle-image.csv",
				imageSM.toString());
		}

		if (journalArticleSM.length() > 0) {
			FileUtil.write(
				"../sql/" + fileName + "/" + fileName +
					"-oracle-journalarticle.csv",
				journalArticleSM.toString());
		}

		if (journalStructureSM.length() > 0) {
			FileUtil.write(
				"../sql/" + fileName + "/" + fileName +
					"-oracle-journalstructure.csv",
				journalStructureSM.toString());
		}

		if (journalTemplateSM.length() > 0) {
			FileUtil.write(
				"../sql/" + fileName + "/" + fileName +
					"-oracle-journaltemplate.csv",
				journalTemplateSM.toString());
		}

		oracle = _postBuildSQL(oracle);

		FileUtil.write(
			"../sql/" + fileName + "/" + fileName + "-oracle.sql", oracle);
	}

	protected OracleUtil() {
	}

	protected void buildCreateFile(String databaseName, boolean minimal)
		throws IOException {

		String minimalSuffix = getMinimalSuffix(minimal);

		File file = new File(
			"../sql/create" + minimalSuffix + "/create" + minimalSuffix +
				"-oracle.sql");

		StringMaker sm = new StringMaker();

		sm.append("drop user &1 cascade;\n");
		sm.append("create user &1 identified by &2;\n");
		sm.append("grant connect,resource to &1;\n");
		sm.append("connect &1/&2;\n");
		sm.append("set define off;\n");
		sm.append("\n");
		sm.append(
			FileUtil.read(
				"../sql/portal" + minimalSuffix + "/portal" + minimalSuffix +
					"-oracle.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/indexes/indexes-oracle.sql"));
		sm.append("\n\n");
		sm.append(FileUtil.read("../sql/sequences/sequences-oracle.sql"));
		sm.append("\n");
		sm.append("quit");

		FileUtil.write(file, sm.toString());
	}

	protected String getServerName() {
		return "oracle";
	}

	protected String[] getTemplate() {
		return _ORACLE;
	}

	protected String reword(String data) throws IOException {
		BufferedReader br = new BufferedReader(new StringReader(data));

		StringMaker sm = new StringMaker();

		String line = null;

		while ((line = br.readLine()) != null) {
			if (line.startsWith(ALTER_COLUMN_TYPE)) {
				String[] template = buildColumnTypeTokens(line);

				line = StringUtil.replace(
					"alter table @table@ modify @old-column@ @type@;",
					REWORD_TEMPLATE, template);
			}
			else if (line.startsWith(ALTER_COLUMN_NAME)) {
				String[] template = buildColumnNameTokens(line);

				line = StringUtil.replace(
					"alter table @table@ rename column @old-column@ to " +
						"@new-column@;",
					REWORD_TEMPLATE, template);
			}

			sm.append(line);
			sm.append("\n");
		}

		br.close();

		return sm.toString();
	}

	private void _convertToOracleCSV(String line, StringMaker sm) {
		int x = line.indexOf("values (");
		int y = line.lastIndexOf(");");

		line = line.substring(x + 8, y);

		line = StringUtil.replace(line, "sysdate, ", "20050101, ");

		sm.append(line);
		sm.append("\n");
	}

	private String _preBuildSQL(String template) throws IOException {
		template = convertTimestamp(template);
		template = StringUtil.replace(template, TEMPLATE, getTemplate());

		template = reword(template);
		template = StringUtil.replace(
			template,
			new String[] {"\\\\", "\\'", "\\\""},
			new String[] {"\\", "''", "\""});

		return template;
	}

	private String _postBuildSQL(String template) throws IOException {
		template = removeLongInserts(template);
		template = StringUtil.replace(template, "\\n", "'||CHR(10)||'");

		return template;
	}

	private static String[] _ORACLE = {
		"--", "1", "0",
		"to_date('1970-01-01 00:00:00','YYYY-MM-DD HH24:MI:SS')", "sysdate",
		" number(1, 0)", " timestamp", " number(30,20)",
		" number(30,0)", " number(30,0)",
		" varchar2(4000)", " clob", " varchar2",
		"", "commit"
	};

	private static OracleUtil _instance = new OracleUtil();

}