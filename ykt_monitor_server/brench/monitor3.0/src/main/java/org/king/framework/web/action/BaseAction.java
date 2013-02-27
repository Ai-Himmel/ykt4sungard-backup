package org.king.framework.web.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.actions.DispatchAction;

public class BaseAction extends DispatchAction
{
  protected final void removeAttribute(ActionMapping mapping, HttpServletRequest request)
  {
    if (mapping.getAttribute() != null)
      if ("request".equals(mapping.getScope()))
        request.removeAttribute(mapping.getAttribute());
      else
        request.getSession().removeAttribute(mapping.getAttribute());
  }

  protected void removeFormBean(ActionMapping mapping, HttpServletRequest request)
  {
    if (mapping.getAttribute() != null)
      if ("request".equals(mapping.getScope())) {
        request.removeAttribute(mapping.getAttribute());
      } else {
        HttpSession session = request.getSession();
        session.removeAttribute(mapping.getAttribute());
      }
  }

  protected void updateFormBean(ActionMapping mapping, HttpServletRequest request, ActionForm form)
  {
    if (mapping.getAttribute() != null)
      if ("request".equals(mapping.getScope())) {
        request.setAttribute(mapping.getAttribute(), form);
      } else {
        HttpSession session = request.getSession();
        session.setAttribute(mapping.getAttribute(), form);
      }
  }
}