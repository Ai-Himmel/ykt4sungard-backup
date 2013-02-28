using System;
using System.Configuration;
using System.Windows.Forms;
using log4net;
using System.Reflection;
using BPImporter;

namespace iWallet
{
    static class Startup
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {


            //show splash form
            Splasher.Show();
            // args = new string[] { Global.App_Key };
            DoStartup(args);
        }



        static void DoStartup(string[] args)
        {
            //start main application
            // if (args.Length != 0 && !string.IsNullOrEmpty(args[0]))

            Global.Logger.Info("application starts....");

            Application.Run(new frmMain(Global.Drtp_Host, Global.Drtp_Port));
        }


    }
}
