using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using SunGard.SmartCard.KSLibInteropServices;
using System.IO;

namespace BPImporter
{
    public partial class frmMain : Form
    {


        public frmMain()
        {
            InitializeComponent();
        }

        public frmMain(string drtpHost, string drtpPort)
            : this()
        {
            //do initialization
            Splasher.Close();
            this.Activate();
            AppDomain.CurrentDomain.UnhandledException += delegate(object sender, UnhandledExceptionEventArgs args)
            {
                Exception e = (Exception)args.ExceptionObject;
                MessageBox.Show(e.Message + e.StackTrace, this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                Global.Logger.Error(e.Message, e);

            };
        }

        private Thread worker;

        private ExcelReader extReader;

        private string selectedSheet = string.Empty;

        private DataTable dtRelation;

        private void btnChoose_Click(object sender, EventArgs e)
        {
            if (dlgOpenFile == null)
                dlgOpenFile = new OpenFileDialog();
            dlgOpenFile.ValidateNames = true;

            dlgOpenFile.Filter = "Excel files | *.xls";
            dlgOpenFile.InitialDirectory = Application.ExecutablePath;
            if (dlgOpenFile.ShowDialog() == DialogResult.OK && dlgOpenFile.FileName != null && dlgOpenFile.CheckFileExists == true)
            {
                this.txtFile.Text = dlgOpenFile.FileName;
                //retrieve sheet names
                this.cboSheetNames.Items.Clear();
                RetrieveSheetNames(this.txtFile.Text, this.cboSheetNames);
                selectedSheet = cboSheetNames.Text;
            }
        }

        private void btnImport_Click(object sender, EventArgs e)
        {
            this.btnImport.Enabled = false;
            this.btnCancel.Enabled = !this.btnImport.Enabled;
            lblStatus.Text = "Excel数据加载中...";
            string file = txtFile.Text.Trim();
            worker = new Thread(delegate()
            {
                //populating student-no-name-walletid mapping relations
                PrepareRelations();
                //do import
                DoPaymentImp(file, dtRelation);
            });
            worker.IsBackground = true;
            worker.Name = "ImpWorker";
            Global.Logger.Info("worker thread start...");
            worker.Start();
        }

        private void DoPaymentImp(string file, DataTable relations)
        {
            if (string.IsNullOrEmpty(selectedSheet))
            {
                Invoke(new Action(delegate()
                {
                    MessageBox.Show("请选择sheet!", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    worker.Abort();
                    worker.Join();
                    this.btnImport.Enabled = true;
                    this.btnCancel.Enabled = !this.btnImport.Enabled;
                    return;
                }));
            }
            if (relations.Rows.Count == 0)
            {
                Invoke(new Action(delegate()
                {
                    MessageBox.Show("学生基本信息有误", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    worker.Abort();
                    worker.Join();
                    this.btnImport.Enabled = true;
                    this.btnCancel.Enabled = !this.btnImport.Enabled;
                    return;
                }));
            }
            extReader.SheetName = selectedSheet;
            extReader.KeepConnectionOpen = true;
            DataTable dt = extReader.GetTable(selectedSheet);
            extReader.Close();

            Global.Logger.Info("load excel data finished with rows=" + dt.Rows.Count);
            // remove empty rows
            DataRow[] rows = dt.Select(" XH IS NULL ");
            foreach (DataRow r in rows)
            {
                r.Delete();
            }
            dt.AcceptChanges();
            Global.Logger.Info("after remove null entries, rows=" + dt.Rows.Count);

            int cnt = dt.Rows.Count;
            if (cnt <= 0)
            {
                Invoke(new Action(delegate()
                {
                    MessageBox.Show("没有可以导入的原始数据", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }));
                return;
            }
            //show initial UI & analysis data 
            Invoke(new Action(delegate()
            {
                this.pBar.Value = 0;
                this.pBar.Maximum = dt.Rows.Count;
                this.lblStatus.Text = "分析数据，可进一步处理的条数为：" + cnt.ToString();
                rBox.Clear();
            }));

            DataTransfer transfer = new DataTransfer(dt, dtRelation);
            transfer.EntryCompleted += delegate(object sender, EntryCompletedEventArgs e)
            {
                string msg = string.Format("{0}: {1}", e.EntryKey, e.Message);
                Invoke(new Action(delegate()
                {
                    this.pBar.Value = this.pBar.Value < cnt ? this.pBar.Value + 1 : cnt;
                    lblStatus.Text = msg;
                    if (!e.CompletedFlag)
                        AppendTextWithGivenColor(rBox, Color.Red, msg + System.Environment.NewLine);

                }));
            };
            transfer.AllEntryCompleted += delegate(object sender, AllEntryCompletedEventArgs e)
            {
                Invoke(new Action(delegate()
                {
                    this.pBar.Value = this.pBar.Maximum;
                    this.btnCancel.Enabled = false;
                    this.btnImport.Enabled = !this.btnCancel.Enabled;
                    Global.Logger.Info(e.Summary);
                    //save error name list
                    string errorFile = Path.Combine(Application.StartupPath,Path.GetFileNameWithoutExtension(this.txtFile.Text)+DateTime.Now.ToString("yyyyMMddhhmmss") + ".err");
                    File.WriteAllText(errorFile,e.Summary);
                    FrmSummary frm = new FrmSummary(e.Summary);
                    frm.ShowDialog();

                }));
            };
            Global.Logger.Info("DoTransfer starts...");
            transfer.DoTransfer();
        }

        #region "Excel helpers"
        private void RetrieveSheetNames(string file, ComboBox ctl)
        {
            //if (extReader == null)
            extReader = new ExcelReader(file, true, true);
            string[] sheets = extReader.GetExcelSheetNames();
            if (sheets != null)
            {
                ctl.Items.AddRange(sheets);
                if (ctl.Items.Count > 0)
                    ctl.SelectedIndex = ctl.Items.Count - 1;
            }
        }
        #endregion

        private void btnCancel_Click(object sender, EventArgs e)
        {
            if (worker != null && worker.IsAlive)
            {
                worker.Abort();
                worker.Join();
                Global.Logger.Info("working thread is cancelled by user.");
            }
            this.btnImport.Enabled = true;
            this.btnCancel.Enabled = !this.btnImport.Enabled;
        }

        private void PrepareRelations()
        {
            if (dtRelation == null)
            {
                dtRelation = new DataTable("relations");
                dtRelation.Columns.Add("StaffId", typeof(string));
                dtRelation.Columns.Add("Name", typeof(string));
                dtRelation.Columns.Add("WalletId", typeof(string));
                dtRelation.PrimaryKey = new DataColumn[] { dtRelation.Columns[0] };
            }
            dtRelation.Rows.Clear();

            int handle = 0;
            Global.BCCInit();
            //make a new bcc handle
            handle = BCCHelper.NewXpackHandle(@"KSLib\cpack.dat");
            if (BCCHelper.SetRequestType(handle, 841601))
            {
                int errCode = 0;
                int retCode = -1;
                bool hasMorePack = false;
                StringBuilder errMsg = new StringBuilder(255);
                bool requestStatus = BCCHelper.CallRequest(handle, Global.Drtp_NO, Global.Drtp_Branch, Global.BCC_BaseFunction, 5000, ref errCode, errMsg);
                if (!requestStatus)
                {
                    Global.Logger.Warn(string.Format("BCCHelper.CallRequest[841601] failed! errorCode ={0} and errMsg= {1}", errCode, errMsg));
                    return;
                }
                BCCHelper.GetRetCode(handle, ref retCode);
                //int packageCnt = 0;
                do
                {
                    if (retCode != 0)
                        continue;
                    //show data rows of package into grid view
                    int cnt = 0;
                    BCCHelper.GetRecordCount(handle, ref cnt);
                    for (int rowIndex = 0; rowIndex < cnt; rowIndex++)
                    {
                        DataRow dr = dtRelation.NewRow();
                        dr["StaffId"] = BCCHelper.GetStringFieldByName(handle, rowIndex, "scust_auth2");
                        dr["Name"] = BCCHelper.GetStringFieldByName(handle, rowIndex, "sname");
                        dr["WalletId"] = BCCHelper.GetStringFieldByName(handle, rowIndex, "sname2");
                        dtRelation.Rows.Add(dr);
                    }
                } while (hasMorePack = BCCHelper.HaveNextPack(handle) && BCCHelper.CallNext(handle, 5000, ref errCode, errMsg));

            }
            else
            {
                Global.Logger.Info("BCCHelper.SetRequestType[841601] failed!");
            }
            //release cpack handle
            if (handle != 0)
            {
                BCCHelper.DeleteXpackHandle(handle);
                Global.Logger.Info("delete xpack handle for request type= 841601");
            }

        }

        private void AppendTextWithGivenColor(RichTextBox box, Color color, string text)
        {
            int start = box.TextLength;
            box.AppendText(text);
            int end = box.TextLength;
            box.Select(start, end - start);
            {
                box.SelectionColor = color;
                // could set box.SelectionBackColor, box.SelectionFont too.
            }
            box.SelectionLength = 0; // clear
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            this.Activate();



        }

    }
}
