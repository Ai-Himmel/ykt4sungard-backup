package org.king.check.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class AbstractTSyncLog implements java.io.Serializable {
    private String id;
    private String term;
    private String useWeek;
    private String recordCount;
    private String syncTime;
    private String remark;

    public AbstractTSyncLog() {
    }

    public AbstractTSyncLog(String id, String term, String useWeek, String recordCount, String syncTime, String remark) {
        this.id = id;
        this.term = term;
        this.useWeek = useWeek;
        this.recordCount = recordCount;
        this.syncTime = syncTime;
        this.remark = remark;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getTerm() {
        return term;
    }

    public void setTerm(String term) {
        this.term = term;
    }

    public String getUseWeek() {
        return useWeek;
    }

    public void setUseWeek(String useWeek) {
        this.useWeek = useWeek;
    }

    public String getRecordCount() {
        return recordCount;
    }

    public void setRecordCount(String recordCount) {
        this.recordCount = recordCount;
    }

    public String getSyncTime() {
        return syncTime;
    }

    public void setSyncTime(String syncTime) {
        this.syncTime = syncTime;
    }

    public String getRemark() {
        return remark;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }
}
