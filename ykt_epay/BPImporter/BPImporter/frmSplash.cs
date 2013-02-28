using System;
using System.Windows.Forms;

namespace BPImporter
{
    public partial class frmSplash : Form
    {
        public frmSplash()
        {
            InitializeComponent();
        }

        private string _statusInfo = "";
        public string StatusInfo
        {
            set
            {
                _statusInfo = value;
                ChangeStatusText();
            }
            get
            {
                return _statusInfo;
            }
        }

        public void ChangeStatusText()
        {
            try
            {
                if (this.InvokeRequired)
                {
                    this.Invoke(new MethodInvoker(this.ChangeStatusText));
                    return;
                }

                lblStatus.Text = _statusInfo;
            }
            catch (Exception e)
            {
                //	do something here...
            }
        }

    }
}
