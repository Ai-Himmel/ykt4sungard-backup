using System;
using System.Collections.Generic;

using System.Text;
using System.Configuration;
using SunGard.SmartCard.KSLibInteropServices;
using log4net;
using System.Reflection;

namespace iWallet
{
    public static class Global
    {
        //configuraion items
        public static string Drtp_Host = "";
        public static string Drtp_Port = "";
        public static int Drtp_Branch = 0;
        public static int BCC_BaseFunction = 6000;

        public static string Impersonate = "";

        public static ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);


        //drtp numner assinged by BCCCLT
        public static int Drtp_NO = 0;
        public static string App_Key = "";

        static Global()
        {
            Initialize();
        }


        //public static string Drtp_Number

        public static bool BCC_Initialized = false;


        public static void Initialize()
        {
            //initialize global params
            Global.Drtp_Host = ConfigurationManager.AppSettings["drtpHost"];
            Global.Drtp_Port = ConfigurationManager.AppSettings["drtpPort"];
            Global.Drtp_Branch = Convert.ToInt32(ConfigurationManager.AppSettings["drtpBranch"]);
            Global.BCC_BaseFunction = Convert.ToInt32(ConfigurationManager.AppSettings["baseFunction"]);
            Global.Impersonate = ConfigurationManager.AppSettings["impersonate"];


        }

        public static void BCCInit()
        {

            if (!Global.BCC_Initialized)
            {
                Global.BCC_Initialized = BCCHelper.BCCCLTInit(1);
                BCCHelper.XPackInit(1);
                Drtp_NO = BCCHelper.AddDrtpNode(Global.Drtp_Host, int.Parse(Global.Drtp_Port));
                Global.BCC_Initialized = true;
            }

        }

    }
}
