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

package com.liferay.portlet.softwarecatalog.model;

import com.liferay.portal.model.BaseModel;

/**
 * <a href="SCProductScreenshotModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>SCProductScreenshot</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.softwarecatalog.service.model.SCProductScreenshot
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductScreenshotImpl
 * @see com.liferay.portlet.softwarecatalog.service.model.impl.SCProductScreenshotModelImpl
 *
 */
public interface SCProductScreenshotModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public long getProductScreenshotId();

	public void setProductScreenshotId(long productScreenshotId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public long getGroupId();

	public void setGroupId(long groupId);

	public long getProductEntryId();

	public void setProductEntryId(long productEntryId);

	public long getThumbnailId();

	public void setThumbnailId(long thumbnailId);

	public long getFullImageId();

	public void setFullImageId(long fullImageId);

	public int getPriority();

	public void setPriority(int priority);

	public SCProductScreenshot toEscapedModel();
}