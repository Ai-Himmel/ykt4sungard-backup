package org.king.framework.web.action;

import java.io.PrintWriter;
import java.io.StringWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.ExceptionHandler;
import org.apache.struts.config.ExceptionConfig;

public final class ActionExceptionHandler extends ExceptionHandler
{
  private final transient Log log = LogFactory.getLog(ActionExceptionHandler.class);

  public ActionForward execute(Exception ex, ExceptionConfig ae, ActionMapping mapping, ActionForm formInstance, HttpServletRequest request, HttpServletResponse response)
    throws ServletException
  {
    ActionErrors errors = (ActionErrors)request.getAttribute("org.apache.struts.action.ERROR");

    if (errors != null) {
      return null;
    }

    ActionForward forward = super.execute(ex, ae, mapping, formInstance, request, response);

    ActionMessage error = null;
    String property = null;

    logException(ex);

    while (ex != null) {
      String msg = ex.getMessage();
      error = new ActionMessage("errors.detail", msg);
      property = error.getKey();
      ex = (Exception)ex.getCause();

      if ((ex != null) && (ex.getMessage() != null))
      {
        if (msg.indexOf(ex.getMessage()) == -1)
          storeException(request, property, error, forward);
      }
      else {
        storeException(request, property, error, forward);
      }
    }

    return forward;
  }

  protected void storeException(HttpServletRequest request, String property, ActionMessage error, ActionForward forward)
  {
    ActionMessages errors = (ActionMessages)request.getAttribute("org.apache.struts.action.ERROR");

    if (errors == null) {
      errors = new ActionMessages();
    }

    errors.add(property, error);

    request.setAttribute("org.apache.struts.action.ERROR", errors);
  }

  protected void logException(Exception ex)
  {
    StringWriter sw = new StringWriter();
    ex.printStackTrace(new PrintWriter(sw));
    log.error(sw.toString());
  }
}