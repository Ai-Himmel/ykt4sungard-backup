package com.kingstargroup.fdykt.trade;

import java.util.*;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import com.kingstargroup.fdykt.dao.*;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;
import java.sql.*;
import com.kingstargroup.fdykt.Util;
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
    else {
      HttpSession session = request.getSession();
      DB2CustomerDAO customerdao = new DB2CustomerDAO();
    /*  if(session.getAttribute("stuempno")==null){
      //  errors.add("pwd",new ActionError("errors.timeout"));
      }else{*/
   //   String stuempno = (String) session.getAttribute("stuempno");

     /* try {
        String ciphered=Util.DESEnc(pwd);
        String sql ="select * from ykt_cur.t_cif_customer cus " +
                "join ykt_cur.T_PIF_Card  card on cus.Cut_id=card.Cosumer_id " +
                "where cus.StuEmp_no='" + stuempno +"' and card.password='" + ciphered +"' ";
        ArrayList customers = customerdao.RetriveCustomer(sql);
        if (customers.size() == 0) {
          errors.add("login", new ActionError("errors.pwd"));
        }
      }
      catch (SQLException ex) {
      }
      catch (Exception ex) {
      }*/
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
