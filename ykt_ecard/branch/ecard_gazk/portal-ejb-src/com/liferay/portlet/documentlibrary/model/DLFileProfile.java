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

package com.liferay.portlet.documentlibrary.model;

import com.liferay.portal.model.Role;
import com.liferay.portlet.documentlibrary.service.persistence.DLFileProfilePK;
import com.liferay.util.FileUtil;
import com.liferay.util.StringUtil;

import java.util.Date;

/**
 * <a href="DLFileProfile.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 *
 */
public class DLFileProfile extends DLFileProfileModel {

	public static final double DEFAULT_VERSION = 1.0;

	public static final String[] READ_ROLES_ARRAY = {
		Role.POWER_USER, Role.USER
	};

	public static final String READ_ROLES = StringUtil.merge(READ_ROLES_ARRAY);

	public static final String[] WRITE_ROLES_ARRAY = {
		Role.POWER_USER, Role.USER
	};

	public static final String WRITE_ROLES =
		StringUtil.merge(WRITE_ROLES_ARRAY);

	public DLFileProfile() {
		super();
	}

	public DLFileProfile(DLFileProfilePK pk) {
		super(pk);
	}

	public DLFileProfile(String companyId, String repositoryId, String fileName,
						 String userId, String userName, String versionUserId,
						 String versionUserName, Date createDate,
						 Date modifiedDate, String readRoles, String writeRoles,
						 String description, double version, int size) {
		super(companyId, repositoryId, fileName, userId, userName,
			  versionUserId, versionUserName, createDate, modifiedDate,
			  readRoles, writeRoles, description, version, size);
	}

	public String getPath() {
		return FileUtil.getPath(getFileName());
	}

	public String getShortFileName() {
		return FileUtil.getShortFileName(getFileName());
	}

}