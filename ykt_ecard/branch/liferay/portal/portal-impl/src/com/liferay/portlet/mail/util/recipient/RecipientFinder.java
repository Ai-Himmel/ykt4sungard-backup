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

package com.liferay.portlet.mail.util.recipient;

import java.util.Map;
import java.util.SortedSet;

import javax.mail.internet.InternetAddress;

import org.apache.commons.collections.map.MultiValueMap;

/**
 * <a href="RecipientFinder.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * Used to support the search for valid recipients for the mail portlet.
 * </p>
 *
 * @author Alexander Chow
 *
 */
public interface RecipientFinder {

	public String getName();

	public MultiValueMap getOptions(long userId);

	public SortedSet getRecipients(long userId, String data, Map options);

	public boolean isReadOnly(long userId);

	public void save(long userId, InternetAddress ia)
		throws UnsupportedOperationException;

}