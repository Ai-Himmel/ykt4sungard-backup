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

package com.liferay.portlet.tags.service.http;

import com.liferay.portlet.tags.service.TagsPropertyServiceUtil;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="TagsPropertyServiceJSON.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a JSON utility for the
 * <code>com.liferay.portlet.tags.service.TagsPropertyServiceUtil</code>
 * service utility. The static methods of this class calls the same methods of
 * the service utility. However, the signatures are different because it is
 * difficult for JSON to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to a <code>org.json.JSONArray</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.tags.model.TagsProperty</code>,
 * that is translated to a <code>org.json.JSONObject</code>. Methods that JSON
 * cannot safely use are skipped. The logic for the translation is encapsulated
 * in <code>com.liferay.portlet.tags.service.http.TagsPropertyJSONSerializer</code>.
 * </p>
 *
 * <p>
 * This allows you to call the the backend services directly from JavaScript.
 * See <code>portal-web/docroot/html/portlet/tags_admin/unpacked.js</code> for a
 * reference of how that portlet uses the generated JavaScript in
 * <code>portal-web/docroot/html/js/service.js</code> to call the backend
 * services directly from JavaScript.
 * </p>
 *
 * <p>
 * The JSON utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.tags.service.TagsPropertyServiceUtil
 * @see com.liferay.portlet.tags.service.http.TagsPropertyJSONSerializer
 *
 */
public class TagsPropertyServiceJSON {
	public static JSONObject addProperty(long entryId, java.lang.String key,
		java.lang.String value)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsProperty returnValue = TagsPropertyServiceUtil.addProperty(entryId,
				key, value);

		return TagsPropertyJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject addProperty(java.lang.String entryName,
		java.lang.String key, java.lang.String value)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsProperty returnValue = TagsPropertyServiceUtil.addProperty(entryName,
				key, value);

		return TagsPropertyJSONSerializer.toJSONObject(returnValue);
	}

	public static void deleteProperty(long propertyId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		TagsPropertyServiceUtil.deleteProperty(propertyId);
	}

	public static JSONArray getProperties(long entryId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		java.util.List returnValue = TagsPropertyServiceUtil.getProperties(entryId);

		return TagsPropertyJSONSerializer.toJSONArray(returnValue);
	}

	public static JSONArray getPropertyValues(long companyId,
		java.lang.String key)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException {
		java.util.List returnValue = TagsPropertyServiceUtil.getPropertyValues(companyId,
				key);

		return TagsPropertyJSONSerializer.toJSONArray(returnValue);
	}

	public static JSONObject updateProperty(long propertyId,
		java.lang.String key, java.lang.String value)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.tags.model.TagsProperty returnValue = TagsPropertyServiceUtil.updateProperty(propertyId,
				key, value);

		return TagsPropertyJSONSerializer.toJSONObject(returnValue);
	}
}