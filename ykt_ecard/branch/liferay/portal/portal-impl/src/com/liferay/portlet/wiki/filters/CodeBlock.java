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

package com.liferay.portlet.wiki.filters;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.stringtree.factory.AbstractStringFetcher;

/**
 * <a href="CodeBlock.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class CodeBlock extends AbstractStringFetcher {

	public Object getObject(String content) {
		StringMaker sm = new StringMaker();

		Matcher matcher = _pattern.matcher(content);

		if (matcher.matches()) {
			sm.append("<div class=\"wiki-code\">");

			String[] lines = matcher.group(1).split("\\n");

			for (int i = 0; i < lines.length; i++) {
				if (i != 0) {
					sm.append("<br />");
				}

				String translation = StringUtil.replace(
					lines[i],
					new String[] {
						"\\s",
						"<",
						">",
						"=",
						"\"",
						"'",
						"\t"
					},
					new String[] {
						"&nbsp;",
						"&lt;",
						"&gt;",
						"&#x003D;",
						"&#0034;",
						"&#0039;",
						"&nbsp;&#8594;&nbsp;"
					});

				int padlength =
					String.valueOf(lines.length).length() -
					String.valueOf(i + 1).length();

				String padding = "";

				for (int j = 0; j < padlength; j++) {
					padding += "&#0149;";
				}

				sm.append("<span class=\"wiki-code-lines\">");
				sm.append(padding + (i + 1));
				sm.append("</span>");

				sm.append(translation);
			}

			sm.append("</div>");

			content = sm.toString();
		}

		return content;
	}

	private static final Pattern _pattern = Pattern.compile(
		"\\[code\\]((.|\\n)*?)\\[/code\\]",
		Pattern.MULTILINE | Pattern.UNIX_LINES);

}