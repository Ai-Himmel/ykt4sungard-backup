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

package com.liferay.portal.upgrade.util;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.upgrade.StagnantRowException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="IdReplacer.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IdReplacer {

	public static String replaceLongIds(
			String s, String begin, ValueMapper valueMapper)
		throws Exception {

		if ((s == null) || (begin == null) ||
			(valueMapper == null) || (valueMapper.size() == 0)) {

			return s;
		}

		char[] charArray = s.toCharArray();

		StringMaker sm = new StringMaker(s.length());

		int pos = 0;

		while (true) {
			int x = s.indexOf(begin, pos);
			int y = _getEndPos(charArray, x + begin.length());

			if ((x == -1) || (y == -1)) {
				sm.append(s.substring(pos, s.length()));

				break;
			}
			else {
				sm.append(s.substring(pos, x + begin.length()));

				String oldString = s.substring(x + begin.length(), y);

				if (Validator.isNotNull(oldString)) {
					Long oldValue = new Long(GetterUtil.getLong(oldString));

					Long newValue = null;

					try {
						newValue = (Long)valueMapper.getNewValue(oldValue);
					}
					catch (StagnantRowException sre) {
						if (_log.isWarnEnabled()) {
							_log.warn(sre);
						}
					}

					if (newValue == null) {
						newValue = oldValue;
					}

					sm.append(newValue);
				}

				pos = y;
			}
		}

		return sm.toString();
	}

	public String replaceLongIds(
			String s, String begin, String end, ValueMapper valueMapper)
		throws Exception {

		if ((s == null) || (begin == null) || (end == null) ||
			(valueMapper == null) || (valueMapper.size() == 0)) {

			return s;
		}

		StringMaker sm = new StringMaker(s.length());

		int pos = 0;

		while (true) {
			int x = s.indexOf(begin, pos);
			int y = s.indexOf(end, x + begin.length());

			if ((x == -1) || (y == -1)) {
				sm.append(s.substring(pos, s.length()));

				break;
			}
			else {
				sm.append(s.substring(pos, x + begin.length()));

				Long oldValue = new Long(GetterUtil.getLong(
					s.substring(x + begin.length(), y)));

				Long newValue = null;

				try {
					newValue = (Long)valueMapper.getNewValue(oldValue);
				}
				catch (StagnantRowException sre) {
					if (_log.isWarnEnabled()) {
						_log.warn(sre);
					}
				}

				if (newValue == null) {
					newValue = oldValue;
				}

				sm.append(newValue);

				pos = y;
			}
		}

		return sm.toString();
	}

	private static int _getEndPos(char[] charArray, int pos) {
        while (true) {
			if (pos >= charArray.length) {
				break;
			}

			if (!Character.isDigit(charArray[pos])) {
				break;
			}

			pos++;
        }

		return pos;
	}

	private static Log _log = LogFactory.getLog(IdReplacer.class);

}