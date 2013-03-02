package com.ext.portlet.reports.model;

import com.liferay.portal.model.BaseModel;

import java.util.Date;


/**
 * <a href="ReportsEntryModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>ReportsEntry</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.ext.portlet.reports.service.model.ReportsEntry
 * @see com.ext.portlet.reports.service.model.impl.ReportsEntryImpl
 * @see com.ext.portlet.reports.service.model.impl.ReportsEntryModelImpl
 *
 */
public interface ReportsEntryModel extends BaseModel {
    public String getPrimaryKey();

    public void setPrimaryKey(String pk);

    public String getEntryId();

    public void setEntryId(String entryId);

    public String getCompanyId();

    public void setCompanyId(String companyId);

    public String getUserId();

    public void setUserId(String userId);

    public String getUserName();

    public void setUserName(String userName);

    public Date getCreateDate();

    public void setCreateDate(Date createDate);

    public Date getModifiedDate();

    public void setModifiedDate(Date modifiedDate);

    public String getName();

    public void setName(String name);

    public ReportsEntry toEscapedModel();
}
