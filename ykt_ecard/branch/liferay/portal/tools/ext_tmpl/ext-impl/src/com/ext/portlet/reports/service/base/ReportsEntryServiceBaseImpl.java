package com.ext.portlet.reports.service.base;

import com.ext.portlet.reports.service.ReportsEntryService;
import com.ext.portlet.reports.service.persistence.ReportsEntryPersistence;
import com.ext.portlet.reports.service.persistence.ReportsEntryUtil;

import com.liferay.portal.service.impl.PrincipalBean;

import org.springframework.beans.factory.InitializingBean;


public abstract class ReportsEntryServiceBaseImpl extends PrincipalBean
    implements ReportsEntryService, InitializingBean {
    protected ReportsEntryPersistence reportsEntryPersistence;

    public ReportsEntryPersistence getReportsEntryPersistence() {
        return reportsEntryPersistence;
    }

    public void setReportsEntryPersistence(
        ReportsEntryPersistence reportsEntryPersistence) {
        this.reportsEntryPersistence = reportsEntryPersistence;
    }

    public void afterPropertiesSet() {
        if (reportsEntryPersistence == null) {
            reportsEntryPersistence = ReportsEntryUtil.getPersistence();
        }
    }
}
