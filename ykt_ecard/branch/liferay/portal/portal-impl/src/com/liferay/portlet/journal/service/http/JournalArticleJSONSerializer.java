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

package com.liferay.portlet.journal.service.http;

import com.liferay.portlet.journal.model.JournalArticle;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;

/**
 * <a href="JournalArticleJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.journal.service.http.JournalArticleServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.journal.service.http.JournalArticleServiceJSON
 *
 */
public class JournalArticleJSONSerializer {
	public static JSONObject toJSONObject(JournalArticle model) {
		JSONObject jsonObj = new JSONObject();

		JSONUtil.put(jsonObj, "uuid", model.getUuid());
		JSONUtil.put(jsonObj, "id", model.getId());
		JSONUtil.put(jsonObj, "resourcePrimKey", model.getResourcePrimKey());
		JSONUtil.put(jsonObj, "groupId", model.getGroupId());
		JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
		JSONUtil.put(jsonObj, "userId", model.getUserId());
		JSONUtil.put(jsonObj, "userName", model.getUserName());
		JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
		JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
		JSONUtil.put(jsonObj, "articleId", model.getArticleId());
		JSONUtil.put(jsonObj, "version", model.getVersion());
		JSONUtil.put(jsonObj, "title", model.getTitle());
		JSONUtil.put(jsonObj, "description", model.getDescription());
		JSONUtil.put(jsonObj, "content", model.getContent());
		JSONUtil.put(jsonObj, "type", model.getType());
		JSONUtil.put(jsonObj, "structureId", model.getStructureId());
		JSONUtil.put(jsonObj, "templateId", model.getTemplateId());
		JSONUtil.put(jsonObj, "displayDate", model.getDisplayDate());
		JSONUtil.put(jsonObj, "approved", model.getApproved());
		JSONUtil.put(jsonObj, "approvedByUserId", model.getApprovedByUserId());
		JSONUtil.put(jsonObj, "approvedByUserName",
			model.getApprovedByUserName());
		JSONUtil.put(jsonObj, "approvedDate", model.getApprovedDate());
		JSONUtil.put(jsonObj, "expired", model.getExpired());
		JSONUtil.put(jsonObj, "expirationDate", model.getExpirationDate());
		JSONUtil.put(jsonObj, "reviewDate", model.getReviewDate());
		JSONUtil.put(jsonObj, "indexable", model.getIndexable());
		JSONUtil.put(jsonObj, "smallImage", model.getSmallImage());
		JSONUtil.put(jsonObj, "smallImageId", model.getSmallImageId());
		JSONUtil.put(jsonObj, "smallImageURL", model.getSmallImageURL());

		return jsonObj;
	}

	public static JSONArray toJSONArray(List models) {
		JSONArray jsonArray = new JSONArray();

		for (int i = 0; i < models.size(); i++) {
			JournalArticle model = (JournalArticle)models.get(i);

			jsonArray.put(toJSONObject(model));
		}

		return jsonArray;
	}
}