using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Controls;
using saXps2Pdf.COM.saXps2PdfLib;

namespace saXps2Pdf
{
    public partial class XpsViewer_Form : Form
    {
        string m_XpsFileName = null;
        DocumentViewer m_Viewer = new DocumentViewer();
        IsaXps2PdfConvert m_ConvertEngine = saXps2PdfConvert.Create();

        public XpsViewer_Form()
        {
            InitializeComponent();

            m_Viewer.Visibility = System.Windows.Visibility.Visible;
            elementHost1.Child = m_Viewer;

            UpdateControls();
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            string bsName = AskOpenFileName(m_XpsFileName, "xps");
            if (!String.IsNullOrEmpty(bsName))
            {
                try
                {
                    System.Windows.Xps.Packaging.XpsDocument doc = new System.Windows.Xps.Packaging.XpsDocument(bsName, System.IO.FileAccess.Read);
                    m_Viewer.Document = doc.GetFixedDocumentSequence(); //viewing it!
                    m_XpsFileName = bsName;
                    UpdateControls();
                }
                catch (Exception ex)
                {
                    textBoxMessage.Text = ex.Message;
                }
            }
        }

        private void buttonPrint_Click(object sender, EventArgs e)
        {
            m_Viewer.Print();
        }

        private void buttonPDF_Click(object sender, EventArgs e)
        {
            string bsOutFileName = AskSaveFileName(System.IO.Path.GetFileNameWithoutExtension(m_XpsFileName) + ".pdf", "pdf");
            if (String.IsNullOrEmpty(bsOutFileName)) return;

            try
            {
                if (m_ConvertEngine.Convert(m_XpsFileName, bsOutFileName, true))
                {
                    MessageBox.Show("Das Dokument wurde konvertiert.");
                }
            }
            catch (Exception)
            {
            }
            textBoxMessage.Text = m_ConvertEngine.ErrorMessage;
        }

        private void UpdateControls()
        {
            // Test, ob die COM-Komponente fuer das Ausfuehren von ghostxps vorhanden ist
            if (m_ConvertEngine == null)
            {
                textBoxMessage.Text = "COM-Objekt nicht instanziert.";
                return;
            }
            textBoxMessage.Text = m_ConvertEngine.Version;

            if (!String.IsNullOrEmpty(m_XpsFileName))
            {
                textBoxMessage.Text = m_XpsFileName;
                buttonPrint.Enabled = true;
                buttonPDF.Enabled = true;
            }
        }

        string AskOpenFileName(string bsFileName, string bsExtension)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = bsExtension + "-Dateien (*." + bsExtension + ")|*." + bsExtension + "|alle Dateien (*.*)|*.*";
            ofd.FileName = bsFileName;
            ofd.CheckFileExists = true;
            ofd.DereferenceLinks = true;
            ofd.Multiselect = false;
            ofd.Title = "Datei öffnen...";
            return ofd.ShowDialog() == DialogResult.OK ? ofd.FileName : "";
        }

        string AskSaveFileName(string bsFileName, string bsExtension)
        {
            SaveFileDialog ofd = new SaveFileDialog();
            ofd.Filter = bsExtension + "-Dateien (*." + bsExtension + ")|*." + bsExtension + "|alle Dateien (*.*)|*.*";
            ofd.FileName = bsFileName;
            ofd.OverwritePrompt = true;
            ofd.Title = "Datei speichern...";
            return ofd.ShowDialog() == DialogResult.OK ? ofd.FileName : "";
        }
    }
}



/*
//assuming this is the file name of some XPS document:
string fileName; //assign appropriate path name to it, from file dialog, for example

System.Windows.Controls.DocumentViewer viewer; //should be initialized and inserted in UI

//...

System.Windows.Xps.Packaging.XpsDocument doc =
    new System.Windows.Xps.Packaging.XpsDocument(fileName, System.IO.FileAccess.Read);
viewer.Document = doc.GetFixedDocumentSequence(); //viewing it!

*/

//DocumentViewer viewer = new DocumentViewer();
/*
viewer = new XpsDocumentViewer(this);
viewer.Visibility = System.Windows.Visibility.Visible;

System.Windows.Forms.Integration.ElementHost host = new System.Windows.Forms.Integration.ElementHost();
host.Dock = System.Windows.Forms.DockStyle.Fill;
host.Child = viewer;
host.ParentChanged += new EventHandler(host_ParentChanged);
*/
