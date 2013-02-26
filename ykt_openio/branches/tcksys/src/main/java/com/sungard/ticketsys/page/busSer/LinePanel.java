/*
 * linePanel.java
 *
 * Created on __DATE__, __TIME__
 */

package com.sungard.ticketsys.page.busSer;

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
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.common.Page;

/**
 * 路线管理主页面
 * 
 * @author Xuan.Zhou
 * 
 */
public class LinePanel extends JPanel {

	private static final long serialVersionUID = 1L;

	private IndexFrame indexFrame = null;

	private JPanel line_search = null;

	private JLabel lb_line = null;
	private JLabel lb_startaddr = null;
	private JLabel lb_endaddr = null;

	private JButton bt_search = null;
	private JButton bt_reset = null;
	private JTextField tf_lineName = null;
	private JTextField tf_startaddr = null;
	private JTextField tf_endaddr = null;

	public JTable line = null;

	// 查询结果
	private JPanel line_result = null;
	private JScrollPane line_list = null;
	private JPanel line_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// 列表相关
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][5];
	private Object columnName[] = { "", "路线名称", "起点站", "终点站", "更新" };

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

	public Line searchLine = new Line();

	private List<Line> lines = null;

	private boolean isSearch = false;

	private int deleteCount = 0;

	private LineAddDlg newLineDlg = null;

	private LineDetailDlg lineDetailDlg = null;

	private LineModifyDlg lineModifyDlg = null;

	protected LinePanel() {
	}

	public LinePanel(IndexFrame indexFrame) {
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
		this.add(getLine_search(), null);
		// 查询列表panel
		this.add(getLine_result(), null);
	}

	/**
	 * 查询panel
	 * 
	 * @return
	 */
	public JPanel getLine_search() {
		if (line_search == null) {
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(50, 30, 80, 30));
			lb_startaddr.setText("起点站：");

			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(420, 30, 80, 30));
			lb_endaddr.setText("终点站：");

			lb_line = new JLabel();
			lb_line.setBounds(new Rectangle(50, 80, 80, 30));
			lb_line.setText("路线名称：");

			line_search = new JPanel();
			line_search.setLayout(null);
			line_search.setBounds(new Rectangle(10, 10, 780, 180));
			line_search.setBorder(BorderFactory.createTitledBorder("查询路线条件"));

			line_search.add(lb_startaddr, null);
			line_search.add(getTf_startaddr(), null);
			line_search.add(lb_endaddr, null);
			line_search.add(getTf_endaddr(), null);

			line_search.add(lb_line, null);
			line_search.add(getTf_lineName(), null);
			line_search.add(getBt_search(), null);
			line_search.add(getBt_reset(), null);
		}
		return line_search;
	}

	/**
	 * 查询列表panel
	 * 
	 * @return javax.swing.JPanel
	 */
	public JPanel getLine_result() {
		if (line_result == null) {
			line_result = new JPanel();
			line_result.setLayout(null);
			line_result.setBounds(new Rectangle(10, 200, 780, 420));
			line_result.setBorder(BorderFactory.createTitledBorder("路线列表"));
			line_result.add(getLine_list(), null);
			line_result.add(getLine_op(), null);
		}
		return line_result;
	}


	/**
	 * This method initializes user_list1
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getLine_list() {
		if (line_list == null) {
			line_list = new JScrollPane();
			line_list.setBounds(new Rectangle(20, 30, 750, 292));
			line_list.setViewportView(getLine());
		}
		return line_list;
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
					getLine();
					getSelect_all().setSelected(false);
					getLine_result().setVisible(false);
					getLine_result().setVisible(true);
				}
			});
		}

		return bt_search;
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
					getLine();
					getSelect_all().setSelected(false);
					getLine_result().setVisible(false);
					getLine_result().setVisible(true);
				}
			});
		}
		return bt_reset;
	}

	/**
	 * This method initializes line_op
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getLine_op() {
		if (line_op == null) {
			line_op = new JPanel();
			line_op.setLayout(null);
			line_op.setBounds(new Rectangle(20, 330, 750, 80));
			line_op.add(getSelect_all(), null);
			line_op.add(getPre(), null);
			line_op.add(getNext(), null);
			line_op.add(getBt_delete(), null);
			line_op.add(getBt_add(), null);
			line_op.add(getLb_total(), null);
		}
		return line_op;
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
			bt_add.setText("添加路线");
			bt_add.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_add.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					newLineDlg = new LineAddDlg(indexFrame,indexFrame.getLinePanel());
					newLineDlg.show(); 
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
			bt_delete.setText("删除路线");
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
						JOptionPane.showMessageDialog(
								indexFrame.getLinePanel(), "至少选择一项", "删除路线",
								JOptionPane.WARNING_MESSAGE);
					} else { // 至少选择了一项
						int result = JOptionPane.showConfirmDialog(indexFrame
								.getLinePanel(), "确定删除所选项吗", "删除路线",
								JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // 确定值为0，取消值为1
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE0表示该行数据被选中
									String lineName = data[i][1].toString();
									boolean isUsed = LineManager.getInstance().lineIsUsed(lineName);
									if (isUsed) {
										JOptionPane.showMessageDialog(indexFrame.getLinePanel(),"路线[" + lineName+ "]已被使用，不可删除","删除路线",
														JOptionPane.WARNING_MESSAGE);
									} else {
										try {
											Line newLine = LineManager.getInstance().getLine(lineName);
											LineManager.getInstance().removeLine(newLine);
											data[i][0] = Boolean.FALSE;
											deleteCount++;
										} catch (Exception e2) {
											JOptionPane.showMessageDialog(indexFrame.getLinePanel(), "删除路线["
													+ lineName + "]失败!", "ERROE!!!",
													JOptionPane.ERROR_MESSAGE);
										}
										
									}
								}
							}
							isSearch = true;
							getLine();
							getSelect_all().setSelected(false);
							getLine_result().setVisible(false);
							getLine_result().setVisible(true);
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
	public JTable getLine() {
		if (!isSearch) {
			this.getTf_lineName().setText("");
			this.getTf_startaddr().setText("");
			this.getTf_endaddr().setText("");
		}

		isSearch = false;
		if (lines != null) {
			if (deleteCount == lines.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}

		// 设置查询条件
		getCondion();

		Page curretPage = LineManager.getInstance().getLinePageByConditions(
				pageNo, Constants.DEFAULT_PAGE_SIZE, searchLine, "id");

		if (curretPage != null && curretPage.getTotalCount() > 0) {
			this.getPre().setVisible(true);
			this.getNext().setVisible(true);
			lines = (List<Line>) curretPage.getResult();
			totalPageNo = curretPage.getTotalPageCount();
			totalCount = curretPage.getTotalCount();
			pageSize = curretPage.getPageSize();
			getLb_total().setText(
					"总计" + Long.toString(totalCount) + "条 每页"
							+ Integer.toString(pageSize) + "条 第"
							+ Integer.toString(pageNo) + "页/共"
							+ Long.toString(totalPageNo) + "页");
		} else {
			this.getPre().setVisible(false);
			this.getNext().setVisible(false);
			lines = new ArrayList<Line>();
			getLb_total().setText("没有找到记录！");
		}
		// 设置列表值
		setData(lines);

		if (line == null) {
			line = new JTable(new DefaultTableModel(data, columnName) {
				private static final long serialVersionUID = 1L;

				public boolean isCellEditable(int row, int clo) {
					if (clo == 0 && row < lines.size()) {
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
					if (c == 4) {
						return ImageIcon.class;
					} else {
						return super.getColumnClass(c);
					}
				}
			});

			line.setRowHeight(27);
			line.getTableHeader().setFont(new Font("宋体", Font.BOLD, 16));

			// 设置第一列类型为Boolean类型
			TableColumn column0 = line.getColumnModel().getColumn(0);
			column0.setCellEditor(line.getDefaultEditor(Boolean.class));
			column0.setCellRenderer(line.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);
			// 设置render属性
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
			render.setToolTipText("双击路线名称查看详细信息");

			TableColumn column1 = line.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = line.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);

			TableColumn column3 = line.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = line.getColumnModel().getColumn(4);
			column4.setPreferredWidth(50);
			// column4.setCellRenderer(render);

			// 添加鼠标双击查看详细信息事件
			final JPanel jp = this;
			line.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					if ((e.getClickCount() == 2)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						// 查看详细信息
						if (line.getSelectedColumn() == 1) {
							int row = line.getSelectedRow();
							if (data[row][1] != null) {
								try {
									String linename = data[row][1].toString();
									Line lineinfo = LineManager.getInstance().getLine(linename);
									lineDetailDlg = new LineDetailDlg(indexFrame,indexFrame.getLinePanel());
									lineDetailDlg.setInfo_line(lineinfo);
									lineDetailDlg.show(); 
									
								} catch (Exception e2) {
									JOptionPane.showMessageDialog(jp, "获取路线["
											+ data[row][1] + "]信息失败!", "ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
								}
							}
						}
					}
					// 编辑
					if ((e.getClickCount() == 1)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						if (line.getSelectedColumn() == 4) {
							int row = line.getSelectedRow();
							if (data[row][1] != null) {
								try {
									String linename = data[row][1].toString();
									Line lineinfo = LineManager.getInstance().getLine(linename);
								    lineModifyDlg = new LineModifyDlg(indexFrame,indexFrame.getLinePanel());
									lineModifyDlg.setInfo_Line(lineinfo);
									lineModifyDlg.show(); 
									
								} catch (Exception e2) {
									JOptionPane.showMessageDialog(jp, "获取路线["
											+ data[row][1] + "]信息失败!", "ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
								}

							}
						}
					}
				}
			});
		} else {
			line.updateUI();
			line.repaint();
		}
		return line;
	}

	/**
	 * 获取查询条件
	 */
	private void getCondion() {
		searchLine.setLineName("");
		searchLine.setStartAddr("");
		searchLine.setEndAddr("");
		if (!"".equals(getTf_lineName().getText().trim())) {
			searchLine.setLineName(getTf_lineName().getText().trim());
		}
		if (!"".equals(getTf_startaddr().getText().trim())) {
			searchLine.setStartAddr(getTf_startaddr().getText().trim());
		}
		if (!"".equals(getTf_endaddr().getText().trim())) {
			searchLine.setEndAddr(getTf_endaddr().getText().trim());
		}
	}

	private void setData(List<Line> lineList) {
		if (lineList != null) {
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
			}
			for (int i = 0; i < lineList.size(); i++) {
				Line myLine = (Line) lineList.get(i);
				data[i][1] = myLine.getLineName();
				data[i][2] = myLine.getStartAddr();
				data[i][3] = myLine.getEndAddr();
				data[i][4] = this
						.getIcon("com/sungard/ticketsys/image/btnEdit.gif");
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
						for (int i = 0; i < lines.size(); i++) {
							data[i][0] = Boolean.TRUE;
						}
					} else {
						for (int i = 0; i < data.length; i++) {
							data[i][0] = Boolean.FALSE;
						}
					}
					// repaint()重画整个图，user.updateUI()刷新user表
					line.repaint();
					getLine_list().setVisible(false);
					getLine_list().setVisible(true);
				}
			});
		}
		return select_all;
	}

	/**
	 * This method initializes tf_lineName
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_lineName() {
		if (tf_lineName == null) {
			tf_lineName = new JTextField();
			tf_lineName.setBounds(new Rectangle(130, 80, 220, 30));
		}
		return tf_lineName;
	}

	/**
	 * This method initializes tf_startaddr
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_startaddr() {
		if (tf_startaddr == null) {
			tf_startaddr = new JTextField();
			tf_startaddr.setBounds(new Rectangle(130, 30, 220, 30));
		}
		return tf_startaddr;
	}

	/**
	 * This method initializes tf_lineName
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_endaddr() {
		if (tf_endaddr == null) {
			tf_endaddr = new JTextField();
			tf_endaddr.setBounds(new Rectangle(500, 30, 220, 30));
		}
		return tf_endaddr;
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
						getLine();
						getSelect_all().setSelected(false);
						getLine_result().setVisible(false);
						getLine_result().setVisible(true);
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
						getLine();
						getSelect_all().setSelected(false);
						getLine_result().setVisible(false);
						getLine_result().setVisible(true);
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