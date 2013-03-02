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

package com.liferay.portlet.jcvs.servlet;

import com.ice.jcvslet.DefaultOutput;
import com.ice.jcvslet.JCVSlet;
import com.ice.jcvslet.JCVSletEntry;
import com.ice.jcvslet.JCVSletProject;
import com.ice.jcvslet.JCVSletProjectUtil;
import com.ice.jcvslet.JCVSletRequest;

import java.io.IOException;
import java.io.PrintWriter;

import java.util.Date;
import java.util.Properties;

import javax.servlet.ServletException;

/**
 * <a href="JCVSOutput.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class JCVSOutput extends DefaultOutput {

	public void init(JCVSlet servlet) throws ServletException {
		super.init(servlet);
	}

	public void sendAboutPage(JCVSletRequest req)
		throws IOException, ServletException {
	}

	public void sendBusyPage(JCVSletRequest req, Date startTime)
		throws IOException, ServletException {
	}

	public void sendDirectoryListing(
			JCVSletRequest req, JCVSletEntry entry, PrintWriter pw)
		throws IOException, ServletException {

		Properties props = entry.getProjectPreferences();

		props.setProperty("JCVSlet.project.showdoclink", "false");
		props.setProperty("JCVSlet.project.showupdadvlinks", "false");
		props.setProperty("JCVSlet.project.linkrowbg", "#EEEEEE");
		props.setProperty("JCVSlet.project.headerbg", "#CECEFF");

		super.sendDirectoryListing(req, entry, pw);
	}

	public void sendDirectoryPage(
			JCVSletRequest req, String prjKey, String pkgName)
		throws IOException, ServletException {

		JCVSletEntry entry = null;
		JCVSletProject project = null;

		if (prjKey != null) {
			project = req.getProjectManager().getProject( prjKey );

			if (project == null) {
				sendErrorPage(
					req, "Could not locate the project '" + prjKey + "'");

				return;
			}
			else if (project.getState() != PS_READY) {
				sendProjectStatePage(
					req, prjKey, project.getState(), new Date());

				return;
			}
			else {
				if (pkgName == null || pkgName.equals("")) {
					entry = project.getRootEntry();
				}
				else {
					entry =
						JCVSletProjectUtil.getPackageEntry(project, pkgName);
				}

				if (entry == null) {
					sendErrorPage(
						req,
						"Could not locate the package '" + pkgName +
							"' in project '" + prjKey + "'");

					return;
				}
			}
		}

		PrintWriter pw = req.getHTMLWriter();

		try {
			if (prjKey == null) {
				sendProjectListing(req, pw);
			}
			else {
				sendDirectoryListing(req, entry, pw);
			}
		}
		finally {
			pw.close();
		}
	}

	public void sendErrorPage(JCVSletRequest req, String errorMsg)
		throws IOException, ServletException {

		PrintWriter pw = req.getHTMLWriter();

		try {
			pw.println("<center>");
			pw.println("<span class=\"gamma-neg-alert\">");
			pw.println(errorMsg);
			pw.println("</span>");
			pw.println("</center>");
		}
		finally {
			pw.close();
		}
	}

	public void sendHelpPage(JCVSletRequest req)
		throws IOException, ServletException {
	}

	public void sendHTMLPage(JCVSletRequest req, String title, String content)
		throws IOException, ServletException {

		PrintWriter pw = req.getHTMLWriter();

		try {
			pw.println(content);
		}
		finally {
			pw.close();
		}
	}

	public void sendHTMLPrefix(
			JCVSletRequest reqq, PrintWriter pw, String title)
		throws IOException, ServletException {
	}

	public void sendHTMLSuffix(JCVSletRequest reqq, PrintWriter pw)
		throws IOException, ServletException {
	}

	public void sendIndexPage(JCVSletRequest req)
		throws IOException, ServletException {
	}

	public void sendServletAdminPage(JCVSletRequest req)
		throws IOException, ServletException {
	}

	public void sendServletDebugPage(JCVSletRequest req)
		throws IOException, ServletException {
	}

}