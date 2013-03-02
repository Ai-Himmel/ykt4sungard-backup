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

package com.liferay.portlet.taglib;

import com.liferay.common.taglib.ParamAncestorTagImpl;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.portlet.RenderResponseImpl;
import com.liferay.util.Validator;

import java.util.Map;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspTagException;

/**
 * <a href="ActionURLTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.24 $
 *
 */
public class ActionURLTag extends ParamAncestorTagImpl {

	public int doEndTag() throws JspTagException {
		try {
			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			String portletName = _portletName;
			if (portletName == null) {
				PortletConfigImpl portletConfig =
					(PortletConfigImpl)req.getAttribute(
						WebKeys.JAVAX_PORTLET_CONFIG);

				portletName = portletConfig.getPortletId();
			}

			RenderResponseImpl renderResponse =
				(RenderResponseImpl)req.getAttribute(
					WebKeys.JAVAX_PORTLET_RESPONSE);

			PortletURLImpl portletURL = null;

			if (isAction()) {
				portletURL =
					(PortletURLImpl)renderResponse.createActionURL(portletName);
			}
			else {
				portletURL =
					(PortletURLImpl)renderResponse.createRenderURL(portletName);
			}

			if (Validator.isNotNull(_windowState)) {
				portletURL.setWindowState(new WindowState(_windowState));
			}

			if (Validator.isNotNull(_portletMode)) {
				portletURL.setPortletMode(new PortletMode(_portletMode));
			}

			if (_secure != null) {
				portletURL.setSecure(_secure.booleanValue());
			}
			else {
				portletURL.setSecure(req.isSecure());
			}

			if (_anchor != null) {
				portletURL.setAnchor(_anchor.booleanValue());
			}

			if (_encrypt != null) {
				portletURL.setEncrypt(_encrypt.booleanValue());
			}

			Map params = getParams();

			if (params != null) {
				portletURL.setParameters(params);
			}

			String portletURLToString = portletURL.toString();

			if (Validator.isNotNull(_var)) {
				pageContext.setAttribute(_var, portletURLToString);
			}
			else {
				pageContext.getOut().print(portletURLToString);
			}

			return EVAL_PAGE;
		}
		catch (Exception e) {
			e.printStackTrace();
			throw new JspTagException(e.getMessage());
		}
		finally {
			clearParams();
		}
	}

	public boolean isAction() {
		return _action;
	}

	public void setWindowState(String windowState) {
		_windowState = windowState;
	}

	public void setPortletMode(String portletMode) {
		_portletMode = portletMode;
	}

	public void setVar(String var) {
		_var = var;
	}

	public void setSecure(boolean secure) {
		_secure = new Boolean(secure);
	}

	public void setPortletName(String portletName) {
		_portletName = portletName;
	}

	public void setAnchor(boolean anchor) {
		_anchor = new Boolean(anchor);
	}

	public void setEncrypt(boolean encrypt) {
		_encrypt = new Boolean(encrypt);
	}

	private boolean _action = true;
	private String _windowState;
	private String _portletMode;
	private String _var;
	private Boolean _secure;
	private String _portletName;
	private Boolean _anchor;
	private Boolean _encrypt;

}