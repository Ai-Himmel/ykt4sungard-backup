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

package com.liferay.taglib.security;

import com.liferay.portal.kernel.util.MethodInvoker;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.PortalClassLoaderUtil;
import com.liferay.portal.kernel.util.StringUtil;

import java.util.HashSet;
import java.util.Set;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="EncryptTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EncryptTag extends TagSupport {

	public int doStartTag() throws JspException {
		ClassLoader contextClassLoader =
			Thread.currentThread().getContextClassLoader();

		try {
			Thread.currentThread().setContextClassLoader(
				PortalClassLoaderUtil.getClassLoader());

			MethodWrapper methodWrapper = new MethodWrapper(
				_TAG_CLASS, _TAG_DO_START_METHOD,
				new Object[] {
					_className, _style, _protocol, _unencryptedParamsSet, _url,
					_target, pageContext
				});

			MethodInvoker.invoke(methodWrapper);
		}
		catch (Exception e) {
			throw new JspException(e);
		}
		finally {
			Thread.currentThread().setContextClassLoader(contextClassLoader);
		}

		return EVAL_BODY_INCLUDE;
	}

	public int doEndTag() throws JspException {
		ClassLoader contextClassLoader =
			Thread.currentThread().getContextClassLoader();

		try {
			Thread.currentThread().setContextClassLoader(
				PortalClassLoaderUtil.getClassLoader());

			MethodWrapper methodWrapper = new MethodWrapper(
				_TAG_CLASS, _TAG_DO_END_METHOD, new Object[] {pageContext});

			MethodInvoker.invoke(methodWrapper);
		}
		catch (Exception e) {
			throw new JspException(e);
		}
		finally {
			Thread.currentThread().setContextClassLoader(contextClassLoader);
		}

		return EVAL_PAGE;
	}

	public void setClassName(String className) {
		_className = className;
	}

	public void setStyle(String style) {
		_style = style;
	}

	public void setProtocol(String protocol) {
		_protocol = protocol;
	}

	public void setUnencryptedParams(String unencryptedParams) {
		_unencryptedParamsSet.clear();

		String[] unencryptedParamsArray = StringUtil.split(unencryptedParams);

		for (int i = 0; i < unencryptedParamsArray.length; i++) {
			_unencryptedParamsSet.add(unencryptedParamsArray[i]);
		}
	}

	public void setUrl(String url) {
		_url = url;
	}

	public void setTarget(String target) {
		_target = target;
	}

	private static final String _TAG_CLASS =
		"com.liferay.portal.servlet.taglib.security.EncryptTagUtil";

	private static final String _TAG_DO_START_METHOD = "doStartTag";

	private static final String _TAG_DO_END_METHOD = "doEndTag";

	private String _className;
	private String _style;
	private String _protocol;
	private Set _unencryptedParamsSet = new HashSet();
	private String _url;
	private String _target;

}