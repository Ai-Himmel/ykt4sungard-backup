package com.ext.portlet.reports.model.impl;

import com.ext.portlet.reports.model.ReportsEntry;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;


/**
 * <a href="ReportsEntryModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ReportsEntry</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.ext.portlet.reports.service.model.ReportsEntry
 * @see com.ext.portlet.reports.service.model.ReportsEntryModel
 * @see com.ext.portlet.reports.service.model.impl.ReportsEntryImpl
 *
 */
public class ReportsEntryModelImpl extends BaseModelImpl {
    public static final String TABLE_NAME = "ReportsEntry";
    public static final Object[][] TABLE_COLUMNS = {
            { "entryId", new Integer(Types.VARCHAR) },
            

            { "companyId", new Integer(Types.VARCHAR) },
            

            { "userId", new Integer(Types.VARCHAR) },
            

            { "userName", new Integer(Types.VARCHAR) },
            

            { "createDate", new Integer(Types.TIMESTAMP) },
            

            { "modifiedDate", new Integer(Types.TIMESTAMP) },
            

            { "name", new Integer(Types.VARCHAR) }
        };
    public static final String TABLE_SQL_CREATE = "create table ReportsEntry (entryId VARCHAR(75) not null primary key,companyId VARCHAR(75) null,userId VARCHAR(75) null,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,name VARCHAR(75) null)";
    public static final String TABLE_SQL_DROP = "drop table ReportsEntry";
    public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
                "value.object.finder.cache.enabled.com.ext.portlet.reports.model.ReportsEntry"),
            true);
    public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
                "lock.expiration.time.com.ext.portlet.reports.model.ReportsEntry"));
    private String _entryId;
    private String _companyId;
    private String _userId;
    private String _userName;
    private Date _createDate;
    private Date _modifiedDate;
    private String _name;

    public ReportsEntryModelImpl() {
    }

    public String getPrimaryKey() {
        return _entryId;
    }

    public void setPrimaryKey(String pk) {
        setEntryId(pk);
    }

    public Serializable getPrimaryKeyObj() {
        return _entryId;
    }

    public String getEntryId() {
        return GetterUtil.getString(_entryId);
    }

    public void setEntryId(String entryId) {
        if (((entryId == null) && (_entryId != null)) ||
                ((entryId != null) && (_entryId == null)) ||
                ((entryId != null) && (_entryId != null) &&
                !entryId.equals(_entryId))) {
            _entryId = entryId;
        }
    }

    public String getCompanyId() {
        return GetterUtil.getString(_companyId);
    }

    public void setCompanyId(String companyId) {
        if (((companyId == null) && (_companyId != null)) ||
                ((companyId != null) && (_companyId == null)) ||
                ((companyId != null) && (_companyId != null) &&
                !companyId.equals(_companyId))) {
            _companyId = companyId;
        }
    }

    public String getUserId() {
        return GetterUtil.getString(_userId);
    }

    public void setUserId(String userId) {
        if (((userId == null) && (_userId != null)) ||
                ((userId != null) && (_userId == null)) ||
                ((userId != null) && (_userId != null) &&
                !userId.equals(_userId))) {
            _userId = userId;
        }
    }

    public String getUserName() {
        return GetterUtil.getString(_userName);
    }

    public void setUserName(String userName) {
        if (((userName == null) && (_userName != null)) ||
                ((userName != null) && (_userName == null)) ||
                ((userName != null) && (_userName != null) &&
                !userName.equals(_userName))) {
            _userName = userName;
        }
    }

    public Date getCreateDate() {
        return _createDate;
    }

    public void setCreateDate(Date createDate) {
        if (((createDate == null) && (_createDate != null)) ||
                ((createDate != null) && (_createDate == null)) ||
                ((createDate != null) && (_createDate != null) &&
                !createDate.equals(_createDate))) {
            _createDate = createDate;
        }
    }

    public Date getModifiedDate() {
        return _modifiedDate;
    }

    public void setModifiedDate(Date modifiedDate) {
        if (((modifiedDate == null) && (_modifiedDate != null)) ||
                ((modifiedDate != null) && (_modifiedDate == null)) ||
                ((modifiedDate != null) && (_modifiedDate != null) &&
                !modifiedDate.equals(_modifiedDate))) {
            _modifiedDate = modifiedDate;
        }
    }

    public String getName() {
        return GetterUtil.getString(_name);
    }

    public void setName(String name) {
        if (((name == null) && (_name != null)) ||
                ((name != null) && (_name == null)) ||
                ((name != null) && (_name != null) && !name.equals(_name))) {
            _name = name;
        }
    }

    public ReportsEntry toEscapedModel() {
        if (isEscapedModel()) {
            return (ReportsEntry) this;
        } else {
            ReportsEntry model = new ReportsEntryImpl();

            model.setEscapedModel(true);

            model.setEntryId(Html.escape(getEntryId()));
            model.setCompanyId(Html.escape(getCompanyId()));
            model.setUserId(Html.escape(getUserId()));
            model.setUserName(Html.escape(getUserName()));
            model.setCreateDate(getCreateDate());
            model.setModifiedDate(getModifiedDate());
            model.setName(Html.escape(getName()));

            model = (ReportsEntry) Proxy.newProxyInstance(ReportsEntry.class.getClassLoader(),
                    new Class[] { ReportsEntry.class },
                    new ReadOnlyBeanHandler(model));

            return model;
        }
    }

    public Object clone() {
        ReportsEntryImpl clone = new ReportsEntryImpl();

        clone.setEntryId(getEntryId());
        clone.setCompanyId(getCompanyId());
        clone.setUserId(getUserId());
        clone.setUserName(getUserName());
        clone.setCreateDate(getCreateDate());
        clone.setModifiedDate(getModifiedDate());
        clone.setName(getName());

        return clone;
    }

    public int compareTo(Object obj) {
        if (obj == null) {
            return -1;
        }

        ReportsEntryImpl reportsEntry = (ReportsEntryImpl) obj;

        int value = 0;

        value = getName().toLowerCase().compareTo(reportsEntry.getName()
                                                              .toLowerCase());

        if (value != 0) {
            return value;
        }

        return 0;
    }

    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }

        ReportsEntryImpl reportsEntry = null;

        try {
            reportsEntry = (ReportsEntryImpl) obj;
        } catch (ClassCastException cce) {
            return false;
        }

        String pk = reportsEntry.getPrimaryKey();

        if (getPrimaryKey().equals(pk)) {
            return true;
        } else {
            return false;
        }
    }

    public int hashCode() {
        return getPrimaryKey().hashCode();
    }
}
