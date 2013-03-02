package org.king.check;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoadFile extends HttpServlet {
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {
		String realPath = request.getRealPath("");
		//String statMonth = request.getParameter("statMonth");
		OutputStream o = response.getOutputStream();
		byte b[] = new byte[1024];
		// the file to download.
		File fileLoad = new File(realPath, "checkRecordReport.xls");
		// the dialogbox of download file.
		response.setHeader("Content-disposition", "attachment;filename=checkRecordReport.xls");
		// set the MIME type.
		response.setContentType("application/xls");
		// get the file length.
		long fileLength = fileLoad.length();
		String length = String.valueOf(fileLength);
		response.setHeader("Content_Length", length);
		// download the file.
		FileInputStream in = new FileInputStream(fileLoad);
		int n = 0;
		while ((n = in.read(b)) != -1) {
			o.write(b, 0, n);
		}
	}

	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws IOException, ServletException {
		doGet(request, response);
	}
}
