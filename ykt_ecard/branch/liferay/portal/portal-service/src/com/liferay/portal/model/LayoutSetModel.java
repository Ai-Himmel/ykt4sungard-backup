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

package com.liferay.portal.model;


/**
 * <a href="LayoutSetModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>LayoutSet</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.LayoutSet
 * @see com.liferay.portal.service.model.impl.LayoutSetImpl
 * @see com.liferay.portal.service.model.impl.LayoutSetModelImpl
 *
 */
public interface LayoutSetModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public long getLayoutSetId();

	public void setLayoutSetId(long layoutSetId);

	public long getGroupId();

	public void setGroupId(long groupId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public boolean getPrivateLayout();

	public boolean isPrivateLayout();

	public void setPrivateLayout(boolean privateLayout);

	public boolean getLogo();

	public boolean isLogo();

	public void setLogo(boolean logo);

	public long getLogoId();

	public void setLogoId(long logoId);

	public String getThemeId();

	public void setThemeId(String themeId);

	public String getColorSchemeId();

	public void setColorSchemeId(String colorSchemeId);

	public String getWapThemeId();

	public void setWapThemeId(String wapThemeId);

	public String getWapColorSchemeId();

	public void setWapColorSchemeId(String wapColorSchemeId);

	public String getCss();

	public void setCss(String css);

	public int getPageCount();

	public void setPageCount(int pageCount);

	public String getVirtualHost();

	public void setVirtualHost(String virtualHost);

	public LayoutSet toEscapedModel();
}