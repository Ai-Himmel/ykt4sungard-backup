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

package com.liferay.portal.util;

import com.liferay.portal.model.ActivityFeedEntry;
import com.liferay.portal.model.ActivityTracker;
import com.liferay.portal.model.ActivityTrackerInterpreter;
import com.liferay.portal.model.impl.ActivityTrackerInterpreterImpl;
import com.liferay.portal.theme.ThemeDisplay;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="ActivityTrackerInterpreterUtil.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActivityTrackerInterpreterUtil {

	public static void addActivityTrackerInterpreter(
		ActivityTrackerInterpreter activityTrackerInterpreter) {

		_instance._addActivityTrackerInterpreter(activityTrackerInterpreter);
	}

	public static void deleteActivityTrackerInterpreter(
		ActivityTrackerInterpreter activityTrackerInterpreter) {

		_instance._deleteActivityTrackerInterpreter(activityTrackerInterpreter);
	}

	public static ActivityFeedEntry interpret(
		ActivityTracker activityTracker, ThemeDisplay themeDisplay) {

		return _instance._interpret(activityTracker, themeDisplay);
	}

	private ActivityTrackerInterpreterUtil() {
		_activityTrackerInterpreters = new ArrayList();
	}

	private void _addActivityTrackerInterpreter(
		ActivityTrackerInterpreter activityTrackerInterpreter) {

		_activityTrackerInterpreters.add(activityTrackerInterpreter);
	}

	private void _deleteActivityTrackerInterpreter(
		ActivityTrackerInterpreter activityTrackerInterpreter) {

		if (activityTrackerInterpreter != null) {
			_activityTrackerInterpreters.remove(activityTrackerInterpreter);
		}
	}

	private ActivityFeedEntry _interpret(
		ActivityTracker activityTracker, ThemeDisplay themeDisplay) {

		String className = PortalUtil.getClassName(
			activityTracker.getClassNameId());

		for (int i = 0; i < _activityTrackerInterpreters.size(); i++) {
			ActivityTrackerInterpreterImpl activityTrackerInterpreter =
				(ActivityTrackerInterpreterImpl)
					_activityTrackerInterpreters.get(i);

			if (activityTrackerInterpreter.hasClassName(className)) {
				ActivityFeedEntry activityFeedEntry =
					activityTrackerInterpreter.interpret(
						activityTracker, themeDisplay);

				if (activityFeedEntry != null) {
					return activityFeedEntry;
				}
			}
		}

		return null;
	}

	private static ActivityTrackerInterpreterUtil _instance =
		new ActivityTrackerInterpreterUtil();

	private List _activityTrackerInterpreters;

}