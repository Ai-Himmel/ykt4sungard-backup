package com.kingstargroup.fdykt.dto;

public class MesListDTO{
  private String incontent;
  private String funId;
  private String level;
  private String deviceId;
  private String mesId;
  private String stateId;
  private String ecode;
  private String indt;
  public String getIncontent() {
    return incontent;
  }

  public String getFunId() {
    return funId;
  }

  public void setLevel(String level) {
    this.level = level;
  }

  public void setIncontent(String incontent) {
    this.incontent = incontent;
  }

  public void setFunId(String funId) {
    this.funId = funId;
  }

  public void setStateId(String stateId) {
    this.stateId = stateId;
  }

  public void setEcode(String ecode) {
    this.ecode = ecode;
  }

  public void setMesId(String mesId) {
    this.mesId = mesId;
  }

  public void setIndt(String indt) {
    this.indt = indt;
  }

  public void setDeviceId(String deviceId) {
    this.deviceId = deviceId;
  }

  public String getLevel() {
    return level;
  }

  public String getStateId() {
    return stateId;
  }

  public String getEcode() {
    return ecode;
  }

  public String getMesId() {
    return mesId;
  }

  public String getIndt() {
    return indt;
  }

  public String getDeviceId() {
    return deviceId;
  }
}
