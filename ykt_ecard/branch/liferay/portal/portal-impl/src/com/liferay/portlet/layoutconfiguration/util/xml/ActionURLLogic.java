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

package com.liferay.portlet.layoutconfiguration.util.xml;

import com.liferay.portal.kernel.portlet.LiferayPortletURL;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.RenderResponseImpl;

import java.io.StringReader;

import javax.portlet.RenderResponse;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ActionURLLogic.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionURLLogic extends RuntimeLogic {

	public static final String OPEN_TAG = "<runtime-action-url";

	public static final String CLOSE_1_TAG = "</runtime-action-url>";

	public static final String CLOSE_2_TAG = "/>";

	public ActionURLLogic(RenderResponse res) {
		_res = (RenderResponseImpl)res;
	}

	public String getOpenTag() {
		return OPEN_TAG;
	}

	public String getClose1Tag() {
		return CLOSE_1_TAG;
	}

	public void processXML(StringMaker sm, String xml) throws Exception {
		SAXReader reader = new SAXReader();

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		LiferayPortletURL portletURL =
			(LiferayPortletURL)_res.createPortletURL(isAction());

		String portletId = root.attributeValue("portlet-name");

		if (portletId != null) {
			portletId = PortalUtil.getJsSafePortletId(portletId);

			portletURL.setPortletId(portletId);
		}

		for (int i = 1;; i++) {
			String paramName = root.attributeValue("param-name-" + i);
			String paramValue = root.attributeValue("param-value-" + i);

			if ((paramName == null) || (paramValue == null))  {
				break;
			}

			portletURL.setParameter(paramName, paramValue);
		}

		sm.append(portletURL.toString());
	}

	public boolean isAction() {
		return _action;
	}

	private RenderResponseImpl _res;
	private boolean _action = false;

}