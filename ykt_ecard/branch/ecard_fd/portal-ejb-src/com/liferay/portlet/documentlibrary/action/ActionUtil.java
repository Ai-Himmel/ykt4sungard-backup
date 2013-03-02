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

package com.liferay.portlet.documentlibrary.action;

import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.documentlibrary.model.DLRepository;
import com.liferay.portlet.documentlibrary.service.spring.DLFileProfileServiceUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLFileVersionServiceUtil;
import com.liferay.portlet.documentlibrary.service.spring.DLRepositoryServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class ActionUtil {

	public static void getFileProfile(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getFileProfile(httpReq);
	}

	public static void getFileProfile(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getFileProfile(httpReq);
	}

	public static void getFileProfile(HttpServletRequest req) throws Exception {
		String repositoryId = ParamUtil.getString(req, "repository_id");

		String path = ParamUtil.getString(req, "file_path");
		String name = ParamUtil.getString(req, "file_name");
		String fileName = StringUtil.replace(path + "/" + name, "//", "/");

		req.setAttribute(
			WebKeys.DOCUMENT_LIBRARY_FILE_PROFILE,
			DLFileProfileServiceUtil.getFileProfile(repositoryId, fileName));

		req.setAttribute(
			WebKeys.DOCUMENT_LIBRARY_FILE_VERSIONS,
			DLFileVersionServiceUtil.getFileVersions(repositoryId, fileName));
	}

	public static void getRepository(ActionRequest req) throws Exception {
		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();

		getRepository(httpReq);
	}

	public static void getRepository(RenderRequest req) throws Exception {
		HttpServletRequest httpReq =
			((RenderRequestImpl)req).getHttpServletRequest();

		getRepository(httpReq);
	}

	public static void getRepository(HttpServletRequest req) throws Exception {
		String repositoryId = ParamUtil.getString(req, "repository_id");

		// Find repository

		DLRepository repository = null;

		if (Validator.isNotNull(repositoryId)) {
			repository = DLRepositoryServiceUtil.getRepository(repositoryId);
		}

		req.setAttribute(WebKeys.DOCUMENT_LIBRARY_REPOSITORY, repository);
	}

}