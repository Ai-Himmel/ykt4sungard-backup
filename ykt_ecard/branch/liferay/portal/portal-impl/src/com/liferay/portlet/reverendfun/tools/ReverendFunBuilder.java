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

package com.liferay.portlet.reverendfun.tools;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portal.util.InitUtil;
import com.liferay.portlet.reverendfun.util.ReverendFunWebCacheItem;
import com.liferay.util.FileUtil;

import java.io.File;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * <a href="ReverendFunBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ReverendFunBuilder {

	static {
		InitUtil.init();
	}

	public static void main(String[] args) {
		new ReverendFunBuilder();
	}

	public ReverendFunBuilder() {
		try {
			File file = new File(
				"../portal-impl/src/com/liferay/portlet/reverendfun/" +
					"dependencies/dates.txt");

			String[] dates = StringUtil.split(FileUtil.read(file), "\n");

			WebCacheItem wci = new ReverendFunWebCacheItem(dates[0]);

			Set moreDates = (Set)wci.convert("");

			if (moreDates.size() > 0) {
				StringMaker sm = new StringMaker();

				Set datesSet = new HashSet();

				Iterator itr = moreDates.iterator();

				while (itr.hasNext()) {
					String date = (String)itr.next();

					datesSet.add(date);

					sm.append(date);
					sm.append("\n");
				}

				for (int i = 0; i < dates.length; i++) {
					String date = dates[i];

					if (!datesSet.contains(date)) {
						datesSet.add(date);

						sm.append(dates[i]);

						if (i + 1 < dates.length) {
							sm.append("\n");
						}
					}
				}

				FileUtil.write(file, sm.toString(), true);
			}
		}
		catch (Exception e) {
		}
	}

}