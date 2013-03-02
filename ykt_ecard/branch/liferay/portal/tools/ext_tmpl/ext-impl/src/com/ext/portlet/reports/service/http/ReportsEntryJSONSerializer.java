package com.ext.portlet.reports.service.http;

import com.ext.portlet.reports.model.ReportsEntry;

import com.liferay.util.JSONUtil;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.List;


/**
 * <a href="ReportsEntryJSONSerializer.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.ext.portlet.reports.service.http.ReportsEntryServiceJSON</code>
 * to translate objects.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.ext.portlet.reports.service.http.ReportsEntryServiceJSON
 *
 */
public class ReportsEntryJSONSerializer {
    public static JSONObject toJSONObject(ReportsEntry model) {
        JSONObject jsonObj = new JSONObject();

        JSONUtil.put(jsonObj, "entryId", model.getEntryId());
        JSONUtil.put(jsonObj, "companyId", model.getCompanyId());
        JSONUtil.put(jsonObj, "userId", model.getUserId());
        JSONUtil.put(jsonObj, "userName", model.getUserName());
        JSONUtil.put(jsonObj, "createDate", model.getCreateDate());
        JSONUtil.put(jsonObj, "modifiedDate", model.getModifiedDate());
        JSONUtil.put(jsonObj, "name", model.getName());

        return jsonObj;
    }

    public static JSONArray toJSONArray(List models) {
        JSONArray jsonArray = new JSONArray();

        for (int i = 0; i < models.size(); i++) {
            ReportsEntry model = (ReportsEntry) models.get(i);

            jsonArray.put(toJSONObject(model));
        }

        return jsonArray;
    }
}
