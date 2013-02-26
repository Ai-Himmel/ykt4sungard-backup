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
 * ·�߹�����ҳ��
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

	// ��ѯ���
	private JPanel line_result = null;
	private JScrollPane line_list = null;
	private JPanel line_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// �б����
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][5];
	private Object columnName[] = { "", "·������", "���վ", "�յ�վ", "����" };

	// ��ҳ���
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JCheckBox select_all = null;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;

	// ����
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
		// ��ѯpanel
		this.add(getLine_search(), null);
		// ��ѯ�б�panel
		this.add(getLine_result(), null);
	}

	/**
	 * ��ѯpanel
	 * 
	 * @return
	 */
	public JPanel getLine_search() {
		if (line_search == null) {
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(50, 30, 80, 30));
			lb_startaddr.setText("���վ��");

			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(420, 30, 80, 30));
			lb_endaddr.setText("�յ�վ��");

			lb_line = new JLabel();
			lb_line.setBounds(new Rectangle(50, 80, 80, 30));
			lb_line.setText("·�����ƣ�");

			line_search = new JPanel();
			line_search.setLayout(null);
			line_search.setBounds(new Rectangle(10, 10, 780, 180));
			line_search.setBorder(BorderFactory.createTitledBorder("��ѯ·������"));

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
	 * ��ѯ�б�panel
	 * 
	 * @return javax.swing.JPanel
	 */
	public JPanel getLine_result() {
		if (line_result == null) {
			line_result = new JPanel();
			line_result.setLayout(null);
			line_result.setBounds(new Rectangle(10, 200, 780, 420));
			line_result.setBorder(BorderFactory.createTitledBorder("·���б�"));
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
			bt_search.setText("��ѯ");
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
			bt_reset.setText("����");
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
			bt_add.setText("���·��");
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
			bt_delete.setText("ɾ��·��");
			bt_delete.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_delete.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean select_one = false; // �ж���û��ѡ��ı�־������Ҫѡ��һ��
					for (int i = 0; i < data.length; i++) {
						if (data[i][0] == Boolean.TRUE) {
							select_one = Boolean.TRUE;
						}
					}
					if (select_one == Boolean.FALSE) { // û��ѡ��
						JOptionPane.showMessageDialog(
								indexFrame.getLinePanel(), "����ѡ��һ��", "ɾ��·��",
								JOptionPane.WARNING_MESSAGE);
					} else { // ����ѡ����һ��
						int result = JOptionPane.showConfirmDialog(indexFrame
								.getLinePanel(), "ȷ��ɾ����ѡ����", "ɾ��·��",
								JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // ȷ��ֵΪ0��ȡ��ֵΪ1
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE0��ʾ�������ݱ�ѡ��
									String lineName = data[i][1].toString();
									boolean isUsed = LineManager.getInstance().lineIsUsed(lineName);
									if (isUsed) {
										JOptionPane.showMessageDialog(indexFrame.getLinePanel(),"·��[" + lineName+ "]�ѱ�ʹ�ã�����ɾ��","ɾ��·��",
														JOptionPane.WARNING_MESSAGE);
									} else {
										try {
											Line newLine = LineManager.getInstance().getLine(lineName);
											LineManager.getInstance().removeLine(newLine);
											data[i][0] = Boolean.FALSE;
											deleteCount++;
										} catch (Exception e2) {
											JOptionPane.showMessageDialog(indexFrame.getLinePanel(), "ɾ��·��["
													+ lineName + "]ʧ��!", "ERROE!!!",
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

		// ���ò�ѯ����
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
					"�ܼ�" + Long.toString(totalCount) + "�� ÿҳ"
							+ Integer.toString(pageSize) + "�� ��"
							+ Integer.toString(pageNo) + "ҳ/��"
							+ Long.toString(totalPageNo) + "ҳ");
		} else {
			this.getPre().setVisible(false);
			this.getNext().setVisible(false);
			lines = new ArrayList<Line>();
			getLb_total().setText("û���ҵ���¼��");
		}
		// �����б�ֵ
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
			line.getTableHeader().setFont(new Font("����", Font.BOLD, 16));

			// ���õ�һ������ΪBoolean����
			TableColumn column0 = line.getColumnModel().getColumn(0);
			column0.setCellEditor(line.getDefaultEditor(Boolean.class));
			column0.setCellRenderer(line.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);
			// ����render����
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
			render.setToolTipText("˫��·�����Ʋ鿴��ϸ��Ϣ");

			TableColumn column1 = line.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = line.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);

			TableColumn column3 = line.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = line.getColumnModel().getColumn(4);
			column4.setPreferredWidth(50);
			// column4.setCellRenderer(render);

			// ������˫���鿴��ϸ��Ϣ�¼�
			final JPanel jp = this;
			line.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					if ((e.getClickCount() == 2)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						// �鿴��ϸ��Ϣ
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
									JOptionPane.showMessageDialog(jp, "��ȡ·��["
											+ data[row][1] + "]��Ϣʧ��!", "ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
								}
							}
						}
					}
					// �༭
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
									JOptionPane.showMessageDialog(jp, "��ȡ·��["
											+ data[row][1] + "]��Ϣʧ��!", "ERROE!!!",
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
	 * ��ȡ��ѯ����
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
			select_all.setText("ȫѡ/ȡ��");
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
					// repaint()�ػ�����ͼ��user.updateUI()ˢ��user��
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
	 * ��ȡͼƬ��Դ
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