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

import com.liferay.portal.model.LayoutSet;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="LayoutSetJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.LayoutSetServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.LayoutSetServiceJSON
 *
 */
public class LayoutSetJSONSerializer {
	public static JSONObject toJSONObject(LayoutSet model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "layoutSetId", model.getLayoutSetId());
		JSONUtil.put(jsonObj, "groupId", model.getGroupId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "privateLayout", model.getPrivateLayout());
		JSONUtil.put(jsonObj, "logo", model.getLogo());
		JSONUtil.put(jsonObj, "logoId", model.getLogoId());
		JSONUtil.put(jsonObj, "themeId", model.getThemeId());
		JSONUtil.put(jsonObj, "colorSchemeId", model.getColorSchemeId());
		JSONUtil.put(jsonObj, "wapThemeId", model.getWapThemeId());
		JSONUtil.put(jsonObj, "wapColorSchemeId", model.getWapColorSchemeId());
		JSONUtil.put(jsonObj, "css", model.getCss());
		JSONUtil.put(jsonObj, "pageCount", model.getPageCount());
		JSONUtil.put(jsonObj, "virtualHost", model.getVirtualHost());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			LayoutSet model = (LayoutSet)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}