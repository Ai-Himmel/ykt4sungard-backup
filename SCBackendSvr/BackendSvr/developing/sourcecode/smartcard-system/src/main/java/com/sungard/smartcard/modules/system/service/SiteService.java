package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.exception.FunctionException;

/**
 * 站点维护业务
 * @author HongYi.Wang
 *
 */
public interface SiteService {
	/*
	 * 新增站点
	 * @param site
	 */
	public void addNewSite(Site site) throws FunctionException;
	
	/*
	 * 修改站点
	 * @param site
	 */
	public void modifySite(Site site) throws FunctionException;
	
	/*
	 * 删除站点
	 * @param site
	 */
	public void delSite(Site site) throws FunctionException;
	
	/*
	 * 查询站点
	 */
	public List<Site> querySite(Site site) throws FunctionException;
	
}
