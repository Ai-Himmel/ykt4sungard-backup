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

package com.liferay.portlet;

import com.liferay.portal.kernel.util.Randomizer;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="CustomUserAttributes.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * A separate instance of this class is created every time
 * <code>renderRequest.getAttribute(PortletRequest.USER_INFO)</code> is called.
 * It is safe to cache attributes in this instance because you can assume that
 * all calls to this instance belong to the same user.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CustomUserAttributes implements Cloneable {

	public String getValue(String name, Map userInfo) {
		if (name == null) {
			return null;
		}

		if (_log.isDebugEnabled()) {
			String companyId = (String)userInfo.get(
				UserAttributes.LIFERAY_COMPANY_ID);
			String userId = (String)userInfo.get(
				UserAttributes.LIFERAY_USER_ID);

			_log.debug("Company id " + companyId);
			_log.debug("User id " + userId);
		}

		if (name.equals("user.name.random")) {
			String[] names = new String[] {"Aaa", "Bbb", "Ccc"};

			return names[Randomizer.getInstance().nextInt(3)];
		}
		else {
			return null;
		}
	}

	public Object clone() {
		return new CustomUserAttributes();
	}

	private static Log _log = LogFactory.getLog(CustomUserAttributes.class);

}