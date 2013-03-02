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

package com.liferay.portlet.enterpriseadmin.search;

import com.liferay.portal.kernel.dao.search.DisplayTerms;
import com.liferay.portal.kernel.util.ParamUtil;

import javax.portlet.RenderRequest;

/**
 * <a href="OrganizationDisplayTerms.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class OrganizationDisplayTerms extends DisplayTerms {

	public static final String TYPE = "type";

	public static final String NAME = "name";

	public static final String STREET = "street";

	public static final String CITY = "city";

	public static final String ZIP = "zip";

	public static final String COUNTRY_ID = "countryId";

	public static final String REGION_ID = "regionId";

	public static final String PARENT_ORGANIZATION_ID = "parentOrganizationId";

	public OrganizationDisplayTerms(RenderRequest req) {
		super(req);

		type = ParamUtil.getInteger(req, TYPE);
		name = ParamUtil.getString(req, NAME);
		street = ParamUtil.getString(req, STREET);
		city = ParamUtil.getString(req, CITY);
		zip = ParamUtil.getString(req, ZIP);
		regionId = ParamUtil.getLong(req, REGION_ID);
		countryId = ParamUtil.getLong(req, COUNTRY_ID);
		parentOrganizationId = ParamUtil.getLong(req, PARENT_ORGANIZATION_ID);
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getName() {
		return name;
	}

	public String getStreet() {
		return street;
	}

	public String getCity() {
		return city;
	}

	public String getZip() {
		return zip;
	}

	public long getRegionId() {
		return regionId;
	}

	public long getCountryId() {
		return countryId;
	}

	public long getParentOrganizationId() {
		return parentOrganizationId;
	}

	protected int type;
	protected String name;
	protected String street;
	protected String city;
	protected String zip;
	protected long regionId;
	protected long countryId;
	protected long parentOrganizationId;

}