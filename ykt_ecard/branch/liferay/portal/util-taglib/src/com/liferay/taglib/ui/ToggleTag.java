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

package com.liferay.taglib.ui;

import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.MethodInvoker;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.kernel.util.PortalClassLoaderUtil;
import com.liferay.taglib.util.IncludeTag;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.JspException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ToggleTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ToggleTag extends IncludeTag {

	public static void doTag(
			String id, String onImage, String offImage, boolean defaultOn,
			String stateVar, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		doTag(_PAGE, id, onImage, offImage, defaultOn, stateVar, ctx, req, res);
	}

	public static void doTag(
			String page, String id, String onImage, String offImage,
			boolean defaultOn, String stateVar, ServletContext ctx,
			HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		ClassLoader contextClassLoader =
			Thread.currentThread().getContextClassLoader();

		try {
			Thread.currentThread().setContextClassLoader(
				PortalClassLoaderUtil.getClassLoader());

			Object pageWrapper = page;

			if (pageWrapper == null) {
				pageWrapper = new NullWrapper(String.class.getName());
			}

			Object idWrapper = id;

			if (idWrapper == null) {
				idWrapper = new NullWrapper(String.class.getName());
			}

			Object onImageWrapper = onImage;

			if (onImageWrapper == null) {
				onImageWrapper = new NullWrapper(String.class.getName());
			}

			Object offImageWrapper = offImage;

			if (offImageWrapper == null) {
				offImageWrapper = new NullWrapper(String.class.getName());
			}

			Object stateVarWrapper = stateVar;

			if (stateVarWrapper == null) {
				stateVarWrapper = new NullWrapper(String.class.getName());
			}

			MethodWrapper methodWrapper = new MethodWrapper(
				_TAG_CLASS, _TAG_DO_END_METHOD,
				new Object[] {
					pageWrapper, idWrapper, onImageWrapper, offImageWrapper,
					new BooleanWrapper(defaultOn), stateVarWrapper, ctx, req,
					res
				});

			MethodInvoker.invoke(methodWrapper);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw e;
		}
		finally {
			Thread.currentThread().setContextClassLoader(contextClassLoader);
		}
	}

	public int doEndTag() throws JspException {
		try {
			ServletContext ctx = getServletContext();
			HttpServletRequest req = getServletRequest();
			StringServletResponse res = getServletResponse();

			doTag(
				_id, _onImage, _offImage, _defaultOn, _stateVar, ctx, req, res);

			pageContext.getOut().print(res.getString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public void setId(String id) {
		_id = id;
	}

	public void setOnImage(String onImage) {
		_onImage = onImage;
	}

	public void setOffImage(String offImage) {
		_offImage = offImage;
	}

	public void setDefaultOn(boolean defaultOn) {
		_defaultOn = defaultOn;
	}

	public void setStateVar(String stateVar) {
		_stateVar = stateVar;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _TAG_CLASS =
		"com.liferay.portal.servlet.taglib.ui.ToggleTagUtil";

	private static final String _TAG_DO_END_METHOD = "doEndTag";

	private static final String _PAGE = "/html/taglib/ui/toggle/page.jsp";

	private static Log _log = LogFactory.getLog(ToggleTag.class);

	private String _id;
	private String _onImage;
	private String _offImage;
	private boolean _defaultOn;
	private String _stateVar;

}