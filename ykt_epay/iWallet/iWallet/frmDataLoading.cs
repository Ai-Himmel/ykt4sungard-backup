using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace iWallet
{
    public partial class frmDataLoading : Form
    {
        //target form reference
        private Form mainForm;

        // flag to indicate if the form has been closed
        private bool IsClosed = false;


        public frmDataLoading()
        {
            InitializeComponent();
        }

        public frmDataLoading(Form targetForm):this()
        {
            mainForm = targetForm;
            //attach main form events
            mainForm.Activated += new EventHandler(mainForm_Activated);
            mainForm.Deactivate += new EventHandler(mainForm_Deactivate);
            mainForm.Move += new EventHandler(mainForm_Move);

            //set appearance
            ShowInTaskbar = false;
            TopMost = true;
            StartPosition = FormStartPosition.Manual;
            Visible = false;

            AdjustLocation();

        }

        void mainForm_Move(object sender, EventArgs e)
        {
            AdjustLocation();
        }

        void mainForm_Deactivate(object sender, EventArgs e)
        {
            //if (!this.IsClosed)
            //{
            //    this.Visible = false;
            //}
        }

        void mainForm_Activated(object sender, EventArgs e)
        {
            if (!this.IsClosed)
            {
                this.Visible = true;
            }
        }

        #region "internal methods"
        private void AdjustLocation()
        {
            // Adjust the position relative to main form
            int dx = (mainForm.Width - this.Width) / 2;
            int dy = (mainForm.Height - this.Height) / 2;
            Point loc = new Point(mainForm.Location.X, mainForm.Location.Y);
            loc.Offset(dx, dy);
            this.Location = loc;
            if (!IsClosed)
            {
                this.Visible = true;
            }
        }
        #endregion

        private void frmDataLoading_FormClosed(object sender, FormClosedEventArgs e)
        {
            IsClosed = true;
        }

        public void NotifyIndicator(string s)
        {
            if (InvokeRequired)
            {
                Invoke(new Action<string>(UpdateCount),s);
                return;
            }
            else
            {
                UpdateCount(s);
            }
        }

        void UpdateCount(string s)
        {
            lblCnt.Text = s;
            lblCnt.Update();
        }

    }
}
