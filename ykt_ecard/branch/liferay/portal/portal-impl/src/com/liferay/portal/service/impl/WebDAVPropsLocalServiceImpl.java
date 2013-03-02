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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchWebDAVPropsException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.WebDAVProps;
import com.liferay.portal.service.base.WebDAVPropsLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.webdav.WebDAVException;

import java.util.Date;

/**
 * <a href="WebDAVPropsLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class WebDAVPropsLocalServiceImpl
	extends WebDAVPropsLocalServiceBaseImpl {

	public void deleteWebDAVProps(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		try {
			webDAVPropsPersistence.removeByC_C(classNameId, classPK);
		}
		catch (NoSuchWebDAVPropsException nswdavpe) {
		}
	}

	public WebDAVProps getWebDAVProps(
			long companyId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		try {
			return webDAVPropsPersistence.findByC_C(classNameId, classPK);
		}
		catch (NoSuchWebDAVPropsException nswdpe) {
			WebDAVProps webDavProps = webDAVPropsPersistence.create(
				counterLocalService.increment());

			Date now = new Date();

			webDavProps.setCompanyId(companyId);
			webDavProps.setCreateDate(now);
			webDavProps.setModifiedDate(now);
			webDavProps.setClassNameId(classNameId);
			webDavProps.setClassPK(classPK);

			webDAVPropsPersistence.update(webDavProps);

			return webDavProps;
		}
	}

	public void storeWebDAVProps(WebDAVProps webDavProps)
		throws PortalException, SystemException {

		try {
			webDavProps.store();
		}
		catch (Exception e) {
			throw new WebDAVException("Problem trying to store WebDAVProps", e);
		}

		webDAVPropsPersistence.update(webDavProps, true);
	}

}