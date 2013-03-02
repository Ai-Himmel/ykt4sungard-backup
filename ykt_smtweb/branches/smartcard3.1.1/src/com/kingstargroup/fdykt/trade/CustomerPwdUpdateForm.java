package com.kingstargroup.fdykt.trade;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;
public class CustomerPwdUpdateForm
    extends ActionForm {
  private String pwd;
  private String newPwd;
  private String againPwd;

  public void setAgainPwd(String againPwd) {
    this.againPwd = againPwd;
  }

  public void setNewPwd(String newPwd) {
    this.newPwd = newPwd;
  }

  public void setPwd(String pwd) {
    this.pwd = pwd;
  }

  public String getAgainPwd() {
    return againPwd;
  }

  public String getNewPwd() {
    return newPwd;
  }

  public String getPwd() {
    return pwd;
  }

  public ActionErrors validate(
      ActionMapping mapping,
      HttpServletRequest request) {
    ActionErrors errors = new ActionErrors();
    if (pwd.equals("")) {
      errors.add("pwd", new ActionError("errors.pwd"));
    }
    if (newPwd.equals("")) {
      errors.add("newPwd", new ActionError("errors.newPwd"));
    }else if(newPwd.length() !=6){
      errors.add("newPwd",new ActionError("errors.pwdLength"));
    }
    if (!againPwd.equals(newPwd)) {
      errors.add("againPwd", new ActionError("errors.againPwd"));
    }
     return errors;
  }

  public void reset(ActionMapping mapping, HttpServletRequest request) {
    pwd = "";
    newPwd = "";
    againPwd = "";
  }
}
