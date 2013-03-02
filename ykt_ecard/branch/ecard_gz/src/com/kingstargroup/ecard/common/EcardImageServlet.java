/**
 * 
 */
package com.kingstargroup.ecard.common;

import java.io.IOException;
import java.io.InputStream;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.photo.TCifPhoto;
import com.kingstargroup.ecard.hibernate.util.PhotoUtil;
import com.kingstargroup.ecard.hibernate.util.UploadFileUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;

/**
 * @author jeffxiao
 *
 */
public class EcardImageServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {
		try {
			String id = req.getParameter("id");
			String cmd = ParamUtil.getString(req, "cmd");
			if (id == null) {				
				String cutId = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
				if (cutId.equals(StringPool.BLANK)) {
					return;
				}
				if (cmd.equals("download")) {
					String header = "attachment; filename=\"portrait.jpg\"";
					_writePortrait(cutId, res, "application/octet-stream", header);
				} else {
					_writePortrait(cutId, res, "image/jpg", null);
				}				
			} else {
				_writeImage(req, res);
			}
		} catch(PortalException pe) {
			_log.error(pe);
		}
	}
	
	private void _writeImage(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException, PortalException {
		String id = req.getParameter("id");
		byte[] bytes = UploadFileUtil.downloadFile(id);
		String fileName = UploadFileUtil.getFileName(id);
		String imageType = fileName.substring(fileName.lastIndexOf(".") + 1);
		res.setContentType("image/" + imageType);
		try {
			if (!res.isCommitted()) {
				ServletOutputStream out = res.getOutputStream();
				out.write(bytes);
				out.flush();
			}
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}
	}
	
	private void _writePortrait(String cutId, HttpServletResponse res, String contentType, String header) throws PortalException {		
		TCifPhoto photo = PhotoUtil.getPhoto(cutId);
		res.setContentType(contentType);
		if (header != null) {
			res.setHeader("Content-Disposition", header);
		}
		try {
			if (!res.isCommitted()) {
				ServletOutputStream out = res.getOutputStream();
				if (photo == null) {
					return;
				} else {
					InputStream is = photo.getPhoto().getBinaryStream();
					if (is == null) {
						return;
					}
					byte buffer[] = new byte[256];
					while (is.read(buffer, 0, 256) != -1) {						
						out.write(buffer);
					}					
				}
				out.flush();
			}
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}
	}
	
	private static final Log _log = LogFactory.getLog(EcardImageServlet.class);
}
