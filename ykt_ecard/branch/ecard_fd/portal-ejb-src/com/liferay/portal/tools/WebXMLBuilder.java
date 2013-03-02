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

import com.liferay.portal.util.EntityResolver;
import com.liferay.util.FileUtil;
import com.liferay.util.Html;
import com.liferay.util.xml.XMLFormatter;
import com.liferay.util.xml.XMLMerger;
import com.liferay.util.xml.descriptor.WebXMLDescriptor;

import java.io.File;
import java.io.IOException;
import java.io.StringReader;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.io.SAXReader;

/**
 * <a href="WebXMLBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Tang Ying Jian
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.37 $
 *
 */
public class WebXMLBuilder {

	public static void main(String[] args) {
		new WebXMLBuilder();
	}

	public static String organizeWebXML(String webXML)
		throws DocumentException, IOException {

		webXML = Html.stripComments(webXML);

		SAXReader reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(new StringReader(webXML));

		XMLMerger merger = new XMLMerger(new WebXMLDescriptor());

		merger.organizeXML(doc);

		webXML = XMLFormatter.toString(doc);

		return webXML;
	}

	public WebXMLBuilder() {
		try {
			String rootDir = "../";
			String portalWebDir = "portal-web/docroot/";
			String webSitesDir = "web-sites/";

			if (!FileUtil.exists(
					rootDir + portalWebDir + "WEB-INF/web.xml") &&
				!FileUtil.exists(rootDir + "ext-web/tmp/WEB-INF/web.xml")) {

				rootDir = "";
			}

			if (!FileUtil.exists(
					rootDir + portalWebDir + "WEB-INF/web.xml")) {

				portalWebDir = "ext-web/tmp/";
			}

			String webXML = FileUtil.read(
				rootDir + portalWebDir + "WEB-INF/web.xml");

			int x = webXML.indexOf("<web-app>");
			int y = webXML.indexOf("</web-app>");

			webXML = webXML.substring(x + 9, y);

			File webSite = new File(rootDir + "web-sites");

			String[] webSites = webSite.list();

			for (int i = 0; i < webSites.length; i++) {
				if (webSites[i].endsWith("-web")) {

					// web.xml

					File webSiteXML = new File(
						rootDir + webSitesDir + webSites[i] +
						"/docroot/WEB-INF/web.xml");

					String content = FileUtil.read(webSiteXML);

					int z = content.indexOf("<web-app>") + 9;

					String newContent =
						content.substring(0, z) +
						webXML +
						content.substring(z, content.length());

					newContent = organizeWebXML(newContent);

					if ((newContent != null) && !content.equals(newContent)) {
						FileUtil.write(webSiteXML, newContent);
					}

					// portlet.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/portlet.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/portlet.xml");

					// portlet-ext.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/portlet-ext.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/portlet-ext.xml");

					// liferay-portlet.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/liferay-portlet.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/liferay-portlet.xml");

					// liferay-portlet-ext.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir +
							"WEB-INF/liferay-portlet-ext.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/liferay-portlet-ext.xml");

					// liferay-display.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/liferay-display.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/liferay-display.xml");

					// liferay-look-and-feel.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir +
							"WEB-INF/liferay-look-and-feel.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/liferay-look-and-feel.xml");

					// liferay-look-and-feel-ext.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir +
							"WEB-INF/liferay-look-and-feel-ext.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/liferay-look-and-feel-ext.xml");

					// struts-config.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/struts-config.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/struts-config.xml");

					// struts-config-ext.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir +
							"WEB-INF/struts-config-ext.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/struts-config-ext.xml");

					// tiles-defs.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/tiles-defs.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/tiles-defs.xml");

					// tiles-defs-ext.xml

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/tiles-defs-ext.xml",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/tiles-defs-ext.xml");

					// /docroot/WEB-INF/server-config.wsdd

					FileUtil.copyFileLazy(
						rootDir + portalWebDir + "WEB-INF/server-config.wsdd",
						rootDir + webSitesDir + webSites[i] +
							"/docroot/WEB-INF/server-config.wsdd");
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}