using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BPImporter
{
    public class EntryCompletedEventArgs:EventArgs
    {
        public string EntryKey;
        public bool CompletedFlag;
        public string Message;
       
        public EntryCompletedEventArgs(string entryKey,bool completedFlag,string message)
        {
            EntryKey = entryKey;
            CompletedFlag = completedFlag;
            Message = message;
        }
    }


    



}
