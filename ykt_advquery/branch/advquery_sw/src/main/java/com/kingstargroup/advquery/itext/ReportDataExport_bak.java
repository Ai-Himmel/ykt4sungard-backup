package com.kingstargroup.advquery.itext;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpSession;

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
import com.kingstargroup.advquery.hibernate.util.ReportShopBalanceUtil;
import com.lowagie.text.BadElementException;
import com.lowagie.text.Cell;
import com.lowagie.text.Document;
import com.lowagie.text.DocumentException;
import com.lowagie.text.Table;
import com.lowagie.text.pdf.DefaultFontMapper;
import com.lowagie.text.pdf.PdfContentByte;
import com.lowagie.text.pdf.PdfTemplate;
import com.lowagie.text.pdf.PdfWriter;

public class ReportDataExport_bak {
	private static final int chartwidth = 600;
	private static final int chartheight = 400;
	public ReportDataExport_bak(String path, String consume30DaysDate,
			String createDate,HttpSession session) {
		Document document = new Document();
		try {
			PdfWriter writer;
			writer = PdfWriter.getInstance(document, new FileOutputStream(path));
			document.open();
			
			consume30Days(consume30DaysDate, createDate,writer,document,session);
			areaCon(consume30DaysDate, createDate,writer,document);
		} catch (DocumentException de) {
			de.printStackTrace();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		document.close();

	}

	private void consume30Days(
			String consume30DaysDate, 
			String createDate,
			PdfWriter writer,
			Document document,
			HttpSession session) {
		try {
			Table table = new Table(6);
			Cell cell = new Cell(new PDFParagragh("近30天消费",
					PDFParagragh.ALIGN_CENTER, 14));
			cell.setColspan(6);
			table.addCell(cell);
			table.addCell(new PDFCell("天数", 1, 1));
			table.addCell(new PDFCell("星期", 1, 1));
			table.addCell(new PDFCell("日期", 1, 1));
			table.addCell(new PDFCell("交易金额", 1, 1));
			table.addCell(new PDFCell("交易笔数", 1, 1));
			table.addCell(new PDFCell("管理费", 1, 1));

			List consume30DaysResult = ReportShopBalanceUtil.getAllConsumeStat(
					consume30DaysDate, createDate, "bydate");
			table.endHeaders();// 换行
			Iterator iter = consume30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();

				table.addCell(map.get("sysdate").toString());
				table.addCell(new PDFCell(map.get("week").toString(), 1, 1));
				table.addCell(map.get("balance_date").toString());
				table.addCell(map.get("tradeamt").toString());
				table.addCell(map.get("tradenum").toString());
				table.addCell(map.get("mngamt").toString());
				table.endHeaders();
			}
			document.add(table);

			PdfContentByte cb = writer.getDirectContent();
			PdfTemplate tp = cb.createTemplate(chartwidth, chartheight);
			Graphics2D g2d = tp.createGraphics(chartwidth, chartheight,new DefaultFontMapper());
			Rectangle2D r2d = new Rectangle2D.Double(0, 0, chartwidth, chartheight);
			
			getconsume30DaysChart(consume30DaysResult,session).draw(g2d, r2d);
			g2d.dispose();
			cb.addTemplate(tp, 0, 0);

		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}
	
	private void areaCon(
			String consume30DaysDate, 
			String createDate,
			PdfWriter writer,
			Document document){
		try {
			Table table = new Table(9);
			int headerwidths[] = {7, 7, 12, 12, 7, 7, 7, 7, 7};
			table.setWidths(headerwidths);
			table.setWidth(100);
			table.setPadding(3);

			Cell cell = new Cell(new PDFParagragh("各校区30天消费情况",
					PDFParagragh.ALIGN_CENTER, 14));
			cell.setColspan(9);
			table.addCell(cell);
			table.addCell(new PDFCell("天数", 1, 1));
			table.addCell(new PDFCell("星期", 1, 1));
			table.addCell(new PDFCell("日期", 1, 1));
			table.addCell(new PDFCell("邯郸笔数", 1, 1));
			table.addCell(new PDFCell("邯郸金额", 1, 1));
			table.addCell(new PDFCell("枫林笔数", 1, 1));
			table.addCell(new PDFCell("枫林金额", 1, 1));
			table.addCell(new PDFCell("张江笔数", 1, 1));
			table.addCell(new PDFCell("张江金额", 1, 1));

			List areaConsume30DaysResult = ReportShopBalanceUtil.getAreaSalesCompare(
					consume30DaysDate, createDate, "bydate");
			table.endHeaders();// 换行
			Iterator iter = areaConsume30DaysResult.iterator();
			while (iter.hasNext()) {
				HashMap map = (HashMap) iter.next();

				table.addCell(map.get("sysdate").toString());
				table.addCell(new PDFCell(map.get("week").toString(), 1, 1));
				table.addCell(map.get("balance_date").toString());
				table.addCell(map.get("hdnum").toString());
				table.addCell(map.get("hdamt").toString());
				table.addCell(map.get("flnum").toString());
				table.addCell(map.get("flamt").toString());
				table.addCell(map.get("zjnum").toString());
				table.addCell(map.get("zjamt").toString());
				table.endHeaders();
			}
			document.add(table);

		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
		
	}
	private static JFreeChart getconsume30DaysChart(List consume30DaysResult,HttpSession session){
		String accTypeMoney[] = { "消费金额" };
		String accTypeNum[] = { "消费笔数" };
		String xData = "balance_date";
		String dataTypeMoney = "float";
		String dataTypeNum = "integer";
		String columnTitleMoney[] = { "tradeamt" };
		String columnTitleNum[] = { "tradenum" };
		String consume30DaysYMoney = "";
		String consume30DaysYNum = "";
		int dataUnitMoney = 1;
		int dataUnitNum = 1;

		JFreeChart chart = ChartFactory.createBarChart(
				"中文", 
				"X-axis", "Y-axis", new DrawBarByTypeMap(consume30DaysResult, accTypeMoney,
						xData, dataTypeMoney, columnTitleMoney,
						dataUnitMoney).getchartDataset(),
				PlotOrientation.VERTICAL, true, true, false);

		
		CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();
		CategoryAxis domainAxis = plot.getDomainAxis();
		domainAxis.setCategoryLabelPositions(CategoryLabelPositions
				.createUpRotationLabelPositions(Math.PI / 6.0));
		plot.setBackgroundPaint(new Color(247, 247, 247));
		plot.setDomainGridlinesVisible(true);
		plot.setDomainGridlinePaint(new Color(185,185,185));
		plot.setRangeGridlinesVisible(true);
		plot.setRangeGridlinePaint(new Color(185,185,185));
		BarRenderer renderer = (BarRenderer) plot.getRenderer();
		renderer.setDrawBarOutline(true);
		renderer.setMinimumBarLength(0.05);
		renderer.setMaxBarWidth(0.01);
		ChartRenderingInfo info = 
			   new ChartRenderingInfo(new StandardEntityCollection());
		try {
			String filename = ServletUtilities.saveChartAsPNG(chart, chartwidth, chartheight, info, session);
			System.out.println("________+++++++++"+filename);
		} catch (Exception e) {
		}
		return chart;
	}

}
