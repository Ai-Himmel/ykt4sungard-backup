package com.sungard.ticketsys.page.busSer;

import java.awt.Cursor;
import java.awt.Font;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
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

import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.page.CalendarDlg;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.SerSetManager;
import com.sungard.ticketsys.common.MyFormat;
import com.sungard.ticketsys.common.Page;

/**
 * 车次管理页面
 * @author Xuan.Zhou
 *
 */
public class SerSetPanel  extends JPanel {

	private static final long serialVersionUID = 1L;

	private IndexFrame indexFrame = null;

	private JPanel serSet_search = null;

	private JLabel lb_serdayId = null;
	private JLabel lb_serilNo = null;
	private JLabel lb_startDate = null;
	private JLabel lb_endDate = null;

	private JButton bt_search = null;
	private JButton bt_reset = null;
	private JComboBox cb_serilNo = null;
	private JTextField tf_serdayId = null;
	
	private JTextField tf_startDate = null;
	private JButton bt_startDate = null;
	private CalendarDlg StartcalendarDlg = new CalendarDlg(indexFrame);
	private JTextField tf_endDate = null;
	private JButton bt_endDate = null;
	private CalendarDlg endcalendarDlg = new CalendarDlg(indexFrame);
	

	public JTable serSet = null;

	// 查询结果
	private JPanel serSet_result = null;
	private JScrollPane serSet_list = null;
	private JPanel serSet_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// 列表相关
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][8];
	private Object columnName[] = { "","车次号","班次号", "发车日期","剩余票数","售票数","预留票数","状态" };

	// 分页相关
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JCheckBox select_all = null;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;

	// 操作
	private JButton bt_add = null;

	public BusserDay searchSerSet = new BusserDay();
	public String startDate = null;
	public String endDate = null;

	private List<BusserDay> serSets = null;

	private boolean isSearch = false;

	private int deleteCount = 0;

	private SerSetAdd newSerSet = null;

//	private SerSetDetail serSet_detail = null;
	// 单个车辆的详细信息
//	private SerSet serSetinfo = null;

//	private SerSetModify serSet_modify = null;

	protected SerSetPanel() {
	}

	public SerSetPanel(IndexFrame indexFrame) {
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
			lb_serdayId = new JLabel();
			lb_serdayId.setBounds(new Rectangle(50, 30, 80, 30));
			lb_serdayId.setText("车次号：");
			lb_serilNo = new JLabel();
			lb_serilNo.setBounds(new Rectangle(420, 30, 80, 30));
			lb_serilNo.setText("班次号：");
			
			lb_startDate = new JLabel();
			lb_startDate.setBounds(new Rectangle(50, 80, 80, 30));
			lb_startDate.setText("起始日期：");
			lb_endDate = new JLabel();
			lb_endDate.setBounds(new Rectangle(420, 80, 80, 30));
			lb_endDate.setText("结束日期：");
			
			serSet_search = new JPanel();
			serSet_search.setLayout(null);
			serSet_search.setBounds(new Rectangle(10, 10, 780, 180));
			serSet_search.setBorder(BorderFactory.createTitledBorder("查询车次条件"));
			serSet_search.add(lb_serdayId, null);
			serSet_search.add(getTf_serdayId(), null);
			serSet_search.add(lb_serilNo, null);
			serSet_search.add(getCb_serilNo(), null);
			
			serSet_search.add(lb_startDate,null);
			serSet_search.add(getTf_startDate(), null);
			serSet_search.add(getBt_startDate(), null);
			serSet_search.add(lb_endDate,null);
			serSet_search.add(getTf_endDate(), null);
			serSet_search.add(getBt_endDate(), null);
			
			serSet_search.add(getBt_search(), null);
			serSet_search.add(getBt_reset(), null);
		}
		return serSet_search;
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
					getTf_serdayId().setText("");
					getCb_serilNo().setSelectedIndex(0);
					getTf_startDate().setText("");
					getTf_endDate().setText("");
					StartcalendarDlg.setValue(null);
					endcalendarDlg.setValue(null);
					
					getSerSet();
					getSerSet_result().setVisible(false);
					getSerSet_result().setVisible(true);
				}
			});
		}
		return bt_reset;
	}

	private JButton getBt_endDate() {
		if (bt_endDate == null) {
			bt_endDate = new JButton();
			bt_endDate.setBounds(new Rectangle(720, 84, 20, 20));
			bt_endDate.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_endDate.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_endDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if(endcalendarDlg == null){
						endcalendarDlg = new CalendarDlg(indexFrame);
					}
					Point p =  bt_endDate.getLocationOnScreen(); 
					p.y = p.y + bt_endDate.getHeight(); 
					p.x = p.x-endcalendarDlg.getWidth();
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


	private JButton getBt_startDate() {
		if (bt_startDate == null) {
			bt_startDate = new JButton();
			bt_startDate.setBounds(new Rectangle(350, 84, 20, 20));
			bt_startDate.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_startDate.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_startDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if(StartcalendarDlg == null){
						StartcalendarDlg = new CalendarDlg(indexFrame);
					}
					Point p =  bt_startDate.getLocationOnScreen(); 
					p.y = p.y + bt_startDate.getHeight(); 
					StartcalendarDlg.setLocation(p);
					StartcalendarDlg.show();
					if(StartcalendarDlg.getValue()!=null){
						SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
					    String date = sdf.format(StartcalendarDlg.getValue());
					    getTf_startDate().setText(date);
					}
				}
			});
		}

		return bt_startDate;
	}


	private JTextField getTf_endDate() {
		if (tf_endDate == null) {
			tf_endDate = new JTextField();
			tf_endDate.setBounds(new Rectangle(500, 80, 220, 30));
		}
		return tf_endDate;
	}

	private JTextField getTf_startDate() {
		if (tf_startDate == null) {
			tf_startDate = new JTextField();
			tf_startDate.setBounds(new Rectangle(130, 80, 220, 30));
		}
		return tf_startDate;
	}

	/**
	 * This method initializes tf_serilNo
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_serdayId() {
		if (tf_serdayId == null) {
			tf_serdayId = new JTextField();
			tf_serdayId.setBounds(new Rectangle(130, 30, 220, 30));;
		}
		return tf_serdayId;
	}

	/**
	 * This method initializes cb_linename
	 * 
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getCb_serilNo() {
		if (cb_serilNo == null) {
			cb_serilNo = new JComboBox();
			cb_serilNo.setBounds(new Rectangle(500, 30, 220, 30));
			cb_serilNo.addItem("-------- 请选择 --------");
			List<BusSer> busSers = BusSerManager.getInstance().getAllBusSer();
			for (int i = 0; i < busSers.size(); i++) {
				BusSer myBusSer = (BusSer) busSers.get(i);
				cb_serilNo.addItem(myBusSer.getSerilNo());
			}
			cb_serilNo.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_serilNo.removeAllItems();
					cb_serilNo.addItem("-------- 请选择 --------");
					List<BusSer> busSers = BusSerManager.getInstance().getAllBusSer();
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
			bt_search.setText("查询");
			bt_search.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_search.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					pageNo = 1;
					isSearch = true;
				
					getSerSet();
					getSelect_all().setSelected(false);
					getSerSet_result().setVisible(false);
					getSerSet_result().setVisible(true);
				}
			});
		}

		return bt_search;
	}
	
	/**
	 * 获取查询条件
	 */
	private void getCondion() {
		searchSerSet.setSerdayId("");
		searchSerSet.setBusSerNo("");
		if (!"".equals(getTf_serdayId().getText().trim())) {
			searchSerSet.setSerdayId(getTf_serdayId().getText().trim());
		}

		if (getCb_serilNo().getSelectedIndex() != 0) {
			String serilNo = getCb_serilNo().getSelectedItem()
					.toString().trim();
			searchSerSet.setBusSerNo(serilNo);
		}
		startDate = getTf_startDate().getText().trim();
		endDate = getTf_endDate().getText().trim();
		
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
			serSet_result.setBorder(BorderFactory.createTitledBorder("车次信息列表"));
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
			serSet_op.add(getSelect_all(), null);
			serSet_op.add(getPre(), null);
			serSet_op.add(getNext(), null);
			serSet_op.add(getBt_delete(), null);
			serSet_op.add(getBt_add(), null);
			serSet_op.add(getLb_total(), null);
		}
		return serSet_op;
	}

	/**
	 * This method initializes lb_add
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_add() {
		if (bt_add == null) {
			bt_add = new JButton();
			bt_add.setBounds(new Rectangle(13, 39, 87, 27));
			bt_add.setText("班次排版");
			bt_add.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_add.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					newSerSet = new SerSetAdd(indexFrame,indexFrame.getSerSetPanel());
					newSerSet.show(); 
				}
			});
		}
		return bt_add;
	}

	/**
	 * This method initializes bt_delete
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_delete() {
		if (bt_delete == null) {
			bt_delete = new JButton();
			bt_delete.setBounds(new Rectangle(121, 39, 87, 27));
			bt_delete.setText("删除车次");
			bt_delete.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_delete.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean select_one = false; // 判断有没有选择的标志，至少要选择一项
					for (int i = 0; i < data.length; i++) {
						if (data[i][0] == Boolean.TRUE) {
							select_one = Boolean.TRUE;
						}
					}
					if (select_one == Boolean.FALSE) { // 没有选择
						JOptionPane.showMessageDialog(indexFrame
								.getSerSetPanel(), "至少选择一项", "删除车次信息",
								JOptionPane.WARNING_MESSAGE);
					} else { // 至少选择了一项
						int result = JOptionPane.showConfirmDialog(indexFrame
								.getSerSetPanel(), "确定删除所选项吗", "删除车次信息",
								JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // 确定值为0，取消值为1
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE0表示该行数据被选中
									String serdayId = data[i][1].toString();
										try {
											BusserDay newBusserDay = SerSetManager.getInstance().getBusserDay(serdayId);
											SerSetManager.getInstance().removeSerSet(newBusserDay);
											data[i][0] = Boolean.FALSE;
											deleteCount++;
										} catch (Exception e1) {
											JOptionPane.showMessageDialog(indexFrame.getSerSetPanel(),e1.getMessage(),
													"ERROE!!!",
													JOptionPane.ERROR_MESSAGE);
											e1.printStackTrace();
										}
								}
							}
							isSearch = true;
							getSerSet();
							getSelect_all().setSelected(false);
							getSerSet_result().setVisible(false);
							getSerSet_result().setVisible(true);
						}
					}
				}
			});

		}
		return bt_delete;
	}

	/**
	 * This method initializes user
	 * 
	 * @return javax.swing.JTable
	 */
	public JTable getSerSet() {
		if (!isSearch) {
			getTf_serdayId().setText("");
			getCb_serilNo().setSelectedIndex(0);
			getTf_startDate().setText("");
			getTf_endDate().setText("");
			
		}
		isSearch = false;
		if (serSets != null) {
			if (deleteCount == serSets.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}
		
		// 设置查询条件
		getCondion();
		
		Page curretPage = SerSetManager.getInstance().getPageByConditions(pageNo, Constants.DEFAULT_PAGE_SIZE,
				searchSerSet,startDate,endDate,"departDate");
		
		if (curretPage != null && curretPage.getTotalPageCount()>0){
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

				public boolean isCellEditable(int row, int clo) {
					if (clo == 0 && row < serSets.size()) {
						return true;
					} else {
						return false;
					}
				}

				public void setValueAt(Object value, int row, int col) {
					data[row][col] = value;
				}

				public Object getValueAt(int row, int col) {
					return data[row][col];
				}

				@SuppressWarnings("unchecked")
				public Class getColumnClass(int c) {
					return super.getColumnClass(c);
				}
			});
			serSet.setRowHeight(27);
			serSet.getTableHeader().setFont(new Font("宋体", Font.BOLD, 16));
			
			// 设置第一列类型为Boolean类型
			TableColumn column0 = serSet.getColumnModel().getColumn(0);
			column0.setCellEditor(serSet.getDefaultEditor(Boolean.class));
			column0.setCellRenderer(serSet.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);
			// 设置render属性
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
//			render.setToolTipText("双击查看详细信息");

			TableColumn column1 = serSet.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = serSet.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);

			TableColumn column3 = serSet.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = serSet.getColumnModel().getColumn(4);
			column4.setCellRenderer(render);

			TableColumn column5 = serSet.getColumnModel().getColumn(5);
			column5.setCellRenderer(render);
			
			TableColumn column6 = serSet.getColumnModel().getColumn(6);
			column6.setCellRenderer(render);
			
			TableColumn column7 = serSet.getColumnModel().getColumn(7);
			column7.setCellRenderer(render);

			// 添加鼠标双击查看详细信息事件
//			serSet.addMouseListener(new MouseAdapter() {
//				public void mouseClicked(MouseEvent e) {
//					if ((e.getClickCount() == 2)
//							&& (e.getButton() == MouseEvent.BUTTON1)) {
//						// 查看详细信息
//						if (serSet.getSelectedColumn() == 1) {
//							IndexFrame.target = 3;
//							int row = serSet.getSelectedRow();
//							String serSetname = data[row][1].toString();
//							serSetinfo = SerSetManager.getInstance().getSerSet(
//									serSetname);
//							serSet_detail.setInfo_serSet(serSetinfo);
//							getSerSet_detail().setVisible(true);
//							getSerSet_search().setVisible(false);
//							getSerSet_result().setVisible(false);
//						}
//					}
//					// 编辑
//					if ((e.getClickCount() == 1)
//							&& (e.getButton() == MouseEvent.BUTTON1)) {
//						if (serSet.getSelectedColumn() == 5) {
//							IndexFrame.target = 3;
//							int row = serSet.getSelectedRow();
//							String serSetname = data[row][1].toString();
//							serSetinfo = SerSetManager.getInstance().getSerSet(
//									serSetname);
//							serSet_modify.setInfo_SerSet(serSetinfo);
//							getSerSet_modify().setVisible(true);
//							getSerSet_search().setVisible(false);
//							getSerSet_result().setVisible(false);
//						}
//					}
//				}
//			});
		} else {
			serSet.updateUI();
			serSet.repaint();
		}
		return serSet;
	}

	private void setData(List<BusserDay> serSetList) {
		if (serSetList != null) {
			
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
				data[i][5] = null;
				data[i][6] = null;
				data[i][7] = null;
			}
			for (int i = 0; i < serSetList.size(); i++) {
				BusserDay mySerSet = (BusserDay) serSetList.get(i);
				data[i][1] = mySerSet.getSerdayId();
				data[i][2] = mySerSet.getBusSerNo();
				data[i][3] = MyFormat.dateSdf(mySerSet.getDepartDate());
				data[i][4] = mySerSet.getRemainCount();
				data[i][5] = mySerSet.getTicketCount();
				data[i][6] = mySerSet.getReserveCount();
				data[i][7] = mySerSet.getStatus();
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
	 * This method initializes select_all
	 * 
	 * @return javax.swing.JCheckBox
	 */
	public JCheckBox getSelect_all() {
		if (select_all == null) {
			select_all = new JCheckBox();
			select_all.setBounds(new Rectangle(9, 4, 96, 21));
			select_all.setText("全选/取消");
			select_all.addItemListener(new ItemListener() {
				public void itemStateChanged(ItemEvent e) {
					if (select_all.isSelected()) {
						for (int i = 0; i < serSets.size(); i++) {
							data[i][0] = Boolean.TRUE;
						}
					} else {
						for (int i = 0; i < data.length; i++) {
							data[i][0] = Boolean.FALSE;
						}
					}
					// repaint()重画整个图，user.updateUI()刷新user表
					serSet.repaint();
					getSerSet_list().setVisible(false);
					getSerSet_list().setVisible(true);
				}
			});
		}
		return select_all;
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
						getSelect_all().setSelected(false);
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
						getSelect_all().setSelected(false);
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

