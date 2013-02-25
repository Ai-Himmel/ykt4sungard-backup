package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Opersite;
import com.sungard.smartcard.domain.Site;

/**
 * 站点设置dao
 * @author HongYi.Wang
 * @since 2012-2-21
 */
public interface SiteDao {
	
	/*
	 * 根据参数获取站点数目 用于更新
	 * @param parm[0] 存放sitename的值 
	 * @param parm[1] 存放ip的值 
	 */
	public int getExistSiteNumForUpdate(int siteno,String ...parm );
	
	/*
	 * 根据参数获取站点数目
	 * @param parm[0] 存放sitename的值 
	 * @param parm[1] 存放ip的值 
	 */
	public int getExistSiteNum(String ... parm);
	
	/*
	 * 添加站点数据
	 */
	public void addSite(Site site);
	
	/*
	 * 删除站点数据
	 */
	public void delSite(Site site);
	
	/*
	 * 更新站点数据
	 */
	public void updateSite(Site site);
	
	/*
	 * 查找站点数据
	 */
	public List<Site> querySite(Site site);
	
	
	/*
	 * 是否有关联操作员
	 */
	public int hasRelatedOperator(Site site);
	
	
	
	/*
	 * 添加站点操作员数据
	 */
	public void addOSite(Opersite os);
	
	/*
	 * 删除站点操作员数据
	 */
	public void delOSite(Opersite os);
	
	/*
	 * 更新站点操作员数据
	 */
	public void updateOSite(Opersite os);
	
	/*
	 * 查找站点操作员数据
	 */
	public List<Site> queryOSite(Opersite os);
	
	/*
	 * 站点操作员存在数
	 */
	public int hasOperatorSiteNum(Opersite os);
	
}
