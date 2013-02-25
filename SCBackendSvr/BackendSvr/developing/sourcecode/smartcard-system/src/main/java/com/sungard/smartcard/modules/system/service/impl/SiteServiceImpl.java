package com.sungard.smartcard.modules.system.service.impl;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.dao.SiteDao;
import com.sungard.smartcard.modules.system.service.SiteService;

@Service
public class SiteServiceImpl implements SiteService {
	private static final Logger logger = LoggerFactory.getLogger(SiteServiceImpl.class);
	@Autowired
	private SiteDao siteDao;
	public void setSiteDao(SiteDao siteDao) {
		this.siteDao = siteDao;
	}

	@Override
	@Transactional
	public void addNewSite(Site site) throws FunctionException{
		String sitename = site.getSitename();
		String ip = site.getIp();
		String machinecode = site.getMachinecode();
		String remark = site.getRemark();
		/**判断站点名称为空*/
		logger.debug("------------进入新增站点业务------------------");
		if(sitename==null || "".equals(sitename)){
			throw new FunctionException(RetCode.ADDSITE_WRONG_NULLSITENAME);
		}
		/**判断站点ip是否为空*/
		if(ip==null || "".equals(ip)){
			throw new FunctionException(RetCode.ADDSITE_WRONG_NULLSITEIP);
		}
		/**判断站点名称是否重复*/
		int i = siteDao.getExistSiteNum(sitename,null);
		if(i!=0){
			throw new FunctionException(RetCode.ADDSITE_WRONG_DUPLICATESITENAME);
		}
		/**判断站点ip是否重复*/
		int ii = siteDao.getExistSiteNum(null,ip);
		if(ii!=0){
			throw new FunctionException(RetCode.ADDSITE_WRONG_DUPLICATESITEIP);
		}
		/**判断站点名称字符串长度是否超出50*/
		if(sitename.length()>50){
			throw new FunctionException(RetCode.ADDSITE_WRONG_LONGSITENAME);
		}
		/**判断ip是否合法*/
		Pattern p = Pattern.compile("(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)){3}");
		Matcher m = p. matcher(ip);
		boolean b = m. matches();
		if(b==false){
			throw new FunctionException(RetCode.ADDSITE_WRONG_IPSTYLE);
		}
		if(machinecode==null){
			site.setMachinecode("");
		}
		if(remark==null){
			site.setRemark("");
		}
		logger.debug("新增站点名称:[{}--站点ip:{}--机器码:{}--备注:{}]",new Object[]{sitename,ip,machinecode,remark});
		/**设置站点保存日期*/
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		site.setLastsaved(sdf.format(new Date()));
		//TODO 添加站点未添加日志功能
		/**添加站点信息*/
		siteDao.addSite(site);
	}

	@Override
	@Transactional
	public void modifySite(Site site) throws FunctionException {
		int siteno = site.getSiteno();
		String sitename = site.getSitename();
		String ip = site.getIp();
		String machinecode = site.getMachinecode();
		String remark = site.getRemark();
		/**判断站点名称为空*/
		if(sitename==null || "".equals(sitename)){
			throw new FunctionException(RetCode.ADDSITE_WRONG_NULLSITENAME);
		}
		/**判断站点ip是否为空*/
		if(ip==null || "".equals(ip)){
			throw new FunctionException(RetCode.ADDSITE_WRONG_NULLSITEIP);
		}
		/**判断站点名称是否重复*/
		int i = siteDao.getExistSiteNumForUpdate(siteno,sitename,null);
		if(i!=0){
			throw new FunctionException(RetCode.ADDSITE_WRONG_DUPLICATESITENAME);
		}
		/**判断站点ip是否重复*/
		int ii = siteDao.getExistSiteNumForUpdate(siteno,null,ip);
		if(ii!=0){
			throw new FunctionException(RetCode.ADDSITE_WRONG_DUPLICATESITEIP);
		}
		/**判断站点名称字符串长度是否超出50*/
		if(sitename.length()>50){
			throw new FunctionException(RetCode.ADDSITE_WRONG_LONGSITENAME);
		}
		/**判断ip是否合法*/
		Pattern p = Pattern.compile("(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)){3}");
		Matcher m = p. matcher(ip);
		boolean b = m. matches();
		if(b==false){
			throw new FunctionException(RetCode.ADDSITE_WRONG_IPSTYLE);
		}
		if(machinecode==null){
			site.setMachinecode("");
		}
		if(remark==null){
			site.setRemark("");
		}
		logger.debug("修改站点名称|[{}站点ip|{}机器码|{}备注|{}]",new Object[]{sitename,ip,machinecode,remark});
		/**设置站点保存日期*/
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		site.setLastsaved(sdf.format(new Date()));
		//TODO 修改站点未添加日志功能
		siteDao.updateSite(site);
	}

	@Override
	@Transactional
	public void delSite(Site site) throws FunctionException {
		logger.info("删除站点"+site.getSiteno()+"的信息");
		/**判断该站点是否存在关联操作员*/
		boolean hasOperator=siteDao.hasRelatedOperator(site)>0?true:false;
		/**如果存在关联操作员抛出错误码1000110107*/
		if(hasOperator){
			throw new FunctionException(RetCode.DELSITE_EXISTOPERATOR);
		}
		/**删除站点数据*/
		siteDao.delSite(site);
	}

	@Override
	public List<Site> querySite(Site site) throws FunctionException {
		/**查询站点信息列表*/
		List<Site> sites = siteDao.querySite(site);
		return sites;
	}

}
