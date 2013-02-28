using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BPImporter
{
    public class AllEntryCompletedEventArgs : EventArgs
    {

        public int Total
        {
            get;
            set;
        }

        public string Message
        {
            get;
            set;
        }

        public List<string> Errors
        {
            get;
            set;
        }


        /*
         eg:
         FileName:
         RawDataCount:
         Import Start:
         Import Finished:
         Import Procesed:%d 1000.33 
         Errors:
         * 
         */
        public string Summary
        {
            get;
            set;
        }

        public AllEntryCompletedEventArgs(int total,string msg)
        {
            Total = total;
            Message = msg;
            Errors = new List<string>();
        }

    }
}
