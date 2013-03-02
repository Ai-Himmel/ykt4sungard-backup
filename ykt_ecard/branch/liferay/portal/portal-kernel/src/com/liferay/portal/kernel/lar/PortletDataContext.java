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

package com.liferay.portal.kernel.lar;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.zip.ZipReader;
import com.liferay.portal.kernel.zip.ZipWriter;

import java.io.Serializable;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * <a href="PortletDataContext.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * Holds context information that is used during exporting adn importing portlet
 * data.
 * </p>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public interface PortletDataContext extends Serializable {

	public long getCompanyId();

	public long getGroupId();

	public long getPlid();

	public void setPlid(long plid);

	public Map getParameterMap();

	public boolean getBooleanParameter(String namespace, String name);

	public Set getPrimaryKeys();

	public boolean addPrimaryKey(Class classObj, Object primaryKey);

	public boolean hasPrimaryKey(Class classObj, Object primaryKey);

	public Map getComments();

	public void addComments(Class classObj, Object primaryKey)
		throws PortalException, SystemException;

	public void addComments(String className, Object primaryKey, List messages)
		throws PortalException, SystemException;

	public void importComments(
			Class classObj, Object primaryKey, Object newPrimaryKey,
			long groupId)
		throws PortalException, SystemException;

	public Map getRatingsEntries();

	public void addRatingsEntries(Class classObj, Object primaryKey)
		throws PortalException, SystemException;

	public void addRatingsEntries(
			String className, Object primaryKey, List entries)
		throws PortalException, SystemException;

	public void importRatingsEntries(
			Class classObj, Object primaryKey, Object newPrimaryKey)
		throws PortalException, SystemException;

	public String[] getTagsEntries(Class classObj, Object primaryKey);

	public String[] getTagsEntries(String className, Object primaryKey);

	public Map getTagsEntries();

	public void addTagsEntries(Class classObj, Object classPK)
		throws PortalException, SystemException;

	public void addTagsEntries(
			String className, Object classPK, String[] values)
		throws PortalException, SystemException;

	public String getDataStrategy();

	public UserIdStrategy getUserIdStrategy() throws SystemException;

	public long getUserId(String userUuid) throws SystemException;

	public ZipReader getZipReader();

	public ZipWriter getZipWriter();

}