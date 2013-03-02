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

package com.liferay.portal.webdav;

import java.util.List;

/**
 * <a href="WebDAVStorage.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public interface WebDAVStorage {

	public String getRootPath();

	public void setRootPath(String rootPath);

	public Status addCollection(WebDAVRequest webDavReq) throws WebDAVException;

	public int copyCollectionResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite, long depth)
		throws WebDAVException;

	public int copySimpleResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException;

	public int deleteResource(WebDAVRequest webDavReq) throws WebDAVException;

	public List getCommunities(WebDAVRequest webDavReq) throws WebDAVException;

	public Resource getResource(WebDAVRequest webDavReq) throws WebDAVException;

	public List getResources(WebDAVRequest webDavReq) throws WebDAVException;

	public boolean isAvailable(WebDAVRequest webDavReq) throws WebDAVException;

	public int moveCollectionResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException;

	public int moveSimpleResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException;

	public int putResource(WebDAVRequest webDavReq) throws WebDAVException;

}