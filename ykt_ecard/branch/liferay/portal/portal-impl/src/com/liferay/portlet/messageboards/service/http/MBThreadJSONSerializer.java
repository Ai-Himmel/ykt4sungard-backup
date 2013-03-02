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

package com.liferay.portlet.messageboards.service.http;

import com.liferay.portlet.messageboards.model.MBThread;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="MBThreadJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.messageboards.service.http.MBThreadServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.http.MBThreadServiceJSON
 *
 */
public class MBThreadJSONSerializer {
	public static JSONObject toJSONObject(MBThread model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "threadId", model.getThreadId());
		JSONUtil.put(jsonObj, "categoryId", model.getCategoryId());
		JSONUtil.put(jsonObj, "rootMessageId", model.getRootMessageId());
		JSONUtil.put(jsonObj, "messageCount", model.getMessageCount());
		JSONUtil.put(jsonObj, "viewCount", model.getViewCount());
		JSONUtil.put(jsonObj, "lastPostByUserId", model.getLastPostByUserId());
		JSONUtil.put(jsonObj, "lastPostDate", model.getLastPostDate());
		JSONUtil.put(jsonObj, "priority", model.getPriority());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			MBThread model = (MBThread)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}