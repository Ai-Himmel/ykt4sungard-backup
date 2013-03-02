package com.ext.portlet.reports.service.persistence;

public interface ReportsEntryPersistence {
    public com.ext.portlet.reports.model.ReportsEntry create(
        java.lang.String entryId);

    public com.ext.portlet.reports.model.ReportsEntry remove(
        java.lang.String entryId)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public com.ext.portlet.reports.model.ReportsEntry remove(
        com.ext.portlet.reports.model.ReportsEntry reportsEntry)
        throws com.liferay.portal.SystemException;

    public com.ext.portlet.reports.model.ReportsEntry update(
        com.ext.portlet.reports.model.ReportsEntry reportsEntry)
        throws com.liferay.portal.SystemException;

    public com.ext.portlet.reports.model.ReportsEntry update(
        com.ext.portlet.reports.model.ReportsEntry reportsEntry, boolean merge)
        throws com.liferay.portal.SystemException;

    public com.ext.portlet.reports.model.ReportsEntry updateImpl(
        com.ext.portlet.reports.model.ReportsEntry reportsEntry, boolean merge)
        throws com.liferay.portal.SystemException;

    public com.ext.portlet.reports.model.ReportsEntry findByPrimaryKey(
        java.lang.String entryId)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public com.ext.portlet.reports.model.ReportsEntry fetchByPrimaryKey(
        java.lang.String entryId) throws com.liferay.portal.SystemException;

    public java.util.List findByCompanyId(java.lang.String companyId)
        throws com.liferay.portal.SystemException;

    public java.util.List findByCompanyId(java.lang.String companyId,
        int begin, int end) throws com.liferay.portal.SystemException;

    public java.util.List findByCompanyId(java.lang.String companyId,
        int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException;

    public com.ext.portlet.reports.model.ReportsEntry findByCompanyId_First(
        java.lang.String companyId,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public com.ext.portlet.reports.model.ReportsEntry findByCompanyId_Last(
        java.lang.String companyId,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public com.ext.portlet.reports.model.ReportsEntry[] findByCompanyId_PrevAndNext(
        java.lang.String entryId, java.lang.String companyId,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public java.util.List findByUserId(java.lang.String userId)
        throws com.liferay.portal.SystemException;

    public java.util.List findByUserId(java.lang.String userId, int begin,
        int end) throws com.liferay.portal.SystemException;

    public java.util.List findByUserId(java.lang.String userId, int begin,
        int end, com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException;

    public com.ext.portlet.reports.model.ReportsEntry findByUserId_First(
        java.lang.String userId,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public com.ext.portlet.reports.model.ReportsEntry findByUserId_Last(
        java.lang.String userId,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public com.ext.portlet.reports.model.ReportsEntry[] findByUserId_PrevAndNext(
        java.lang.String entryId, java.lang.String userId,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException, 
            com.ext.portlet.reports.NoSuchEntryException;

    public java.util.List findWithDynamicQuery(
        com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
        throws com.liferay.portal.SystemException;

    public java.util.List findWithDynamicQuery(
        com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
        int begin, int end) throws com.liferay.portal.SystemException;

    public java.util.List findAll() throws com.liferay.portal.SystemException;

    public java.util.List findAll(int begin, int end)
        throws com.liferay.portal.SystemException;

    public java.util.List findAll(int begin, int end,
        com.liferay.portal.kernel.util.OrderByComparator obc)
        throws com.liferay.portal.SystemException;

    public void removeByCompanyId(java.lang.String companyId)
        throws com.liferay.portal.SystemException;

    public void removeByUserId(java.lang.String userId)
        throws com.liferay.portal.SystemException;

    public void removeAll() throws com.liferay.portal.SystemException;

    public int countByCompanyId(java.lang.String companyId)
        throws com.liferay.portal.SystemException;

    public int countByUserId(java.lang.String userId)
        throws com.liferay.portal.SystemException;

    public int countAll() throws com.liferay.portal.SystemException;
}
