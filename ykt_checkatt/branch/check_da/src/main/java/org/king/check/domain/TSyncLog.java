package org.king.check.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class TSyncLog extends AbstractTSyncLog{
    public TSyncLog() {
    }

    public TSyncLog(String id, String term, String useWeek, String recordCount, String syncTime, String remark) {
        super(id, term, useWeek, recordCount, syncTime, remark);
    }
}
