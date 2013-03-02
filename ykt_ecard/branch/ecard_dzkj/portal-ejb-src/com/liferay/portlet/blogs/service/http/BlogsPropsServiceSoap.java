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

package com.liferay.portlet.blogs.service.http;

import com.liferay.portlet.blogs.service.spring.BlogsPropsServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BlogsPropsServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsPropsServiceSoap {
	public static com.liferay.portlet.blogs.model.BlogsPropsModel getProps(
		java.lang.String propsId) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsProps returnValue = BlogsPropsServiceUtil.getProps(propsId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsPropsModel[] getPropsList(
		java.lang.String entryId) throws RemoteException {
		try {
			java.util.List returnValue = BlogsPropsServiceUtil.getPropsList(entryId);

			return (com.liferay.portlet.blogs.model.BlogsProps[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsProps[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsPropsModel[] getPropsList(
		java.lang.String entryId, int quantity) throws RemoteException {
		try {
			java.util.List returnValue = BlogsPropsServiceUtil.getPropsList(entryId,
					quantity);

			return (com.liferay.portlet.blogs.model.BlogsProps[])returnValue.toArray(new com.liferay.portlet.blogs.model.BlogsProps[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.blogs.model.BlogsPropsModel updateProps(
		java.lang.String entryId, int quantity) throws RemoteException {
		try {
			com.liferay.portlet.blogs.model.BlogsProps returnValue = BlogsPropsServiceUtil.updateProps(entryId,
					quantity);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}