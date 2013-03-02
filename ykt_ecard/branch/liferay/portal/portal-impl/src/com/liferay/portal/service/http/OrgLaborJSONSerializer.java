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

package com.liferay.portal.service.http;

import com.liferay.portal.model.OrgLabor;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="OrgLaborJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.OrgLaborServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.OrgLaborServiceJSON
 *
 */
public class OrgLaborJSONSerializer {
	public static JSONObject toJSONObject(OrgLabor model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "orgLaborId", model.getOrgLaborId());
		JSONUtil.put(jsonObj, "organizationId", model.getOrganizationId());
		JSONUtil.put(jsonObj, "typeId", model.getTypeId());
		JSONUtil.put(jsonObj, "sunOpen", model.getSunOpen());
		JSONUtil.put(jsonObj, "sunClose", model.getSunClose());
		JSONUtil.put(jsonObj, "monOpen", model.getMonOpen());
		JSONUtil.put(jsonObj, "monClose", model.getMonClose());
		JSONUtil.put(jsonObj, "tueOpen", model.getTueOpen());
		JSONUtil.put(jsonObj, "tueClose", model.getTueClose());
		JSONUtil.put(jsonObj, "wedOpen", model.getWedOpen());
		JSONUtil.put(jsonObj, "wedClose", model.getWedClose());
		JSONUtil.put(jsonObj, "thuOpen", model.getThuOpen());
		JSONUtil.put(jsonObj, "thuClose", model.getThuClose());
		JSONUtil.put(jsonObj, "friOpen", model.getFriOpen());
		JSONUtil.put(jsonObj, "friClose", model.getFriClose());
		JSONUtil.put(jsonObj, "satOpen", model.getSatOpen());
		JSONUtil.put(jsonObj, "satClose", model.getSatClose());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			OrgLabor model = (OrgLabor)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}