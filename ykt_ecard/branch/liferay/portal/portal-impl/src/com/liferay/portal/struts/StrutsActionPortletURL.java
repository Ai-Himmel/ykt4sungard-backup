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

package com.liferay.portal.struts;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Portlet;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.PortletURLImplWrapper;
import com.liferay.portlet.RenderResponseImpl;

import java.util.Iterator;
import java.util.Map;

/**
 * <a href="StrutsActionPortletURL.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class StrutsActionPortletURL extends PortletURLImplWrapper {

	public StrutsActionPortletURL(ActionResponseImpl res, boolean action) {
		super(res, action);

		_portlet = res.getPortlet();
		_strutsPath =
			StringPool.SLASH + _portlet.getStrutsPath() + StringPool.SLASH;
	}

	public StrutsActionPortletURL(RenderResponseImpl res, boolean action) {
		super(res, action);

		_portlet = res.getPortlet();
		_strutsPath =
			StringPool.SLASH + _portlet.getStrutsPath() + StringPool.SLASH;
	}

	public void setParameter(String name, String value) {
		if (name.equals("struts_action")) {
			if (!value.startsWith(_strutsPath)) {
				int pos = value.lastIndexOf(StringPool.SLASH);

				value = _strutsPath + value.substring(pos + 1, value.length());
			}
		}

		super.setParameter(name, value);
	}

	public void setParameters(Map params) {
		Iterator itr = params.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String name = (String)entry.getKey();
			String[] values = (String[])entry.getValue();

			if (name.equals("struts_action")) {
				for (int i = 0; i < values.length; i++) {
					String value = values[i];

					if (!value.startsWith(_strutsPath)) {
						int pos = value.lastIndexOf(StringPool.SLASH);

						value =
							_strutsPath +
								value.substring(pos + 1, value.length());

						values[i] = value;
					}
				}
			}
		}

		super.setParameters(params);
	}

	private Portlet _portlet;
	private String _strutsPath;

}