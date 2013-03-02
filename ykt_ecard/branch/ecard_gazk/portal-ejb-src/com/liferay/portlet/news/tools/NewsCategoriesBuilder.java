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

package com.liferay.portlet.news.tools;

import com.liferay.portal.util.InitUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.Http;

import java.io.File;

/**
 * <a href="NewsCategoriesBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class NewsCategoriesBuilder {

	static {
		InitUtil.init();
	}

	public static void main(String[] args) {
		new NewsCategoriesBuilder();
	}

	public NewsCategoriesBuilder() {
		try {
			String newCategories = Http.URLtoString(
				"http://w.moreover.com/categories/category_list.tsv2");

			newCategories =
				newCategories.substring(0, newCategories.length() - 1);

			File file = new File(
				"../portal-ejb/classes/content/common/news.tsv");

			FileUtil.write(file, newCategories, true);
		}
		catch (Exception e) {
		}
	}

}