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

package com.liferay.portlet.workflow.search;

import com.liferay.portal.kernel.dao.search.SearchContainer;

import java.util.ArrayList;
import java.util.List;

import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;

/**
 * <a href="DefinitionSearch.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DefinitionSearch extends SearchContainer {

	static List headerNames = new ArrayList();

	static {
		headerNames.add("definition-id");
		headerNames.add("definition-name");
		headerNames.add("definition-version");
	}

	public static final String EMPTY_RESULTS_MESSAGE =
		"no-definitions-were-found";

	public DefinitionSearch(RenderRequest req, PortletURL iteratorURL) {
		super(req, new DefinitionDisplayTerms(req),
			  new DefinitionSearchTerms(req), DEFAULT_CUR_PARAM, DEFAULT_DELTA,
			  iteratorURL, headerNames, EMPTY_RESULTS_MESSAGE);

		DefinitionDisplayTerms displayTerms =
			(DefinitionDisplayTerms)getDisplayTerms();

		iteratorURL.setParameter(
			DefinitionDisplayTerms.DEFINITION_ID,
			String.valueOf(displayTerms.getDefinitionId()));
		iteratorURL.setParameter(
			DefinitionDisplayTerms.NAME, displayTerms.getName());
	}

}