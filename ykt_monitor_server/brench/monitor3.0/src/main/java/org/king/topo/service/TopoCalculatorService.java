package org.king.topo.service;

import java.util.List;

import org.king.framework.service.Service;

public interface TopoCalculatorService  extends Service {

	/**
	* Description: 
	* @param 
	* @return void
	* Modify History: 2011-3-23 Linqing.He create
	*/
	public void calculateDevgroupInfo();
	
	
	/**
	* Description: 
	* @param  param 0:delete all then calc  1:comm calc to update
	* @return void
	* Modify History: 2011-3-24 Linqing.He create
	*/
	public void calculateTopoServerStatistic(int param);
	/**
	* Description: 
	* @param param 0:delete all then calc  1:comm calc to update  2:host reference calc 4 termdev reference calc
	* @return void
	* Modify History: 2011-3-23 Linqing.He create
	*/
	public void calculateTopoGroupStatistic(int param);
	/**
	* Description: 计算vml
	* @param 
	* @return void
	* Modify History: 2011-3-14 Linqing.He create
	*/
	public void calculateDivHtml(); 
	/**
	* Description: 获取vml信息
	* @param @return
	* @return List
	* Modify History: 2011-3-14 Linqing.He create
	*/
	public List getTopoGroupInfoList();
	
	public String getTopoHeadVMLInfo();
	
	/**
	* Description: 获取各组别统计信息
	* @param @return
	* @return List
	* Modify History: 2011-3-21 Linqing.He create
	*/
	public List getTopoGroupStatisticList();
	
	/**
	* Description: 获取各服务器统计
	* @param @return
	* @return List
	* Modify History: 2011-3-24 Linqing.He create
	*/
	public List getServerStatisticList();
	
}
