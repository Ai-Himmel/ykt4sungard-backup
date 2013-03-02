package com.kingstargroup.fdykt.dto;

public class SysParaDTO {
  private int id;
  private String Value;
  private String paraName;
  private String Usetime;
  private String Optime;
  private String Unit;
  private String Comments;
  public String getComments() {
    return Comments;
  }

  public String getUnit() {
    return Unit;
  }

  public String getOptime() {
    return Optime;
  }

  public String getUsetime() {
    return Usetime;
  }

  public String getParaName() {
    return paraName;
  }

  public String getValue() {
    return Value;
  }

  public void setId(int id) {
    this.id = id;
  }

  public void setComments(String Comments) {
    this.Comments = Comments;
  }

  public void setUnit(String Unit) {
    this.Unit = Unit;
  }

  public void setOptime(String Optime) {
    this.Optime = Optime;
  }

  public void setUsetime(String Usetime) {
    this.Usetime = Usetime;
  }

  public void setParaName(String paraName) {
    this.paraName = paraName;
  }

  public void setValue(String Value) {
    this.Value = Value;
  }

  public int getId() {
    return id;
  }

}
