package com.kingstargroup.ecard.portlet.information.service;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.portlet.infotype.service.InfoTypeServiceUtil;
import com.kingstargroup.ecard.portlet.uploadfile.service.UploadFileServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.EcardInformationPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.util.PropsUtil;

public class EcardInformationServiceImpl extends EcardInformationServiceBase {

	private static String cardlistDir = PropsUtil.get("info.cardlist.dir");

	/**
	 * Description:添加无上传文件的信息
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
	public  EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException {
		return add(title, content, attachments, type, creater, null, null, 0);
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
	public  EcardInformation add(String title, String content,
			String attachments, String type, String creater,
			HttpServletRequest req, String[] uploadFieldNames, int uploadType)
			throws IOException, PortalException {
		EcardInformation info = new EcardInformation();
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setInfoType(type);
		info.setCreateDate(new Date());
		info.setCreater(creater);
		try {
			// 如果有待上传的文件
			if (req != null) {
				attachments = UploadFileServiceUtil.upload(req, uploadFieldNames,
						uploadType);
			}
			info.setAttachments(attachments);
			informationPersistence.add(info);
		} catch (PortalException pe) {
			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
		return info;

	}
	
	public  EcardInformation add(String title, String content,
			String attachments, String type, String creater,UpLoadForm upLoadForm,int uploadType)
			throws IOException, PortalException {
		EcardInformation info = new EcardInformation();
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setInfoType(type);
		info.setCreateDate(new Date());
		info.setCreater(creater);
		try {
			// 如果有待上传的文件
			if (upLoadForm != null) {
				attachments = UploadFileServiceUtil.upload(upLoadForm,uploadType);
			}
			info.setAttachments(attachments);
			informationPersistence.add(info);
		} catch (PortalException pe) {
			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
		return info;

	}

	/**
	 * Description:根据信息ID得到对应的信息对象
	 * 
	 * @param id
	 *            传入的信息ID
	 * @return Modify History:
	 */
	public  EcardInformation getInfoById(String id)
			throws PortalException {
		EcardInformation info = null;

		try {
			info =informationPersistence.getInfoById(id);
		} catch (DBSystemException e) {
			throw e;
		}
		return info;
	}

	public  void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException {
		updateInfoById(id, title, content, attachments, null, null,
				EcardConstants.DOCUMENT_TYPE);
	}

	/**
	 * Description:
	 * 
	 * @param id
	 *            要更新的信息ID
	 * @param title
	 *            要更新的信息标题
	 * @param content
	 *            要更新的信息内容
	 * @param attachments
	 *            要更新的信息附件ID
	 * @param req
	 *            用户上传文件的Action请求
	 * @param uploadFieldNames
	 *            上传文件的名字域
	 * @param uploadType
	 *            上传类型
	 * @throws PortalException
	 *             Modify History:
	 */
	public  void updateInfoById(String id, String title, String content,
			String attachments, HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException {
		EcardInformation info = informationPersistence.getInfoById(id);
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setCreateDate(new Date());
		info.setAttachments(attachments);
		try {
			if (req != null) {
				UploadFileServiceUtil.updateUpload(req, uploadFieldNames, uploadType,
						com.liferay.portal.kernel.util.StringUtil.split(attachments));
			}
			informationPersistence.update(info);

		} catch (PortalException pe) {

			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
	}
	
	public  void updateInfoById(String id, String title, String content,
			String attachments, UpLoadForm upLoadForm, int uploadType) throws IOException,
			PortalException {
		EcardInformation info = informationPersistence.getInfoById(id);
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setCreateDate(new Date());
		info.setAttachments(attachments);
		try {
			if (upLoadForm != null) {
				UploadFileServiceUtil.updateUpload(upLoadForm, uploadType,
						com.liferay.portal.kernel.util.StringUtil.split(attachments));
			}
			informationPersistence.update(info);

		} catch (PortalException pe) {

			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
	}

	public  ResultPage list(String infoType) throws PortalException {
		return list(0, infoType);
	}

	public  ResultPage list(int page, String infoType)
			throws PortalException {
		return list(page, infoType, EcardConstants.MAX_RESULT_SIZE);
	}

	/**
	 * Description:根据要请求的页和页记录数、信息类型查询需要的信息数据?
	 * 
	 * @param page
	 *            页码?
	 * @param size
	 *            一页需要包含的记录数
	 * @param infoType
	 *            要取得的信息类型
	 * @throws PortalException
	 * @return Modify History:
	 */
	public  ResultPage list(int page, String infoType, int size)
			throws PortalException {
		return search(null, null, infoType, page, size);
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
	public  ResultPage search(String title, String content,
			String infoType, int page) throws PortalException {
		return search(title, content, infoType, page,
				EcardConstants.LIST_MORE_SIZE);
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
	 * @param size
	 *            指定一页返回多少记录
	 * @throws PortalException
	 * @return Modify History:
	 */
	public  ResultPage search(String title, String content,
			String infoType, int page, int size) throws PortalException {
		List subTypes = InfoTypeServiceUtil.getChildList(String.valueOf(infoType))
				.getList();
		List typeIds = new ArrayList();
		for (int i = 0; i < subTypes.size(); i++) {
			InfoType type = (InfoType) subTypes.get(i);
			typeIds.add(type.getInfoType());
		}
		typeIds.add(infoType);
		ResultPage result = null;
		try {
			result = informationPersistence.search(title, content, typeIds, page,
					size);
		} catch (DBSystemException e) {
			throw e;
		}
		return result;
	}

	public  List search(String title) throws PortalException {
		List results = null;
		try {
			results = informationPersistence.search(title);
		} catch (DBSystemException e) {
			throw e;
		}
		return results;
	}

	/**
	 * Description:根据传入要删除的ID数组删除对应的新闻
	 * 
	 * @param ids
	 *            要删除的ID数组
	 * @throws PortalException
	 *             Modify History:
	 */
	public  boolean deleteInfos(String[] ids) throws PortalException {
		boolean result = false;
		try {
			List delAttachIds = new ArrayList();
			for (int i = 0; i < ids.length; i++) {
				EcardInformation info = informationPersistence.getInfoById(ids[i]);
				String[] tmpAttachId = StringUtil.split(info.getAttachments(),
						EcardConstants.DELIMITER);
				if (tmpAttachId.length != 0) {
					delAttachIds.add(tmpAttachId[0]);
				}
			}
			UploadFileServiceUtil.deleteFile((String[]) delAttachIds
					.toArray(new String[delAttachIds.size()]));
			result = informationPersistence.deleteInfosByIds(ids);
		} catch (Exception e) {
			throw new PortalException(e);
		}
		return result;
	}
	
	
	/**
	 * Description:删除卡名单
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public  void deleteInfomations(String[] ids) throws PortalException {
		try {
			for (int i = 0; i < ids.length; i++) {				
				EcardInformation info = informationPersistence.getInfoById(ids[i]);
				File ioFile = new File(cardlistDir + info.getAttachments());
				ioFile.delete();
				EcardInformationPool.remove(ids[i]);//update cache pool
			}
			informationPersistence.deleteInfosByIds(ids);			
		} catch (Exception e) {
			throw new PortalException(e);
		} 
	}

}
