package com.liferay.portal.mycaptcha;

import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;

import javax.imageio.ImageIO;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.octo.captcha.service.CaptchaServiceException;
import com.sun.image.codec.jpeg.JPEGCodec;
import com.sun.image.codec.jpeg.JPEGImageEncoder;

public class ImageCaptchaServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public ImageCaptchaServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		  byte[] captchaChallengeAsJpeg = null;
	       // the output stream to render the captcha image as jpeg into
	        ByteArrayOutputStream jpegOutputStream = new ByteArrayOutputStream();
	        try {
	        // get the session id that will identify the generated captcha. 
	        //the same id must be used to validate the response, the session id is a good candidate!
	        
	        String captchaId = request.getSession().getId();
	        // call the ImageCaptchaService getChallenge method
	       
	        BufferedImage challenge = null;
	        synchronized (this) {
	        	 System.out.println("ipaddr:"+request.getRemoteAddr()+",capthchaid:"+captchaId);
	        	 challenge =
	                    CaptchaServiceSingleton.getInstance().getImageChallengeForID(captchaId,
	                            request.getLocale());
			}
	            // a jpeg encoder
	            JPEGImageEncoder jpegEncoder =
	                    JPEGCodec.createJPEGEncoder(jpegOutputStream);
	            jpegEncoder.encode(challenge);
	        } catch (IllegalArgumentException e) {
	        	 System.out.println("here error occur===A");
	        	e.printStackTrace();
	            response.sendError(HttpServletResponse.SC_NOT_FOUND);
	            return;
	        } catch (CaptchaServiceException e) {
	        	System.out.println("here error occur===B");
	        	e.printStackTrace();
	        	response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
	            return;
	        }

	        captchaChallengeAsJpeg = jpegOutputStream.toByteArray();

	        // flush it in the response
	        //Çå¿Õ»º³åÇø
	        response.reset();
	        response.setHeader("Cache-Control", "no-store");
	        response.setHeader("Pragma", "no-cache");
	        response.setDateHeader("Expires", 0);
	        response.setContentType("image/jpeg");
	        ServletOutputStream responseOutputStream =
	        	response.getOutputStream();
	        responseOutputStream.write(captchaChallengeAsJpeg);
	        responseOutputStream.flush();
	        responseOutputStream.close();

	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		doGet(request, response);
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
		super.init();
	}
	
	
	public void init(ServletConfig servletConfig) throws ServletException {

        super.init(servletConfig);

    }
	
	

}
