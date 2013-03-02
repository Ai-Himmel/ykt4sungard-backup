package com.kingstargroup.fdykt.logon;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class UsrexitAction
    extends Action {
  public ActionForward execute(ActionMapping mapping,
                               ActionForm form,
                               HttpServletRequest request,
                               HttpServletResponse response) {
    /**@todo: complete the business logic here, this is just a skeleton.*/
    HttpSession session = request.getSession(true);
    session.removeAttribute("name");
    session.removeAttribute("cutid");
    session.removeAttribute("stuempno");
    session.removeAttribute("cardid");
    session.removeAttribute("device");
    session.removeAttribute("trademsg");
    session.invalidate();
//    request.getSession(true);
    return (mapping.findForward("success"));
  }
}
