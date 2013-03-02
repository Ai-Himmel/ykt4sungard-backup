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

package com.liferay.portal.verify;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="VerifyProcessSuite.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class VerifyProcessSuite extends VerifyProcess {

	public void verify() throws VerifyException {
		_log.info("Verifying integrity");

		verify(new VerifyLucene());
		verify(new VerifyBlogs());
		verify(new VerifyBookmarks());
		verify(new VerifyDocumentLibrary());
		verify(new VerifyImageGallery());
		verify(new VerifyJournal());
		verify(new VerifyMessageBoards());
		verify(new VerifyWiki());

		// VerifyImage is very powerful because it removes all images that it
		// believes is stale. Do not run this unless you are also not managing
		// images in Liferay's Image service for your custom models.

		//verify(new VerifyImage());
	}

	private static Log _log = LogFactory.getLog(VerifyProcessSuite.class);

}