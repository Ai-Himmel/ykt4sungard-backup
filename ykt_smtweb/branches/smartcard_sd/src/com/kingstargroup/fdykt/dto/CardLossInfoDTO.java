package com.kingstargroup.fdykt.dto;

public class CardLossInfoDTO{
  private String operateDate;
  private String operateTime;
  private String cardId;
  private String stateId;
  private String beginDate;
  private String endDate;
  public String getStateId() {
    return stateId;
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

  public void setBeginDate(String beginDate) {
    this.beginDate = beginDate;
  }

  public void setStateId(String stateId) {
    this.stateId = stateId;
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

  public String getBeginDate() {
    return beginDate;
  }
}
