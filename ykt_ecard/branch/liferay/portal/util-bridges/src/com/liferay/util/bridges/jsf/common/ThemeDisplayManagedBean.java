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

package com.liferay.util.bridges.jsf.common;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;

import javax.faces.context.FacesContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ThemeDisplayManagedBean.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class is designed to be a convenient JSF managed bean that can be used
 * to get portal related information (such as the user's time zone).
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class ThemeDisplayManagedBean {

	public User getUser() {
		FacesContext facesContext = FacesContext.getCurrentInstance();

		String remoteUser = facesContext.getExternalContext().getRemoteUser();

		try {
			long userId = GetterUtil.getLong(remoteUser);

			return UserLocalServiceUtil.getUserById(userId);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		return null;
	}

	private static Log _log = LogFactory.getLog(User.class);

}