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

package com.liferay.util.ant;

import com.liferay.portal.kernel.util.StringMaker;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

import org.apache.tools.ant.BuildEvent;
import org.apache.tools.ant.DefaultLogger;
import org.apache.tools.ant.Project;
import org.apache.tools.ant.util.StringUtils;

/**
 * <a href="SystemLogger.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SystemLogger extends DefaultLogger {

	public void messageLogged(BuildEvent event) {
		int priority = event.getPriority();

		if (priority <= msgOutputLevel) {
			StringMaker sb = new StringMaker();

			try {
				BufferedReader reader = new BufferedReader(
					new StringReader(event.getMessage()));

				String line = reader.readLine();

				boolean first = true;

				while (line != null) {
					if (!first) {
						sb.append(StringUtils.LINE_SEP);
					}

					first = false;

					sb.append("  ");
					sb.append(line);

					line = reader.readLine();
				}
			}
			catch (IOException e) {
			}

			String msg = sb.toString();

			if (priority != Project.MSG_ERR) {
				printMessage(msg, out, priority);
			}
			else {
				printMessage(msg, err, priority);
			}

			log(msg);
		}
	}

}