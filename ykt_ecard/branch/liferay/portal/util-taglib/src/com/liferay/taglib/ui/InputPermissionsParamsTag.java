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

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.permission.ResourceActionsUtil;
import com.liferay.portal.util.WebKeys;

import java.util.List;

import javax.portlet.RenderResponse;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="InputPermissionsParamsTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputPermissionsParamsTag extends TagSupport {

	public int doEndTag() throws JspException {
		try {
			ServletRequest req = pageContext.getRequest();

			RenderResponse res = (RenderResponse)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_RESPONSE);

			Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

			Group group = layout.getGroup();

			List supportedActions =
				ResourceActionsUtil.getModelResourceActions(_modelName);
			List communityDefaultActions =
				ResourceActionsUtil.getModelResourceCommunityDefaultActions(
					_modelName);
			List guestDefaultActions =
				ResourceActionsUtil.getModelResourceGuestDefaultActions(
					_modelName);
			List guestUnsupportedActions =
				ResourceActionsUtil.getModelResourceGuestUnsupportedActions(
					_modelName);

			StringMaker sm = new StringMaker();

			for (int i = 0; i < supportedActions.size(); i++) {
				String action = (String)supportedActions.get(i);

				boolean communityChecked = communityDefaultActions.contains(
					action);
				boolean guestChecked = guestDefaultActions.contains(action);
				boolean guestDisabled = guestUnsupportedActions.contains(
					action);

				if (guestDisabled) {
					guestChecked = false;
				}

				if (group.isCommunity() || group.isOrganization()) {
					if (communityChecked) {
						sm.append(StringPool.AMPERSAND);
						sm.append(res.getNamespace());
						sm.append("communityPermissions=");
						sm.append(action);
					}
				}

				if (guestChecked) {
					sm.append(StringPool.AMPERSAND);
					sm.append(res.getNamespace());
					sm.append("guestPermissions=");
					sm.append(action);
				}
			}

			pageContext.getOut().print(sm.toString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspException(e);
		}
	}

	public void setModelName(String modelName) {
		_modelName = modelName;
	}

	private String _modelName;

}