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

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.IntegerWrapper;

import java.io.File;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * <a href="AutoDeployDir.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Brian Wing Shun Chan
 *
 */
public class AutoDeployDir {

	public AutoDeployDir(String name, File deployDir, File destDir,
						 long interval, int blacklistThreshold,
						 List listeners) {

		_name = name;
		_deployDir = deployDir;
		_destDir = destDir;
		_interval = interval;
		_blacklistThreshold = blacklistThreshold;
		_listeners = listeners;
		_inProcessFiles = new HashMap();
		_blacklistFiles = new HashSet();
	}

	public String getName() {
		return _name;
	}

	public File getDeployDir() {
		return _deployDir;
	}

	public File getDestDir() {
		return _destDir;
	}

	public long getInterval() {
		return _interval;
	}

	public int getBlacklistThreshold() {
		return _blacklistThreshold;
	}

	public List getListeners() {
		return _listeners;
	}

	public void start() {
		if (!_deployDir.exists()) {
			if (_log.isInfoEnabled()) {
				_log.info("Creating missing directory " + _deployDir);
			}

			boolean created = _deployDir.mkdirs();

			if (!created) {
				_log.error("Directory " + _deployDir + " could not be created");
			}
		}

		if (_interval > 0) {
			try {
				_scanner = new AutoDeployScanner(
					Thread.currentThread().getThreadGroup(),
					AutoDeployScanner.class.getName(), this);

				_scanner.start();

				if (_log.isInfoEnabled()) {
					_log.info("Auto deploy scanner started for " + _deployDir);
				}
			}
			catch (Exception e) {
				_log.error(e, e);

				stop();

				return;
			}
		}
		else {
			if (_log.isInfoEnabled()) {
				_log.info("Auto deploy scanning is disabled for " + _deployDir);
			}
		}
	}

	public void stop() {
		if (_scanner != null) {
			_scanner.pause();
		}
	}

	protected void scanDirectory() {
		File[] files = _deployDir.listFiles();

		for (int i = 0; i < files.length; i++) {
			File file = files[i];

			String fileName = file.getName().toLowerCase();

			if ((file.isFile()) &&
				(fileName.endsWith(".war") || fileName.endsWith(".zip") ||
				 fileName.endsWith(".xml"))) {

				processFile(file);
			}
		}
	}

	protected void processFile(File file) {
		String fileName = file.getName();

		if (!file.canRead()) {
			_log.error("Unable to read " + fileName);

			return;
		}

		if (!file.canWrite()) {
			_log.error("Unable to write " + fileName);

			return;
		}

		if (_blacklistFiles.contains(fileName)) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Skip processing of " + fileName + " because it is " +
						"blacklisted. You must restart the server to remove " +
							"the file from the blacklist.");
			}

			return;
		}

		IntegerWrapper attempt = (IntegerWrapper)_inProcessFiles.get(fileName);

		if (attempt == null) {
			attempt = new IntegerWrapper(1);

			_inProcessFiles.put(fileName, attempt);

			if (_log.isInfoEnabled()) {
				_log.info("Processing " + fileName);
			}
		}
		else {
			if (_log.isInfoEnabled()) {
				_log.info(
					"Processing " + fileName + ". This is attempt " +
						attempt.getValue() + ".");
			}
		}

		try {
			Iterator itr = _listeners.iterator();

			while (itr.hasNext()) {
				AutoDeployListener listener = (AutoDeployListener)itr.next();

				listener.deploy(file);
			}

			if (file.delete()) {
				_inProcessFiles.remove(fileName);
			}
			else {
				_log.error("Auto deploy failed to remove " + fileName);

				if (_log.isInfoEnabled()) {
					_log.info("Add " + fileName + " to the blacklist");
				}

				_blacklistFiles.add(fileName);
			}
		}
		catch (Exception e) {
			_log.error(e, e);

			attempt.increment();

			if (attempt.getValue() >= _blacklistThreshold) {
				if (_log.isInfoEnabled()) {
					_log.info("Add " + fileName + " to the blacklist");
				}

				_blacklistFiles.add(fileName);
			}
		}
	}

	private static Log _log = LogFactoryUtil.getLog(AutoDeployDir.class);

	private String _name;
	private File _deployDir;
	private File _destDir;
	private long _interval;
	private int _blacklistThreshold;
	private List _listeners;
	private Map _inProcessFiles;
	private Set _blacklistFiles;
	private AutoDeployScanner _scanner;

}