package com.kingstargroup.fdykt.dto;

public class CardDTO{
  private String cardId;
  private String stateId;
  private String cosumerId;
  private String physicalNo;
  private String password;

  public String getStateId() {
    return stateId;
  }

  public String getCardId() {
    return cardId;
  }

  public void setCosumerId(String cosumerId) {
    this.cosumerId = cosumerId;
  }

  public void setStateId(String stateId) {
    this.stateId = stateId;
  }

  public void setCardId(String cardId) {
    this.cardId = cardId;
  }

  public void setPassword(String password) {
    this.password = password;
  }

  public void setPhysicalNo(String physicalNo) {
    this.physicalNo = physicalNo;
  }

  public String getCosumerId() {
    return cosumerId;
  }

  public String getPassword() {
    return password;
  }

  public String getPhysicalNo() {
    return physicalNo;
  }
}
