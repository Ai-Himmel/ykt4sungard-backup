package com.kingstargroup.fdykt.trade;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import java.util.*;

public class TradeSerialForm
    extends ActionForm {
  private String begin;
  private String end;

  public String getBegin() {
    return begin;
  }

  public void setEnd(String end) {
    this.end = end;
  }

  public void setBegin(String begin) {
    this.begin = begin;
  }

  public String getEnd() {
    return end;
  }

  public void reset(ActionMapping mapping, HttpServletRequest request) {
    begin = "";
    end = "";
  }

  public ActionErrors validate(ActionMapping mapping,
                               HttpServletRequest request) {
    ActionErrors errors = new ActionErrors();
    if (begin.length() < 8 || end.length() < 8) {
      errors.add("date", new ActionError("errors.date"));
      return errors;
    }
    Integer byear = new Integer(begin.substring(0, 4));
    Integer eyear = new Integer(end.substring(0, 4));
    Integer bmonth = new Integer(begin.substring(4, 6));
    Integer emonth = new Integer(end.substring(4, 6));
    Integer bday = new Integer(begin.substring(6, 8));
    Integer eday = new Integer(end.substring(6, 8));
    //日期格式
    if (byear.intValue() < 2000 || byear.intValue() > 2100 ||
        eyear.intValue() < 2000 || eyear.intValue() > 2100) {
      errors.add("date", new ActionError("errors.date"));
    }
    if (bmonth.intValue() < 1 || bmonth.intValue() > 12 ||
        emonth.intValue() < 1 || emonth.intValue() > 12) {
      errors.add("date", new ActionError("errors.date"));
    }
    if (bday.intValue() < 1 || bday.intValue() > 31 || eday.intValue() < 1 ||
        eday.intValue() > 31) {
      errors.add("date", new ActionError("errors.date"));
    }
     //截止日期是否大于开始日期
    if (byear.intValue() > eyear.intValue()) {
      errors.add("datesmall", new ActionError("errors.datesmall"));
    }
    else if (byear.intValue() == eyear.intValue() &&
             bmonth.intValue() > emonth.intValue()) {
      errors.add("datesmall", new ActionError("errors.datesmall"));
    }
    else if (byear.intValue() == eyear.intValue() &&
             bmonth.intValue() == emonth.intValue() &&
             bday.intValue() > eday.intValue()) {
      errors.add("datesmall", new ActionError("errors.datesmall"));
    }
    return errors;
  }
}
