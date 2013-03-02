package com.kingstargroup.advquery.itext;

import java.awt.Color;
import java.awt.GradientPaint;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpSession;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartRenderingInfo;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.CategoryLabelPositions;
import org.jfree.chart.entity.StandardEntityCollection;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.renderer.category.BarRenderer;
import org.jfree.chart.servlet.ServletUtilities;

import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetPropertiesUtil;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.util.ReportActiveUtil;
import com.kingstargroup.advquery.hibernate.util.ReportShopBalanceUtil;
import com.lowagie.text.BadElementException;
import com.lowagie.text.Cell;
import com.lowagie.text.Chunk;
import com.lowagie.text.Document;
import com.lowagie.text.DocumentException;
import com.lowagie.text.Element;
import com.lowagie.text.Font;
import com.lowagie.text.Image;
import com.lowagie.text.Paragraph;
import com.lowagie.text.Table;
import com.lowagie.text.rtf.RtfWriter2;

public class ReportDataExport {
	private static int chartwidth = 700;

	private static int chartheight = 400;

	private static String filePath = "";

	// 总体消费情况开始统计日期
	private String consume30DaysDate = "";

	// 当前日期的前30周周一的日期
	private String beginWeekDate = "";

	// 当前日期所在月份
	private String beginMonthDate = "";

	// 当前日期的前30月所在月份
	private String endMonthDate = "";

	// 圈存开始日期
	private String tranBeginDate = "";

	public ReportDataExport(String path, String endWeekDate, String createDate,
			HttpSession session) {
		initDate(createDate, endWeekDate);
		getChartPicPath();
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 30天消费情况
		List consume30DaysResult = ReportShopBalanceUtil.getAllConsumeStat(
				consume30DaysDate, createDate, "bydate");
		// 生成前30周统计数据,如果当前日期不是周日，则不算当前周
		List consume30DaysResult1 = ReportShopBalanceUtil.getAllConsumeStat(
				beginWeekDate, endWeekDate, "byweek");
		List consume30WeeksResult = new GetListResultStat().getListByWeek(
				consume30DaysResult1, beginWeekDate, endWeekDate);
		Collections.sort(consume30WeeksResult, new SortListByResult(
				"balance_date"));
		// 30个月消费数据集
		List consume30MonthsResult = ReportShopBalanceUtil.getAllConsumeStat(
				beginMonthDate, endMonthDate, "bymonth");
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 各校区30天消费情况对比
		//List areaConsume30DaysResult = ReportShopBalanceUtil.getAreaSalesCompare(consume30DaysDate, createDate, "bydate");
		// POS和圈存转账情况对比
		List saving30DaysResult = ReportActiveUtil.getTotleSavingStat(
				consume30DaysDate, createDate, "bydate");
		// 经费本和支票充值情况对比
		List billSaving30DaysResult = ReportActiveUtil.getBillTotleSavingStat(
				consume30DaysDate, createDate, "bydate");
		// 各校区POS充值情况对比
		//List posSaving30DaysResult = ReportOperUtil.posSavingCompareStat(consume30DaysDate, createDate, "bydate");
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Pos和圈存转账30周情况对比
		List savingCompare30DaysResult = ReportActiveUtil.getTotleSavingStat(
				beginWeekDate, endWeekDate, "byweek");

		List savingCompare30WeeksResult = new GetListResultStat()
				.getListByWeek(savingCompare30DaysResult, beginWeekDate,
						endWeekDate);
		Collections.sort(savingCompare30WeeksResult, new SortListByResult(
				"balance_date"));
		// 经费本和支票30周情况对比
		List billSavingCompare30DaysResult = ReportActiveUtil
				.getBillTotleSavingStat(beginWeekDate, endWeekDate, "byweek");

		List billSavingCompare30WeeksResult = new GetListResultStat()
				.getListByWeek(billSavingCompare30DaysResult, beginWeekDate,
						endWeekDate);
		Collections.sort(billSavingCompare30WeeksResult, new SortListByResult(
				"balance_date"));
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Pos和圈存转账30月情况对比
		List savingCompare30MonthsResult = ReportActiveUtil
		.getTotleSavingStat(beginMonthDate, endMonthDate, "bymonth");
		// 经费本和支票30月情况对比
		List billSavingCompare30MonthsResult = ReportActiveUtil
		.getBillTotleSavingStat(beginMonthDate, endMonthDate,
				"bymonth");
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 圈存成功率
		List transferSuccResult = ReportActiveUtil.getTransferSuccessRate(
				tranBeginDate, createDate, "bydate");
		
		// =========================================================================
		Document document = new Document();
		try {
			RtfWriter2 writer;
			//System.out.println(path);
			writer = RtfWriter2.getInstance(document,
					new FileOutputStream(path));
			document.open();
			// 30天消费情况图形（金额）
			getconsume30DaysMoneyChart(consume30DaysResult, session, document);
			// 30天消费情况图形（笔数）
			getconsume30DaysNumChart(consume30DaysResult, session, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// 各校区30天消费情况对比（笔数和金额）
			//areaConsume30daysMoneyChart(areaConsume30DaysResult, session,document);
			//areaConsume30daysNumChart(areaConsume30DaysResult, session,document);
			// 30周消费情况（金额和笔数）
			getconsume30WeeksMoneyChart(consume30WeeksResult, session, document);
			getconsume30WeeksNumChart(consume30WeeksResult, session, document);
			// 30月消费情况（金额和笔数）
			getconsume30MonthsMoneyChart(consume30MonthsResult, session,
					document);
			getconsume30MonthsNumChart(consume30MonthsResult, session, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// 30天消费情况报表
			consume30Days(consume30DaysResult, writer, document, session);
			// 个校区30天消费情况对比报表
			//areaConsume30days(areaConsume30DaysResult, writer, document);
			// 30周消费情况报表
			Consume30Weeks(consume30WeeksResult, writer, document);
			// 30月消费情况报表
			Consume30Months(consume30MonthsResult, writer, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// POS和圈存存款30天情况对比(金额和笔数)
			savingCompare30DaysMoneyChart(saving30DaysResult, session, document);
			savingCompare30DaysNumChart(saving30DaysResult, session, document);
			// 经费本和支票存款30天情况对比（金额和笔数）
			billSavingCompare30DaysMoneyChart(billSaving30DaysResult, session,
					document);
			billSavingCompare30DaysNumChart(billSaving30DaysResult, session,
					document);
			// 各校区POS充值情况对比（金额和笔数）
			//posSavingCompare30DaysMoneyChart(posSaving30DaysResult, session,document);
			//posSavingCompare30DaysNumChart(posSaving30DaysResult, session,document);
			// pos和圈存存款30周情况对比（金额和笔数）
			savingCompare30WeeksMoneyChart(savingCompare30WeeksResult, session,
					document);
			savingCompare30WeeksNumChart(savingCompare30WeeksResult, session,
					document);
			// 票据充值30周情况对比（金额和笔数）
			billSavingCompare30WeeksMoneyChart(billSavingCompare30WeeksResult, session,
					document);
			billSavingCompare30WeeksNumChart(billSavingCompare30WeeksResult, session,
					document);
			// pos和圈存存款30月情况对比（金额和笔数）
			savingCompare30MonthsMoneyChart(savingCompare30MonthsResult, session,
					document);
			savingCompare30MonthsNumChart(savingCompare30MonthsResult, session,
					document);
			// 票据充值30月情况对比（金额和笔数）
			billSavingCompare30MonthsMoneyChart(billSavingCompare30MonthsResult, session,
					document);
			billSavingCompare30MonthsNumChart(billSavingCompare30MonthsResult, session,
					document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// POS和圈存存款30天情况对比报表
			savingCompare30Days(saving30DaysResult, writer, document);
			// 经费本和支票存款30天情况对比报表
			billSavingCompare30Days(billSaving30DaysResult, writer, document);
			// 各校区30天POS充值情况对比报表
			//posSavingCompare30Days(posSaving30DaysResult, writer, document);
			// pos和圈存存款30周情况对比报表
			savingCompare30Weeks(savingCompare30WeeksResult, writer, document);
			// 票据充值30周情况报表
			billSavingCompare30Weeks(billSavingCompare30WeeksResult, writer, document);
			// pos和圈存存款30月报表
			savingCompare30Months(savingCompare30MonthsResult, writer, document);
			// 票据充值30个月报表
			billSavingCompare30Months(billSavingCompare30MonthsResult, writer, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// 圈存成功率
			transferSuccessInAccountChart(transferSuccResult, session,
					document);
			transferSuccessRateChart(transferSuccResult, session,
					document);
			// 圈存情况报表
			transferSuccessRate(transferSuccResult, writer, document);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally {
			document.close();
			session.removeAttribute("JFreeChart_Deleter");
		}

	}

	/**
	 * 30天消费情况报表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void consume30Days(List consume30DaysResult, RtfWriter2 writer,
			Document document, HttpSession session) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("最近30天消费记录", PDFChineseFont.createChineseFont(12,
					Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			
			document.add(para);
			int widths[] = { 200, 200, 200, 300, 200, 300 };

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("天数"); 
			Cell week = new Cell("星期"); 
			Cell balance_date = new Cell("日期"); 
			Cell tradeamt = new Cell("交易金额"); 
			Cell tradenum = new Cell("交易笔数"); 
			Cell mngamt = new Cell("管理费"); 
			sysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
			week.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradeamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradenum.setHorizontalAlignment(Element.ALIGN_CENTER);
			mngamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			table.addCell(sysdate);
			table.addCell(week);
			table.addCell(balance_date);
			table.addCell(tradeamt);
			table.addCell(tradenum);
			table.addCell(mngamt);

			//table.endHeaders();// 换行
			Iterator iter = consume30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysdate = new Cell(map.get("sysdate").toString()); 
				Cell dweek = new Cell(map.get("week").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dtradeamt = new Cell(formatMoney(map.get("tradeamt").toString())); 
				Cell dtradenum = new Cell(map.get("tradenum").toString()); 
				Cell dmngamt = new Cell(formatMoney(map.get("mngamt").toString())); 
				dsysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
				dweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dtradeamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtradenum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dmngamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				table.addCell(dsysdate);
				table.addCell(dweek);
				table.addCell(dbalance_date);
				table.addCell(dtradeamt);
				table.addCell(dtradenum);
				table.addCell(dmngamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();

		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 各校区消费情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void areaConsume30days(List areaConsume30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("各校区最近30天消费情况", PDFChineseFont.createChineseFont(
					12, Font.NORMAL)));

			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 150, 300, 300, 300, 300, 300, 300, 300 };

			Table table = new Table(9);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("天数"); 
			Cell week = new Cell("星期"); 
			Cell balance_date = new Cell("日期"); 
			Cell hdnum = new Cell("邯郸笔数"); 
			Cell hdamt = new Cell("邯郸金额"); 
			Cell flnum = new Cell("枫林笔数"); 
			Cell flamt = new Cell("枫林金额"); 
			Cell zjnum = new Cell("张江笔数"); 
			Cell zjamt = new Cell("张江金额"); 
			sysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
			week.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			hdnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			hdamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			flnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			flamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			zjnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			zjamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(sysdate);
			table.addCell(week);
			table.addCell(balance_date);
			table.addCell(hdnum);
			table.addCell(hdamt);
			table.addCell(flnum);
			table.addCell(flamt);
			table.addCell(zjnum);
			table.addCell(zjamt);

			//table.endHeaders();// 换行
			Iterator iter = areaConsume30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysdate = new Cell(map.get("sysdate").toString()); 
				Cell dweek = new Cell(map.get("week").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dhdnum = new Cell(map.get("hdnum").toString()); 
				Cell dhdamt = new Cell(formatMoney(map.get("hdamt").toString())); 
				Cell dflnum = new Cell(map.get("flnum").toString()); 
				Cell dflamt = new Cell(formatMoney(map.get("flamt").toString())); 
				Cell dzjnum = new Cell(map.get("zjnum").toString()); 
				Cell dzjamt = new Cell(formatMoney(map.get("zjamt").toString())); 
				dsysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
				dweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dhdnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dhdamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dflnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dflamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dzjnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dzjamt.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysdate);
				table.addCell(dweek);
				table.addCell(dbalance_date);
				table.addCell(dhdnum);
				table.addCell(dhdamt);
				table.addCell(dflnum);
				table.addCell(dflamt);
				table.addCell(dzjnum);
				table.addCell(dzjamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 消费情况30周统计报表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void Consume30Weeks(List consume30WeeksResult, RtfWriter2 writer,
			Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("最近30个周消费记录", PDFChineseFont.createChineseFont(
					12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 400, 300, 300, 200 };

			Table table = new Table(5);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysusedweek = new Cell("第N周"); 
			Cell balance_date = new Cell("日期范围"); 
			Cell tradeamt = new Cell("交易金额"); 
			Cell tradenum = new Cell("交易笔数"); 
			Cell mngamt = new Cell("管理费"); 
			sysusedweek.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradeamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradenum.setHorizontalAlignment(Element.ALIGN_CENTER);
			mngamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			table.addCell(sysusedweek);
			table.addCell(balance_date);
			table.addCell(tradeamt);
			table.addCell(tradenum);
			table.addCell(mngamt);

			//table.endHeaders();// 换行
			Iterator iter = consume30WeeksResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysusedweek = new Cell(map.get("sysusedweek").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dtradeamt = new Cell(formatMoney(map.get("tradeamt").toString())); 
				Cell dtradenum = new Cell(map.get("tradenum").toString()); 
				Cell dmngamt = new Cell(formatMoney(map.get("mngamt").toString())); 
				dsysusedweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dtradeamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtradenum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dmngamt.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysusedweek);
				table.addCell(dbalance_date);
				table.addCell(dtradeamt);
				table.addCell(dtradenum);
				table.addCell(dmngamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	private void Consume30Months(List consume30MonthsResult, RtfWriter2 writer,
			Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("最近30个月消费记录", PDFChineseFont.createChineseFont(
					12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 200, 400, 300, 300 };

			Table table = new Table(4);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell balance_date = new Cell("月份"); 
			Cell tradeamt = new Cell("交易金额"); 
			Cell tradenum = new Cell("交易笔数"); 
			Cell mngamt = new Cell("管理费"); 
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradeamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradenum.setHorizontalAlignment(Element.ALIGN_CENTER);
			mngamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(balance_date);
			table.addCell(tradeamt);
			table.addCell(tradenum);
			table.addCell(mngamt);

			//table.endHeaders();// 换行
			Iterator iter = consume30MonthsResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dtradeamt = new Cell(formatMoney(map.get("tradeamt").toString())); 
				Cell dtradenum = new Cell(map.get("tradenum").toString()); 
				Cell dmngamt = new Cell(formatMoney(map.get("mngamt").toString())); 
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dtradeamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtradenum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dmngamt.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dbalance_date);
				table.addCell(dtradeamt);
				table.addCell(dtradenum);
				table.addCell(dmngamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * POS和圈存转账30天情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void savingCompare30Days(List saving30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("POS和圈存最近30天存款情况", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 150, 250, 200, 300, 200, 300 ,300};

			Table table = new Table(8);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("天数"); 
			Cell week = new Cell("星期"); 
			Cell balance_date = new Cell("日期"); 
			Cell posnum = new Cell("POS笔数"); 
			Cell posamt = new Cell("POS金额"); 
			Cell transfernum = new Cell("圈存笔数"); 
			Cell transferamt = new Cell("圈存金额"); 
			Cell cashamt = new Cell("现金充值");
			sysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
			week.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			posnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			posamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			transfernum.setHorizontalAlignment(Element.ALIGN_CENTER);
			transferamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			cashamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(sysdate);
			table.addCell(week);
			table.addCell(balance_date);
			table.addCell(posnum);
			table.addCell(posamt);
			table.addCell(transfernum);
			table.addCell(transferamt);
			table.addCell(cashamt);

			//table.endHeaders();// 换行
			Iterator iter = saving30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysdate = new Cell(map.get("sysdate").toString()); 
				Cell dweek = new Cell(map.get("week").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dposnum = new Cell(map.get("posnum").toString()); 
				Cell dposamt = new Cell(formatMoney(map.get("posamt").toString())); 
				Cell dtransfernum = new Cell(map.get("transfernum").toString()); 
				Cell dtransferamt = new Cell(formatMoney(map.get("transferamt").toString())); 
				Cell dcashamt = new Cell(formatMoney(map.get("cashamt").toString())); 
				dsysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
				dweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dposnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dposamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtransfernum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtransferamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dcashamt.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysdate);
				table.addCell(dweek);
				table.addCell(dbalance_date);
				table.addCell(dposnum);
				table.addCell(dposamt);
				table.addCell(dtransfernum);
				table.addCell(dtransferamt);
				table.addCell(dcashamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * POS和圈存30周充值报表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void savingCompare30Weeks(List savingCompare30WeeksResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("POS和圈存最近30个周存款情况", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 400, 200, 200, 200, 200 ,200};

			Table table = new Table(7);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysusedweek = new Cell("第N周"); 
			Cell balance_date = new Cell("日期范围"); 
			Cell posnum = new Cell("POS笔数"); 
			Cell posamt = new Cell("POS金额"); 
			Cell transfernum = new Cell("圈存笔数"); 
			Cell transferamt = new Cell("圈存金额"); 
			Cell cashamt = new Cell("现金充值"); 
			sysusedweek.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			posnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			posamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			transfernum.setHorizontalAlignment(Element.ALIGN_CENTER);
			transferamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			cashamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(sysusedweek);
			table.addCell(balance_date);
			table.addCell(posnum);
			table.addCell(posamt);
			table.addCell(transfernum);
			table.addCell(transferamt);
			table.addCell(cashamt);

			//table.endHeaders();// 换行
			Iterator iter = savingCompare30WeeksResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysusedweek = new Cell(map.get("sysusedweek").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dposnum = new Cell(map.get("posnum").toString()); 
				Cell dposamt = new Cell(formatMoney(map.get("posamt").toString())); 
				Cell dtransfernum = new Cell(map.get("transfernum").toString()); 
				Cell dtransferamt = new Cell(formatMoney(map.get("transferamt").toString())); 
				Cell dcashamt = new Cell(formatMoney(map.get("cashamt").toString())); 
				dsysusedweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dposnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dposamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtransfernum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtransferamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dcashamt.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysusedweek);
				table.addCell(dbalance_date);
				table.addCell(dposnum);
				table.addCell(dposamt);
				table.addCell(dtransfernum);
				table.addCell(dtransferamt);
				table.addCell(dcashamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}
	private void savingCompare30Months(List savingCompare30MonthsResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("POS和圈存最近30个月存款情况", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 250, 200, 300, 200, 300 ,300};

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell balance_date = new Cell("月份"); 
			Cell posnum = new Cell("POS笔数"); 
			Cell posamt = new Cell("POS金额"); 
			Cell transfernum = new Cell("圈存笔数"); 
			Cell transferamt = new Cell("圈存金额"); 
			Cell cashamt = new Cell("现金充值"); 
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			posnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			posamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			transfernum.setHorizontalAlignment(Element.ALIGN_CENTER);
			transferamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			cashamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(balance_date);
			table.addCell(posnum);
			table.addCell(posamt);
			table.addCell(transfernum);
			table.addCell(transferamt);
			table.addCell(cashamt);

			//table.endHeaders();// 换行
			Iterator iter = savingCompare30MonthsResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dposnum = new Cell(map.get("posnum").toString()); 
				Cell dposamt = new Cell(formatMoney(map.get("posamt").toString())); 
				Cell dtransfernum = new Cell(map.get("transfernum").toString()); 
				Cell dtransferamt = new Cell(formatMoney(map.get("transferamt").toString())); 
				Cell dcashamt = new Cell(formatMoney(map.get("cashamt").toString())); 
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dposnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dposamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtransfernum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dtransferamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dcashamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				table.addCell(dbalance_date);
				table.addCell(dposnum);
				table.addCell(dposamt);
				table.addCell(dtransfernum);
				table.addCell(dtransferamt);
				table.addCell(dcashamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 经费本和支票30周充值情况报表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void billSavingCompare30Weeks(List billSavingCompare30WeeksResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("经费本和支票最近30个周存款情况", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 400, 200, 200, 200, 200 };

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysusedweek = new Cell("第N周"); 
			Cell balance_date = new Cell("日期范围"); 
			Cell outlaynum = new Cell("经费本笔数"); 
			Cell outlaymoney = new Cell("经费本金额"); 
			Cell ticketnum = new Cell("支票笔数"); 
			Cell ticketmoney = new Cell("支票金额"); 
			sysusedweek.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			outlaynum.setHorizontalAlignment(Element.ALIGN_CENTER);
			outlaymoney.setHorizontalAlignment(Element.ALIGN_CENTER);
			ticketnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			ticketmoney.setHorizontalAlignment(Element.ALIGN_CENTER);
			table.addCell(sysusedweek);
			table.addCell(balance_date);
			table.addCell(outlaynum);
			table.addCell(outlaymoney);
			table.addCell(ticketnum);
			table.addCell(ticketmoney);

			//table.endHeaders();// 换行
			Iterator iter = billSavingCompare30WeeksResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysusedweek = new Cell(map.get("sysusedweek").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell doutlaynum = new Cell(map.get("outlaynum").toString()); 
				Cell doutlaymoney = new Cell(formatMoney(map.get("outlaymoney").toString())); 
				Cell dticketnum = new Cell(map.get("ticketnum").toString()); 
				Cell dticketmoney = new Cell(formatMoney(map.get("ticketmoney").toString())); 
				
				dsysusedweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				doutlaynum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				doutlaymoney.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dticketnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dticketmoney.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysusedweek);
				table.addCell(dbalance_date);
				table.addCell(doutlaynum);
				table.addCell(doutlaymoney);
				table.addCell(dticketnum);
				table.addCell(dticketmoney);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 经费本和支票30天充值情况对比报表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void billSavingCompare30Days(List billSaving30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("经费本和支票最近30天存款情况", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 100, 100, 200, 250, 250, 200, 200 };

			Table table = new Table(7);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("天数"); 
			Cell week = new Cell("星期"); 
			Cell balance_date = new Cell("日期"); 
			Cell outlaynum = new Cell("经费本笔数"); 
			Cell outlaymoney = new Cell("经费本金额"); 
			Cell ticketnum = new Cell("支票笔数"); 
			Cell ticketmoney = new Cell("支票金额"); 
			sysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
			week.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			outlaynum.setHorizontalAlignment(Element.ALIGN_CENTER);
			outlaymoney.setHorizontalAlignment(Element.ALIGN_CENTER);
			ticketnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			ticketmoney.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(sysdate);
			table.addCell(week);
			table.addCell(balance_date);
			table.addCell(outlaynum);
			table.addCell(outlaymoney);
			table.addCell(ticketnum);
			table.addCell(ticketmoney);

			//table.endHeaders();// 换行
			Iterator iter = billSaving30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysdate = new Cell(map.get("sysdate").toString()); 
				Cell dweek = new Cell(map.get("week").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell doutlaynum = new Cell(map.get("outlaynum").toString()); 
				Cell doutlaymoney = new Cell(formatMoney(map.get("outlaymoney").toString())); 
				Cell dticketnum = new Cell(map.get("ticketnum").toString()); 
				Cell dticketmoney = new Cell(formatMoney(map.get("ticketmoney").toString())); 
				dsysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
				dweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				doutlaynum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				doutlaymoney.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dticketnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dticketmoney.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysdate);
				table.addCell(dweek);
				table.addCell(dbalance_date);
				table.addCell(doutlaynum);
				table.addCell(doutlaymoney);
				table.addCell(dticketnum);
				table.addCell(dticketmoney);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}
	private void billSavingCompare30Months(List billSavingCompare30MonthsResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("经费本和支票最近30个月存款情况", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 200, 250, 250, 200, 200 };

			Table table = new Table(5);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell balance_date = new Cell("月份"); 
			Cell outlaynum = new Cell("经费本笔数"); 
			Cell outlaymoney = new Cell("经费本金额"); 
			Cell ticketnum = new Cell("支票笔数"); 
			Cell ticketmoney = new Cell("支票金额"); 
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			outlaynum.setHorizontalAlignment(Element.ALIGN_CENTER);
			outlaymoney.setHorizontalAlignment(Element.ALIGN_CENTER);
			ticketnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			ticketmoney.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(balance_date);
			table.addCell(outlaynum);
			table.addCell(outlaymoney);
			table.addCell(ticketnum);
			table.addCell(ticketmoney);

			//table.endHeaders();// 换行
			Iterator iter = billSavingCompare30MonthsResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell doutlaynum = new Cell(map.get("outlaynum").toString()); 
				Cell doutlaymoney = new Cell(formatMoney(map.get("outlaymoney").toString())); 
				Cell dticketnum = new Cell(map.get("ticketnum").toString()); 
				Cell dticketmoney = new Cell(formatMoney(map.get("ticketmoney").toString())); 
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				doutlaynum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				doutlaymoney.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dticketnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dticketmoney.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dbalance_date);
				table.addCell(doutlaynum);
				table.addCell(doutlaymoney);
				table.addCell(dticketnum);
				table.addCell(dticketmoney);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 各校区POS充值30天情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void posSavingCompare30Days(List posSavingCompare30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("各校区最近30天POS充值情况报表", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 150, 300, 300, 300, 300, 300, 300, 300 };

			Table table = new Table(9);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("天数"); 
			Cell week = new Cell("星期"); 
			Cell balance_date = new Cell("日期"); 
			Cell hdnum = new Cell("邯郸笔数"); 
			Cell hdamt = new Cell("邯郸金额"); 
			Cell flnum = new Cell("枫林笔数"); 
			Cell flamt = new Cell("枫林金额"); 
			Cell zjnum = new Cell("张江笔数"); 
			Cell zjamt = new Cell("张江金额"); 
			sysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
			week.setHorizontalAlignment(Element.ALIGN_CENTER);
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			hdnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			hdamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			flnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			flamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			zjnum.setHorizontalAlignment(Element.ALIGN_CENTER);
			zjamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(sysdate);
			table.addCell(week);
			table.addCell(balance_date);
			table.addCell(hdnum);
			table.addCell(hdamt);
			table.addCell(flnum);
			table.addCell(flamt);
			table.addCell(zjnum);
			table.addCell(zjamt);

			//table.endHeaders();// 换行
			Iterator iter = posSavingCompare30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				Cell dsysdate = new Cell(map.get("sysdate").toString()); 
				Cell dweek = new Cell(map.get("week").toString()); 
				Cell dbalance_date = new Cell(map.get("balance_date").toString()); 
				Cell dhdnum = new Cell(map.get("hdnum").toString()); 
				Cell dhdamt = new Cell(formatMoney(map.get("hdamt").toString())); 
				Cell dflnum = new Cell(map.get("flnum").toString()); 
				Cell dflamt = new Cell(formatMoney(map.get("flamt").toString())); 
				Cell dzjnum = new Cell(map.get("zjnum").toString()); 
				Cell dzjamt = new Cell(formatMoney(map.get("zjamt").toString())); 
				dsysdate.setHorizontalAlignment(Element.ALIGN_CENTER);
				dweek.setHorizontalAlignment(Element.ALIGN_CENTER);
				dbalance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
				dhdnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dhdamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dflnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dflamt.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dzjnum.setHorizontalAlignment(Element.ALIGN_RIGHT);
				dzjamt.setHorizontalAlignment(Element.ALIGN_RIGHT);

				table.addCell(dsysdate);
				table.addCell(dweek);
				table.addCell(dbalance_date);
				table.addCell(dhdnum);
				table.addCell(dhdamt);
				table.addCell(dflnum);
				table.addCell(dflamt);
				table.addCell(dzjnum);
				table.addCell(dzjamt);
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 创建30天消费记录图表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30DaysMoneyChart(List consume30DaysResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "消费金额" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitleMoney[] = { "tradeamt" };
		String consume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(consume30DaysResult,
				"tradeamt", dataType);
		consume30DaysY = new GetListResultStat().getYLabelMoney(
				consume30DaysResult, "tradeamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天消费记录(金额)", "消费日期",
				consume30DaysY, new DrawBarByTypeMap(consume30DaysResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, true);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			//System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"+filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 30天消费情况（笔数） 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30DaysNumChart(List consume30DaysResult,
			HttpSession session, Document document) {
		String accType[] = { "消费笔数" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "tradenum" };
		String consume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(consume30DaysResult,
				"tradenum", dataType);
		consume30DaysY = new GetListResultStat().getYLabelNum(
				consume30DaysResult, "tradenum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天消费记录(笔数)", "消费日期",
				consume30DaysY, new DrawBarByTypeMap(consume30DaysResult,
						accType, xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30天充值金额对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30DaysMoneyChart(
			List billSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accTypeMoney[] = { "经费本充值", "支票充值" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitleMoney[] = { "outlaymoney", "ticketmoney" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				billSavingCompare30DaysResult, "outlaymoney", dataType);
		Y = new GetListResultStat().getYLabelMoney(
				billSavingCompare30DaysResult, "outlaymoney", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天经费本和支票存款对比(金额)",
				"存款日期", Y, new DrawBarByTypeMap(billSavingCompare30DaysResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, true);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30天充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30DaysNumChart(
			List billSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accType[] = { "经费本充值", "支票充值" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "outlaynum", "ticketnum" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				billSavingCompare30DaysResult, "posnum", dataType);
		Y = new GetListResultStat().getYLabelNum(billSavingCompare30DaysResult,
				"posnum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天经费本和支票存款对比(笔数)",
				"存款日期", Y, new DrawBarByTypeMap(billSavingCompare30DaysResult,
						accType, xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

		/**
		 * 经费本和支票充值30个周（金额）
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void billSavingCompare30WeeksMoneyChart(
			List billSavingCompare30WeeksResult, HttpSession session,
			Document document) {
		String accTypeMoney[] = { "经费本充值", "支票充值" };
		String xData = "sysusedweek";
		String dataType = "float";
		String columnTitleMoney[] = { "outlaymoney", "ticketmoney" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				billSavingCompare30WeeksResult, "outlaymoney", dataType);
		Y = new GetListResultStat().getYLabelMoney(
				billSavingCompare30WeeksResult, "outlaymoney", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个周经费本和支票存款对比(金额)",
				"第N周", Y, new DrawBarByTypeMap(billSavingCompare30WeeksResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, false);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30天充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30WeeksNumChart(
			List billSavingCompare30WeeksResult, HttpSession session,
			Document document) {
		String accType[] = { "经费本充值", "支票充值" };
		String xData = "sysusedweek";
		String dataType = "integer";
		String columnTitle[] = { "outlaynum", "ticketnum" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				billSavingCompare30WeeksResult, "posnum", dataType);
		Y = new GetListResultStat().getYLabelNum(
				billSavingCompare30WeeksResult, "posnum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个周经费本和支票存款对比(笔数)",
				"第N周", Y, new DrawBarByTypeMap(billSavingCompare30WeeksResult,
						accType, xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, false);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}
		/**
		 * 经费本和支票充值30个月（金额）
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void billSavingCompare30MonthsMoneyChart(
			List billSavingCompare30MonthsResult, HttpSession session,
			Document document) {
		String accTypeMoney[] = { "经费本充值", "支票充值" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitleMoney[] = { "outlaymoney", "ticketmoney" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				billSavingCompare30MonthsResult, "outlaymoney", dataType);
		Y = new GetListResultStat().getYLabelMoney(
				billSavingCompare30MonthsResult, "outlaymoney", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个月经费本和支票存款对比(金额)",
				"存款月份", Y, new DrawBarByTypeMap(billSavingCompare30MonthsResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, true);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30月充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30MonthsNumChart(
			List billSavingCompare30MonthsResult, HttpSession session,
			Document document) {
		String accType[] = { "经费本充值", "支票充值" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "outlaynum", "ticketnum" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				billSavingCompare30MonthsResult, "posnum", dataType);
		Y = new GetListResultStat().getYLabelNum(billSavingCompare30MonthsResult,
				"posnum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天经费本和支票存款对比(笔数)",
				"存款月份", Y, new DrawBarByTypeMap(billSavingCompare30MonthsResult,
						accType, xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * "POS充值", "圈存转账"30天充值金额对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30DaysMoneyChart(List saving30DaysResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "POS充值", "圈存转账" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitleMoney[] = { "posamt", "transferamt" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(saving30DaysResult,
				"posamt", dataType);
		Y = new GetListResultStat().getYLabelMoney(saving30DaysResult,
				"posamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天POS和圈存存款对比(金额)",
				"存款日期", Y, new DrawBarByTypeMap(saving30DaysResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, true);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30天充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30DaysNumChart(List saving30DaysResult,
			HttpSession session, Document document) {
		String accType[] = { "POS充值", "圈存转账" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "posnum", "transfernum" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(saving30DaysResult,
				"posnum", dataType);
		Y = new GetListResultStat().getYLabelNum(saving30DaysResult, "posnum",
				dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30天POS和圈存存款对比(笔数)",
				"存款日期", Y, new DrawBarByTypeMap(saving30DaysResult, accType,
						xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * "POS充值", "圈存转账"30个周充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30WeeksMoneyChart(
			List saving30WeeksResult, HttpSession session, Document document) {
		String accTypeMoney[] = { "POS充值", "圈存转账" };
		String xData = "sysusedweek";
		String dataType = "float";
		String columnTitleMoney[] = { "posamt", "transferamt" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(saving30WeeksResult,
				"posamt", dataType);
		Y = new GetListResultStat().getYLabelMoney(saving30WeeksResult,
				"posamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个周POS和圈存存款对比(金额)",
				"第N周", Y, new DrawBarByTypeMap(saving30WeeksResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, false);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30周充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30WeeksNumChart(List saving30WeeksResult,
			HttpSession session, Document document) {
		String accType[] = { "POS充值", "圈存转账" };
		String xData = "sysusedweek";
		String dataType = "integer";
		String columnTitle[] = { "posnum", "transfernum" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(saving30WeeksResult,
				"posnum", dataType);
		Y = new GetListResultStat().getYLabelNum(saving30WeeksResult, "posnum",
				dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个周POS和圈存存款对比(笔数)",
				"第N周", Y, new DrawBarByTypeMap(saving30WeeksResult, accType,
						xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, false);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}
		/**
		 * pos充值和圈存转帐30个月对比（金额）
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void savingCompare30MonthsMoneyChart(List saving30MonthsResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "POS充值", "圈存转账" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitleMoney[] = { "posamt", "transferamt" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(saving30MonthsResult,
				"posamt", dataType);
		Y = new GetListResultStat().getYLabelMoney(saving30MonthsResult,
				"posamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个月POS和圈存存款对比(金额)",
				"存款月份", Y, new DrawBarByTypeMap(saving30MonthsResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, true);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * "POS充值", "圈存转账"30月充值情况对比 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30MonthsNumChart(List saving30MonthsResult,
			HttpSession session, Document document) {
		String accType[] = { "POS充值", "圈存转账" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "posnum", "transfernum" };
		String Y = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(saving30MonthsResult,
				"posnum", dataType);
		Y = new GetListResultStat().getYLabelNum(saving30MonthsResult, "posnum",
				dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个月POS和圈存存款对比(笔数)",
				"存款月份", Y, new DrawBarByTypeMap(saving30MonthsResult, accType,
						xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 创建30周消费记录图表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30WeeksMoneyChart(List consume30WeeksResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "消费金额" };
		String xData = "sysusedweek";
		String dataType = "float";
		String columnTitleMoney[] = { "tradeamt" };
		String consume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(consume30WeeksResult,
				"tradeamt", dataType);
		consume30DaysY = new GetListResultStat().getYLabelMoney(
				consume30WeeksResult, "tradeamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个周消费记录(金额)", "第N周消费",
				consume30DaysY, new DrawBarByTypeMap(consume30WeeksResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, false);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 第N周消费情况 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30WeeksNumChart(List consume30WeeksResult,
			HttpSession session, Document document) {
		String accType[] = { "消费笔数" };
		String xData = "sysusedweek";
		String dataType = "integer";
		String columnTitle[] = { "tradenum" };
		String consume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(consume30WeeksResult,
				"tradenum", dataType);
		consume30DaysY = new GetListResultStat().getYLabelNum(
				consume30WeeksResult, "tradenum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个周消费记录(笔数)", "第N周消费",
				consume30DaysY, new DrawBarByTypeMap(consume30WeeksResult,
						accType, xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, false);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 创建30月消费记录图表 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30MonthsMoneyChart(
			List consume30MonthsResult, HttpSession session, Document document) {
		String accTypeMoney[] = { "消费金额" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitleMoney[] = { "tradeamt" };
		String consume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(consume30MonthsResult,
				"tradeamt", dataType);
		consume30DaysY = new GetListResultStat().getYLabelMoney(
				consume30MonthsResult, "tradeamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个月消费记录(金额)", "消费月份",
				consume30DaysY, new DrawBarByTypeMap(consume30MonthsResult,
						accTypeMoney, xData, dataType, columnTitleMoney,
						dataUnit).getchartDataset(), PlotOrientation.VERTICAL,
				true, false, false);
		setChartFormat(chart, true);

		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 30月消费情况（笔数） 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30MonthsNumChart(List consume30MonthsResult,
			HttpSession session, Document document) {
		String accType[] = { "消费笔数" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "tradenum" };
		String consume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(consume30MonthsResult,
				"tradenum", dataType);
		consume30DaysY = new GetListResultStat().getYLabelNum(
				consume30MonthsResult, "tradenum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("最近30个月消费记录(笔数)", "消费月份",
				consume30DaysY, new DrawBarByTypeMap(consume30MonthsResult,
						accType, xData, dataType, columnTitle, dataUnit)
						.getchartDataset(), PlotOrientation.VERTICAL, true,
				false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 各校区消费情况对比（30天金额） 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void areaConsume30daysMoneyChart(
			List areaConsume30daysResult, HttpSession session, Document document) {
		String accType[] = { "邯郸校区", "枫林校区", "张江校区" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitle[] = { "hdamt", "flamt", "zjamt" };
		// String columnTitleNum[] = { "hdnum", "flnum", "zjnum" };
		String areaConsume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				areaConsume30daysResult, "hdamt", dataType);
		areaConsume30DaysY = new GetListResultStat().getYLabelMoney(
				areaConsume30daysResult, "hdamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("各校区最近30天消费情况对比(金额)",
				"消费日期", areaConsume30DaysY, new DrawBarByTypeMap(
						areaConsume30daysResult, accType, xData, dataType,
						columnTitle, dataUnit).getchartDataset(),
				PlotOrientation.VERTICAL, true, false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	private static void areaConsume30daysNumChart(List areaConsume30daysResult,
			HttpSession session, Document document) {
		String accType[] = { "邯郸校区", "枫林校区", "张江校区" };
		String xData = "balance_date";
		String dataType = "integer";
		// String columnTitle[] = { "hdamt", "flamt", "zjamt" };
		String columnTitle[] = { "hdnum", "flnum", "zjnum" };
		String areaConsume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				areaConsume30daysResult, "flnum", dataType);
		areaConsume30DaysY = new GetListResultStat().getYLabelNum(
				areaConsume30daysResult, "flnum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("各校区最近30天消费情况对比(笔数)",
				"消费日期", areaConsume30DaysY, new DrawBarByTypeMap(
						areaConsume30daysResult, accType, xData, dataType,
						columnTitle, dataUnit).getchartDataset(),
				PlotOrientation.VERTICAL, true, false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 各校区POS充值情况对比（30天金额） 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void posSavingCompare30DaysMoneyChart(
			List posSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accType[] = { "邯郸校区", "枫林校区", "张江校区" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitle[] = { "hdamt", "flamt", "zjamt" };
		// String columnTitleNum[] = { "hdnum", "flnum", "zjnum" };
		String areaConsume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				posSavingCompare30DaysResult, "hdamt", dataType);
		areaConsume30DaysY = new GetListResultStat().getYLabelMoney(
				posSavingCompare30DaysResult, "hdamt", dataType);
		JFreeChart chart = ChartFactory.createBarChart("各校区最近30天POS充值情况对比(金额)",
				"充值日期", areaConsume30DaysY, new DrawBarByTypeMap(
						posSavingCompare30DaysResult, accType, xData, dataType,
						columnTitle, dataUnit).getchartDataset(),
				PlotOrientation.VERTICAL, true, false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 各校区POS充值情况对比（30天笔数） 2006-6-16 hjw 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void posSavingCompare30DaysNumChart(
			List posSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accType[] = { "邯郸校区", "枫林校区", "张江校区" };
		String xData = "balance_date";
		String dataType = "integer";
		// String columnTitle[] = { "hdamt", "flamt", "zjamt" };
		String columnTitle[] = { "hdnum", "flnum", "zjnum" };
		String areaConsume30DaysY = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				posSavingCompare30DaysResult, "flnum", dataType);
		areaConsume30DaysY = new GetListResultStat().getYLabelNum(
				posSavingCompare30DaysResult, "flnum", dataType);
		JFreeChart chart = ChartFactory.createBarChart("各校区最近30天POS充值情况对比(笔数)",
				"充值日期", areaConsume30DaysY, new DrawBarByTypeMap(
						posSavingCompare30DaysResult, accType, xData, dataType,
						columnTitle, dataUnit).getchartDataset(),
				PlotOrientation.VERTICAL, true, false, false);
		setChartFormat(chart, true);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}
	private void transferSuccessRate(List transferSuccessRateResult, RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("最近30天圈存情况报表", PDFChineseFont.createChineseFont(12,
					Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 200, 200, 200, 300, 300, 200 };

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			table.addCell("天数");
			table.addCell("星期");
			table.addCell("日期");
			table.addCell("交易笔数");
			table.addCell("入账笔数");
			table.addCell("成功率");

			//table.endHeaders();// 换行
			Iterator iter = transferSuccessRateResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();
				table.addCell(map.get("sysdate").toString());
				table.addCell(map.get("week").toString());
				table.addCell(map.get("balance_date").toString());
				table.addCell(map.get("inaccount").toString());
				table.addCell(map.get("account").toString());
				table.addCell(map.get("rate").toString());
				table.endHeaders();
			}
			document.add(table);
			table.endHeaders();
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

		/**
		 * 圈存入账笔数对比曲线图
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void transferSuccessInAccountChart(
			List transferSuccessInAccountResult, HttpSession session,
			Document document) {
		String accType[] = { "入帐笔数" };
		String xData = "balance_date";
		String dataType = "integer";
		String columnTitle[] = { "inaccount"  };
		String yLabel = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				transferSuccessInAccountResult, "inaccount", dataType);
		yLabel = new GetListResultStat().getYLabelNum(
				transferSuccessInAccountResult, "inaccount", dataType);
		JFreeChart chart = ChartFactory.createTimeSeriesChart("圈存入账笔数曲线图",
				"圈存日期", yLabel, new DrawTimeSeries(
						transferSuccessInAccountResult, columnTitle, xData,
						dataType, accType, dataUnit).getChartDataSet(), true, false, false);
		setLineChartFormat(chart);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}
		/**
		 * 圈存成功率
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void transferSuccessRateChart(
			List transferSuccessRateResult, HttpSession session,
			Document document) {
		String accType[] = { "圈存成功率" };
		String xData = "balance_date";
		String dataType = "float";
		String columnTitle[] = { "rate"  };
		String yLabel = "";
		String filename = "";
		int dataUnit = 1;
		dataUnit = new GetListResultStat().getUnitValue(
				transferSuccessRateResult, "rate", dataType);
		yLabel = new GetListResultStat().getYLabelRate(
				transferSuccessRateResult, "rate", dataType);
		JFreeChart chart = ChartFactory.createTimeSeriesChart("圈存成功率",
				"圈存日期", yLabel, new DrawTimeSeries(
						transferSuccessRateResult, columnTitle, xData,
						dataType, accType, dataUnit).getChartDataSet(), true, false, false);
		setLineChartFormat(chart);
		try {
			ChartRenderingInfo info = new ChartRenderingInfo(
					new StandardEntityCollection());
			filename = ServletUtilities.saveChartAsPNG(chart, chartwidth,
					chartheight, info, session);
		} catch (Exception e) {
			e.printStackTrace();
		}
		try {
			Image img = Image.getInstance(filePath + filename);
			document.add(new Chunk(img, 0, 0));
		} catch (IOException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}

	}

	/**
	 * 设置图表显示格式 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void setChartFormat(JFreeChart chart, boolean rotation) {
		// 图片背景色
		chart.setBackgroundPaint(new Color(247, 247, 247));

		CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();
		CategoryAxis domainAxis = plot.getDomainAxis();
		if (rotation) {
			// 文字旋转角度
			domainAxis.setCategoryLabelPositions(CategoryLabelPositions
					.createUpRotationLabelPositions(Math.PI / 6.0));
		}
		// 图形背景色
		plot.setBackgroundPaint(new Color(247, 247, 247));
		// 网格线
		plot.setDomainGridlinesVisible(true);
		plot.setDomainGridlinePaint(new Color(185, 185, 185));
		plot.setRangeGridlinesVisible(true);
		plot.setRangeGridlinePaint(new Color(185, 185, 185));
		BarRenderer renderer = (BarRenderer) plot.getRenderer();
		// 显示轮廓线
		renderer.setDrawBarOutline(true);
		renderer.setMinimumBarLength(0.05);
		renderer.setMaxBarWidth(0.02);
		// 设置直方图的绘制渐进色
		Color color[] = new Color[5];
		color[0] = new Color(99, 99, 247);
		color[1] = new Color(255, 169, 66);
		color[2] = new Color(33, 255, 66);
		color[3] = new Color(33, 0, 255);
		color[4] = new Color(255, 0, 66);
		for (int i = 0; i < color.length; i++) {
			GradientPaint gp = new GradientPaint(0, 0, color[i].brighter(), 0,
					chartheight, color[i].darker());
			renderer.setSeriesPaint(i, gp);
		}
	}
	
	private static void setLineChartFormat(JFreeChart chart) {
		// 图片背景色
		chart.setBackgroundPaint(new Color(247, 247, 247));

		//CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();
		// 图形背景色
		//plot.setBackgroundPaint(new Color(247, 247, 247));
	}
	
		/**
		 * 取得jfreechart图形存在的临时目录
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void getChartPicPath(){
		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		filePath = config.getString("jfreechart.path");
		chartwidth = config.getInt("jfreechart.width");
		chartheight = config.getInt("jfreechart.height");
	}

	/**
	 * 初始化统计日期数据 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void initDate(String createDate, String endWeekDate) {
		consume30DaysDate = DateUtilExtend.decDate(createDate, 30);

		//endWeekDate = DateUtilExtend.getPreWeekByDate(createDate);
		beginWeekDate = DateUtilExtend.decDate(endWeekDate, 210);

		beginMonthDate = DateUtilExtend.desMonth(createDate, 30);
		endMonthDate = createDate.substring(0, 6);

		tranBeginDate = "20050418";

	}
	
		/**
		 * 格式化金额，返回格式为：￥00,000,000,000,000.00
		 * 2006-6-20
		 * hjw
		 * @param
		 * @return
		 */
	private static String formatMoney(String money){
		NumberFormat formatter = new DecimalFormat("##,###,##0.00");
		return "￥"+formatter.format(new Float(money)).toString();
	}

}
