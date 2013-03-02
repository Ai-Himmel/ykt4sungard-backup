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

import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.LiferayWindowState;
import com.liferay.util.lang.FastStringBuffer;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="UploadProgressTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Keith R. Davis
 * @version $Revision: 1.5 $
 *
 */
public class UploadProgressTag extends TagSupport {

	public int doEndTag() throws JspTagException {
		try {
			FastStringBuffer sb = new FastStringBuffer();

			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			String mainPath =
				(String)req.getSession().getAttribute(WebKeys.MAIN_PATH);

			sb.append("var winWidth = 400;");
			sb.append("var winHeight = 140;");
			sb.append("var winLeft = (screen.width - winWidth) / 2;");
			sb.append("var winTop = (screen.height - winHeight) / 2;");
			sb.append("var uploadProgressWindow = window.open('");
			sb.append(mainPath);
			sb.append("/portal/upload_progress?p_p_state=");
			sb.append(LiferayWindowState.POP_UP);
			sb.append("&cache_control=0', 'uploadProgress', 'top=' + winTop + ',left=' + winLeft + ',height=' + winHeight + ',width=' + winWidth + ',directories=no,location=no,menubar=no,resizable=no,scrollbars=no,status=no,toolbar=no');");
			sb.append("uploadProgressWindow.focus();");

			pageContext.getOut().print(sb.toString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
	}

}