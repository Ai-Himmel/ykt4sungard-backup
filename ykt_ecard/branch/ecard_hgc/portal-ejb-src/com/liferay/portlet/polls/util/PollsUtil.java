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

package com.liferay.portlet.polls.util;

import com.liferay.portal.SystemException;
import com.liferay.portlet.polls.model.PollsChoice;
import com.liferay.portlet.polls.service.spring.PollsChoiceServiceUtil;
import com.liferay.portlet.polls.service.spring.PollsVoteServiceUtil;
import com.liferay.util.StringPool;

import java.util.Iterator;

import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

/**
 * <a href="PollsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Shepherd Ching
 * @version $Revision: 1.18 $
 *
 */
public class PollsUtil {

	public static CategoryDataset getVotesDataset(String questionId)
		throws SystemException {

		DefaultCategoryDataset dataset = new DefaultCategoryDataset();

		String seriesName = StringPool.BLANK;

		Iterator itr = PollsChoiceServiceUtil.getChoices(questionId).iterator();

		while (itr.hasNext()) {
			PollsChoice choice = (PollsChoice)itr.next();

			String category = choice.getChoiceId();
			Integer number = new Integer(PollsVoteServiceUtil.getVotesSize(
				questionId, choice.getChoiceId()));

			dataset.addValue(number, seriesName, choice.getChoiceId());
		}

		return dataset;
	}

}