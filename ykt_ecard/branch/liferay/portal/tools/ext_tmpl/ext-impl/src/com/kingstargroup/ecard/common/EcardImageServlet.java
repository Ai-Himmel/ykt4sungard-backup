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
import com.kingstargroup.ecard.hibernate.photo.TPhoto;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.portlet.uploadfile.service.UploadFileServiceUtil;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.WebKeys;

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
				Long realUserId = (Long) req.getSession().getAttribute(
						WebKeys.USER_ID);
				User myuser;
				String stuempNo = "";
				try {
					myuser = UserLocalServiceUtil.getUserById(realUserId);
					stuempNo = myuser.getScreenName();
				} catch (com.liferay.portal.PortalException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (SystemException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				if (stuempNo.equals(StringPool.BLANK)) {
					return;
				}
				if (cmd.equals("download")) {
					String header = "attachment; filename=\"portrait.jpg\"";
					_writePortrait(stuempNo, res, "application/octet-stream",
							header);
				} else {
					_writePortrait(stuempNo, res, "image/jpg", null);
				}
			} else {
				_writeImage(req, res);
			}
		} catch (PortalException pe) {
			_log.error(pe);
		}
	}

	private void _writeImage(HttpServletRequest req, HttpServletResponse res)
			throws IOException, ServletException, PortalException {
		String id = req.getParameter("id");
		byte[] bytes = UploadFileServiceUtil.downloadFile(id);
		String fileName = UploadFileServiceUtil.getFileName(id);
		String imageType = fileName.substring(fileName.lastIndexOf(".") + 1);
		res.setContentType("image/" + imageType);
		try {
			if (!res.isCommitted()) {
				ServletOutputStream out = res.getOutputStream();
				out.write(bytes);
				out.flush();
			}
		} catch (Exception e) {
			_log.error(e.getMessage());
		}
	}

	private void _writePortrait(String stuempNo, HttpServletResponse res,
			String contentType, String header) throws IOException, ServletException, PortalException {
		TPhoto photo = CardServiceUtil.getPhoto(stuempNo);
		res.setContentType(contentType);
		if (header != null) {
			res.setHeader("Content-Disposition", header);
		}

		if (!res.isCommitted()) {
			ServletOutputStream out = null;
			try {
				out = res.getOutputStream();
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
			} catch (IOException e) {
				_log.error(e.getMessage());
			} catch (Exception e) {
				_log.error(e.getMessage());

			}
		}

	}

	private static final Log _log = LogFactory.getLog(EcardImageServlet.class);
}
