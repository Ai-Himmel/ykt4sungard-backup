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

package com.liferay.portal.kernel.deploy.auto;

/**
 * <a href="AutoDeployScanner.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public class AutoDeployScanner extends Thread {

	public AutoDeployScanner(ThreadGroup group, String name,
							 AutoDeployDir dir) {

		super(group, name);

		_dir = dir;

		setContextClassLoader(getClass().getClassLoader());
		setDaemon(true);
		setPriority(MIN_PRIORITY);
	}

	public void run() {
		try {
			sleep(1000 * 10);
		}
		catch (InterruptedException ie) {
		}

		while (_started) {
			try {
				sleep(_dir.getInterval());
			}
			catch (InterruptedException ie) {
			}

			_dir.scanDirectory();
		}
	}

	public void pause() {
		_started = false;
	}

	private AutoDeployDir _dir;
	private boolean _started = true;

}