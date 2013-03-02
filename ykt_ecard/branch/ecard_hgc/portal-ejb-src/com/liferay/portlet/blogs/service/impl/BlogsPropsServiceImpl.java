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

package com.liferay.portlet.blogs.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.blogs.NoSuchPropsException;
import com.liferay.portlet.blogs.PropsQuantityException;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.model.BlogsProps;
import com.liferay.portlet.blogs.service.persistence.BlogsEntryUtil;
import com.liferay.portlet.blogs.service.persistence.BlogsPropsUtil;
import com.liferay.portlet.blogs.service.spring.BlogsEntryServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsPropsService;

import java.util.Date;
import java.util.List;

/**
 * <a href="BlogsPropsServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsPropsServiceImpl
	extends PrincipalBean implements BlogsPropsService {

	// Business methods

	public BlogsProps getProps(String propsId)
		throws PortalException, SystemException {

		return BlogsPropsUtil.findByPrimaryKey(propsId);
	}

	public List getPropsList(String entryId) throws SystemException {
		return BlogsPropsUtil.findByEntryId(entryId);
	}

	public List getPropsList(String entryId, int quantity)
		throws SystemException {

		return BlogsPropsUtil.findByE_Q(entryId, quantity);
	}

	public BlogsProps updateProps(String entryId, int quantity)
		throws PortalException, SystemException {

		_validate(entryId, quantity);

		User user = getUser();

		BlogsProps props = null;

		Date now = new Date();

		try	{
			props = BlogsPropsUtil.findByU_E(user.getUserId(), entryId);
		}
		catch (NoSuchPropsException nspe) {
			String propsId = Long.toString(CounterServiceUtil.increment(
				BlogsProps.class.getName()));

			props = BlogsPropsUtil.create(propsId);

			props.setCompanyId(user.getCompanyId());
			props.setUserId(user.getUserId());
			props.setUserName(user.getFullName());
			props.setCreateDate(now);
		}

		props.setModifiedDate(now);
		props.setEntryId(entryId);
		props.setQuantity(quantity);

		BlogsPropsUtil.update(props);

		// Update props count

		BlogsEntryServiceUtil.updatePropsCount(entryId);

		return props;
	}

	// Private methods

	private void _validate(String entryId, int quantity)
		throws PortalException, SystemException {

		BlogsEntry entry = BlogsEntryUtil.findByPrimaryKey(entryId);

		if (!entry.getCompanyId().equals(getUser().getCompanyId())) {
			throw new PrincipalException();
		}

		if ((quantity != 1) && (quantity != 2)) {
			throw new PropsQuantityException();
		}
	}

}