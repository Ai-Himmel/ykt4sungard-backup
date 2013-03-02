package com.ext.portlet.reports.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;


/**
 * <a href="ReportsEntrySoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.ext.portlet.reports.service.http.ReportsEntryServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.ext.portlet.reports.service.http.ReportsEntryServiceSoap
 *
 */
public class ReportsEntrySoap implements Serializable {
    private String _entryId;
    private String _companyId;
    private String _userId;
    private String _userName;
    private Date _createDate;
    private Date _modifiedDate;
    private String _name;

    public ReportsEntrySoap() {
    }

    public static ReportsEntrySoap toSoapModel(ReportsEntry model) {
        ReportsEntrySoap soapModel = new ReportsEntrySoap();

        soapModel.setEntryId(model.getEntryId());
        soapModel.setCompanyId(model.getCompanyId());
        soapModel.setUserId(model.getUserId());
        soapModel.setUserName(model.getUserName());
        soapModel.setCreateDate(model.getCreateDate());
        soapModel.setModifiedDate(model.getModifiedDate());
        soapModel.setName(model.getName());

        return soapModel;
    }

    public static ReportsEntrySoap[] toSoapModels(List models) {
        List soapModels = new ArrayList(models.size());

        for (int i = 0; i < models.size(); i++) {
            ReportsEntry model = (ReportsEntry) models.get(i);

            soapModels.add(toSoapModel(model));
        }

        return (ReportsEntrySoap[]) soapModels.toArray(new ReportsEntrySoap[0]);
    }

    public String getPrimaryKey() {
        return _entryId;
    }

    public void setPrimaryKey(String pk) {
        setEntryId(pk);
    }

    public String getEntryId() {
        return _entryId;
    }

    public void setEntryId(String entryId) {
        _entryId = entryId;
    }

    public String getCompanyId() {
        return _companyId;
    }

    public void setCompanyId(String companyId) {
        _companyId = companyId;
    }

    public String getUserId() {
        return _userId;
    }

    public void setUserId(String userId) {
        _userId = userId;
    }

    public String getUserName() {
        return _userName;
    }

    public void setUserName(String userName) {
        _userName = userName;
    }

    public Date getCreateDate() {
        return _createDate;
    }

    public void setCreateDate(Date createDate) {
        _createDate = createDate;
    }

    public Date getModifiedDate() {
        return _modifiedDate;
    }

    public void setModifiedDate(Date modifiedDate) {
        _modifiedDate = modifiedDate;
    }

    public String getName() {
        return _name;
    }

    public void setName(String name) {
        _name = name;
    }
}
