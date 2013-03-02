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

package com.liferay.portal.kernel.lar;

import javax.portlet.PortletPreferences;

/**
 * <a href="PortletDataHandler.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * A <code>PortletDataHandler</code> is a special class capable of exporting and
 * importing portlet specific data to a Liferay Archive file (LAR) when a
 * community's layouts are exported or imported.
 * <code>PortletDataHandler</code>s are defined by placing a
 * <code>portlet-data-handler-class</code> element in the <code>portlet</code>
 * section of the <b>liferay-portlet.xml</b> file.
 * </p>
 *
 * @author Raymond Augé
 * @author Joel Kozikowski
 * @author Bruno Farache
 *
 */
public interface PortletDataHandler {

	/**
	 * Deletes the data created by the portlet. Can optionally return a modified
	 * version of <code>prefs</code> if it contains reference to data that
	 * does not exist anymore.
	 *
	 * @param		context the context of the data deletion
	 * @param		portletId the portlet id of the portlet
	 * @param		prefs the portlet preferences of the portlet
	 *
	 * @return		A modified version of prefs that should be saved. Null if
	 *				the preferences were unmodified by this data handler.
	 * @throws PortletDataException
	 */
	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException;

	/**
	 * Returns a string of data to be placed in the &lt;portlet-data&gt; section
	 * of the LAR file. This data will be passed as the <code>data</code>
	 * parameter of <code>importData()</code>.
	 *
	 * @param		context the context of the data export
	 * @param		portletId the portlet id of the portlet
	 * @param		prefs the portlet preferences of the portlet
	 * @return		A string of data to be placed in the LAR. It may be XML,
	 *				but not necessarily. Null should be returned if no portlet
	 *				data is to be written out.
	 * @throws		PortletDataException
	 */
	public String exportData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException;

	/**
	 * Returns an array of the controls defined for this data handler. These
	 * controls enable the developer to create fine grained controls over export
	 * behavior. The controls are rendered in the export UI.
	 *
	 * @return		an array of PortletDataHandlerControls
	 */
	public PortletDataHandlerControl[] getExportControls()
		throws PortletDataException;

	/**
	 * Returns an array of the controls defined for this data handler. These
	 * controls enable the developer to create fine grained controls over import
	 * behavior. The controls are rendered in the import UI.
	 *
	 * @return		An array of PortletDataHandlerControls
	 */
	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException;

	/**
	 * Handles any special processing of the data when the portlet is imported
	 * into a new layout. Can optionally return a modified version of
	 * <code>prefs</code> to be saved in the new portlet.
	 *
	 * @param		context the context of the data import
	 * @param		portletId the portlet id of the portlet
	 * @param		prefs the portlet preferences of the portlet
	 * @param		data the string data that was returned by
	 *				<code>exportData()</code>
	 * @return		A modified version of prefs that should be
	 *				saved. Null if the preferences were unmodified by this data
	 *				handler.
	 * @throws PortletDataException
	 */
	public PortletPreferences importData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs, String data)
		throws PortletDataException;

}