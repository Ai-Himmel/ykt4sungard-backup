using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using SunGard.SmartCard.KSLibInteropServices;

namespace BPImporter
{

    public delegate void EntryCompletedHandler (object sender,EntryCompletedEventArgs e);

    public delegate void AllEntryCompletedHandler(object sender,AllEntryCompletedEventArgs e);

    public class DataTransfer
    {
        private DataTable dataSource;

        private DataTable dataRelations;

        double importedAmount = 0.0d;
        int importedCnt = 0;
        List<string> errors = null;

        public event EntryCompletedHandler EntryCompleted;

        public event AllEntryCompletedHandler AllEntryCompleted;
       
        public DataTransfer(DataTable data,DataTable dataRelations)
        {
            this.dataSource = data;
            this.dataRelations = dataRelations;
        }

        public void DoTransfer()
        {
            int handle = 0;
            Global.BCCInit();
            //make a new bcc handle
            handle = BCCHelper.NewXpackHandle(@"KSLib\cpack.dat");
            importedAmount = 0.0d;
            importedCnt = 0;
            errors = new List<string>();
            DateTime start = DateTime.Now;
          
            foreach (DataRow dr in dataSource.Rows)
            {
                BCCHelper.ResetPackHandle(handle);
                DoSingleEntryTrans(dr, handle);
            }
            AllEntryCompletedEventArgs e = new AllEntryCompletedEventArgs(dataSource.Rows.Count, "All Completed!");
            StringBuilder summary = new StringBuilder();
            summary.Append(System.Environment.NewLine+"结果汇总：" + System.Environment.NewLine);
            summary.Append("\t原始记录数：" + dataSource.Rows.Count + System.Environment.NewLine);
            summary.Append("\t导入开始时间：" + start.ToString() + System.Environment.NewLine);
            summary.Append("\t导入结束时间：" + DateTime.Now.ToString() + System.Environment.NewLine);
            summary.AppendFormat("\t成功处理：{0}条，总金额：{1} {2}", importedCnt, importedAmount,System.Environment.NewLine);
            summary.Append("\t未能导入的名单如下：" + System.Environment.NewLine);
            summary.AppendFormat("{0}",FormatListToString(errors));
            e.Errors = errors;
            e.Summary = summary.ToString();
            OnAllEntryCompleted(e);
        }

        private void DoSingleEntryTrans(DataRow dr, int handle)
        {
            string staffId=GetFieldFromRow(dr,"XH");
            string name = GetFieldFromRow(dr, "XM");
            string walletId= "";//GetFieldFromRow(dr, "WalletId");
            //商户编号
            BCCHelper.SetIntFieldByName(handle, 0, "lvol0", Convert.ToInt32( GetFieldFromRow(dr, "ShopId")));
            DataRow tmp = dataRelations.Rows.Find(staffId);
            if (tmp != null)
            {
                walletId = Convert.ToString(tmp["WalletId"]);
            }
            //电子账号
            BCCHelper.SetStringFieldByName(handle, 0, "scust_no", walletId);
            //定单编号
            BCCHelper.SetStringFieldByName(handle, 0, "sbankname", "000000");
            //支付总金额
            double tmpAmount=Convert.ToDouble(GetFieldFromRow(dr, "Mount"));
            BCCHelper.SetDoubleFieldByName(handle, 0, "damt0", tmpAmount);
            //订单日期
            BCCHelper.SetStringFieldByName(handle, 0,"sdate0",DateTime.Now.Date.ToString("yyMMdd"));
            //订单时间
            BCCHelper.SetStringFieldByName(handle, 0,"stime0", DateTime.Now.ToString("hhmmss"));
            //货币代码
            BCCHelper.SetStringFieldByName(handle, 0,"sstock_code","CNY");
            //操作标志
            BCCHelper.SetIntFieldByName(handle, 0,"lvol1",1);
            //交易备注	snote
            BCCHelper.SetStringFieldByName(handle, 0,"snote", GetFieldFromRow(dr, "Type"));
            string entryMsg = "";
            bool entryFlag = true;
            if (BCCHelper.SetRequestType(handle, 846340))
            {
                int errCode = 0;
                int retCode = -1;
                StringBuilder errMsg = new StringBuilder(255);
                bool requestStatus = BCCHelper.CallRequest(handle, Global.Drtp_NO, Global.Drtp_Branch, Global.BCC_BaseFunction, 1000, ref errCode, errMsg);
                if (!requestStatus)
                {
                    entryFlag = false;
                    entryMsg = string.Format("CallRequest[846340] failed! errorCode ={0} and errMsg= {1}.学号={2},姓名={3}", errCode, errMsg,staffId,name);
                    Global.Logger.Warn(entryMsg);
                    errors.Add(string.Format("{0}\t{1}",staffId,name));
                }
                else
                {
                    BCCHelper.GetRetCode(handle, ref retCode);
                    if (retCode != 0)  //failture
                    {
                        entryFlag = false;
                        entryMsg = string.Format("CallRequest[846340] failed and return code ={0}.学号={1},姓名={2}",retCode,staffId,name);
                        Global.Logger.Error(entryMsg);
                        errors.Add(string.Format("{0}\t{1}", staffId, name));
                    }
                    else         //succ
                    {
                        importedCnt++;
                        importedAmount += tmpAmount;
                        string serial = BCCHelper.GetStringFieldByName(handle, 0, "sphone3");
                        entryMsg = string.Format("CallRequest[846340] with succ  and  ser#{0}.学号={1},姓名={2}", serial, staffId, name);
                        Global.Logger.Info(entryMsg);
                    }
                }
            }
            else
            {
                entryMsg = string.Format("SetRequestType[846340] failed.学号={0},姓名={1} ",staffId,name);
                entryFlag = false;
                Global.Logger.Error(entryMsg);
                errors.Add(string.Format("{0}\t{1}", staffId, name));
            }
            //raise event 
            OnEntryCompleted(new EntryCompletedEventArgs(string.Format("{0}[{1}]",name,walletId),entryFlag,entryMsg));
        }

        private string GetFieldFromRow(DataRow dr, string field)
        {
            string retVal = string.Empty;
            if (dr[field] != DBNull.Value)
                retVal = Convert.ToString(dr[field]);
            return retVal;
        }

        protected virtual void OnEntryCompleted(EntryCompletedEventArgs e)
        {
            if (EntryCompleted != null)
                EntryCompleted(this, e);
        }

        protected virtual void OnAllEntryCompleted(AllEntryCompletedEventArgs e)
        {
            if (AllEntryCompleted != null)
                AllEntryCompleted(this, e);
        }


        private string FormatListToString(List<string> list)
        {

            StringBuilder sb = new StringBuilder();
            foreach (string item in list)
            {
                sb.AppendFormat("{0}{1}", item, System.Environment.NewLine);
            }
            return sb.ToString();
        }



    }
}
