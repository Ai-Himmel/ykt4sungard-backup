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

package com.liferay.portal.tools;

import com.liferay.util.ant.WarTask;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="WebSiteWar.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class WebSiteWar {

	public static void main(String[] args) {
		new WebSiteWar();
	}

	public WebSiteWar() {
		try {
			List webSites = WebSiteBuilder.getWebSites();

			_war(webSites);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void _war(List webSites) throws Exception {
		Iterator itr = webSites.iterator();

		while (itr.hasNext()) {
			WebSite webSite = (WebSite)itr.next();

			WarTask.war(
				"../web-sites/" + webSite.getId() + "-web/docroot",
				"../web-sites/" + webSite.getId() + "-web.war",
				"WEB-INF/web.xml",
				"../web-sites/" + webSite.getId() +
					"-web/docroot/WEB-INF/web.xml");
		}
	}

	private String _portalExtProperties = null;
	private String _orionConfigDir = null;
	private int _nfcListenPort = 7777;

}