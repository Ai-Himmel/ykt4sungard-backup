package com.sungard.ticketsys.page.report;

import java.awt.Cursor;
import java.awt.Font;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.page.CalendarDlg;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.page.ticket.TickePanel;
import com.sungard.ticketsys.service.BusManager;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.service.RunbusManager;
import com.sungard.ticketsys.common.Page;

public class BusReportPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(TickePanel.class);

	private IndexFrame indexFrame = null;

	private JPanel serSet_search = null;

	private JLabel lb_line = null;
	private JLabel lb_serilNo = null;
	private JLabel lb_startDate = null;
	private JLabel lb_endDate = null;
	private JLabel lb_bus = null;

	private JComboBox cb_serilNo = null;
	private JComboBox  cb_line = null;

	private JTextField tf_startDate = null;
	private JButton bt_startDate = null;
	private CalendarDlg startcalendarDlg = new CalendarDlg(indexFrame);
	private JTextField tf_endDate = null;
	private JButton bt_endDate = null;
	private CalendarDlg endcalendarDlg = new CalendarDlg(indexFrame);
	
	private JComboBox cb_bus = null;
	private JButton bt_search = null;
	private JButton bt_reset = null;

	public JTable serSet = null;

	// 查询结果
	private JPanel serSet_result = null;
	private JScrollPane serSet_list = null;
	private JPanel serSet_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// 列表相关
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][7];
	private Object columnName[] = {"车次号","班次号","发车时间", "售票数","票价","路线名称","运输车辆"};

	// 分页相关
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;

	public BusserDay searchSerSet = new BusserDay();
	public String startDate = null;
	public String endDate = null;
	public String lineName = null;
	
	private List<BusserDay> serSets = new ArrayList<BusserDay>();

	private boolean isSearch = false;

	private int deleteCount = 0;

	protected BusReportPanel() {
	}

	public BusReportPanel(IndexFrame indexFrame) {
		this.indexFrame = indexFrame;
		initComponents();
	}

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initComponents() {
		this.setSize(890, 630);
		this.setLayout(null);
		// 查询panel
		this.add(getSerSet_search(), null);
		// 查询列表panel
		this.add(getSerSet_result(), null);
	}


	/**
	 * 查询panel
	 * 
	 * @return
	 */
	public JPanel getSerSet_search() {
		if (serSet_search == null) {
			lb_serilNo = new JLabel();
			lb_serilNo.setBounds(new Rectangle(50, 30, 80, 30));
			lb_serilNo.setText("班次：");
			
			lb_line = new JLabel();
			lb_line.setBounds(new Rectangle(420, 30, 80, 30));
			lb_line.setText("路线：");

			lb_startDate = new JLabel();
			lb_startDate.setBounds(new Rectangle(50, 80, 80, 30));
			lb_startDate.setText("起始日期：");
			
			lb_endDate = new JLabel();
			lb_endDate.setBounds(new Rectangle(420, 80, 80, 30));
			lb_endDate.setText("结束日期：");
			
			lb_bus = new JLabel();
			lb_bus.setBounds(new Rectangle(50, 130, 80, 30));
			lb_bus.setText("运输车辆：");
			
			serSet_search = new JPanel();
			serSet_search.setLayout(null);
			serSet_search.setBounds(new Rectangle(10, 10, 780, 180));
			serSet_search.setBorder(BorderFactory.createTitledBorder("班车统计条件"));
			serSet_search.add(lb_serilNo, null);
			serSet_search.add(getCb_serilNo(), null);
			serSet_search.add(lb_line, null);
			serSet_search.add(getCb_line(), null);

			serSet_search.add(lb_startDate, null);
			serSet_search.add(getTf_startDate(), null);
			serSet_search.add(getBt_startDate(), null);
			serSet_search.add(lb_endDate, null);
			serSet_search.add(getTf_endDate(), null);
			serSet_search.add(getBt_endDate(), null);
			
			serSet_search.add(lb_bus, null);
			serSet_search.add(getCb_bus(), null);
			serSet_search.add(getBt_search(), null);
			serSet_search.add(getBt_reset(), null);

		}
		return serSet_search;
	}
	
	/**
	 * 运输车辆
	 * 
	 * @return
	 */
	private JComboBox getCb_bus() {
		if (cb_bus == null) {
			cb_bus = new JComboBox();
			cb_bus.setBounds(new Rectangle(130, 130, 220, 30));
			cb_bus.addItem("-------- 请选择 --------");
	        List<Bus> busList = BusManager.getInstance().getAllBus();
	        for (int i = 0; i < busList.size(); i++) {
	        	Bus myBus = (Bus) busList.get(i);
	        	cb_bus.addItem(myBus.getBusNo());
	        }
			cb_bus.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_bus.removeAllItems();
					cb_bus.addItem("-------- 请选择 --------");
			        List<Bus> busList = BusManager.getInstance().getAllBus();
			        for (int i = 0; i < busList.size(); i++) {
			        	Bus myBus = (Bus) busList.get(i);
			        	cb_bus.addItem(myBus.getBusNo());
			        }
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_bus;
	}
	
	private JButton getBt_endDate() {
		if (bt_endDate == null) {
			bt_endDate = new JButton();
			bt_endDate.setBounds(new Rectangle(720, 84, 20, 20));
			bt_endDate.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_endDate.setCursor(Cursor
					.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_endDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (endcalendarDlg == null) {
						endcalendarDlg = new CalendarDlg(indexFrame);
					}
					Point p =  bt_endDate.getLocationOnScreen(); 
					p.y = p.y + bt_endDate.getHeight(); 
					endcalendarDlg.setLocation(p);
					endcalendarDlg.show();
					if(endcalendarDlg.getValue()!=null){
						SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
						String date = sdf.format(endcalendarDlg.getValue());
						getTf_endDate().setText(date);
					}
				}
			});
		}

		return bt_endDate;
	}
	
	private JTextField getTf_endDate() {
		if (tf_endDate == null) {
			tf_endDate = new JTextField();
			tf_endDate.setBounds(new Rectangle(500, 80, 220, 30));
		}
		return tf_endDate;
	}
	
	/**
	 * This method initializes cb_category
	 *
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getCb_line() {
		if (cb_line == null) {
			cb_line = new JComboBox();
			cb_line.setBounds(new Rectangle(500, 30, 220, 30));
			cb_line.addItem("-------- 请选择 --------");
	        List<Line> lines = LineManager.getInstance().getAllLine();
	        for (int i = 0; i < lines.size(); i++) {
	        	Line myLine = (Line) lines.get(i);
	        	cb_line.addItem(myLine.getLineName());
	        }
			cb_line.addPopupMenuListener(new PopupMenuListener(){
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_line.removeAllItems();
					cb_line.addItem("-------- 请选择 --------");
			        List<Line> lines = LineManager.getInstance().getAllLine();
			        for (int i = 0; i < lines.size(); i++) {
			        	Line myLine = (Line) lines.get(i);
			        	cb_line.addItem(myLine.getLineName());
			        }
				}
				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}
				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_line;
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(630, 130, 70, 30));
			bt_reset.setText("重置");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getCb_serilNo().setSelectedIndex(0);
					getCb_line().setSelectedIndex(0);
					getTf_startDate().setText("");
					getTf_endDate().setText("");
					getCb_bus().setSelectedIndex(0);
					startcalendarDlg.setValue(null);
					endcalendarDlg.setValue(null);
					
					getSerSet();
					getSerSet_result().setVisible(false);
					getSerSet_result().setVisible(true);
				}
			});
		}
		return bt_reset;
	}

	private JButton getBt_startDate() {
		if (bt_startDate == null) {
			bt_startDate = new JButton();
			bt_startDate.setBounds(new Rectangle(350, 84, 20, 20));
			bt_startDate
					.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_startDate.setCursor(Cursor
					.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_startDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (startcalendarDlg == null) {
						startcalendarDlg = new CalendarDlg(indexFrame);
					}
					Point p =  bt_startDate.getLocationOnScreen(); 
					p.y = p.y + bt_startDate.getHeight(); 
					startcalendarDlg.setLocation(p);
					startcalendarDlg.show();
					if(startcalendarDlg.getValue()!=null){
						SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
						String date = sdf.format(startcalendarDlg.getValue());
						getTf_startDate().setText(date);
					}
					
				}
			});
		}

		return bt_startDate;
	}

	private JTextField getTf_startDate() {
		if (tf_startDate == null) {
			tf_startDate = new JTextField();
			tf_startDate.setBounds(new Rectangle(130, 80, 220, 30));
		}
		return tf_startDate;
	}


	/**
	 * This method initializes cb_linename
	 * 
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getCb_serilNo() {
		if (cb_serilNo == null) {
			cb_serilNo = new JComboBox();
			cb_serilNo.setBounds(new Rectangle(130, 30, 220, 30));
			cb_serilNo.addItem("-------- 请选择 --------");
			List<BusSer> busSers = BusSerManager.getInstance()
					.getAllBusSer();
			for (int i = 0; i < busSers.size(); i++) {
				BusSer myBusSer = (BusSer) busSers.get(i);
				cb_serilNo.addItem(myBusSer.getSerilNo());
			}
			cb_serilNo.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_serilNo.removeAllItems();
					cb_serilNo.addItem("-------- 请选择 --------");
					List<BusSer> busSers = BusSerManager.getInstance()
							.getAllBusSer();
					for (int i = 0; i < busSers.size(); i++) {
						BusSer myBusSer = (BusSer) busSers.get(i);
						cb_serilNo.addItem(myBusSer.getSerilNo());
					}
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_serilNo;
	}

	/**
	 * This method initializes bt_search
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_search() {
		if (bt_search == null) {
			bt_search = new JButton();
			bt_search.setBounds(new Rectangle(520, 130, 70, 30));
			bt_search.setText("查 询");
			bt_search.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_search.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					pageNo = 1;
					isSearch = true;
					
					getSerSet();
					getSerSet_result().setVisible(false);
					getSerSet_result().setVisible(true);
				}
			});
		}

		return bt_search;
	}

	/**
	 * 查询列表panel
	 * 
	 * @return javax.swing.JPanel
	 */
	public JPanel getSerSet_result() {
		if (serSet_result == null) {
			serSet_result = new JPanel();
			serSet_result.setLayout(null);
			serSet_result.setBounds(new Rectangle(10, 200, 780, 420));
			serSet_result.setBorder(BorderFactory.createTitledBorder("班车统计列表"));
			serSet_result.add(getSerSet_list(), null);
			serSet_result.add(getSerSet_op(), null);
		}
		return serSet_result;
	}

	/**
	 * This method initializes user_list1
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getSerSet_list() {
		if (serSet_list == null) {
			serSet_list = new JScrollPane();
			serSet_list.setBounds(new Rectangle(20, 30, 750, 292));
			serSet_list.setViewportView(getSerSet());
		}
		return serSet_list;
	}

	/**
	 * This method initializes serSet_op
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getSerSet_op() {
		if (serSet_op == null) {
			serSet_op = new JPanel();
			serSet_op.setLayout(null);
			serSet_op.setBounds(new Rectangle(20, 330, 750, 80));
			serSet_op.add(getPre(), null);
			serSet_op.add(getNext(), null);
			serSet_op.add(getLb_total(), null);
		}
		return serSet_op;
	}



	/**
	 * This method initializes user
	 * 
	 * @return javax.swing.JTable
	 */
	public JTable getSerSet() {
		if (!isSearch) {
			getCb_serilNo().setSelectedIndex(0);
			getCb_line().setSelectedIndex(0);
			getTf_startDate().setText("");
			getTf_endDate().setText("");
			getCb_bus().setSelectedIndex(0);
			startcalendarDlg.setValue(null);
			endcalendarDlg.setValue(null);
			
		}
		isSearch = false;
		if (serSets != null) {
			if (deleteCount == serSets.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}
		
		//设置查询条件
		getCondion();
		
		Page curretPage = RunbusManager.getInstance().getPageByConditions(
				pageNo, Constants.DEFAULT_PAGE_SIZE, searchSerSet,
				startDate, endDate, lineName, "departDate");

		if (curretPage != null && curretPage.getTotalPageCount()>0) {
			this.getPre().setVisible(true);
			this.getNext().setVisible(true);
			serSets = (List<BusserDay>) curretPage.getResult();
			totalPageNo = curretPage.getTotalPageCount();
			totalCount = curretPage.getTotalCount();
			pageSize = curretPage.getPageSize();
			getLb_total().setText(
					"总计" + Long.toString(totalCount) + "条 每页"
							+ Integer.toString(pageSize) + "条 第"
							+ Integer.toString(pageNo) + "页/共"
							+ Long.toString(totalPageNo) + "页");
		} else {
			serSets =  new ArrayList<BusserDay>(); 
			this.getPre().setVisible(false);
			this.getNext().setVisible(false);
			getLb_total().setText("没有找到记录！");
		}
		// 设置列表值
		setData(serSets);

		if (serSet == null) {
			serSet = new JTable(new DefaultTableModel(data, columnName) {
				private static final long serialVersionUID = 1L;

				public void setValueAt(Object value, int row, int col) {
					data[row][col] = value;
				}

				public Object getValueAt(int row, int col) {
					return data[row][col];
				}

				@SuppressWarnings("unchecked")
				public Class getColumnClass(int c) {
					if (c == 10 || c == 9) {
						return ImageIcon.class;
					} else {
						return super.getColumnClass(c);
					}
				}
			});
			serSet.setRowHeight(27);
			serSet.getTableHeader().setFont(new Font("宋体", Font.BOLD, 16));

			// 设置render属性
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
			
			TableColumn column0= serSet.getColumnModel().getColumn(0);
			column0.setCellRenderer(render);

			TableColumn column1 = serSet.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = serSet.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);
			column2.setPreferredWidth(120);

			TableColumn column3 = serSet.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = serSet.getColumnModel().getColumn(4);
			column4.setCellRenderer(render);

			TableColumn column5 = serSet.getColumnModel().getColumn(5);
			column5.setCellRenderer(render);

			TableColumn column6 = serSet.getColumnModel().getColumn(6);
			column6.setCellRenderer(render);

		} else {
			serSet.updateUI();
			serSet.repaint();
		}
		return serSet;
	}
	

	/**
	 * 获取查询条件
	 */
	private void getCondion() {
		searchSerSet.setBusSerNo("");
		searchSerSet.setBusNo("");
		lineName = null;
		
		
		if (getCb_serilNo().getSelectedIndex() != 0) {
			String serilNo = getCb_serilNo().getSelectedItem()
					.toString().trim();
			searchSerSet.setBusSerNo(serilNo);
		}
		
		if(getCb_bus().getSelectedIndex() != 0) {
			String busNo = getCb_bus().getSelectedItem().toString().trim();
			searchSerSet.setBusNo(busNo);
		}
		
		if(getCb_line().getSelectedIndex() != 0){
			lineName = getCb_line().getSelectedItem().toString().trim();
		}
		
		startDate = getTf_startDate().getText().trim();
		endDate = getTf_endDate().getText().trim();
		
	}

	private void setData(List<BusserDay> serSetList) {
		if (serSetList != null) {
			for (int i = 0; i < data.length; i++) {
				data[i][0] = null;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
				data[i][5] = null;
				data[i][6] = null;
			}

			for (int i = 0; i < serSetList.size(); i++) {
				BusserDay mySerSet = (BusserDay) serSetList.get(i);
				data[i][0] = mySerSet.getSerdayId();
				data[i][1] = mySerSet.getBusSerNo();
				// 发车日期
				String oldDepartDate = mySerSet.getDepartDate();
			    String departDate = oldDepartDate.substring(0, 4) + "-"
						+ oldDepartDate.substring(4, 6) + "-"
						+ oldDepartDate.substring(6, oldDepartDate.length());
				// 获取对应的班次信息
				BusSer currBusSer = BusSerManager.getInstance().getBusSer(
						mySerSet.getBusSerNo());
				// 发车时间
				String oldDepartTime = currBusSer.getDepartTime();
				String departTime= oldDepartTime.substring(0, 2) + ":"
						+ oldDepartTime.substring(2, 4) + ":"
						+ oldDepartTime.substring(4, oldDepartTime.length());
				data[i][2] = departDate+" "+departTime;
				data[i][3] = mySerSet.getTicketCount();
				data[i][4] = currBusSer.getPrice();
				data[i][5] = currBusSer.getLineName();
				data[i][6] = mySerSet.getBusNo();
			}
		}
	}

	private JLabel getLb_total() {
		if (lb_total == null) {
			lb_total = new JLabel();
			lb_total.setBounds(new Rectangle(550, 8, 220, 18));
		}
		return lb_total;
	}


	/**
	 * This method initializes pre
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getPre() {
		if (pre == null) {
			pre = new JButton();
			pre.setBounds(new Rectangle(430, 8, 55, 18));
			pre.setText("<<<");
			pre.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			pre.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (pageNo > 1) {
						pageNo--;
						isSearch = true;
						getSerSet();
						getSerSet_result().setVisible(false);
						getSerSet_result().setVisible(true);
					}
				}
			});
		}
		return pre;
	}

	/**
	 * This method initializes next
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getNext() {
		if (next == null) {
			next = new JButton();
			next.setBounds(new Rectangle(490, 8, 55, 18));
			next.setText(">>>");
			next.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			next.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (pageNo < totalPageNo) {
						pageNo++;
						isSearch = true;
						getSerSet();
						getSerSet_result().setVisible(false);
						getSerSet_result().setVisible(true);
					}
				}
			});
		}
		return next;
	}

	/**
	 * 获取图片资源
	 * 
	 * @param url
	 * @return
	 */
	private ImageIcon getIcon(String url) {
		ClassLoader cl = this.getClass().getClassLoader();
		ImageIcon icon = new ImageIcon(cl.getResource(url));
		return icon;
	}


}

