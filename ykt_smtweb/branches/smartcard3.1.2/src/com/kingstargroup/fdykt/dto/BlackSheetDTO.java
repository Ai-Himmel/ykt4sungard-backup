package com.kingstargroup.fdykt.dto;

public class BlackSheetDTO implements java.io.Serializable {
  private String cardId;
  private String volume;
  private String validdate;
  private String stateId;
  private String isAd;
  private String operateDate;
  private String operateTime;
  private String endDate;
  private String endTime;
  public String getIsAd() {
    return isAd;
  }

  public String getEndTime() {
    return endTime;
  }

  public String getStateId() {
    return stateId;
  }

  public String getValiddate() {
    return validdate;
  }

  public String getEndDate() {
    return endDate;
  }

  public String getOperateTime() {
    return operateTime;
  }

  public String getOperateDate() {
    return operateDate;
  }

  public String getCardId() {
    return cardId;
  }

  public void setVolume(String volume) {
    this.volume = volume;
  }

  public void setIsAd(String isAd) {
    this.isAd = isAd;
  }

  public void setEndTime(String endTime) {
    this.endTime = endTime;
  }

  public void setStateId(String stateId) {
    this.stateId = stateId;
  }

  public void setValiddate(String validdate) {
    this.validdate = validdate;
  }

  public void setEndDate(String endDate) {
    this.endDate = endDate;
  }

  public void setOperateTime(String operateTime) {
    this.operateTime = operateTime;
  }

  public void setOperateDate(String operateDate) {
    this.operateDate = operateDate;
  }

  public void setCardId(String cardId) {
    this.cardId = cardId;
  }

  public String getVolume() {
    return volume;
  }
}
