namespace HelloMobileSDK
{
  partial class Form1
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;
    private System.Windows.Forms.MainMenu mainMenu1;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.components = new System.ComponentModel.Container();
      //ESRI.ArcGIS.Mobile.USCustomaryUnitLabels usCustomaryUnitLabels1 = new ESRI.ArcGIS.Mobile.USCustomaryUnitLabels();
      this.mainMenu1 = new System.Windows.Forms.MainMenu();
      this.menuItemMapActions = new System.Windows.Forms.MenuItem();
      this.menuItemZoomIn = new System.Windows.Forms.MenuItem();
      this.menuItemZoomOut = new System.Windows.Forms.MenuItem();
      this.menuItemPan = new System.Windows.Forms.MenuItem();
      this.menuItemExit = new System.Windows.Forms.MenuItem();
      //this.map1 = new ESRI.ArcGIS.Mobile.Map();
      //this.mobileService1 = new ESRI.ArcGIS.Mobile.MobileServices.MobileService(this.components);
      //this.zoomInMapAction1 = new ESRI.ArcGIS.Mobile.MapActions.ZoomInMapAction(this.components);
      //this.zoomOutMapAction1 = new ESRI.ArcGIS.Mobile.MapActions.ZoomOutMapAction(this.components);
      //this.panMapAction1 = new ESRI.ArcGIS.Mobile.MapActions.PanMapAction(this.components);
      //this.scaleBar1 = new ESRI.ArcGIS.Mobile.ScaleBar(this.components);
      this.SuspendLayout();
      // 
      // mainMenu1
      // 
      this.mainMenu1.MenuItems.Add(this.menuItemMapActions);
      this.mainMenu1.MenuItems.Add(this.menuItemExit);
      // 
      // menuItemMapActions
      // 
      this.menuItemMapActions.MenuItems.Add(this.menuItemZoomIn);
      this.menuItemMapActions.MenuItems.Add(this.menuItemZoomOut);
      this.menuItemMapActions.MenuItems.Add(this.menuItemPan);
      this.menuItemMapActions.Text = "Map Actions";
      // 
      // menuItemZoomIn
      // 
      this.menuItemZoomIn.Text = "Zoom In";
      this.menuItemZoomIn.Click += new System.EventHandler(this.menuItemZoomIn_Click);
      // 
      // menuItemZoomOut
      // 
      this.menuItemZoomOut.Text = "Zoom Out";
      this.menuItemZoomOut.Click += new System.EventHandler(this.menuItemZoomOut_Click);
      // 
      // menuItemPan
      // 
      this.menuItemPan.Text = "Pan";
      this.menuItemPan.Click += new System.EventHandler(this.menuItemPan_Click);
      // 
      // menuItemExit
      // 
      this.menuItemExit.Text = "Exit";
      this.menuItemExit.Click += new System.EventHandler(this.menuItemExit_Click);
      // 
      // map1
      // 
      //this.map1.DataSources.Add(this.mobileService1);
      //this.map1.Location = new System.Drawing.Point(3, 0);
      //this.map1.MapActions.Add(this.zoomInMapAction1);
      //this.map1.MapActions.Add(this.zoomOutMapAction1);
      //this.map1.MapActions.Add(this.panMapAction1);
      //this.map1.Name = "map1";
      //this.map1.Size = new System.Drawing.Size(237, 265);
      //this.map1.SnappingEnvironment.Active = true;
      //this.map1.SnappingEnvironment.ShowSegmentLength = false;
      //this.map1.SnappingEnvironment.ShowTips = false;
      //this.map1.SnappingEnvironment.ShowToleranceRadius = true;
      //this.map1.SnappingEnvironment.SignificantDigits = 2;
      //this.map1.SnappingEnvironment.Tolerance = 10;
      //this.map1.TabIndex = 0;
      //this.map1.Text = "map1";
      //this.map1.ExtentChanged += new System.EventHandler(this.map1_ExtentChanged);
      //// 
      //// scaleBar1
      //// 
      //this.scaleBar1.BarColor = System.Drawing.SystemColors.ActiveCaption;
      //this.scaleBar1.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular);
      //this.scaleBar1.HaloColor = System.Drawing.SystemColors.Control;
      //this.scaleBar1.Map = this.map1;
      //this.scaleBar1.MobileService = this.mobileService1;
      //this.scaleBar1.OutlineBarColor = System.Drawing.SystemColors.ActiveBorder;
      //this.scaleBar1.ProgressColor = System.Drawing.SystemColors.Info;
      //this.scaleBar1.TextColor = System.Drawing.SystemColors.ControlText;
      //usCustomaryUnitLabels1.Feet = "ft";
      //usCustomaryUnitLabels1.Inches = "in";
      //usCustomaryUnitLabels1.Miles = "mi";
      //usCustomaryUnitLabels1.Yards = "yd";
      //this.scaleBar1.UnitLabels = usCustomaryUnitLabels1;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
      this.AutoScroll = true;
      this.ClientSize = new System.Drawing.Size(240, 268);
      //this.Controls.Add(this.map1);
      this.Menu = this.mainMenu1;
      this.Name = "Form1";
      this.Text = "Hello MobileSDK";
      this.Load += new System.EventHandler(this.Form1_Load);
      this.ResumeLayout(false);

    }

    #endregion

    //private ESRI.ArcGIS.Mobile.Map map1;
    //private ESRI.ArcGIS.Mobile.MobileServices.MobileService mobileService1;
    private System.Windows.Forms.MenuItem menuItemMapActions;
    private System.Windows.Forms.MenuItem menuItemZoomIn;
    private System.Windows.Forms.MenuItem menuItemZoomOut;
    private System.Windows.Forms.MenuItem menuItemPan;
    private System.Windows.Forms.MenuItem menuItemExit;
    //private ESRI.ArcGIS.Mobile.MapActions.ZoomInMapAction zoomInMapAction1;
    //private ESRI.ArcGIS.Mobile.MapActions.ZoomOutMapAction zoomOutMapAction1;
    //private ESRI.ArcGIS.Mobile.MapActions.PanMapAction panMapAction1;
    //private ESRI.ArcGIS.Mobile.ScaleBar scaleBar1;
  }
}

