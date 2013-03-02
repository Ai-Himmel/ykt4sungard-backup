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
import com.liferay.portlet.blogs.LinkNameException;
import com.liferay.portlet.blogs.LinkURLException;
import com.liferay.portlet.blogs.model.BlogsLink;
import com.liferay.portlet.blogs.service.persistence.BlogsLinkUtil;
import com.liferay.portlet.blogs.service.spring.BlogsLinkLocalServiceUtil;
import com.liferay.portlet.blogs.service.spring.BlogsLinkService;
import com.liferay.util.Validator;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.Date;
import java.util.List;

/**
 * <a href="BlogsLinkServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class BlogsLinkServiceImpl
	extends PrincipalBean implements BlogsLinkService {

	// Business methods

	public BlogsLink addLink(String name, String url)
		throws PortalException, SystemException {

		_validate(name, url);

		User user = getUser();

		String linkId = Long.toString(CounterServiceUtil.increment(
			BlogsLink.class.getName()));

		BlogsLink link = BlogsLinkUtil.create(linkId);

		Date now = new Date();

		link.setCompanyId(user.getCompanyId());
		link.setUserId(user.getUserId());
		link.setCreateDate(now);
		link.setModifiedDate(now);
		link.setName(name);
		link.setUrl(url);

		BlogsLinkUtil.update(link);

		return link;
	}

	public void deleteLink(String linkId)
		throws PortalException, SystemException {

		BlogsLink link = BlogsLinkUtil.findByPrimaryKey(linkId);

		deleteLink(link);
	}

	public void deleteLink(BlogsLink link)
		throws PortalException, SystemException {

		if (!link.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		BlogsLinkLocalServiceUtil.deleteLink(link.getLinkId());
	}

	public BlogsLink getLink(String linkId)
		throws PortalException, SystemException {

		return BlogsLinkUtil.findByPrimaryKey(linkId);
	}

	public List getLinks(String userId) throws SystemException {
		return BlogsLinkUtil.findByUserId(userId);
	}

	public int getLinksSize(String userId) throws SystemException {
		return BlogsLinkUtil.countByUserId(userId);
	}

	public BlogsLink updateLink(String linkId, String name, String url)
		throws PortalException, SystemException {

		_validate(name, url);

		BlogsLink link = BlogsLinkUtil.findByPrimaryKey(linkId);

		if (!link.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		link.setModifiedDate(new Date());
		link.setName(name);
		link.setUrl(url);

		BlogsLinkUtil.update(link);

		return link;
	}

	// Private methods

	private void _validate(String name, String url) throws PortalException {
		if (Validator.isNull(name)) {
			throw new LinkNameException();
		}

		if (Validator.isNull(url)) {
			throw new LinkURLException();
		}
		else {
			try {
				new URL(url);
			}
			catch (MalformedURLException murle) {
				throw new LinkURLException();
			}
		}
	}

}