package org.king.bean;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-30
 */
public class ReceiveItem {
    private String ecardId;

    private String checkResult;

    private String status;

    public String getEcardId() {
        return ecardId;
    }

    public void setEcardId(String ecardId) {
        this.ecardId = ecardId;
    }

    public String getCheckResult() {
        return checkResult;
    }

    public void setCheckResult(String checkResult) {
        this.checkResult = checkResult;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "ReceiveItem{" +
                "ecardId='" + ecardId +
                ", checkResult='" + checkResult +
                '}';
    }
}
