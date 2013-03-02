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

package com.liferay.portal.servlet;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;

import java.util.Enumeration;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="SharedSessionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 *
 */
public class SharedSessionUtil {

	public static final String[] SHARED_SESSION_ATTRIBUTES =
		PropsUtil.getArray(PropsUtil.SESSION_SHARED_ATTRIBUTES);

	public static Map getSharedSessionAttributes(HttpServletRequest req) {
		Map map = CollectionFactory.getSyncHashMap();

		HttpSession ses = req.getSession();

		Enumeration enu = ses.getAttributeNames();

		while (enu.hasMoreElements()) {
			String attrName = (String)enu.nextElement();
			Object attrValue = ses.getAttribute(attrName);

			if (attrValue != null) {
				for (int i = 0; i < SHARED_SESSION_ATTRIBUTES.length; i++) {
					if (attrName.startsWith(SHARED_SESSION_ATTRIBUTES[i])) {
						map.put(attrName, attrValue);

						if (_log.isDebugEnabled()) {
							_log.debug("Sharing " + attrName);
						}

						break;
					}
				}
			}
		}

		return map;
	}

	private static Log _log = LogFactory.getLog(SharedSessionUtil.class);

}