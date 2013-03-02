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

import com.liferay.portlet.mail.util.*;
import com.liferay.util.*;
import com.liferay.util.xml.*;

import de.hunsicker.jalopy.storage.*;

import java.awt.image.*;

import java.io.*;

import java.lang.reflect.*;

import java.net.*;

import java.sql.*;

import java.util.*;

import javax.imageio.*;

import net.jmge.gif.Gif89Encoder;

import org.apache.oro.text.perl.Perl5Util;

import org.apache.tools.ant.DirectoryScanner;

import org.jdom.*;
import org.jdom.input.*;

/**
 * <a href="Test.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Test {

	public static void main(String[] args) {
		try {
			Convention convention = Convention.getInstance();

			convention.putBoolean(ConventionKeys.SORT, false);

			convention.putInt(ConventionKeys.BLANK_LINES_AFTER_HEADER, 1);
			convention.putBoolean(ConventionKeys.HEADER, true);
			convention.put(ConventionKeys.HEADER_TEXT, FileUtil.read("../copyright.txt"));

			convention.putInt(ConventionKeys.BLANK_LINES_AFTER_IMPORT, 1);

			convention.putInt(ConventionKeys.INDENT_SIZE_TABS, 4);
			convention.putBoolean(ConventionKeys.INDENT_WITH_TABS, true);

			convention.putBoolean(ConventionKeys.INSERT_TRAILING_NEWLINE, false);

			convention.putBoolean(ConventionKeys.BRACE_NEWLINE_RIGHT, true);
			convention.putInt(ConventionKeys.INDENT_SIZE_BRACE_RIGHT_AFTER, 0);

			convention.putBoolean(ConventionKeys.SPACE_AFTER_CAST, false);

			/*
			convention.putInt(ConventionKeys.BLANK_LINES_AFTER_BRACE_LEFT, 1);
			//convention.putInt(ConventionKeys.BLANK_LINES_AFTER_CLASS, 1);
			//convention.putInt(ConventionKeys.BLANK_LINES_AFTER_INTERFACE, 1);
			convention.putInt(ConventionKeys.BLANK_LINES_AFTER_DECLARATION, 1);
			convention.putInt(ConventionKeys.BLANK_LINES_KEEP_UP_TO, 1);

			//convention.putBoolean(ConventionKeys.INDENT_CONTINUATION_IF_TERNARY, true);
			convention.putInt(ConventionKeys.INDENT_SIZE_CONTINUATION, 0);
			//convention.putBoolean(ConventionKeys.INDENT_USE_PARAMS_METHOD_CALL, true);

			convention.putBoolean(ConventionKeys.LINE_WRAP_BEFORE_THROWS, true);
			convention.putInt(ConventionKeys.INDENT_SIZE_THROWS, 4);
			*/

			String classMask =
				"/**\n" +
				" * <a href=\"$fileName$.html\"><b><i>View Source</i></b></a>\n" +
				" *\n" +
				" * @author $author$\n" +
				" *\n" +
				" */";

			convention.putInt(ConventionKeys.COMMENT_JAVADOC_CLASS_MASK, 1);
			convention.putBoolean(ConventionKeys.COMMENT_JAVADOC_REMOVE, true);
			convention.putBoolean(ConventionKeys.COMMENT_REMOVE_MULTI_LINE, true);
			convention.putBoolean(ConventionKeys.COMMENT_REMOVE_SINGLE_LINE, true);
			convention.put(ConventionKeys.COMMENT_JAVADOC_TEMPLATE_CLASS, classMask);
			convention.put(ConventionKeys.COMMENT_JAVADOC_TEMPLATE_INTERFACE, classMask);

			convention.exportSettings(new FileOutputStream(new File("../tools/jalopy.xml")), Convention.EXTENSION_XML);

			/*
			com.liferay.portlet.messageboards.util.Preference pref =
				new com.liferay.portlet.messageboards.util.Preference();

			com.liferay.portlet.messageboards.util.PreferenceSerializer prefSerializer =
				new com.liferay.portlet.messageboards.util.PreferenceSerializer();

			System.out.println(prefSerializer.toPrefString(pref));
			*/

			/*
			String basedir = "../portal-web/";

			DirectoryScanner ds = new DirectoryScanner();
			ds.setIncludes(new String[] {"**\\*.jsp"});
			ds.setBasedir(basedir);
			ds.scan();

			String[] files = ds.getIncludedFiles();

			for (int i = 0; i < files.length; i++) {
				File file = new File(basedir + files[i]);

				String content = FileUtil.read(file);

				BufferedReader br =
					new BufferedReader(new StringReader(content));

				StringBuffer sb = new StringBuffer();
				String line = null;

				while ((line = br.readLine()) != null) {
					int x = line.indexOf("<%=");
					int y = line.indexOf("%>", x);

					if ((x != -1) && (y != -1) && ((line.indexOf("<jsp:") != -1) || (line.indexOf("<util:") != -1))) {
						try {
							String regexp = line.substring(
								x, y + 2);

							if (regexp.indexOf("\\\"") != -1) {
								regexp = regexp.substring(0, regexp.length() - 2);

								if (regexp.indexOf("\\\"") != -1) {
									String patched = StringUtil.replace(regexp, "\\\"", "\"");

									sb.append(line.substring(0, x) + patched + line.substring(y, line.length()));

									//return;
								}
								else {
									sb.append(line);
								}
							}
							else {
								sb.append(line);
							}
						}
						catch (Exception exc) {
							sb.append(line);
						}
					}
					else if ((x != -1) && (y == -1)) {
						System.out.println("ERROR " + file.toString());

						return;
					}
					else {
						sb.append(line);
					}

					sb.append("\n");
				}

				sb.delete(sb.length() - 1, sb.length());

				br.close();

				String newContent = sb.toString();

				//System.out.println(content.length());
				//System.out.println(newContent.length());

				if ((newContent != null) && !content.equals(newContent)) {
					FileUtil.write(file, newContent);

					System.out.println(file.toString());

					//break;
				}
			}
			*/

			/*
			String basedir = "../portal-web/";

			DirectoryScanner ds = new DirectoryScanner();
			ds.setIncludes(new String[] {"**\\*.jsp"});
			ds.setBasedir(basedir);
			ds.scan();

			String[] files = ds.getIncludedFiles();

			for (int i = 0; i < files.length; i++) {
				File file = new File(basedir + files[i]);

				String content = FileUtil.read(file);

				BufferedReader br =
					new BufferedReader(new StringReader(content));

				StringBuffer sb = new StringBuffer();
				String line = null;

				while ((line = br.readLine()) != null) {
					int x = line.indexOf("<%=");
					int y = line.indexOf("%>", x);

					if ((x != -1) && (y != -1) && ((line.indexOf("<c:") != -1) || (line.indexOf("<jsp:") != -1) || (line.indexOf("<util:") != -1))) {
						try {
							String regexp = line.substring(
								x, y + 2);

							if (regexp.indexOf("\\\"") == -1) {
								regexp = regexp.substring(0, regexp.length() - 2);

								if (regexp.indexOf("\"") != -1) {
									String patched = StringUtil.replace(regexp, "\"", "\\\"");

									sb.append(line.substring(0, x) + patched + line.substring(y, line.length()));

									//return;
								}
								else {
									sb.append(line);
								}
							}
							else {
								sb.append(line);
							}
						}
						catch (Exception exc) {
							sb.append(line);
						}
					}
					else if ((x != -1) && (y == -1)) {
						System.out.println("ERROR " + file.toString());

						return;
					}
					else {
						sb.append(line);
					}

					sb.append("\n");
				}

				if (sb.length() > 0) {
					sb.delete(sb.length() - 1, sb.length());
				}

				br.close();

				String newContent = sb.toString();

				//System.out.println(content.length());
				//System.out.println(newContent.length());

				if ((newContent != null) && !content.equals(newContent)) {
					FileUtil.write(file, newContent);

					System.out.println(file.toString());

					//break;
				}
			}
			*/

			/*
			String basedir = "../portal-web/";

			DirectoryScanner ds = new DirectoryScanner();
			ds.setIncludes(new String[] {"**\\*.jsp"});
			ds.setBasedir(basedir);
			ds.scan();

			String[] files = ds.getIncludedFiles();

			for (int i = 0; i < files.length; i++) {
				File file = new File(basedir + files[i]);

				String content = FileUtil.read(file);

				BufferedReader br =
					new BufferedReader(new StringReader(content));

				StringBuffer sb = new StringBuffer();
				String line = null;

				while ((line = br.readLine()) != null) {
					int x = line.indexOf("\"<%=");
					int y = line.indexOf("%>\"", x);

					if ((x != -1) && (y != -1) && ((line.indexOf("<c:") != -1) || (line.indexOf("<jsp:") != -1) || (line.indexOf("<liferay:") != -1))) {
						try {
							String regexp = line.substring(
								x, y + 3);

							if (regexp.indexOf("\\\"") == -1) {
								regexp = regexp.substring(1, regexp.length() - 1);

								if (regexp.indexOf("\"") != -1) {
									//System.out.println(regexp);

									sb.append(line.substring(0, x));
									sb.append("'");
									sb.append(regexp);
									sb.append("'");
									sb.append(line.substring(y + 3, line.length()));
								}
								else {
									sb.append(line);
								}
							}
							else {
								sb.append(line);
							}
						}
						catch (Exception exc) {
							sb.append(line);
						}
					}
					//else if ((x != -1) && (y == -1)) {
					//	System.out.println("ERROR " + file.toString());
					//
					//	return;
					//}
					else {
						sb.append(line);
					}

					sb.append("\n");
				}

				if (sb.length() > 0) {
					sb.delete(sb.length() - 1, sb.length());
				}

				br.close();

				String newContent = sb.toString();

				//System.out.println(content.length());
				//System.out.println(newContent.length());

				if ((newContent != null) && !content.equals(newContent)) {
					FileUtil.write(file, newContent);

					System.out.println(file.toString());

					break;
				}
			}
			*/
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}