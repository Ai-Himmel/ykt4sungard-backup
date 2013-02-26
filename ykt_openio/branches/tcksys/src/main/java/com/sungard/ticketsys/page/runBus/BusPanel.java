package com.sungard.ticketsys.page.runBus;

import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
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

import org.apache.log4j.Logger;

import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.model.Bus;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.service.BusManager;
import com.sungard.ticketsys.common.Page;

public class BusPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BusPanel.class);

	private IndexFrame indexFrame = null;
	
	private JPanel bus_search = null;
	private JButton bt_reset = null;

	private JLabel lb_busno = null;
	private JLabel lb_busstate = null;

	private JButton bt_search = null;
	private JTextField tf_busNo = null;
	private JComboBox cb_busstate = null;
	
	public JTable bus = null;
	
	//查询结果
	private JPanel bus_result = null;
	private JScrollPane bus_list = null;
	private JPanel bus_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;
	
	
	//列表相关
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][6];
	private Object columnName[] = {"", "车牌号", "车型","座位数", "使用状态","编辑"};
	
	//分页相关
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JCheckBox select_all = null;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;
	
	//操作
	private JButton bt_add = null;
	
	
	public Bus searchBus = new Bus();
	
	private List<Bus> buss = null;

	private boolean isSearch = false;

	private int deleteCount = 0;
	
	private BusAddDlg newBusDlg = null;
	
	private BusDetailDlg busDetailDlg = null;
	//单个车辆的详细信息
	private Bus businfo=null;

	private BusModifyDlg busModifyDlg = null;

	protected BusPanel() {
	}

	public BusPanel(IndexFrame indexFrame) {
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
		//查询panel
		this.add(getBus_search(), null);
		//查询列表panel
		this.add(getBus_result(), null);
	}
	

	/**
	 * 查询panel
	 * @return
	 */
	public JPanel getBus_search() {
		if (bus_search == null) {
			lb_busno = new JLabel();
			lb_busno.setBounds(new Rectangle(50, 30, 80, 30));
			lb_busno.setText("车牌号：");
			
			lb_busstate = new JLabel();
			lb_busstate.setBounds(new Rectangle(420, 30, 80, 30));
			lb_busstate.setText("使用状态：");	
			
			bus_search = new JPanel();
			bus_search.setLayout(null);
			bus_search.setBounds(new Rectangle(10, 10, 780, 180));
			bus_search.setBorder(BorderFactory.createTitledBorder("查询车辆条件"));
			bus_search.add(lb_busno, null);
			bus_search.add(getTf_busno(), null);
			bus_search.add(lb_busstate, null);
			bus_search.add(getCb_busstate(), null);
			bus_search.add(getBt_search(), null);
			bus_search.add(getBt_reset(), null);
		}
		return bus_search;
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
					isSearch = false;
					
					getBus();
					getSelect_all().setSelected(false);
					getBus_result().setVisible(false);
					getBus_result().setVisible(true);
				}
			});
		}
		return bt_reset;
	}
	
	/**
	 * This method initializes tf_busName
	 *
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_busno() {
		if (tf_busNo == null) {
			tf_busNo = new JTextField();
			tf_busNo.setBounds(new Rectangle(130, 30, 220, 30));
		}
		return tf_busNo;
	}
	
	/**
	 * This method initializes cb_category
	 *
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getCb_busstate() {
		if (cb_busstate == null) {
			cb_busstate = new JComboBox();
			cb_busstate.setBounds(new Rectangle(500, 30, 220, 30));
			cb_busstate.addItem("-------- 请选择 --------");
			cb_busstate.addItem(Bus.STATE_UN_USER);
			cb_busstate.addItem(Bus.STATE_RUN);
			cb_busstate.addItem(Bus.STATE_REPAIRS);
		}
		return cb_busstate;
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
					
					getBus();
					getSelect_all().setSelected(false);
					getBus_result().setVisible(false);
					getBus_result().setVisible(true);
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
	public JPanel getBus_result() {
		if (bus_result == null) {
			bus_result = new JPanel();
			bus_result.setLayout(null);
			bus_result.setBounds(new Rectangle(10, 200, 780, 420));
			bus_result.setBorder(BorderFactory.createTitledBorder("车辆信息列表"));
			bus_result.add(getBus_list(), null);
			bus_result.add(getBus_op(), null);
		}
		return bus_result;
	}
	

	/**
	 * This method initializes user_list1
	 *
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getBus_list() {
		if (bus_list == null) {
			bus_list = new JScrollPane();
			bus_list.setBounds(new Rectangle(20, 30, 750, 292));
			bus_list.setViewportView(getBus());
		}
		return bus_list;
	}

	
	/**
	 * This method initializes bus_op
	 *
	 * @return javax.swing.JPanel
	 */
	private JPanel getBus_op() {
		if (bus_op == null) {
			bus_op = new JPanel();
			bus_op.setLayout(null);
			bus_op.setBounds(new Rectangle(20, 330, 750, 80));
			bus_op.add(getSelect_all(), null);
			bus_op.add(getPre(), null);
			bus_op.add(getNext(), null);
			bus_op.add(getBt_delete(), null);
			bus_op.add(getBt_add(), null);
			bus_op.add(getLb_total(), null);
		}
		return bus_op;
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
			bt_add.setText("添加车辆");
			bt_add.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_add.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					newBusDlg = new BusAddDlg(indexFrame, indexFrame.getBusPanel());
					newBusDlg.show();
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
			bt_delete.setText("删除车辆");
			bt_delete.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_delete.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean select_one = false; //判断有没有选择的标志，至少要选择一项
					for (int i = 0; i < data.length; i++) {
						if (data[i][0] == Boolean.TRUE) {
							select_one = Boolean.TRUE;
						}
					}
					if(select_one == Boolean.FALSE) { //没有选择
						JOptionPane.showMessageDialog(indexFrame.getBusPanel(), "至少选择一项", "删除车辆信息", JOptionPane.WARNING_MESSAGE);
					}
					else { //至少选择了一项
						int result = JOptionPane.showConfirmDialog(indexFrame.getBusPanel(),
								"确定删除所选项吗", "删除车辆信息", JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // 确定值为0，取消值为1
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE0表示该行数据被选中
									String busName = data[i][1].toString();
									boolean isUsed =  BusManager.getInstance().busIsUsed(busName);
									if (isUsed) {
										JOptionPane.showMessageDialog(indexFrame.getBusPanel(),"车辆[" + busName+ "]已被使用，不可删除","删除车辆",
														JOptionPane.WARNING_MESSAGE);
									}else{
										try {
											Bus newBus = BusManager.getInstance().getBus(busName);
											BusManager.getInstance().removeBus(newBus);
											data[i][0] = Boolean.FALSE;
											deleteCount++;
										} catch (Exception e2) {
											JOptionPane.showMessageDialog(indexFrame.getBusPanel(), "删除车辆["
													+ busName + "]失败!", "ERROE!!!",
													JOptionPane.ERROR_MESSAGE);
										}
									}
									
								}
							}
							isSearch = true;
							getBus();
							getSelect_all().setSelected(false);
							getBus_result().setVisible(false);
							getBus_result().setVisible(true);
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
	public JTable getBus() {
		if (!isSearch) {
			this.getTf_busno().setText("");
			this.getCb_busstate().setSelectedIndex(0);
		}
		isSearch = false;
		if (buss != null) {
			if (deleteCount == buss.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}
		
		// 设置查询条件
		getCondion();
		
		buss = BusManager.getInstance().getBusByConditions(pageNo,
				Constants.DEFAULT_PAGE_SIZE, searchBus, null);
		
		Page curretPage = BusManager.getInstance().getBusByConditions(pageNo,
				Constants.DEFAULT_PAGE_SIZE, searchBus);

		if (curretPage != null && curretPage.getTotalCount() > 0){
			this.getPre().setVisible(true);
			this.getNext().setVisible(true);
			buss = (List<Bus>)curretPage.getResult();
			totalPageNo = curretPage.getTotalPageCount();
			totalCount = curretPage.getTotalCount();
			pageSize = curretPage.getPageSize();
			getLb_total().setText(
					"总计"+Long.toString(totalCount)+"条 每页"+Integer.toString(pageSize)+"条 第" + Integer.toString(pageNo) + "页/共"
							+ Long.toString(totalPageNo) + "页");
		}
		else {
			buss =  new ArrayList<Bus>();
			this.getPre().setVisible(false);
			this.getNext().setVisible(false);
			getLb_total().setText("没有找到记录！");
		}
		
		//设置列表值
		setData(buss);
		if (bus == null) {
		  bus = new JTable(new DefaultTableModel(data, columnName) {
			private static final long serialVersionUID = 1L;

			public boolean isCellEditable(int row, int clo) {
				if (clo == 0 && row < buss.size()) {
					return true;
				}
				else {
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
				if (c == 5) {
					return ImageIcon.class;
				}
				else {
					return super.getColumnClass(c);
				}
			}
		});

		bus.setRowHeight(27);
		bus.getTableHeader().setFont(new Font("宋体", Font.BOLD, 16));
		
		// 设置第一列类型为Boolean类型
		TableColumn column0 = bus.getColumnModel().getColumn(0);
		column0.setCellEditor(bus.getDefaultEditor(Boolean.class));
		column0.setCellRenderer(bus.getDefaultRenderer(Boolean.class));
		column0.setPreferredWidth(20);
		// 设置render属性
		render = new MyTableCellRenderer();
		render.setHorizontalAlignment(JLabel.CENTER);
		render.setToolTipText("双击车牌号查看详细信息");

		TableColumn column1 = bus.getColumnModel().getColumn(1);
		column1.setCellRenderer(render);

		TableColumn column2 = bus.getColumnModel().getColumn(2);
		column2.setCellRenderer(render);
		
		TableColumn column3 = bus.getColumnModel().getColumn(3);
		column3.setCellRenderer(render);
		
		TableColumn column4 = bus.getColumnModel().getColumn(4);
		column4.setCellRenderer(render);

		TableColumn column5 = bus.getColumnModel().getColumn(5);
		column5.setPreferredWidth(50);
		// column4.setCellRenderer(render);

		// 添加鼠标双击查看详细信息事件
		bus.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent e) {
				if ((e.getClickCount() == 2)
						&& (e.getButton() == MouseEvent.BUTTON1)) {
					// 查看详细信息
					if (bus.getSelectedColumn() == 1) {
						int row = bus.getSelectedRow();
						if(data[row][1]!=null){
							try {
								String busname = data[row][1].toString();
								businfo = BusManager.getInstance().getBus(busname);
								busDetailDlg = new BusDetailDlg(indexFrame, indexFrame.getBusPanel());
								busDetailDlg.setInfo_bus(businfo);
								busDetailDlg.show();
							} catch (Exception e2) {
								logger.error( "获取车辆["+ data[row][1] + "]信息失败!"+e2.getMessage());
								JOptionPane.showMessageDialog(indexFrame.getBusSerPanel(), "获取车辆["
										+ data[row][1] + "]信息失败!", "ERROE!!!",
										JOptionPane.ERROR_MESSAGE);
							}
						}
						
					}
				}
				// 编辑
				if ((e.getClickCount() == 1)
						&& (e.getButton() == MouseEvent.BUTTON1)) {
					if (bus.getSelectedColumn() == 5) {
						int row = bus.getSelectedRow();
						if(data[row][1]!=null){
							try {
								String busname = data[row][1].toString();
								businfo = BusManager.getInstance().getBus(busname);
								busModifyDlg = new BusModifyDlg(indexFrame, indexFrame.getBusPanel());
								busModifyDlg.setInfo_Bus(businfo);
								busModifyDlg.show();
							} catch (Exception e2) {
								logger.error( "获取车辆["+ data[row][1] + "]信息失败!"+e2.getMessage());
								JOptionPane.showMessageDialog(indexFrame.getBusSerPanel(), "获取车辆["
										+ data[row][1] + "]信息失败!", "ERROE!!!",
										JOptionPane.ERROR_MESSAGE);
							}
						}
						
					}
				}
			}
		 });
	    }
		else {
			bus.updateUI();
			bus.repaint();
		}
		return bus;
	}
	
	/**
	 * 获取查询条件
	 */
	private void getCondion() {
		searchBus.setBusNo("");
		searchBus.setBusState("");
		if(!"".equals(getTf_busno().getText().trim())) {
			searchBus.setBusNo(getTf_busno().getText().trim());
		}

		if (getCb_busstate().getSelectedIndex() != 0) {
			String busState = getCb_busstate().getSelectedItem().toString().trim();
			searchBus.setBusState(busState);
		}
	}
	
	private void setData(List<Bus> busList) {
		if (busList != null) {
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
				data[i][5] = null;
			}
			for (int i = 0; i < busList.size(); i++) {
				Bus myBus = (Bus) busList.get(i);
				data[i][1] = myBus.getBusNo();
				data[i][2] = myBus.getBusType();
				data[i][3] = myBus.getSeatCount();
				data[i][4] = myBus.getBusState();
				data[i][5] = this.getIcon("com/sungard/ticketsys/image/btnEdit.gif");
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
						for (int i = 0; i < buss.size(); i++) {
							data[i][0] = Boolean.TRUE;
						}
					}
					else {
						for (int i = 0; i < data.length; i++) {
							data[i][0] = Boolean.FALSE;
						}
					}
					//repaint()重画整个图，user.updateUI()刷新user表
					bus.repaint();
					getBus_list().setVisible(false);
					getBus_list().setVisible(true);
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
					if(pageNo>1) {
						pageNo--;
						isSearch = true;
						getBus();
						getSelect_all().setSelected(false);
						getBus_result().setVisible(false);
						getBus_result().setVisible(true);
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
						getBus();
						getSelect_all().setSelected(false);
						getBus_result().setVisible(false);
						getBus_result().setVisible(true);
					}
				}
			});
		}
		return next;
	}

	/**
	 * 获取图片资源
	 * @param url
	 * @return
	 */
	private ImageIcon getIcon(String url) {
        ClassLoader cl = this.getClass().getClassLoader();
        ImageIcon icon = new ImageIcon(cl.getResource(url));
        return icon;
	}

}