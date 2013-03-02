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

package com.liferay.portal.apache.bridges.struts;

import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.PortletURLImplWrapper;
import com.liferay.portlet.RenderResponseImpl;
import com.liferay.util.HttpUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.portals.bridges.struts.StrutsPortletURL;

/**
 * <a href="LiferayStrutsPortletURLImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class LiferayStrutsPortletURLImpl extends PortletURLImplWrapper {

	public LiferayStrutsPortletURLImpl(ActionResponseImpl res, boolean action) {
		super(res, action);
	}

	public LiferayStrutsPortletURLImpl(RenderResponseImpl res, boolean action) {
		super(res, action);
	}

	public void setParameter(String name, String value) {
		super.setParameter(name, value);

		// Add parameters from the query string because bridges passes these
		// through instead of setting them on the portlet URL

		String decodedValue = HttpUtil.decodeURL(value);

		try {
			if (name.equals(StrutsPortletURL.PAGE)) {
				String[] urlComponents = decodedValue.split("\\?", 2);

				if (urlComponents.length != 2) {
					return;
				}

				String[] nameValue = urlComponents[1].split("\\&");

				for (int i = 0; i < nameValue.length; i++) {
					String[] nameValuePair = nameValue[i].split("\\=", 2);

					if (nameValuePair.length == 2) {
						super.setParameter(nameValuePair[0], nameValuePair[1]);
					}
					else if (nameValuePair.length == 1) {
						super.setParameter(nameValuePair[0], "true");
					}
				}
			}
		}
		catch (Throwable t) {
			_log.error("Could not parse Struts page query string " + value, t);
		}
	}

	private static Log _log =
		LogFactory.getLog(LiferayStrutsPortletURLImpl.class);

}