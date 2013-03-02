package org.king.check.service;

import org.king.check.domain.TSyncLog;

import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public interface SyncService {
    public List findCourseplanTemp(String status) throws Exception;

    public List findPendingCourseplanTemp() throws Exception;

    public List findSyncLog(String termName, String useWeek);

    public String importData();

    public String checkPreviewData();
    
    public List findErrorCourseplanTemp(String termName,String beginDate,String endDate) throws Exception;

    public void deletePreviewData();

    public void saveSyncLog(TSyncLog tSyncLog);
    
}
