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

package com.liferay.common.taglib;

import com.liferay.util.Http;
import com.liferay.util.lang.FastStringBuffer;

import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="BibleTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class BibleTag extends TagSupport {

	public int doStartTag() throws JspTagException {
		try {
			FastStringBuffer sb = new FastStringBuffer();

			// Open anchor

			sb.append("<a ");

			// Class

			sb.append("class=\"").append(_className).append("\" ");

			// HREF

			sb.append("href=\"http://www.biblegateway.com/cgi-bin/bible?");
			sb.append("showfn=yes&showxref=yes&passage=");
			sb.append(Http.encodeURL(_verse));
			sb.append("&version=ESV&showfn_cb=on&showxref_cb=on\" ");

			// Target

			sb.append("target=\"_blank\"");

			// Close anchor

			sb.append(">");

			pageContext.getOut().print(sb.toString());

			return EVAL_BODY_INCLUDE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
	}

	public int doEndTag() throws JspTagException {
		try {
			pageContext.getOut().print("</a>");

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
	}

	public void setClassName(String className) {
		_className = className;
	}

	public void setTarget(String target) {
		_target = target;
	}

	public void setVerse(String verse) {
		_verse = verse;
	}

	private String _className;
	private String _target;
	private String _verse;

}