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

/**
 * This abstract class should be extended for startup processes that verify the
 * integrity of the database.  They can be added as part of
 * <code>com.liferay.portal.verify.VerifyProcessSuite</code> or be executed
 * independently by being set in the portal.properties file.  Each of these
 * processes should not cause any problems if run multiple times.
 *
 * <a href="VerifyProcess.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public abstract class VerifyProcess {

	public static final int ALWAYS = -1;

	public static final int NEVER = 0;

	public static final int ONCE = 1;

	public VerifyProcess() {
	}

	public abstract void verify() throws VerifyException;

	public void verify(VerifyProcess verifyProcess)
		throws VerifyException {

		verifyProcess.verify();
	}

}