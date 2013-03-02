package com.kingstargroup.ecard.portlet.information.service;

import java.io.IOException;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.util.EcardConstants;

public class EcardInformationServiceUtil {

	public static ResultPage list(String infoType) throws PortalException {
		return list(0, infoType);
	}

	public static ResultPage list(int page, String infoType)
			throws PortalException {
		return list(page, infoType, EcardConstants.MAX_RESULT_SIZE);
	}

	public static ResultPage list(int page, String infoType, int size)
			throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.list(page, infoType, size);
	}

	public static ResultPage search(String title, String content,
			String infoType, int page, int size) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.search(title, content, infoType, page,
				size);

	}
	
	/**
	 * Description:根据用户提供的查询项查询出结果集
	 * 
	 * @param title
	 *            查询标题
	 * @param content
	 *            查询内容
	 * @param infoType
	 *            查询信息类型
	 * @param page
	 *            需要查询的页
	 * @throws PortalException
	 * @return Modify History:
	 */
	public static ResultPage search(String title, String content,
			String infoType, int page) throws PortalException {
		return search(title, content, infoType, page,
				EcardConstants.LIST_MORE_SIZE);
	}

	public static EcardInformation getInfoById(String id)
			throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.getInfoById(id);

	}

	/**
	 * Description:增加一条卡名单
	 * 
	 * @param title
	 * @param content
	 * @param attachments
	 * @param type
	 * @param creater
	 * @return
	 * @throws IOException
	 * @throws PortalException
	 *             Modify History:
	 */
	public static EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.add(title, content, attachments, type,
				creater);
	}

	/**
	 * Description:添加信息
	 * 
	 * @param title
	 *            信息标题
	 * @param content
	 *            信息内容
	 * @param attachments
	 *            信息附件，以,分隔上传文件的ID
	 * @param type
	 *            信息类型0-新闻通知 1-制度规章 2-文档下载 3-设备分布图 4-FAQ 5-领卡名单 6-失卡名单 7-操作指南
	 *            8-挂失需知
	 * @param creater
	 *            创建信息人的ID
	 * @param req
	 *            用户的上传Action请求
	 * @param uploadFieldNames
	 *            上传文件的域名称
	 * @param uploadType
	 *            上传的文件类型,0-文档,1-图片
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static EcardInformation add(String title, String content,
			String attachments, String type, String creater,
			HttpServletRequest req, String[] uploadFieldNames, int uploadType)
			throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.add(title, content, attachments, type,
				creater, req, uploadFieldNames, uploadType);
	}
	
	public static EcardInformation add(String title, String content,
			String attachments, String type, String creater,UpLoadForm upLoadForm, int uploadType)
			throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.add(title, content, attachments, type,
				creater,upLoadForm, uploadType);
	}

	/**
	 * Description:更新指定卡名单
	 * 
	 * @param id
	 * @param title
	 * @param content
	 * @param attachments
	 * @throws IOException
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.updateInfoById(id, title, content, attachments);
	}

	/**
	 * Description:删除卡名单
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteInfomations(String[] ids) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.deleteInfomations(ids);
	}

	public static void updateInfoById(String id, String title, String content,
			String attachments, HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.updateInfoById(id, title, content, attachments,
				req, uploadFieldNames, uploadType);
	}
	
	public static void updateInfoById(String id, String title, String content,
			String attachments, UpLoadForm upLoadForm, int uploadType) throws IOException,
			PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.updateInfoById(id, title, content, attachments,
				upLoadForm, uploadType);
	}

	public static List search(String title) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.search(title);
	}

	/**
	 * Description:根据传入要删除的ID数组删除对应的新闻
	 * 
	 * @param ids
	 *            要删除的ID数组
	 * @throws PortalException
	 *             Modify History:
	 */
	public static boolean deleteInfos(String[] ids) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.deleteInfos(ids);
	}

}
