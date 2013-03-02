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
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.hibernate.util.UploadFileUtil;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.EcardInformationPool;
import com.liferay.portal.kernel.util.StringUtil;

public interface EcardInformationService {
	
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
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException ;

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
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater,
			HttpServletRequest req, String[] uploadFieldNames, int uploadType)
			throws IOException, PortalException ;
	
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater,UpLoadForm upLoadForm, int uploadType)
			throws IOException, PortalException ;

	/**
	 * Description:根据信息ID得到对应的信息对象
	 * 
	 * @param id
	 *            传入的信息ID
	 * @return Modify History:
	 */
	public EcardInformation getInfoById(String id)throws PortalException ;
	
	
	public void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException;
	

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
	public void updateInfoById(String id, String title, String content,
			String attachments, HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException ;
	public void updateInfoById(String id, String title, String content,
			String attachments, UpLoadForm upLoadForm, int uploadType) throws IOException,
			PortalException ;

	public ResultPage list(String infoType) throws PortalException ;

	public ResultPage list(int page, String infoType)
			throws PortalException ;

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
	public ResultPage list(int page, String infoType, int size)
			throws PortalException;

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
	public ResultPage search(String title, String content,
			String infoType, int page) throws PortalException ;

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
	public ResultPage search(String title, String content,
			String infoType, int page, int size) throws PortalException ;

	public List search(String title) throws PortalException ;

	/**
	 * Description:根据传入要删除的ID数组删除对应的新闻
	 * 
	 * @param ids
	 *            要删除的ID数组
	 * @throws PortalException
	 *             Modify History:
	 */
	public boolean deleteInfos(String[] ids) throws PortalException ;
	
	
	/**
	 * Description:删除卡名单
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public void deleteInfomations(String[] ids) throws PortalException ;
	
}
