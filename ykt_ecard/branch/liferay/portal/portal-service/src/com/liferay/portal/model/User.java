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
 * <a href="User.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>User</code> table
 * in the database.
 * </p>
 *
 * <p>
 * Customize <code>com.liferay.portal.service.model.impl.UserImpl</code>
 * and rerun the ServiceBuilder to generate the new methods.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.UserModel
 * @see com.liferay.portal.service.model.impl.UserImpl
 * @see com.liferay.portal.service.model.impl.UserModelImpl
 *
 */
public interface User extends UserModel {
	public java.lang.String getCompanyMx();

	public boolean hasCompanyMx();

	public boolean hasCompanyMx(java.lang.String emailAddress);

	public java.lang.String getLogin()
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public com.liferay.portal.model.PasswordPolicy getPasswordPolicy()
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException;

	public java.lang.String getPasswordUnencrypted();

	public void setPasswordUnencrypted(java.lang.String passwordUnencrypted);

	public boolean getPasswordModified();

	public boolean isPasswordModified();

	public void setPasswordModified(boolean passwordModified);

	public java.util.Locale getLocale();

	public void setLanguageId(java.lang.String languageId);

	public java.util.TimeZone getTimeZone();

	public void setTimeZoneId(java.lang.String timeZoneId);

	public com.liferay.portal.model.Contact getContact();

	public java.lang.String getFirstName();

	public java.lang.String getMiddleName();

	public java.lang.String getLastName();

	public java.lang.String getFullName();

	public boolean getMale();

	public boolean isMale();

	public boolean getFemale();

	public boolean isFemale();

	public java.util.Date getBirthday();

	public com.liferay.portal.model.Group getGroup();

	public com.liferay.portal.model.Organization getOrganization();

	public long[] getOrganizationIds();

	public java.util.List getOrganizations();

	public boolean hasOrganization();

	public com.liferay.portal.model.Organization getLocation();

	public long getLocationId();

	public boolean hasLocation();

	public int getPrivateLayoutsPageCount();

	public boolean hasPrivateLayouts();

	public int getPublicLayoutsPageCount();

	public boolean hasPublicLayouts();

	public boolean isLayoutsRequired();

	public java.util.List getMyPlaces();

	public boolean hasMyPlaces();

	public java.lang.String getDisplayURL(java.lang.String portalURL);
}