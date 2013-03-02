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

package com.liferay.portlet.jcvs.action;

import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.jcvs.servlet.JCVSServletRequest;
import com.liferay.util.ParamUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="DownloadAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class DownloadAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			String jcvsCmd = ParamUtil.getString(req, "jcvs_cmd");

			ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

			ServletContext jcvsCtx = ctx.getContext("/jcvs");

			RequestDispatcher jcvsRd = jcvsCtx.getRequestDispatcher("/jcvs");

			JCVSServletRequest jcvsReq =
				new JCVSServletRequest(req, null, jcvsCmd);

			String fileName = null;

			try {
				fileName = jcvsCmd.substring(
					jcvsCmd.lastIndexOf("/") + 1, jcvsCmd.length());
			}
			catch (Exception e) {
			}

			if (fileName == null || !fileName.endsWith(".zip")) {
				fileName = "cvs.zip";
			}

			res.setHeader(
				ServletResponseUtil.CACHE_CONTROL, ServletResponseUtil.PUBLIC);
			res.setHeader(
				ServletResponseUtil.PRAGMA, ServletResponseUtil.PUBLIC);

			res.setHeader(
				ServletResponseUtil.CONTENT_DISPOSITION,
				"attachment; filename=\"" + fileName + "\"");

			jcvsRd.include(jcvsReq, res);

			return mapping.findForward(Constants.COMMON_NULL);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}