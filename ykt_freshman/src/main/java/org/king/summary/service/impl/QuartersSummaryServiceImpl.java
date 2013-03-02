/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QuartersSummaryServiceImpl.java
 * 创建日期： 2007-6-18 11:03:30
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-18 11:03:30     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.summary.service.impl;

import java.util.List;

import org.king.common.dao.AllDAO;
import org.king.summary.service.IQuartersSummaryService;

public class QuartersSummaryServiceImpl implements IQuartersSummaryService {
	private AllDAO allDAO;
	public void setAllDAO(AllDAO allDAO) {
		this.allDAO = allDAO;
	}

	public List getSummaryInfo() {
		return allDAO.getHibernateTemplate().find("select new Map(d.dormitoryId as id," +
				" d1.dictCaption as area,d2.dictCaption as location,d3.dictCaption as dormitory," +
				" d.roomNumber as roomNumber,d.ifDistribute as newStudent,d.accomodation as sumBeds," +
				" d.distributeNum as emptyBeds) " +
				" from Dormitorymodel d,Dictionary d1, Dictionary d2,Dictionary d3 " +
				" where d.area=d1.id.dictValue and d1.id.dictNo=17 " +
				" and d.location=d2.id.dictValue and d2.id.dictNo=20 " +
				" and d.dormitory=d3.id.dictValue and d3.id.dictNo=21 ");
	}

	

}
