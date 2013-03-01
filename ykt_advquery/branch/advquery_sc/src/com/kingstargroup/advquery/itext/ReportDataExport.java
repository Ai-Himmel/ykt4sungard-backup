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

	// �������������ʼͳ������
	private String consume30DaysDate = "";

	// ��ǰ���ڵ�ǰ30����һ������
	private String beginWeekDate = "";

	// ��ǰ���������·�
	private String beginMonthDate = "";

	// ��ǰ���ڵ�ǰ30�������·�
	private String endMonthDate = "";

	// Ȧ�濪ʼ����
	private String tranBeginDate = "";

	public ReportDataExport(String path, String endWeekDate, String createDate,
			HttpSession session) {
		initDate(createDate, endWeekDate);
		getChartPicPath();
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 30���������
		List consume30DaysResult = ReportShopBalanceUtil.getAllConsumeStat(
				consume30DaysDate, createDate, "bydate");
		// ����ǰ30��ͳ������,�����ǰ���ڲ������գ����㵱ǰ��
		List consume30DaysResult1 = ReportShopBalanceUtil.getAllConsumeStat(
				beginWeekDate, endWeekDate, "byweek");
		List consume30WeeksResult = new GetListResultStat().getListByWeek(
				consume30DaysResult1, beginWeekDate, endWeekDate);
		Collections.sort(consume30WeeksResult, new SortListByResult(
				"balance_date"));
		// 30�����������ݼ�
		List consume30MonthsResult = ReportShopBalanceUtil.getAllConsumeStat(
				beginMonthDate, endMonthDate, "bymonth");
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ��У��30����������Ա�
		//List areaConsume30DaysResult = ReportShopBalanceUtil.getAreaSalesCompare(consume30DaysDate, createDate, "bydate");
		// POS��Ȧ��ת������Ա�
		List saving30DaysResult = ReportActiveUtil.getTotleSavingStat(
				consume30DaysDate, createDate, "bydate");
		// ���ѱ���֧Ʊ��ֵ����Ա�
		List billSaving30DaysResult = ReportActiveUtil.getBillTotleSavingStat(
				consume30DaysDate, createDate, "bydate");
		// ��У��POS��ֵ����Ա�
		//List posSaving30DaysResult = ReportOperUtil.posSavingCompareStat(consume30DaysDate, createDate, "bydate");
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Pos��Ȧ��ת��30������Ա�
		List savingCompare30DaysResult = ReportActiveUtil.getTotleSavingStat(
				beginWeekDate, endWeekDate, "byweek");

		List savingCompare30WeeksResult = new GetListResultStat()
				.getListByWeek(savingCompare30DaysResult, beginWeekDate,
						endWeekDate);
		Collections.sort(savingCompare30WeeksResult, new SortListByResult(
				"balance_date"));
		// ���ѱ���֧Ʊ30������Ա�
		List billSavingCompare30DaysResult = ReportActiveUtil
				.getBillTotleSavingStat(beginWeekDate, endWeekDate, "byweek");

		List billSavingCompare30WeeksResult = new GetListResultStat()
				.getListByWeek(billSavingCompare30DaysResult, beginWeekDate,
						endWeekDate);
		Collections.sort(billSavingCompare30WeeksResult, new SortListByResult(
				"balance_date"));
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Pos��Ȧ��ת��30������Ա�
		List savingCompare30MonthsResult = ReportActiveUtil
		.getTotleSavingStat(beginMonthDate, endMonthDate, "bymonth");
		// ���ѱ���֧Ʊ30������Ա�
		List billSavingCompare30MonthsResult = ReportActiveUtil
		.getBillTotleSavingStat(beginMonthDate, endMonthDate,
				"bymonth");
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Ȧ��ɹ���
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
			// 30���������ͼ�Σ���
			getconsume30DaysMoneyChart(consume30DaysResult, session, document);
			// 30���������ͼ�Σ�������
			getconsume30DaysNumChart(consume30DaysResult, session, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// ��У��30����������Աȣ������ͽ�
			//areaConsume30daysMoneyChart(areaConsume30DaysResult, session,document);
			//areaConsume30daysNumChart(areaConsume30DaysResult, session,document);
			// 30��������������ͱ�����
			getconsume30WeeksMoneyChart(consume30WeeksResult, session, document);
			getconsume30WeeksNumChart(consume30WeeksResult, session, document);
			// 30��������������ͱ�����
			getconsume30MonthsMoneyChart(consume30MonthsResult, session,
					document);
			getconsume30MonthsNumChart(consume30MonthsResult, session, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// 30�������������
			consume30Days(consume30DaysResult, writer, document, session);
			// ��У��30����������Աȱ���
			//areaConsume30days(areaConsume30DaysResult, writer, document);
			// 30�������������
			Consume30Weeks(consume30WeeksResult, writer, document);
			// 30�������������
			Consume30Months(consume30MonthsResult, writer, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// POS��Ȧ����30������Ա�(���ͱ���)
			savingCompare30DaysMoneyChart(saving30DaysResult, session, document);
			savingCompare30DaysNumChart(saving30DaysResult, session, document);
			// ���ѱ���֧Ʊ���30������Աȣ����ͱ�����
			billSavingCompare30DaysMoneyChart(billSaving30DaysResult, session,
					document);
			billSavingCompare30DaysNumChart(billSaving30DaysResult, session,
					document);
			// ��У��POS��ֵ����Աȣ����ͱ�����
			//posSavingCompare30DaysMoneyChart(posSaving30DaysResult, session,document);
			//posSavingCompare30DaysNumChart(posSaving30DaysResult, session,document);
			// pos��Ȧ����30������Աȣ����ͱ�����
			savingCompare30WeeksMoneyChart(savingCompare30WeeksResult, session,
					document);
			savingCompare30WeeksNumChart(savingCompare30WeeksResult, session,
					document);
			// Ʊ�ݳ�ֵ30������Աȣ����ͱ�����
			billSavingCompare30WeeksMoneyChart(billSavingCompare30WeeksResult, session,
					document);
			billSavingCompare30WeeksNumChart(billSavingCompare30WeeksResult, session,
					document);
			// pos��Ȧ����30������Աȣ����ͱ�����
			savingCompare30MonthsMoneyChart(savingCompare30MonthsResult, session,
					document);
			savingCompare30MonthsNumChart(savingCompare30MonthsResult, session,
					document);
			// Ʊ�ݳ�ֵ30������Աȣ����ͱ�����
			billSavingCompare30MonthsMoneyChart(billSavingCompare30MonthsResult, session,
					document);
			billSavingCompare30MonthsNumChart(billSavingCompare30MonthsResult, session,
					document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// POS��Ȧ����30������Աȱ���
			savingCompare30Days(saving30DaysResult, writer, document);
			// ���ѱ���֧Ʊ���30������Աȱ���
			billSavingCompare30Days(billSaving30DaysResult, writer, document);
			// ��У��30��POS��ֵ����Աȱ���
			//posSavingCompare30Days(posSaving30DaysResult, writer, document);
			// pos��Ȧ����30������Աȱ���
			savingCompare30Weeks(savingCompare30WeeksResult, writer, document);
			// Ʊ�ݳ�ֵ30���������
			billSavingCompare30Weeks(billSavingCompare30WeeksResult, writer, document);
			// pos��Ȧ����30�±���
			savingCompare30Months(savingCompare30MonthsResult, writer, document);
			// Ʊ�ݳ�ֵ30���±���
			billSavingCompare30Months(billSavingCompare30MonthsResult, writer, document);
			// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// Ȧ��ɹ���
			transferSuccessInAccountChart(transferSuccResult, session,
					document);
			transferSuccessRateChart(transferSuccResult, session,
					document);
			// Ȧ���������
			transferSuccessRate(transferSuccResult, writer, document);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} finally {
			document.close();
			session.removeAttribute("JFreeChart_Deleter");
		}

	}

	/**
	 * 30������������� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void consume30Days(List consume30DaysResult, RtfWriter2 writer,
			Document document, HttpSession session) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("���30�����Ѽ�¼", PDFChineseFont.createChineseFont(12,
					Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			
			document.add(para);
			int widths[] = { 200, 200, 200, 300, 200, 300 };

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("����"); 
			Cell week = new Cell("����"); 
			Cell balance_date = new Cell("����"); 
			Cell tradeamt = new Cell("���׽��"); 
			Cell tradenum = new Cell("���ױ���"); 
			Cell mngamt = new Cell("�����"); 
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

			//table.endHeaders();// ����
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
	 * ��У����������Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void areaConsume30days(List areaConsume30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("��У�����30���������", PDFChineseFont.createChineseFont(
					12, Font.NORMAL)));

			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 150, 300, 300, 300, 300, 300, 300, 300 };

			Table table = new Table(9);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("����"); 
			Cell week = new Cell("����"); 
			Cell balance_date = new Cell("����"); 
			Cell hdnum = new Cell("��������"); 
			Cell hdamt = new Cell("�������"); 
			Cell flnum = new Cell("���ֱ���"); 
			Cell flamt = new Cell("���ֽ��"); 
			Cell zjnum = new Cell("�Ž�����"); 
			Cell zjamt = new Cell("�Ž����"); 
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

			//table.endHeaders();// ����
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
	 * �������30��ͳ�Ʊ��� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void Consume30Weeks(List consume30WeeksResult, RtfWriter2 writer,
			Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("���30�������Ѽ�¼", PDFChineseFont.createChineseFont(
					12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 400, 300, 300, 200 };

			Table table = new Table(5);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysusedweek = new Cell("��N��"); 
			Cell balance_date = new Cell("���ڷ�Χ"); 
			Cell tradeamt = new Cell("���׽��"); 
			Cell tradenum = new Cell("���ױ���"); 
			Cell mngamt = new Cell("�����"); 
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

			//table.endHeaders();// ����
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
			para.add(new Chunk("���30�������Ѽ�¼", PDFChineseFont.createChineseFont(
					12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 200, 400, 300, 300 };

			Table table = new Table(4);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell balance_date = new Cell("�·�"); 
			Cell tradeamt = new Cell("���׽��"); 
			Cell tradenum = new Cell("���ױ���"); 
			Cell mngamt = new Cell("�����"); 
			balance_date.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradeamt.setHorizontalAlignment(Element.ALIGN_CENTER);
			tradenum.setHorizontalAlignment(Element.ALIGN_CENTER);
			mngamt.setHorizontalAlignment(Element.ALIGN_CENTER);

			table.addCell(balance_date);
			table.addCell(tradeamt);
			table.addCell(tradenum);
			table.addCell(mngamt);

			//table.endHeaders();// ����
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
	 * POS��Ȧ��ת��30������Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void savingCompare30Days(List saving30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("POS��Ȧ�����30�������", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 150, 250, 200, 300, 200, 300 ,300};

			Table table = new Table(8);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("����"); 
			Cell week = new Cell("����"); 
			Cell balance_date = new Cell("����"); 
			Cell posnum = new Cell("POS����"); 
			Cell posamt = new Cell("POS���"); 
			Cell transfernum = new Cell("Ȧ�����"); 
			Cell transferamt = new Cell("Ȧ����"); 
			Cell cashamt = new Cell("�ֽ��ֵ");
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

			//table.endHeaders();// ����
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
	 * POS��Ȧ��30�ܳ�ֵ���� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void savingCompare30Weeks(List savingCompare30WeeksResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("POS��Ȧ�����30���ܴ�����", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 400, 200, 200, 200, 200 ,200};

			Table table = new Table(7);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysusedweek = new Cell("��N��"); 
			Cell balance_date = new Cell("���ڷ�Χ"); 
			Cell posnum = new Cell("POS����"); 
			Cell posamt = new Cell("POS���"); 
			Cell transfernum = new Cell("Ȧ�����"); 
			Cell transferamt = new Cell("Ȧ����"); 
			Cell cashamt = new Cell("�ֽ��ֵ"); 
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

			//table.endHeaders();// ����
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
			para.add(new Chunk("POS��Ȧ�����30���´�����", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 250, 200, 300, 200, 300 ,300};

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell balance_date = new Cell("�·�"); 
			Cell posnum = new Cell("POS����"); 
			Cell posamt = new Cell("POS���"); 
			Cell transfernum = new Cell("Ȧ�����"); 
			Cell transferamt = new Cell("Ȧ����"); 
			Cell cashamt = new Cell("�ֽ��ֵ"); 
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

			//table.endHeaders();// ����
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
	 * ���ѱ���֧Ʊ30�ܳ�ֵ������� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void billSavingCompare30Weeks(List billSavingCompare30WeeksResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("���ѱ���֧Ʊ���30���ܴ�����", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 400, 200, 200, 200, 200 };

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysusedweek = new Cell("��N��"); 
			Cell balance_date = new Cell("���ڷ�Χ"); 
			Cell outlaynum = new Cell("���ѱ�����"); 
			Cell outlaymoney = new Cell("���ѱ����"); 
			Cell ticketnum = new Cell("֧Ʊ����"); 
			Cell ticketmoney = new Cell("֧Ʊ���"); 
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

			//table.endHeaders();// ����
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
	 * ���ѱ���֧Ʊ30���ֵ����Աȱ��� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void billSavingCompare30Days(List billSaving30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("���ѱ���֧Ʊ���30�������", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 100, 100, 200, 250, 250, 200, 200 };

			Table table = new Table(7);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("����"); 
			Cell week = new Cell("����"); 
			Cell balance_date = new Cell("����"); 
			Cell outlaynum = new Cell("���ѱ�����"); 
			Cell outlaymoney = new Cell("���ѱ����"); 
			Cell ticketnum = new Cell("֧Ʊ����"); 
			Cell ticketmoney = new Cell("֧Ʊ���"); 
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

			//table.endHeaders();// ����
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
			para.add(new Chunk("���ѱ���֧Ʊ���30���´�����", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 200, 250, 250, 200, 200 };

			Table table = new Table(5);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell balance_date = new Cell("�·�"); 
			Cell outlaynum = new Cell("���ѱ�����"); 
			Cell outlaymoney = new Cell("���ѱ����"); 
			Cell ticketnum = new Cell("֧Ʊ����"); 
			Cell ticketmoney = new Cell("֧Ʊ���"); 
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

			//table.endHeaders();// ����
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
	 * ��У��POS��ֵ30������Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private void posSavingCompare30Days(List posSavingCompare30DaysResult,
			RtfWriter2 writer, Document document) {
		try {
			Paragraph para = new Paragraph();
			para.add(new Chunk("��У�����30��POS��ֵ�������", PDFChineseFont
					.createChineseFont(12, Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 150, 150, 300, 300, 300, 300, 300, 300, 300 };

			Table table = new Table(9);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			Cell sysdate = new Cell("����"); 
			Cell week = new Cell("����"); 
			Cell balance_date = new Cell("����"); 
			Cell hdnum = new Cell("��������"); 
			Cell hdamt = new Cell("�������"); 
			Cell flnum = new Cell("���ֱ���"); 
			Cell flamt = new Cell("���ֽ��"); 
			Cell zjnum = new Cell("�Ž�����"); 
			Cell zjamt = new Cell("�Ž����"); 
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

			//table.endHeaders();// ����
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
	 * ����30�����Ѽ�¼ͼ�� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30DaysMoneyChart(List consume30DaysResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "���ѽ��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�����Ѽ�¼(���)", "��������",
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
	 * 30����������������� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30DaysNumChart(List consume30DaysResult,
			HttpSession session, Document document) {
		String accType[] = { "���ѱ���" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�����Ѽ�¼(����)", "��������",
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
	 * "POS��ֵ", "Ȧ��ת��"30���ֵ���Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30DaysMoneyChart(
			List billSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accTypeMoney[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�쾭�ѱ���֧Ʊ���Ա�(���)",
				"�������", Y, new DrawBarByTypeMap(billSavingCompare30DaysResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30���ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30DaysNumChart(
			List billSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accType[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�쾭�ѱ���֧Ʊ���Ա�(����)",
				"�������", Y, new DrawBarByTypeMap(billSavingCompare30DaysResult,
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
		 * ���ѱ���֧Ʊ��ֵ30���ܣ���
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void billSavingCompare30WeeksMoneyChart(
			List billSavingCompare30WeeksResult, HttpSession session,
			Document document) {
		String accTypeMoney[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30���ܾ��ѱ���֧Ʊ���Ա�(���)",
				"��N��", Y, new DrawBarByTypeMap(billSavingCompare30WeeksResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30���ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30WeeksNumChart(
			List billSavingCompare30WeeksResult, HttpSession session,
			Document document) {
		String accType[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30���ܾ��ѱ���֧Ʊ���Ա�(����)",
				"��N��", Y, new DrawBarByTypeMap(billSavingCompare30WeeksResult,
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
		 * ���ѱ���֧Ʊ��ֵ30���£���
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void billSavingCompare30MonthsMoneyChart(
			List billSavingCompare30MonthsResult, HttpSession session,
			Document document) {
		String accTypeMoney[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30���¾��ѱ���֧Ʊ���Ա�(���)",
				"����·�", Y, new DrawBarByTypeMap(billSavingCompare30MonthsResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30�³�ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void billSavingCompare30MonthsNumChart(
			List billSavingCompare30MonthsResult, HttpSession session,
			Document document) {
		String accType[] = { "���ѱ���ֵ", "֧Ʊ��ֵ" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�쾭�ѱ���֧Ʊ���Ա�(����)",
				"����·�", Y, new DrawBarByTypeMap(billSavingCompare30MonthsResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30���ֵ���Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30DaysMoneyChart(List saving30DaysResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "POS��ֵ", "Ȧ��ת��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30��POS��Ȧ����Ա�(���)",
				"�������", Y, new DrawBarByTypeMap(saving30DaysResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30���ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30DaysNumChart(List saving30DaysResult,
			HttpSession session, Document document) {
		String accType[] = { "POS��ֵ", "Ȧ��ת��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30��POS��Ȧ����Ա�(����)",
				"�������", Y, new DrawBarByTypeMap(saving30DaysResult, accType,
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
	 * "POS��ֵ", "Ȧ��ת��"30���ܳ�ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30WeeksMoneyChart(
			List saving30WeeksResult, HttpSession session, Document document) {
		String accTypeMoney[] = { "POS��ֵ", "Ȧ��ת��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30����POS��Ȧ����Ա�(���)",
				"��N��", Y, new DrawBarByTypeMap(saving30WeeksResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30�ܳ�ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30WeeksNumChart(List saving30WeeksResult,
			HttpSession session, Document document) {
		String accType[] = { "POS��ֵ", "Ȧ��ת��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30����POS��Ȧ����Ա�(����)",
				"��N��", Y, new DrawBarByTypeMap(saving30WeeksResult, accType,
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
		 * pos��ֵ��Ȧ��ת��30���¶Աȣ���
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void savingCompare30MonthsMoneyChart(List saving30MonthsResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "POS��ֵ", "Ȧ��ת��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30����POS��Ȧ����Ա�(���)",
				"����·�", Y, new DrawBarByTypeMap(saving30MonthsResult,
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
	 * "POS��ֵ", "Ȧ��ת��"30�³�ֵ����Ա� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void savingCompare30MonthsNumChart(List saving30MonthsResult,
			HttpSession session, Document document) {
		String accType[] = { "POS��ֵ", "Ȧ��ת��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30����POS��Ȧ����Ա�(����)",
				"����·�", Y, new DrawBarByTypeMap(saving30MonthsResult, accType,
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
	 * ����30�����Ѽ�¼ͼ�� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30WeeksMoneyChart(List consume30WeeksResult,
			HttpSession session, Document document) {
		String accTypeMoney[] = { "���ѽ��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�������Ѽ�¼(���)", "��N������",
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
	 * ��N��������� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30WeeksNumChart(List consume30WeeksResult,
			HttpSession session, Document document) {
		String accType[] = { "���ѱ���" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�������Ѽ�¼(����)", "��N������",
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
	 * ����30�����Ѽ�¼ͼ�� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30MonthsMoneyChart(
			List consume30MonthsResult, HttpSession session, Document document) {
		String accTypeMoney[] = { "���ѽ��" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�������Ѽ�¼(���)", "�����·�",
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
	 * 30����������������� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void getconsume30MonthsNumChart(List consume30MonthsResult,
			HttpSession session, Document document) {
		String accType[] = { "���ѱ���" };
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
		JFreeChart chart = ChartFactory.createBarChart("���30�������Ѽ�¼(����)", "�����·�",
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
	 * ��У����������Աȣ�30��� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void areaConsume30daysMoneyChart(
			List areaConsume30daysResult, HttpSession session, Document document) {
		String accType[] = { "����У��", "����У��", "�Ž�У��" };
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
		JFreeChart chart = ChartFactory.createBarChart("��У�����30����������Ա�(���)",
				"��������", areaConsume30DaysY, new DrawBarByTypeMap(
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
		String accType[] = { "����У��", "����У��", "�Ž�У��" };
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
		JFreeChart chart = ChartFactory.createBarChart("��У�����30����������Ա�(����)",
				"��������", areaConsume30DaysY, new DrawBarByTypeMap(
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
	 * ��У��POS��ֵ����Աȣ�30��� 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void posSavingCompare30DaysMoneyChart(
			List posSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accType[] = { "����У��", "����У��", "�Ž�У��" };
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
		JFreeChart chart = ChartFactory.createBarChart("��У�����30��POS��ֵ����Ա�(���)",
				"��ֵ����", areaConsume30DaysY, new DrawBarByTypeMap(
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
	 * ��У��POS��ֵ����Աȣ�30������� 2006-6-16 hjw 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void posSavingCompare30DaysNumChart(
			List posSavingCompare30DaysResult, HttpSession session,
			Document document) {
		String accType[] = { "����У��", "����У��", "�Ž�У��" };
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
		JFreeChart chart = ChartFactory.createBarChart("��У�����30��POS��ֵ����Ա�(����)",
				"��ֵ����", areaConsume30DaysY, new DrawBarByTypeMap(
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
			para.add(new Chunk("���30��Ȧ���������", PDFChineseFont.createChineseFont(12,
					Font.NORMAL)));
			para.setAlignment(Element.ALIGN_CENTER);
			document.add(para);
			int widths[] = { 200, 200, 200, 300, 300, 200 };

			Table table = new Table(6);
			table.setAlignment(Element.ALIGN_CENTER);
			table.setWidths(widths);
			table.addCell("����");
			table.addCell("����");
			table.addCell("����");
			table.addCell("���ױ���");
			table.addCell("���˱���");
			table.addCell("�ɹ���");

			//table.endHeaders();// ����
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
		 * Ȧ�����˱����Ա�����ͼ
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void transferSuccessInAccountChart(
			List transferSuccessInAccountResult, HttpSession session,
			Document document) {
		String accType[] = { "���ʱ���" };
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
		JFreeChart chart = ChartFactory.createTimeSeriesChart("Ȧ�����˱�������ͼ",
				"Ȧ������", yLabel, new DrawTimeSeries(
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
		 * Ȧ��ɹ���
		 * 2006-6-19
		 * hjw
		 * @param
		 * @return
		 */
	private static void transferSuccessRateChart(
			List transferSuccessRateResult, HttpSession session,
			Document document) {
		String accType[] = { "Ȧ��ɹ���" };
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
		JFreeChart chart = ChartFactory.createTimeSeriesChart("Ȧ��ɹ���",
				"Ȧ������", yLabel, new DrawTimeSeries(
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
	 * ����ͼ����ʾ��ʽ 2006-6-16 hjw
	 * 
	 * @param
	 * @return
	 */
	private static void setChartFormat(JFreeChart chart, boolean rotation) {
		// ͼƬ����ɫ
		chart.setBackgroundPaint(new Color(247, 247, 247));

		CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();
		CategoryAxis domainAxis = plot.getDomainAxis();
		if (rotation) {
			// ������ת�Ƕ�
			domainAxis.setCategoryLabelPositions(CategoryLabelPositions
					.createUpRotationLabelPositions(Math.PI / 6.0));
		}
		// ͼ�α���ɫ
		plot.setBackgroundPaint(new Color(247, 247, 247));
		// ������
		plot.setDomainGridlinesVisible(true);
		plot.setDomainGridlinePaint(new Color(185, 185, 185));
		plot.setRangeGridlinesVisible(true);
		plot.setRangeGridlinePaint(new Color(185, 185, 185));
		BarRenderer renderer = (BarRenderer) plot.getRenderer();
		// ��ʾ������
		renderer.setDrawBarOutline(true);
		renderer.setMinimumBarLength(0.05);
		renderer.setMaxBarWidth(0.02);
		// ����ֱ��ͼ�Ļ��ƽ���ɫ
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
		// ͼƬ����ɫ
		chart.setBackgroundPaint(new Color(247, 247, 247));

		//CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();
		// ͼ�α���ɫ
		//plot.setBackgroundPaint(new Color(247, 247, 247));
	}
	
		/**
		 * ȡ��jfreechartͼ�δ��ڵ���ʱĿ¼
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
	 * ��ʼ��ͳ���������� 2006-6-16 hjw
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
		 * ��ʽ�������ظ�ʽΪ����00,000,000,000,000.00
		 * 2006-6-20
		 * hjw
		 * @param
		 * @return
		 */
	private static String formatMoney(String money){
		NumberFormat formatter = new DecimalFormat("##,###,##0.00");
		return "��"+formatter.format(new Float(money)).toString();
	}

}
