using System.Text;
using System.Threading;
using System.Windows.Forms;
//using System.Diagnostics;
using iWallet.BO;
using SunGard.SmartCard.KSLibInteropServices;
using System.Collections.Generic;
using iWallet.Caching;
using System;

namespace iWallet
{
    public partial class frmMain : Form
    {
        public delegate void QueryResultInvoker<T>(T t);
        public delegate void QueryResultInvoker();


        private Thread worker;

        QueryCriteria criteria = null;
        private List<Customer> customers = new List<Customer>();
        //private SortableBindingList<Customer> data = new SortableBindingList<Customer>();


        public frmDataLoading frmLoading
        {
            get;
            set;
        }

        public frmMain()
        {
            InitializeComponent();
        }

        public frmMain(string drtpHost, string drtpPort)
            : this()
        {
            Global.Logger.Info("iWallet is going to acquire key...");
            Splasher.Status = string.Format("系统签到：[{0}:{1}]", Global.Drtp_Host, Global.Drtp_Port);
            Global.App_Key = SignIn();
            Global.Logger.Info("completion on acquiring key: " + Global.App_Key);

            //if (string.IsNullOrEmpty(Global.App_Key))
            //{
            //    MessageBox.Show("子系统签到失败！", this.Text, MessageBoxButtons.OK);
            //    this.Close();
            //    Splasher.Close();
            //    Application.Exit();
            //}
            Splasher.Status = "[正在从后台获取字典数据...]";
            DataCacher.Instance.InitializeMasterData();
            Splasher.Status = "[初始化客户类型...]";
            InitCombo(DataCacher.Instance[MasterKind.CustomerType], cmbCustomerType, true);
            Splasher.Status = "[初始化收费类型...]";
            InitCombo(DataCacher.Instance[MasterKind.FeeType], cmbFeeType, true);
            Splasher.Status = "[初始化性别类型...]";
            InitCombo(DataCacher.Instance[MasterKind.Sex], cmbSex, true);
            Splasher.Close();
            Global.Logger.Info("system startup successfully!");
        }

        #region "query customer list"

        private void PopuateCriteria()
        {

            if (InvokeRequired)
            {
                Invoke(new Action(CreateQueryCriteria));
            }
            else
            {
                CreateQueryCriteria();
            }
        }

        private void CreateQueryCriteria()
        {
            criteria = new QueryCriteria();
            criteria.CustomerId = txtCustId.Text.Trim();
            criteria.CustomerName = txtCustName.Text.Trim();
            criteria.Category = cmbCustomerType.SelectedValue.ToString();
            criteria.FeeType = cmbFeeType.SelectedValue.ToString();

            criteria.Sex = cmbSex.SelectedValue.ToString();
            criteria.SchoolId = txtSchoolId.Text.Trim();

        }

        private void DoWalletQuery(QueryCriteria c)
        {
            int handle = 0;
            Global.BCCInit();
            //make a new bcc handle
            handle = BCCHelper.NewXpackHandle(@"KSLib\cpack.dat");
            //prepare input params
            BCCHelper.SetIntFieldByName(handle, 0, "lvol1", string.IsNullOrEmpty(c.CustomerId) ? 0 : Convert.ToInt32(c.CustomerId));
            BCCHelper.SetStringFieldByName(handle, 0, "sall_name", c.CustomerName);

            BCCHelper.SetIntFieldByName(handle, 0, "lvol3", string.IsNullOrEmpty(c.Category) ? 0 : Convert.ToInt32(c.Category));
            BCCHelper.SetIntFieldByName(handle, 0, "lvol5", string.IsNullOrEmpty(c.FeeType) ? 0 : Convert.ToInt32(c.FeeType));

            BCCHelper.SetStringFieldByName(handle, 0, "smarket_code2", c.Sex);
            BCCHelper.SetStringFieldByName(handle, 0, "scust_auth2", c.SchoolId);

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
                    Invoke(new QueryResultInvoker(HideLoadingForm));
                    Invoke(new Action(RestoreUI));
                    return;
                }
                BCCHelper.GetRetCode(handle, ref retCode);
                int packageCnt = 0;
                do
                {
                    if (retCode != 0)
                        continue;
                    //show data rows of package into grid view
                    packageCnt++;
                    Global.Logger.Info("do package data show with package#:" + packageCnt);
                    DoPackageDataShow(handle);
                } while (hasMorePack = BCCHelper.HaveNextPack(handle) && BCCHelper.CallNext(handle, 5000, ref errCode, errMsg));
            }//
            else
            {
                Global.Logger.Info("BCCHelper.SetRequestType[841601] failed!");
            }
            //release cpack handle
            if (handle != 0)
            {
                BCCHelper.DeleteXpackHandle(handle);
                Global.Logger.Info("delete xpack handle");
            }
            //show data in grid
            Invoke(new QueryResultInvoker(AddCustomersToGrid));
            //hide loading form
            Invoke(new QueryResultInvoker(HideLoadingForm));

        } //end of DoWalletQuery(QueryCriteria c)

        private void DoPackageDataShow(int handle)
        {

            if (worker.ThreadState == ThreadState.Background)
            {
                List<Customer> packageData = Utility.GetEntities<Customer>(handle);
                customers.AddRange(packageData);
            }
            frmLoading.NotifyIndicator(customers.Count.ToString());
        }

        private void AddCustomerToGrid(Customer c)
        {
            DataGridViewRow r = new DataGridViewRow();
            gvCust.Rows.Add(r);

            DataGridViewCell c1 = new DataGridViewCheckBoxCell();
            c1.Value = false;
            r.Cells[this.colCheck.Name] = c1;

            DataGridViewCell c2 = new DataGridViewTextBoxCell();
            c2.Value = c.CustomerId;
            r.Cells[this.CustomerId.Name] = c2;

            DataGridViewCell c3 = new DataGridViewTextBoxCell();
            c3.Value = c.CustomerName;
            r.Cells[this.CustomerName.Name] = c3;




        }

        private void AddCustomersToGrid()
        {
            gvCust.DataSource = new SortableBindingList<Customer>(customers);
            gvCust.Refresh();
            /*hide cols*/
            //foreach (DataGridViewColumn c in gvCust.Columns)
            //{
            //    if (c.HeaderText == c.Name)
            //        c.Visible = false;
            //}
            //restore UI
            RestoreUI();
        }

        private void btnGet_Click(object sender, System.EventArgs e)
        {
            gvCust.Rows.Clear();
            customers.Clear();
            //disable UI
            btnGet.Enabled = false;
            btnCancel.Enabled = true;
            btnRegister.Enabled = false;

            if (frmLoading == null || !frmLoading.Visible)
                frmLoading = new frmDataLoading(this);
            Global.Logger.Info("populating query criteria...");
            PopuateCriteria();

            worker = new Thread(delegate(object obj)
            {
                DoWalletQuery(criteria);
            });
            worker.IsBackground = true;
            worker.Name = "QueryWorker";
            Global.Logger.Info("query working thread is about to start");
            worker.Start();
        }

        private void gvCust_CellValueNeeded(object sender, DataGridViewCellValueEventArgs e)
        {

            if (gvCust.Columns[e.ColumnIndex].Name == NetAccFlag.Name)
            {
                //e.Value = customers[e.RowIndex].NetAccFlag == "1" ? "已开通" : "未开通";
            }
            else if (gvCust.Columns[e.ColumnIndex].Name == SexName.Name)
            {
                Master m = DataCacher.Instance[MasterKind.Sex].Find(delegate(Master obj)
                {
                    return obj.Code == customers[e.RowIndex].SexName;
                });
                e.Value = m == null ? string.Empty : m.Name;
            }
            else if (gvCust.Columns[e.ColumnIndex].Name == Category.Name)
            {
                Master m = DataCacher.Instance[MasterKind.CustomerType].Find(delegate(Master obj)
                {
                    return obj.Code == customers[e.RowIndex].Category;
                });
                e.Value = m == null ? string.Empty : m.Name;
            }
            else if (gvCust.Columns[e.ColumnIndex].Name == CustomerStatus.Name)
            {
                Master m = DataCacher.Instance[MasterKind.CustomerStatus].Find(delegate(Master obj)
                {
                    return obj.Code == customers[e.RowIndex].StatusName;
                });
                e.Value = m == null ? string.Empty : m.Name;
            }
        }

        #endregion

        private void btnRegister_Click(object sender, EventArgs e)
        {
            btnCancel.Enabled = true;
            bool registerAll = chkAll.Checked;
            //prepare data source
            List<Customer> list = null;
            if (registerAll)
                list = customers;
            else
                list = customers.FindAll(c => c.Checked);
            if (frmLoading == null || !frmLoading.Visible)
                frmLoading = new frmDataLoading(this);
            worker = new Thread(delegate(object obj)
            {
                DoWalletRegister(obj);
            });
            worker.IsBackground = true;
            worker.Name = "RegisterWorker";
            Global.Logger.Info("register wallet working thread is about to start");
            worker.Start(list);

        }

        private void DoWalletRegister(object obj)
        {
            List<Customer> list = obj as List<Customer>;
            if (list != null && list.Count > 0)
            {
                int handle = 0;
                Global.BCCInit();
                //make a new bcc handle
                handle = BCCHelper.NewXpackHandle(@"KSLib\cpack.dat");
                foreach (Customer c in list)
                {
                    DoSingleWalletRegister(c, handle);
                }
                //delete handle
                if (handle > 0)
                    BCCHelper.DeleteXpackHandle(handle);
                //hide form
                Invoke(new QueryResultInvoker(HideLoadingForm));

            }
        }

        private void DoSingleWalletRegister(Customer c, int handle)
        {
            BCCHelper.ResetPackHandle(handle);
            BCCHelper.SetIntFieldByName(handle, 0, "lvol0", c.CustomerId);  //客户号
            //BCCHelper.SetIntFieldByName(handle, 0, "lvol1", 888);  //终端号
            if (BCCHelper.SetRequestType(handle, 846331))
            {
                int errCode = 0;
                int retCode = -1;
                StringBuilder errMsg = new StringBuilder(255);
                bool requestStatus = BCCHelper.CallRequest(handle, Global.Drtp_NO, Global.Drtp_Branch, Global.BCC_BaseFunction, 5000, ref errCode, errMsg);
                if (!requestStatus)
                {
                    Global.Logger.Warn(string.Format("BCCHelper.CallRequest[846331] failed! errorCode ={0} and errMsg= {1}", errCode, errMsg));
                    return;
                }
                BCCHelper.GetRetCode(handle, ref retCode);
                //int ser=0;
                //BCCHelper.GetIntFieldByName(handle, 0, "scust_no", ref ser);
                string ser = BCCHelper.GetStringFieldByName(handle, 0, "scust_no");
                string pass = BCCHelper.GetStringFieldByName(handle, 0, "scust_limit");
                string msg = BCCHelper.GetStringFieldByName(handle, 0, "vsmess");
                if (retCode != 0)
                {
                    //fail to wallet registration
                    frmLoading.NotifyIndicator(string.Format("failed ,customer#{0}:{1}", c.CustomerId, errMsg));
                    Global.Logger.Warn(string.Format(" failed ,Customerid ={0} and errMsg= {1}", c.CustomerId, msg));
                }
                else
                {
                    //succuess to wallet registration
                    Customer target = customers.Find(delegate(Customer o)
                     {
                         return o.CustomerId == c.CustomerId;
                     });
                    //target.NetAccFlag = "1";
                    //target.NetAccFlagDes = "已开通";
                    Global.Logger.Info(string.Format("succ ,Customerid# = {0} and Wallet#= {1} ", c.CustomerId, ser));
                    frmLoading.NotifyIndicator(string.Format("Customer#{0}，ser#：{1} ", c.CustomerId, ser));
                }
            }
            else
            {
                Global.Logger.Info("BCCHelper.SetRequestType[846331] failed!");
            }
            //frmLoading.NotifyIndicator(customers.Count.ToString());
        }

        private void btnCancel_Click(object sender, System.EventArgs e)
        {
            if (worker != null && worker.IsAlive)
            {
                worker.Abort();
                worker.Join();
                Global.Logger.Info("working thread is cancelled by user.");
                gvCust.DataSource = new SortableBindingList<Customer>(customers);
                frmLoading.Close();
                RestoreUI();
            }

        }

        public void HideLoadingForm()
        {
            if (frmLoading != null)
            {
                frmLoading.Close();
                //frmLoading.Visible = false;
                gvCust.RefreshEdit();
                gvCust.Refresh();
            }
        }

        public void RestoreUI()
        {
            btnGet.Enabled = !btnGet.Enabled;
            btnCancel.Enabled = !btnCancel.Enabled;
            btnRegister.Enabled = !btnRegister.Enabled;
        }

        #region "input validation "
        private void txtCustId_KeyPress(object sender, KeyPressEventArgs e)
        {
            ForceDigitalOnly(e);
        }

        private static void ForceDigitalOnly(KeyPressEventArgs e)
        {
            const char Delete = (char)8;
            e.Handled = !Char.IsDigit(e.KeyChar) && e.KeyChar != Delete;
        }

        private void txtSchoolId_KeyPress(object sender, KeyPressEventArgs e)
        {
            ForceDigitalOnly(e);
        }

        #endregion

        #region "Initialization"

        private string SignIn()
        {
            string key = string.Empty;
            int handle = 0;
            Global.BCCInit();
            //make a new bcc handle
            handle = BCCHelper.NewXpackHandle(@"KSLib\cpack.dat");
            //prepare input params
            string myIp = Utility.GetHostIP();
            string myMac = Utility.GetHostMac();
            BCCHelper.SetStringFieldByName(handle, 0, "scust_limit", "192.168.0.127");
            BCCHelper.SetStringFieldByName(handle, 0, "scust_limit2", "00-21-5E-68-40-20");
            BCCHelper.SetStringFieldByName(handle, 0, "scert_no", "sungard kingstar gateway common version");
            if (BCCHelper.SetRequestType(handle, 950001))
            {
                int errCode = 0;
                int retCode = -1;
                StringBuilder errMsg = new StringBuilder(255);
                bool requestStatus = BCCHelper.CallRequest(handle, Global.Drtp_NO, Global.Drtp_Branch, Global.BCC_BaseFunction, 5000, ref errCode, errMsg);
                if (!requestStatus)
                {
                    Splasher.Status = "调用后台功能号失败：[950001]";
                    Global.Logger.Warn("BCCHelper.CallRequest [950001] failed and errorcode =" + errCode + errMsg);
                }
                BCCHelper.GetRetCode(handle, ref retCode);
                if (retCode == 0)
                {
                    StringBuilder val = new StringBuilder(256);
                    BCCHelper.GetStringFieldByName(handle, 0, "scust_limit", val, 256);
                    key = val.ToString();
                    Splasher.Status = string.Format("签到成功：[{0}]", val);
                }
                else
                {
                    Splasher.Status = "子系统签到失败！";
                    Global.Logger.Warn("BCCHelper.CallRequest [950001] failed and return code = : " + retCode);
                }
            }
            else
            {
                Splasher.Status = "设置后台功能号失败：[950001]";
                Global.Logger.Warn("BCCHelper.SetRequestType [950001] failed!");
            }
            if (handle != 0)
                BCCHelper.DeleteXpackHandle(handle);
            return key;
        } //end of SignIn()

        public void InitCombo(List<Master> list, ComboBox cmb, bool insertEmpty)
        {
            if (insertEmpty)
                list.Insert(0, new Master
                {
                    Code = "",
                    Name = "-"
                });
            cmb.DisplayMember = "Name";
            cmb.ValueMember = "Code";
            cmb.DataSource = list;

        }


        #endregion

        private void btnChkAll_Click(object sender, EventArgs e)
        {
            CheckGrid(true);
        }

        private void btnUnchkAll_Click(object sender, EventArgs e)
        {
            CheckGrid(false);
        }

        private void CheckGrid(bool status)
        {
            for (int i = 0; i < gvCust.Rows.Count; i++)
            {
                DataGridViewCheckBoxCell cell = gvCust.Rows[i].Cells[colCheck.Name] as DataGridViewCheckBoxCell;
                if (cell != null)
                    cell.Value = status;
            }
        }

    } //end of frmMain
}
