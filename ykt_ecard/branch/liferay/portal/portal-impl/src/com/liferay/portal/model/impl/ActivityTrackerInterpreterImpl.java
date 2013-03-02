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

package com.liferay.portal.model.impl;

import com.liferay.portal.model.ActivityFeedEntry;
import com.liferay.portal.model.ActivityTracker;
import com.liferay.portal.model.ActivityTrackerInterpreter;
import com.liferay.portal.theme.ThemeDisplay;

import java.util.HashSet;
import java.util.Set;

/**
 * <a href="ActivityTrackerInterpreterImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActivityTrackerInterpreterImpl
	implements ActivityTrackerInterpreter {

	public ActivityTrackerInterpreterImpl(
		ActivityTrackerInterpreter activityTrackerInterpreter) {

		_activityTrackerInterpreter = activityTrackerInterpreter;

		String[] classNames = _activityTrackerInterpreter.getClassNames();

		for (int i = 0; i < classNames.length; i++) {
			_classNames.add(classNames[i]);
		}
	}

	public String[] getClassNames() {
		return _activityTrackerInterpreter.getClassNames();
	}

	public boolean hasClassName(String className) {
		if (_classNames.contains(className)) {
			return true;
		}
		else {
			return false;
		}
	}

	public ActivityFeedEntry interpret(
		ActivityTracker activityTracker, ThemeDisplay themeDisplay) {

		return _activityTrackerInterpreter.interpret(
			activityTracker, themeDisplay);
	}

	private ActivityTrackerInterpreter _activityTrackerInterpreter;
	private Set _classNames = new HashSet();

}