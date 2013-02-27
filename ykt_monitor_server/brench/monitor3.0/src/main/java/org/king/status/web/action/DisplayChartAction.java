package org.king.status.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.framework.web.action.BaseAction;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;

/**
 * .œ‘ æÕº∆¨
 * User: Yiming.You
 * Date: 2010-9-1
 */
public class DisplayChartAction extends BaseAction {
    public ActionForward display(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        response.setHeader("Content-Type", "image/jpeg");

        String filename = request.getParameter("filename");
        if (filename == null) {
            throw new ServletException("Parameter 'filename' must be supplied");
        }

        File file = new File(System.getProperty("java.io.tmpdir"), filename);
        if (!file.exists()) {
            throw new ServletException("File '" + file.getAbsolutePath() + "' does not exist");
        }
        BufferedInputStream bis = new BufferedInputStream(new FileInputStream(file));
        BufferedOutputStream bos = new BufferedOutputStream(response.getOutputStream());
        byte[] input = new byte[1024];
        boolean eof = false;
        while (!eof) {
            int length = bis.read(input);
            if (length == -1) {
                eof = true;
            } else {
                bos.write(input, 0, length);
            }
        }
        bos.flush();
        bis.close();
        bos.close();
        return null;
    }
}
