/**
 * 
 */
package org.king.checkinmanage.web.form;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.upload.FormFile;
import org.apache.struts.upload.MultipartRequestHandler;

/**
 * <p> UpLoadForm.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="UpLoadForm.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-5-25
 * 
 *
 */
public class UpLoadForm extends ActionForm {

	  public static final String ERROR_PROPERTY_MAX_LENGTH_EXCEEDED = "org.apache.struts.webapp.upload.MaxLengthExceeded";
	  protected FormFile theFile;
	  public FormFile getTheFile() {
	      return theFile;
	  }
	  public void setTheFile(FormFile theFile) {
	      this.theFile = theFile;
	  }
	   public ActionErrors validate(
	        ActionMapping mapping,
	        HttpServletRequest request) {
	            
	        ActionErrors errors = null;
	        //has the maximum length been exceeded?
	        Boolean maxLengthExceeded =
	            (Boolean) request.getAttribute(
	                MultipartRequestHandler.ATTRIBUTE_MAX_LENGTH_EXCEEDED);
	                
	        if ((maxLengthExceeded != null) && (maxLengthExceeded.booleanValue())) {
	            errors = new ActionErrors();
	            errors.add(
	                ActionMessages.GLOBAL_MESSAGE ,
	                new ActionMessage("maxLengthExceeded"));
	            errors.add(
	                ActionMessages.GLOBAL_MESSAGE ,
	                new ActionMessage("maxLengthExplanation"));
	        }
	        return errors;

	    } 
}
