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

package com.liferay.util.bridges.jsf.sun;

import com.sun.faces.RIConstants;
import com.sun.faces.application.ApplicationAssociate;
import com.sun.faces.config.ConfigureListener;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;

/**
 * <a href="LiferayConfigureListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Myunghun Kim
 *
 */
public class LiferayConfigureListener extends ConfigureListener {

	public static final String ASSOCIATE_KEY =
		RIConstants.FACES_PREFIX + "ApplicationAssociate";

	public void contextInitialized(ServletContextEvent sce) {
		ServletContext sc = sce.getServletContext();

		super.contextInitialized(sce);

		ApplicationAssociate associate = ApplicationAssociate.getInstance(
			new LiferayServletContextAdapter(sc));

		if (associate != null) {
			sc.setAttribute(ASSOCIATE_KEY, associate);
		}
	}

}