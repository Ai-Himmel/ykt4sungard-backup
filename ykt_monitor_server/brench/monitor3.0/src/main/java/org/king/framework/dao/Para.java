package org.king.framework.dao;

public class Para
{
  private Object pName;
  private int typeNo;

  public Para()
  {
  }

  public Para(Object name, int type)
  {
    pName = name;
    typeNo = type;
  }

  public Object getPName() {
    return pName;
  }

  public void setPName(Object name) {
    pName = name;
  }

  public int getTypeNo() {
    return typeNo;
  }

  public void setTypeNo(int typeNo) {
    this.typeNo = typeNo;
  }
}